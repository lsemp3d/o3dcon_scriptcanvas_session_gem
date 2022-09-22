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
	
	void PlayerController::Activate()
	{
		AZ::TickBus::Handler::BusConnect();

		m_transform = AZ::EntityUtils::FindFirstDerivedComponent<AZ::TransformInterface>(GetEntity());
	}
	
	void PlayerController::Deactivate()
	{
		AZ::TickBus::Handler::BusDisconnect();

		m_onCollisionBeginHandler.Disconnect();
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

				m_gameplayNode->CallPlayerMoved(m_delta);

			}

		}
	}
	
	void PlayerController::ProcessIntentions()
	{
		static AZ::Crc32 strafe = AZ_CRC_CE("Strafe");
		static AZ::Crc32 shoot = AZ_CRC_CE("Shoot");

		auto& intentions = m_gameplayNode->GetIntentions();
		while (!intentions.empty())
		{
			Game::Intention intention = intentions.front();
			if (intention.Is(strafe))
			{
				m_strafeEvent = true;
				m_inputValue = intention.m_value;
			}
			else if (intention.Is(shoot))
			{
				// Spawn Projectile Prefab
				m_gameplayNode->SpawnProjectile();
			}

			intentions.pop();
		}
	}
}