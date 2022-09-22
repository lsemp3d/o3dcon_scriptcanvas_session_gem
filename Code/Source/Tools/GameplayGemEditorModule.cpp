
#include <GameplayGemModuleInterface.h>
#include "GameplayGemEditorSystemComponent.h"

#include <GameComponents/PlayerController.h>
#include <GameComponents/EnemyController.h>

namespace GameplayGem
{
    class GameplayGemEditorModule
        : public GameplayGemModuleInterface
    {
    public:
        AZ_RTTI(GameplayGemEditorModule, "{B51B469D-2AD8-489F-AE35-5C8831DF925A}", GameplayGemModuleInterface);
        AZ_CLASS_ALLOCATOR(GameplayGemEditorModule, AZ::SystemAllocator, 0);

        GameplayGemEditorModule()
        {
            // Push results of [MyComponent]::CreateDescriptor() into m_descriptors here.
            // Add ALL components descriptors associated with this gem to m_descriptors.
            // This will associate the AzTypeInfo information for the components with the the SerializeContext, BehaviorContext and EditContext.
            // This happens through the [MyComponent]::Reflect() function.
            m_descriptors.insert(m_descriptors.end(), {
                GameplayGemEditorSystemComponent::CreateDescriptor(),
                Game::PlayerController::CreateDescriptor(),
                Game::EnemyController::CreateDescriptor(),
            });
        }

        /**
         * Add required SystemComponents to the SystemEntity.
         * Non-SystemComponents should not be added here
         */
        AZ::ComponentTypeList GetRequiredSystemComponents() const override
        {
            return AZ::ComponentTypeList {
                azrtti_typeid<GameplayGemEditorSystemComponent>(),
            };
        }
    };
}// namespace GameplayGem

AZ_DECLARE_MODULE_CLASS(Gem_GameplayGem, GameplayGem::GameplayGemEditorModule)
