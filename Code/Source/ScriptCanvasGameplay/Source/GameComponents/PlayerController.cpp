/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#include <GameComponents/PlayerController.h>

namespace Game
{
	PlayerController::PlayerController(Nodes::ScriptCanvasGameplay* gameplayNode)
		: m_gameplayNode(gameplayNode)
	{}

	void PlayerController::Configure(float radius, float speed, AZ::EntityId shipEntityId)
	{
		m_radius = radius;
		m_speed = speed;

		m_onCollisionBeginHandler = AzPhysics::SimulatedBodyEvents::OnTriggerEnter::Handler(
			[this]([[maybe_unused]] AzPhysics::SimulatedBodyHandle bodyHandle,
				const AzPhysics::TriggerEvent& event)
			{

				// Collision took place! I can send out even through node
				m_gameplayNode->EnemyContact(event);
			});

		if (auto* physicsSystem = AZ::Interface<AzPhysics::SystemInterface>::Get())
		{
			auto [sceneHandle, bodyHandle] = physicsSystem->FindAttachedBodyHandleFromEntityId(shipEntityId);

			if (sceneHandle != AzPhysics::InvalidSceneHandle)
			{
				AzPhysics::SimulatedBodyEvents::RegisterOnTriggerEnterHandler(sceneHandle, bodyHandle, m_onCollisionBeginHandler);
			}
		}
	}
	
	void PlayerController::Activate()
	{
		AZ::TickBus::Handler::BusConnect();

		m_transform = AZ::EntityUtils::FindFirstDerivedComponent<AZ::TransformInterface>(GetEntity());
	}
	
	void PlayerController::Deactivate()
	{
		m_onCollisionBeginHandler.Disconnect();
		AZ::TickBus::Handler::BusDisconnect();
	}
	
	void PlayerController::OnTick(float deltaTime, AZ::ScriptTimePoint)
	{
		ProcessIntentions();

		if (m_transform)
		{
			if (m_strafeEvent)
			{
				m_delta += (m_speed * deltaTime) * m_inputValue;

				m_transform->SetWorldY(m_radius * sinf(m_delta));
				m_transform->SetWorldZ(m_radius * cosf(m_delta));
				m_strafeEvent = false;

				m_gameplayNode->CallOnPlayerMoved(GetEntity()->GetTransform()->GetWorldTranslation());
			}
		}
	}
	
	void PlayerController::ProcessIntentions()
	{
		static AZ::Crc32 strafe = AZ_CRC_CE("Strafe");

		auto& intentions = m_gameplayNode->GetIntentions();
		while (!intentions.empty())
		{
			Game::Intention intention = intentions.front();
			if (intention.Is(strafe))
			{
				m_strafeEvent = true;
				m_inputValue = intention.m_value;
			}

			intentions.pop();
		}
	}
}