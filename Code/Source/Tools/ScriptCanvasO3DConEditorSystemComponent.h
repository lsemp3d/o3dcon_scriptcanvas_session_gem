
#pragma once

#include <AzToolsFramework/API/ToolsApplicationAPI.h>

#include <Clients/ScriptCanvasO3DConSystemComponent.h>

namespace ScriptCanvasO3DCon
{
    /// System component for ScriptCanvasO3DCon editor
    class ScriptCanvasO3DConEditorSystemComponent
        : public ScriptCanvasO3DConSystemComponent
        , protected AzToolsFramework::EditorEvents::Bus::Handler
    {
        using BaseSystemComponent = ScriptCanvasO3DConSystemComponent;
    public:
        AZ_COMPONENT(ScriptCanvasO3DConEditorSystemComponent, "{900AB6EF-965D-42EF-8159-0CBF67F322FA}", BaseSystemComponent);
        static void Reflect(AZ::ReflectContext* context);

        ScriptCanvasO3DConEditorSystemComponent();
        ~ScriptCanvasO3DConEditorSystemComponent();

    private:
        static void GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided);
        static void GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible);
        static void GetRequiredServices(AZ::ComponentDescriptor::DependencyArrayType& required);
        static void GetDependentServices(AZ::ComponentDescriptor::DependencyArrayType& dependent);

        // AZ::Component
        void Activate() override;
        void Deactivate() override;
    };
} // namespace ScriptCanvasO3DCon
