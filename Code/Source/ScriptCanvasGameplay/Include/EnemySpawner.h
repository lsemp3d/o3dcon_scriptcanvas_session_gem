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

        void Configure(AzFramework::Scripts::SpawnableScriptMediator* scriptMediator, AZStd::unordered_map<AZStd::string, AzFramework::Scripts::SpawnableScriptAssetRef>& enemyPrefabs, const AZ::Vector3& spawnLocation);

        void OnSpawn([[maybe_unused]] AzFramework::EntitySpawnTicket spawnTicket, [[maybe_unused]] AZStd::vector<AZ::EntityId> entityList) override;


        ~EnemyWaveSpawner()
        {
            AZ::TickBus::Handler::BusDisconnect();
        }

        void SpawnRandom()
        {
            if (m_spawnTickets.empty())
            {
                return;
            }

            int randomIndex = rand() % ((int)m_spawnTickets.size());

            auto spawnTicket = m_spawnTickets[randomIndex];

            AzFramework::Scripts::SpawnableScriptNotificationsBus::MultiHandler::BusConnect(spawnTicket.GetId());
            m_scriptMediator->Spawn(spawnTicket);
        }

        void OnTick(float deltaTime, AZ::ScriptTimePoint) override;

        void Start(int numEnemies, float interval)
        {
            m_numEnemies = numEnemies;
            m_interval = interval;

            m_randomInterval = ((float)(rand() % 100)) / 100.f;
        }

        float m_interval = 1.f;
        float m_randomInterval = 0.f;

        int m_numEnemies = 10;

        float m_elapsedTime = 0.f;

        Game::Nodes::ScriptCanvasGameplay* m_gameplayNode;

        AZ::Vector3 m_spawnLocation;

        AZStd::unordered_map<AZStd::string, AzFramework::Scripts::SpawnableScriptAssetRef> m_enemyPrefabs;
        AZStd::vector<AzFramework::EntitySpawnTicket> m_spawnTickets;

        AzFramework::Scripts::SpawnableScriptMediator* m_scriptMediator;
    };

}