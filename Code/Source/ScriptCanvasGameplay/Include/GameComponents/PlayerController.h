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

#include <AzFramework/Physics/Common/PhysicsSimulatedBodyEvents.h>
#include <AzFramework/Physics/PhysicsSystem.h>

namespace Game
{

	class PlayerController 
		: public AZ::Component
		, public AZ::TickBus::Handler
	{
	public:

		AZ_COMPONENT(PlayerController, "{BF93B0C3-5B34-4756-8608-DF33395B7626}");

		static void Reflect(AZ::ReflectContext*) {}

		PlayerController() = default;
		PlayerController(Nodes::ScriptCanvasGameplay* gameplayNode);

		void Configure(float radius, float speed, AZ::EntityId shipEntityId);

		void Activate() override;
		void Deactivate() override;

		void OnTick([[maybe_unused]] float deltaTime, AZ::ScriptTimePoint);

		void ProcessIntentions();

	protected:

		float m_speed = 1.f;
		float m_radius = 1.f;

		float m_delta = 0.f;
		float m_inputValue = 0.f;
		bool m_strafeEvent = false;

		AzPhysics::SimulatedBodyEvents::OnTriggerEnter::Handler m_onCollisionBeginHandler;

		Nodes::ScriptCanvasGameplay* m_gameplayNode = nullptr;
		AZ::TransformInterface* m_transform = nullptr;
	};
}
