
#include "GameplayGemSystemComponent.h"

#include <AzCore/Serialization/SerializeContext.h>
#include <AzCore/Serialization/EditContext.h>
#include <AzCore/Serialization/EditContextConstants.inl>

namespace GameplayGem
{
    void GameplayGemSystemComponent::Reflect(AZ::ReflectContext* context)
    {
        if (AZ::SerializeContext* serialize = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serialize->Class<GameplayGemSystemComponent, AZ::Component>()
                ->Version(0)
                ;

            if (AZ::EditContext* ec = serialize->GetEditContext())
            {
                ec->Class<GameplayGemSystemComponent>("GameplayGem", "[Description of functionality provided by this System Component]")
                    ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                        ->Attribute(AZ::Edit::Attributes::AppearsInAddComponentMenu, AZ_CRC("System"))
                        ->Attribute(AZ::Edit::Attributes::AutoExpand, true)
                    ;
            }
        }
    }

    void GameplayGemSystemComponent::GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided)
    {
        provided.push_back(AZ_CRC_CE("GameplayGemService"));
    }

    void GameplayGemSystemComponent::GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible)
    {
        incompatible.push_back(AZ_CRC_CE("GameplayGemService"));
    }

    void GameplayGemSystemComponent::GetRequiredServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& required)
    {
    }

    void GameplayGemSystemComponent::GetDependentServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& dependent)
    {
    }

    GameplayGemSystemComponent::GameplayGemSystemComponent()
    {
        if (GameplayGemInterface::Get() == nullptr)
        {
            GameplayGemInterface::Register(this);
        }
    }

    GameplayGemSystemComponent::~GameplayGemSystemComponent()
    {
        if (GameplayGemInterface::Get() == this)
        {
            GameplayGemInterface::Unregister(this);
        }
    }

    void GameplayGemSystemComponent::Init()
    {
    }

    void GameplayGemSystemComponent::Activate()
    {
        GameplayGemRequestBus::Handler::BusConnect();
        AZ::TickBus::Handler::BusConnect();
    }

    void GameplayGemSystemComponent::Deactivate()
    {
        AZ::TickBus::Handler::BusDisconnect();
        GameplayGemRequestBus::Handler::BusDisconnect();
    }

    void GameplayGemSystemComponent::OnTick([[maybe_unused]] float deltaTime, [[maybe_unused]] AZ::ScriptTimePoint time)
    {
    }

} // namespace GameplayGem
