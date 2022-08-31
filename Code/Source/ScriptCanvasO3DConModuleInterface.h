
#include <AzCore/Memory/SystemAllocator.h>
#include <AzCore/Module/Module.h>
#include <Clients/ScriptCanvasO3DConSystemComponent.h>

namespace ScriptCanvasO3DCon
{
    class ScriptCanvasO3DConModuleInterface
        : public AZ::Module
    {
    public:
        AZ_RTTI(ScriptCanvasO3DConModuleInterface, "{628ACA4E-426F-4EBE-B355-5B8AA12A3E4A}", AZ::Module);
        AZ_CLASS_ALLOCATOR(ScriptCanvasO3DConModuleInterface, AZ::SystemAllocator, 0);

        ScriptCanvasO3DConModuleInterface()
        {
            // Push results of [MyComponent]::CreateDescriptor() into m_descriptors here.
            // Add ALL components descriptors associated with this gem to m_descriptors.
            // This will associate the AzTypeInfo information for the components with the the SerializeContext, BehaviorContext and EditContext.
            // This happens through the [MyComponent]::Reflect() function.
            m_descriptors.insert(m_descriptors.end(), {
                ScriptCanvasO3DConSystemComponent::CreateDescriptor(),
                });
        }

        /**
         * Add required SystemComponents to the SystemEntity.
         */
        AZ::ComponentTypeList GetRequiredSystemComponents() const override
        {
            return AZ::ComponentTypeList{
                azrtti_typeid<ScriptCanvasO3DConSystemComponent>(),
            };
        }
    };
}// namespace ScriptCanvasO3DCon
