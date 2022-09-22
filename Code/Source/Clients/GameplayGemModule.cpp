

#include <GameplayGemModuleInterface.h>
#include "GameplayGemSystemComponent.h"

#include <GameComponents/PlayerController.h>
#include <GameComponents/EnemyController.h>

namespace GameplayGem
{
    class GameplayGemModule
        : public GameplayGemModuleInterface
    {
    public:
        AZ_RTTI(GameplayGemModule, "{B51B469D-2AD8-489F-AE35-5C8831DF925A}", GameplayGemModuleInterface);
        AZ_CLASS_ALLOCATOR(GameplayGemModule, AZ::SystemAllocator, 0);

        GameplayGemModule()
        {
            m_descriptors.insert(m_descriptors.end(), {
                Game::PlayerController::CreateDescriptor(),
                Game::EnemyController::CreateDescriptor(),
                });
        }
    };
}// namespace GameplayGem

AZ_DECLARE_MODULE_CLASS(Gem_GameplayGem, GameplayGem::GameplayGemModule)
