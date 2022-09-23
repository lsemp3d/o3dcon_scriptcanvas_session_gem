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

    EnemyWaveSpawner::~EnemyWaveSpawner()
    {
        AZ::TickBus::Handler::BusDisconnect();

        m_numEnemies = 0;

        for (auto& spawnTicket : m_spawnTickets)
        {
            m_scriptMediator->Despawn(spawnTicket);
            AzFramework::Scripts::SpawnableScriptNotificationsBus::MultiHandler::BusDisconnect(spawnTicket.GetId());
        }

        m_spawnTickets.clear();
    }

    void EnemyWaveSpawner::Configure(AzFramework::Scripts::SpawnableScriptMediator* scriptMediator, AZStd::vector<AzFramework::Scripts::SpawnableScriptAssetRef>& enemyPrefabs, const AZ::Vector3& spawnLocation, AZ::EntityId playerEntityId)
    {
        m_playerEntityId = playerEntityId;
        m_spawnLocation = spawnLocation;
        m_enemyPrefabs = enemyPrefabs;
        m_scriptMediator = scriptMediator;
    }

    void EnemyWaveSpawner::Start(int numEnemies, float interval)
    {
        m_numEnemies = numEnemies;
        m_interval = interval;

        m_randomInterval = ((float)(rand() % 100)) / 100.f;
    }

    void EnemyWaveSpawner::SpawnRandom()
    {
        int randomIndex = rand() % ((int)m_enemyPrefabs.size());

        auto spawnTicket = m_scriptMediator->CreateSpawnTicket(m_enemyPrefabs[randomIndex]);
        m_spawnTickets.insert(spawnTicket);

        AzFramework::Scripts::SpawnableScriptNotificationsBus::MultiHandler::BusConnect(spawnTicket.GetId());
        m_scriptMediator->Spawn(spawnTicket);
    }

    void EnemyWaveSpawner::OnSpawn(AzFramework::EntitySpawnTicket spawnTicket, AZStd::vector<AZ::EntityId> entityList)
    {
        AZ::Entity* entity = nullptr;
        AZ::ComponentApplicationBus::BroadcastResult(entity, &AZ::ComponentApplicationBus::Events::FindEntity, entityList[0]);
        if (entity)
        {
            entity->Deactivate();
            [[maybe_unused]] EnemyController* enemyController = entity->CreateComponent<EnemyController>(m_gameplayNode, spawnTicket);
            entity->Activate();

            entity->GetTransform()->SetWorldTranslation(m_spawnLocation);

            enemyController->Configure(m_gameplayNode->GetRadius(), m_gameplayNode->GetSpeed(), entityList[1], m_playerEntityId);
        }
    }

    void EnemyWaveSpawner::OnDespawn(AzFramework::EntitySpawnTicket spawnTicket)
    {
        AzFramework::Scripts::SpawnableScriptNotificationsBus::MultiHandler::BusDisconnect(spawnTicket.GetId());

        const auto& it = AZStd::find(m_spawnTickets.begin(), m_spawnTickets.end(), spawnTicket);
        if (it != m_spawnTickets.end())
        {
            m_spawnTickets.erase(it);
        }

        if (m_spawnTickets.empty())
        {
            // Notify that this wave is complete
            m_gameplayNode->OnWaveComplete();
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

                --m_numEnemies;

            }
        }

        m_elapsedTime += deltaTime;
    }
}
