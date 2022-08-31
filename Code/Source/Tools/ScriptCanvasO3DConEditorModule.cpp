
#include <ScriptCanvasO3DConModuleInterface.h>
#include "ScriptCanvasO3DConEditorSystemComponent.h"

namespace ScriptCanvasO3DCon
{
    class ScriptCanvasO3DConEditorModule
        : public ScriptCanvasO3DConModuleInterface
    {
    public:
        AZ_RTTI(ScriptCanvasO3DConEditorModule, "{45EF915D-1F71-47AF-A7B2-8CA0E9AA3CC4}", ScriptCanvasO3DConModuleInterface);
        AZ_CLASS_ALLOCATOR(ScriptCanvasO3DConEditorModule, AZ::SystemAllocator, 0);

        ScriptCanvasO3DConEditorModule()
        {
            // Push results of [MyComponent]::CreateDescriptor() into m_descriptors here.
            // Add ALL components descriptors associated with this gem to m_descriptors.
            // This will associate the AzTypeInfo information for the components with the the SerializeContext, BehaviorContext and EditContext.
            // This happens through the [MyComponent]::Reflect() function.
            m_descriptors.insert(m_descriptors.end(), {
                ScriptCanvasO3DConEditorSystemComponent::CreateDescriptor(),
            });
        }

        /**
         * Add required SystemComponents to the SystemEntity.
         * Non-SystemComponents should not be added here
         */
        AZ::ComponentTypeList GetRequiredSystemComponents() const override
        {
            return AZ::ComponentTypeList {
                azrtti_typeid<ScriptCanvasO3DConEditorSystemComponent>(),
            };
        }
    };
}// namespace ScriptCanvasO3DCon

AZ_DECLARE_MODULE_CLASS(Gem_ScriptCanvasO3DCon, ScriptCanvasO3DCon::ScriptCanvasO3DConEditorModule)
