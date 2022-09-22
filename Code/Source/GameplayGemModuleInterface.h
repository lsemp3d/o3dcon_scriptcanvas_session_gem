
#include <AzCore/Memory/SystemAllocator.h>
#include <AzCore/Module/Module.h>
#include <Clients/GameplayGemSystemComponent.h>

namespace GameplayGem
{
    class GameplayGemModuleInterface
        : public AZ::Module
    {
    public:
        AZ_RTTI(GameplayGemModuleInterface, "{7024F50B-F08D-4E5A-9CC9-8E5C59B0DDA8}", AZ::Module);
        AZ_CLASS_ALLOCATOR(GameplayGemModuleInterface, AZ::SystemAllocator, 0);

        GameplayGemModuleInterface()
        {
            // Push results of [MyComponent]::CreateDescriptor() into m_descriptors here.
            // Add ALL components descriptors associated with this gem to m_descriptors.
            // This will associate the AzTypeInfo information for the components with the the SerializeContext, BehaviorContext and EditContext.
            // This happens through the [MyComponent]::Reflect() function.
            m_descriptors.insert(m_descriptors.end(), {
                GameplayGemSystemComponent::CreateDescriptor(),
                });
        }

        /**
         * Add required SystemComponents to the SystemEntity.
         */
        AZ::ComponentTypeList GetRequiredSystemComponents() const override
        {
            return AZ::ComponentTypeList{
                azrtti_typeid<GameplayGemSystemComponent>(),
            };
        }
    };
}// namespace GameplayGem
