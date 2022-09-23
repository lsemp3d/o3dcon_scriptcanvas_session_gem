/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#pragma once

#include <AzCore/Component/TickBus.h>

#include <AzFramework/Spawnable/Script/SpawnableScriptBus.h>
#include <AzFramework/Spawnable/Script/SpawnableScriptMediator.h>

namespace Game::Nodes
{
    class ScriptCanvasGameplay;
}

namespace Game
{

    class EnemyWaveSpawner
        : public AZ::TickBus::Handler
        , public AzFramework::Scripts::SpawnableScriptNotificationsBus::MultiHandler
    {
    public:

        EnemyWaveSpawner(Game::Nodes::ScriptCanvasGameplay* gameplayNode);
        ~EnemyWaveSpawner();

        void Configure(AzFramework::Scripts::SpawnableScriptMediator* scriptMediator, AZStd::vector<AzFramework::Scripts::SpawnableScriptAssetRef>& enemyPrefabs, const AZ::Vector3& spawnLocation, AZ::EntityId playerEntityId);
        void Start(int numEnemies, float interval);
        
        void SpawnRandom();
        void OnSpawn(AzFramework::EntitySpawnTicket spawnTicket, AZStd::vector<AZ::EntityId> entityList) override;
        void OnDespawn(AzFramework::EntitySpawnTicket spawnTicket) override;

        void OnTick(float deltaTime, AZ::ScriptTimePoint) override;


    protected:

        float m_interval = 1.f;
        float m_randomInterval = 0.f;

        int m_numEnemies = 10;

        float m_elapsedTime = 0.f;

        AZ::EntityId m_playerEntityId;

        Game::Nodes::ScriptCanvasGameplay* m_gameplayNode;

        AZ::Vector3 m_spawnLocation;

        AZStd::unordered_set<AzFramework::EntitySpawnTicket> m_spawnTickets;

        AZStd::vector<AzFramework::Scripts::SpawnableScriptAssetRef> m_enemyPrefabs;

        AzFramework::Scripts::SpawnableScriptMediator* m_scriptMediator;
    };

}