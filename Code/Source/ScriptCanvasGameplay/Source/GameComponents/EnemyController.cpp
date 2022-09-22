/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#pragma optimize("", off)

#include <GameComponents/EnemyController.h>
#include <AzFramework/Physics/PhysicsSystem.h>

namespace Game
{
	EnemyController::EnemyController(Nodes::ScriptCanvasGameplay* gameplayNode, AzFramework::EntitySpawnTicket& spawnTicket)
		: m_gameplayNode(gameplayNode)
		, m_spawnTicket(spawnTicket)
	{}

	void EnemyController::Configure(float radius, float speed, AZ::EntityId enemyEntityId)
	{
		m_radius = radius;
		m_speed = speed;


		float angle = AZ::Constants::TwoPi * ((rand() % 100) / 100.f);

		// Need to compute a random destination vector that sits on an intersect path with the player
		float x = cosf(angle) * m_radius;
		float y = sinf(angle) * m_radius;

		AZ::Vector3 targetVector = AZ::Vector3(0.f, x, y);
		m_direction = targetVector - m_transform->GetWorldTranslation();



		m_onCollisionBeginHandler = AzPhysics::SimulatedBodyEvents::OnTriggerEnter::Handler(
			[this]([[maybe_unused]] AzPhysics::SimulatedBodyHandle bodyHandle,
				const AzPhysics::TriggerEvent& /*event*/)
			{
				m_gameplayNode->GetScriptMediator().Despawn(m_spawnTicket);
				// Collision took place! I can send out even through node
				//m_gameplayNode->EnemyContact(event);

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
		if (m_transform)
		{
			AZ::Vector3 target = m_transform->GetWorldTranslation() + (m_direction * deltaTime/*m_speed*/);
			m_transform->SetWorldTranslation(target);
		}
	}
	
	
}

#pragma optimize("", on)