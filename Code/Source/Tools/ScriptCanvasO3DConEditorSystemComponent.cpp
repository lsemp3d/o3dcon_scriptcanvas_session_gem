
#include <AzCore/Serialization/SerializeContext.h>
#include "ScriptCanvasO3DConEditorSystemComponent.h"

namespace ScriptCanvasO3DCon
{
    void ScriptCanvasO3DConEditorSystemComponent::Reflect(AZ::ReflectContext* context)
    {
        if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serializeContext->Class<ScriptCanvasO3DConEditorSystemComponent, ScriptCanvasO3DConSystemComponent>()
                ->Version(0);
        }
    }

    ScriptCanvasO3DConEditorSystemComponent::ScriptCanvasO3DConEditorSystemComponent() = default;

    ScriptCanvasO3DConEditorSystemComponent::~ScriptCanvasO3DConEditorSystemComponent() = default;

    void ScriptCanvasO3DConEditorSystemComponent::GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided)
    {
        BaseSystemComponent::GetProvidedServices(provided);
        provided.push_back(AZ_CRC_CE("ScriptCanvasO3DConEditorService"));
    }

    void ScriptCanvasO3DConEditorSystemComponent::GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible)
    {
        BaseSystemComponent::GetIncompatibleServices(incompatible);
        incompatible.push_back(AZ_CRC_CE("ScriptCanvasO3DConEditorService"));
    }

    void ScriptCanvasO3DConEditorSystemComponent::GetRequiredServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& required)
    {
        BaseSystemComponent::GetRequiredServices(required);
    }

    void ScriptCanvasO3DConEditorSystemComponent::GetDependentServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& dependent)
    {
        BaseSystemComponent::GetDependentServices(dependent);
    }

    void ScriptCanvasO3DConEditorSystemComponent::Activate()
    {
        ScriptCanvasO3DConSystemComponent::Activate();
        AzToolsFramework::EditorEvents::Bus::Handler::BusConnect();
    }

    void ScriptCanvasO3DConEditorSystemComponent::Deactivate()
    {
        AzToolsFramework::EditorEvents::Bus::Handler::BusDisconnect();
        ScriptCanvasO3DConSystemComponent::Deactivate();
    }

} // namespace ScriptCanvasO3DCon
