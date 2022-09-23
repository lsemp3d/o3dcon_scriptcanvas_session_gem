/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#include "ScriptCanvasGameplay.h"

#include <GameComponents/PlayerController.h>
#include <GameComponents/EnemyController.h>

#include <AzCore/Console/ILogger.h>

/////////////////////////////////////////////////////////////
// This registration only needs to happen once per module
// You can keep it here, or move it into this module's 
// system component
#include <ScriptCanvas/AutoGen/ScriptCanvasAutoGenRegistry.h>
#include <Source/ScriptCanvasGameplay_Nodeables.generated.h>
#include <GameComponents/EnemyController.h>
REGISTER_SCRIPTCANVAS_AUTOGEN_NODEABLE(ScriptCanvasGameplayObject);
/////////////////////////////////////////////////////////////

namespace Game::Nodes
{
    ScriptCanvasGameplay::ScriptCanvasGameplay()
        : m_enemySpawnPosition(AZ::Vector3::CreateZero())
    {
    }

    ScriptCanvasGameplay::~ScriptCanvasGameplay()
    {
    }

    void ScriptCanvasGameplay::OnDeactivate()
    { 
        AzFramework::Scripts::SpawnableScriptNotificationsBus::MultiHandler::BusDisconnect();

        for (auto& spawnTicket : m_spawnTickets)
        {
            m_spawnableScriptMediator.Despawn(spawnTicket);
        }

        m_enemyWaveSpawner.reset();
        m_spawnTickets.clear();
        m_spawnableScriptMediator.Clear();
    }

    void ScriptCanvasGameplay::Start(float PlayerRadius, float PlayerSpeed, int Enemies, float SpawnSpeed)
    {
        AZLOG_INFO("ScriptCanvasGameplay::Start");

        m_radius = PlayerRadius;
        m_speed = PlayerSpeed;
        m_numEnemies = Enemies;
        m_enemySpawnSpeed = SpawnSpeed;


        // Spawn the player
        if (PlayerPrefab.GetAsset())
        {
            m_playerTicket = m_spawnableScriptMediator.CreateSpawnTicket(PlayerPrefab);
            m_spawnTickets.insert(m_playerTicket);
            
            AzFramework::Scripts::SpawnableScriptNotificationsBus::MultiHandler::BusConnect(m_playerTicket.GetId());

            m_spawnableScriptMediator.Spawn(m_playerTicket);

        }
        else
        {
            AZLOG_ERROR("You need to provide a Player Prefab");
        }
    }

    void ScriptCanvasGameplay::MoveInputEvent(float value)
    {
        static Intention Intention_Strafe(AZ_CRC_CE("Strafe"));

        Intention_Strafe.m_value = value;
        m_intentions.push(Intention_Strafe);
    }

    void ScriptCanvasGameplay::EnemyContact(const AzPhysics::TriggerEvent& event)
    {
        CallOnEnemyContact(event);
    }

    void ScriptCanvasGameplay::OnSpawn(AzFramework::EntitySpawnTicket spawnTicket, AZStd::vector<AZ::EntityId> entityList)
    {
        AzFramework::Scripts::SpawnableScriptNotificationsBus::MultiHandler::BusDisconnect(spawnTicket.GetId());

        if (spawnTicket == m_playerTicket)
        {
            constexpr int PlayerEntity = 1;
            m_playerEntityId = entityList[PlayerEntity];

            AZ::Entity* playerEntity = nullptr;
            AZ::ComponentApplicationBus::BroadcastResult(playerEntity, &AZ::ComponentApplicationBus::Events::FindEntity, m_playerEntityId);
            if (playerEntity)
            {
                playerEntity->Deactivate();
                m_playerController = playerEntity->CreateComponent<PlayerController>(this);
                playerEntity->Activate();
                m_playerController->Configure(GetRadius(), GetSpeed(), m_playerEntityId);
            }

            // Find the enemy spawner entity in the prefab and get its location, we don't need anything else from it
            constexpr int EnemySpawnEntity = 2;
            m_enemySpawnerEntityId = entityList[EnemySpawnEntity];

            AZ::Entity* enemySpawnEntity = nullptr;
            AZ::ComponentApplicationBus::BroadcastResult(enemySpawnEntity, &AZ::ComponentApplicationBus::Events::FindEntity, m_enemySpawnerEntityId);
            if (enemySpawnEntity)
            {
                m_enemySpawnPosition = enemySpawnEntity->GetTransform()->GetWorldTranslation();
            }

            m_enemyWaveSpawner = AZStd::make_unique<EnemyWaveSpawner>(this);
            m_enemyWaveSpawner->Configure(&m_spawnableScriptMediator, EnemyPrefabs, m_enemySpawnPosition, m_playerEntityId);
            m_enemyWaveSpawner->Start(GetNumEnemies(), GetEnemySpawnSpeed());

            CallOnPlayerSpawned();
        }
    }
    
    void ScriptCanvasGameplay::OnDespawn(AzFramework::EntitySpawnTicket spawnTicket)
    {
        m_spawnTickets.erase(spawnTicket);
    }

    void ScriptCanvasGameplay::OnWaveComplete()
    {
        m_spawnableScriptMediator.Despawn(m_playerTicket);

        CallOnWaveComplete();
    }

} // namespace ScriptCanvas::Nodes
