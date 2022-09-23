/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#pragma once

#include <ScriptCanvas/CodeGen/NodeableCodegen.h>
#include <ScriptCanvas/Core/Node.h>
#include <ScriptCanvas/Core/Nodeable.h>

#include <Source/ScriptCanvasGameplay.generated.h>

#include <AzFramework/Spawnable/Script/SpawnableScriptAssetRef.h>
#include <AzFramework/Spawnable/Script/SpawnableScriptMediator.h>
#include <AzFramework/Spawnable/SpawnableEntitiesInterface.h>
#include <AzFramework/Spawnable/Script/SpawnableScriptBus.h>

#include <EnemySpawner.h>

#include <AzFramework/Physics/Common/PhysicsSimulatedBodyEvents.h>



namespace Game
{
    class PlayerController;

    //! An Intention is a system to handle player requests or commands
    //! such as inputs
    class Intention
    {
    public:
        AZ::Crc32 m_intentionID;
        float m_value;

        Intention(AZ::Crc32 id)
            : m_intentionID(id)
        {}

        bool Is(AZ::Crc32& id) const { return id == m_intentionID; }
    };
}

namespace Game::Nodes
{
    class ScriptCanvasGameplay
        : public ScriptCanvas::Nodeable
        , public AzFramework::Scripts::SpawnableScriptNotificationsBus::MultiHandler
    {
        SCRIPTCANVAS_NODE(ScriptCanvasGameplay);
    public:

        ScriptCanvasGameplay();
        ~ScriptCanvasGameplay() override;
        void OnDeactivate() override;

        AZStd::queue<Intention>& GetIntentions() { return m_intentions; }

        void EnemyContact(const AzPhysics::TriggerEvent& event);

        void SpawnProjectile();

        AzFramework::Scripts::SpawnableScriptMediator& GetScriptMediator() { return m_spawnableScriptMediator; }

        void OnWaveComplete();

        float GetRadius() const { return m_radius; }
        float GetSpeed() const { return m_speed; }
        int GetNumEnemies() const { return m_numEnemies; }
        float GetEnemySpawnSpeed() const { return m_enemySpawnSpeed; }

    protected:

        void OnSpawn(AzFramework::EntitySpawnTicket spawnTicket, AZStd::vector<AZ::EntityId> entityList) override;
        void OnDespawn(AzFramework::EntitySpawnTicket spawnTicket) override;

        float m_radius = 4;
        float m_speed = 5;
        int m_numEnemies = 10;
        float m_enemySpawnSpeed = 5.f;

        AzFramework::Scripts::SpawnableScriptMediator m_spawnableScriptMediator;

        AZStd::unordered_set<AzFramework::EntitySpawnTicket> m_spawnTickets;

        AzFramework::EntitySpawnTicket m_playerTicket;
        AZ::EntityId m_playerEntityId;

        AZ::EntityId m_enemySpawnerEntityId;
        AZ::Vector3 m_enemySpawnPosition;

        PlayerController* m_playerController;

        AZStd::unique_ptr<EnemyWaveSpawner> m_enemyWaveSpawner;

        AZStd::queue<Intention> m_intentions;

    };
}
