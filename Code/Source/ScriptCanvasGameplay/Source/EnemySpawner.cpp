/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#include "EnemySpawner.h"
#include <GameComponents/EnemyController.h>

namespace Game
{
    EnemyWaveSpawner::EnemyWaveSpawner(Game::Nodes::ScriptCanvasGameplay* gameplayNode)
        : m_gameplayNode(gameplayNode)
    {
        AZ::TickBus::Handler::BusConnect();
    }

    void EnemyWaveSpawner::Configure(AzFramework::Scripts::SpawnableScriptMediator* scriptMediator, AZStd::unordered_map<AZStd::string, AzFramework::Scripts::SpawnableScriptAssetRef>& enemyPrefabs, const AZ::Vector3& spawnLocation)
    {
        m_spawnLocation = spawnLocation;
        m_enemyPrefabs = enemyPrefabs;
        m_scriptMediator = scriptMediator;

        for (auto& enemy : enemyPrefabs)
        {
            auto spawnTicket = scriptMediator->CreateSpawnTicket(enemy.second);
            m_spawnTickets.push_back(spawnTicket);
        }
    }

    void EnemyWaveSpawner::OnSpawn(AzFramework::EntitySpawnTicket spawnTicket, AZStd::vector<AZ::EntityId> entityList)
    {
        AzFramework::Scripts::SpawnableScriptNotificationsBus::MultiHandler::BusDisconnect(spawnTicket.GetId());

        AZ::Entity* entity = nullptr;
        AZ::ComponentApplicationBus::BroadcastResult(entity, &AZ::ComponentApplicationBus::Events::FindEntity, entityList[0]);
        if (entity)
        {
            entity->Deactivate();
            [[maybe_unused]] EnemyController* enemyController = entity->CreateComponent<EnemyController>(m_gameplayNode, spawnTicket);
            entity->Activate();

            entity->GetTransform()->SetWorldTranslation(m_spawnLocation);

            enemyController->Configure(m_gameplayNode->Radius, 10.f, entityList[1]);
        }
    }

    void EnemyWaveSpawner::OnTick(float deltaTime, AZ::ScriptTimePoint)
    {
        if (m_numEnemies > 0)
        {
            if (m_elapsedTime >= m_interval + m_randomInterval)
            {
                m_elapsedTime = 0.f;

                // Reset the randomization
                m_randomInterval = (float)(rand() % 100) / 100.f;

                // Spawn an enemy
                SpawnRandom();

                //AZLOG_INFO("SPAWN ENEMY %d", m_numEnemies);

                --m_numEnemies;

                if (m_numEnemies == 0)
                {
                    // Notify that this wave is complete
                    m_gameplayNode->OnWaveComplete();
                }
            }
        }

        m_elapsedTime += deltaTime;
    }
}