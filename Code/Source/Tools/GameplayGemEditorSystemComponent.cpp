
#include <AzCore/Serialization/SerializeContext.h>
#include "GameplayGemEditorSystemComponent.h"

namespace GameplayGem
{
    void GameplayGemEditorSystemComponent::Reflect(AZ::ReflectContext* context)
    {
        if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serializeContext->Class<GameplayGemEditorSystemComponent, GameplayGemSystemComponent>()
                ->Version(0);
        }
    }

    GameplayGemEditorSystemComponent::GameplayGemEditorSystemComponent() = default;

    GameplayGemEditorSystemComponent::~GameplayGemEditorSystemComponent() = default;

    void GameplayGemEditorSystemComponent::GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided)
    {
        BaseSystemComponent::GetProvidedServices(provided);
        provided.push_back(AZ_CRC_CE("GameplayGemEditorService"));
    }

    void GameplayGemEditorSystemComponent::GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible)
    {
        BaseSystemComponent::GetIncompatibleServices(incompatible);
        incompatible.push_back(AZ_CRC_CE("GameplayGemEditorService"));
    }

    void GameplayGemEditorSystemComponent::GetRequiredServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& required)
    {
        BaseSystemComponent::GetRequiredServices(required);
    }

    void GameplayGemEditorSystemComponent::GetDependentServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& dependent)
    {
        BaseSystemComponent::GetDependentServices(dependent);
    }

    void GameplayGemEditorSystemComponent::Activate()
    {
        GameplayGemSystemComponent::Activate();
        AzToolsFramework::EditorEvents::Bus::Handler::BusConnect();
    }

    void GameplayGemEditorSystemComponent::Deactivate()
    {
        AzToolsFramework::EditorEvents::Bus::Handler::BusDisconnect();
        GameplayGemSystemComponent::Deactivate();
    }

} // namespace GameplayGem
