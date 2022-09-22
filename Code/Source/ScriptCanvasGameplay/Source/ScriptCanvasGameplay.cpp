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

#pragma optimize("", off)

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

    void ScriptCanvasGameplay::Start()
    {
        AZLOG_INFO("ScriptCanvasGameplay::Start");

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

    void ScriptCanvasGameplay::ShootInputEvent(float value)
    {
        static Intention Intention_Shoot(AZ_CRC_CE("Shoot"));

        Intention_Shoot.m_value = value;
        m_intentions.push(Intention_Shoot);
    }

    void ScriptCanvasGameplay::EnemyContact(const AzPhysics::TriggerEvent& event)
    {
        CallEnemyContact(event);
    }

    void ScriptCanvasGameplay::SpawnProjectile()
    {
        auto projectileTicket = m_spawnableScriptMediator.CreateSpawnTicket(ProjectilePrefab);
        
        AzFramework::Scripts::SpawnableScriptNotificationsBus::MultiHandler::BusConnect(projectileTicket.GetId());

        AZ::Entity* playerEntity = nullptr;
        AZ::ComponentApplicationBus::BroadcastResult(playerEntity, &AZ::ComponentApplicationBus::Events::FindEntity, m_playerEntityId);
        if (playerEntity)
        {
            m_spawnableScriptMediator.SpawnAndParentAndTransform(projectileTicket, m_playerEntityId, playerEntity->GetTransform()->GetWorldTranslation(), AZ::Vector3(0.f, -90.f, 0.f), 1.f);
        }

    }

    void ScriptCanvasGameplay::OnSpawn(AzFramework::EntitySpawnTicket spawnTicket, AZStd::vector<AZ::EntityId> entityList)
    {
        AzFramework::Scripts::SpawnableScriptNotificationsBus::MultiHandler::BusDisconnect(spawnTicket.GetId());

        if (spawnTicket == m_playerTicket)
        {
            [[maybe_unused]] constexpr int ContainerEntity = 0;
            constexpr int PlayerEntity = 1;
            constexpr int EnemySpawnEntity = 2;

            m_playerEntityId = entityList[PlayerEntity];
            m_enemySpawnerEntityId = entityList[EnemySpawnEntity];

            AZ::Entity* playerEntity = nullptr;
            AZ::ComponentApplicationBus::BroadcastResult(playerEntity, &AZ::ComponentApplicationBus::Events::FindEntity, m_playerEntityId);
            if (playerEntity)
            {
                playerEntity->Deactivate();
                m_playerController = playerEntity->CreateComponent<PlayerController>(this);
                playerEntity->Activate();
                m_playerController->Configure(Radius, Speed, m_playerEntityId);
            }

            AZ::Vector3 containerPosition = AZ::Vector3::CreateZero();

            // Find the enemy spawner entity in the prefab and get its location, we don't need anything else from it
            AZ::Entity* containerEntity = nullptr;
            AZ::ComponentApplicationBus::BroadcastResult(containerEntity, &AZ::ComponentApplicationBus::Events::FindEntity, entityList[ContainerEntity]);
            if (containerEntity)
            {
                containerPosition = containerEntity->GetTransform()->GetWorldTranslation();
            }

            // Find the enemy spawner entity in the prefab and get its location, we don't need anything else from it
            AZ::Entity* enemySpawnEntity = nullptr;
            AZ::ComponentApplicationBus::BroadcastResult(enemySpawnEntity, &AZ::ComponentApplicationBus::Events::FindEntity, m_enemySpawnerEntityId);
            if (enemySpawnEntity)
            {
                m_enemySpawnPosition = containerPosition + enemySpawnEntity->GetTransform()->GetWorldTranslation();
            }


            m_enemyWaveSpawner = new EnemyWaveSpawner(this);
            m_enemyWaveSpawner->Configure(&m_spawnableScriptMediator, EnemyPrefabs, m_enemySpawnPosition);
            m_enemyWaveSpawner->Start(10, 2.f);


            CallPlayerSpawned();
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




#pragma optimize("", on)