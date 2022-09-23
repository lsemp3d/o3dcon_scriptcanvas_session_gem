/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#include <GameComponents/EnemyController.h>
#include <AzFramework/Physics/PhysicsSystem.h>

namespace Game
{
	EnemyController::EnemyController(Nodes::ScriptCanvasGameplay* gameplayNode, AzFramework::EntitySpawnTicket& spawnTicket)
		: m_gameplayNode(gameplayNode)
		, m_spawnTicket(spawnTicket)
	{}

	void EnemyController::Configure(float radius, float speed, AZ::EntityId enemyEntityId, AZ::EntityId playerEntityId)
	{
		m_playerEntityId = playerEntityId;
		m_radius = radius;
		m_speed = speed;

		float angle = AZ::Constants::TwoPi * ((rand() % 100) / 100.f);

		// Caclulate a random destination vector that sits on an intersect path with the player
		float y = cosf(angle) * m_radius;
		float z = sinf(angle) * m_radius;

		// Calculate a direction vector from the spawn point to an intersection point on the circle
		AZ::Vector3 targetVector = AZ::Vector3(0.f, y, z);
		m_direction = targetVector - m_transform->GetWorldTranslation();
		m_direction.Normalize();

		// Install a collision handler that despawns the enemy on collision
		m_onCollisionBeginHandler = AzPhysics::SimulatedBodyEvents::OnTriggerEnter::Handler(
			[this, enemyEntityId]([[maybe_unused]] AzPhysics::SimulatedBodyHandle bodyHandle,
				const AzPhysics::TriggerEvent& event)
			{
				if (event.m_triggerBody->GetEntityId() == enemyEntityId && event.m_otherBody->GetEntityId() == m_playerEntityId)
				{
					m_gameplayNode->GetScriptMediator().Despawn(m_spawnTicket);
				}
			});

		if (auto* physicsSystem = AZ::Interface<AzPhysics::SystemInterface>::Get())
		{
			auto [sceneHandle, bodyHandle] = physicsSystem->FindAttachedBodyHandleFromEntityId(enemyEntityId);
			if (sceneHandle != AzPhysics::InvalidSceneHandle)
			{
				AzPhysics::SimulatedBodyEvents::RegisterOnTriggerEnterHandler(sceneHandle, bodyHandle, m_onCollisionBeginHandler);
			}
		}
	}
	
	void EnemyController::Activate()
	{
		AZ::TickBus::Handler::BusConnect();

		m_transform = AZ::EntityUtils::FindFirstDerivedComponent<AZ::TransformInterface>(GetEntity());
	}
	
	void EnemyController::Deactivate()
	{
		AZ::TickBus::Handler::BusDisconnect();
	}
	
	void EnemyController::OnTick(float deltaTime, AZ::ScriptTimePoint)
	{
		// Continously move the enemy in the calculated direction
		if (m_transform)
		{
			AZ::Vector3 target = m_transform->GetWorldTranslation() + (m_direction * (deltaTime * m_speed));
			m_transform->SetWorldTranslation(target);
		}

		m_lifetime -= deltaTime;
		if (m_lifetime <= 0.f)
		{
			m_gameplayNode->GetScriptMediator().Despawn(m_spawnTicket);
		}
	}	
}
