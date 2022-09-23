/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#pragma once

#include <AzCore/Component/Component.h>
#include <AzCore/Component/TickBus.h>

#include <AzCore/Component/TransformBus.h>
#include <AzCore/Component/EntityUtils.h>

#include <AzCore/Console/ILogger.h>
#include <ScriptCanvasGameplay.h>

#include <PhysX/ColliderShapeBus.h>

namespace Game
{

	class EnemyController 
		: public AZ::Component
		, public AZ::TickBus::Handler
	{
	public:

		AZ_COMPONENT(EnemyController, "{4C87C82C-34A1-4CF4-84A1-227EC6F38A6B}");

		static void Reflect(AZ::ReflectContext*) {}

		EnemyController() = default;
		EnemyController(Nodes::ScriptCanvasGameplay* gameplayNode, AzFramework::EntitySpawnTicket& spawnTicket);

		void Configure(float radius, float speed, AZ::EntityId enemyEntityId, AZ::EntityId playerEntityId);

		void Activate() override;
		void Deactivate() override;

		void OnTick([[maybe_unused]] float deltaTime, AZ::ScriptTimePoint);


	protected:

		float m_speed = 1.f;
		float m_radius = 1.f;
		float m_lifetime = 8.f;

		AZ::EntityId m_playerEntityId;

		AzFramework::EntitySpawnTicket m_spawnTicket;

		AZ::Vector3 m_direction;

		AzPhysics::SimulatedBodyEvents::OnTriggerEnter::Handler m_onCollisionBeginHandler;

		Nodes::ScriptCanvasGameplay* m_gameplayNode = nullptr;
		AZ::TransformInterface* m_transform = nullptr;
	};
}
