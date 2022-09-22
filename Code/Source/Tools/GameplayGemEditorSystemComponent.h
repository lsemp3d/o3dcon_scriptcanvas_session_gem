
#pragma once

#include <AzToolsFramework/API/ToolsApplicationAPI.h>

#include <Clients/GameplayGemSystemComponent.h>

namespace GameplayGem
{
    /// System component for GameplayGem editor
    class GameplayGemEditorSystemComponent
        : public GameplayGemSystemComponent
        , protected AzToolsFramework::EditorEvents::Bus::Handler
    {
        using BaseSystemComponent = GameplayGemSystemComponent;
    public:
        AZ_COMPONENT(GameplayGemEditorSystemComponent, "{6F974FD5-847A-4550-A897-38C473712076}", BaseSystemComponent);
        static void Reflect(AZ::ReflectContext* context);

        GameplayGemEditorSystemComponent();
        ~GameplayGemEditorSystemComponent();

    private:
        static void GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided);
        static void GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible);
        static void GetRequiredServices(AZ::ComponentDescriptor::DependencyArrayType& required);
        static void GetDependentServices(AZ::ComponentDescriptor::DependencyArrayType& dependent);

        // AZ::Component
        void Activate() override;
        void Deactivate() override;
    };
} // namespace GameplayGem
