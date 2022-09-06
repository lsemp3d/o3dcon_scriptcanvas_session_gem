
#include "ScriptCanvasO3DConSystemComponent.h"

#include <AzCore/Serialization/SerializeContext.h>
#include <AzCore/Serialization/EditContext.h>
#include <AzCore/Serialization/EditContextConstants.inl>

namespace ScriptCanvasO3DCon
{
    void ScriptCanvasO3DConSystemComponent::Reflect(AZ::ReflectContext* context)
    {
        if (AZ::SerializeContext* serialize = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serialize->Class<ScriptCanvasO3DConSystemComponent, AZ::Component>()
                ->Version(0)
                ;

            if (AZ::EditContext* ec = serialize->GetEditContext())
            {
                ec->Class<ScriptCanvasO3DConSystemComponent>("ScriptCanvasO3DCon", "[Description of functionality provided by this System Component]")
                    ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                        ->Attribute(AZ::Edit::Attributes::AppearsInAddComponentMenu, AZ_CRC("System"))
                        ->Attribute(AZ::Edit::Attributes::AutoExpand, true)
                    ;
            }
        }
    }

    void ScriptCanvasO3DConSystemComponent::GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided)
    {
        provided.push_back(AZ_CRC_CE("ScriptCanvasO3DConService"));
    }

    void ScriptCanvasO3DConSystemComponent::GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible)
    {
        incompatible.push_back(AZ_CRC_CE("ScriptCanvasO3DConService"));
    }

    void ScriptCanvasO3DConSystemComponent::GetRequiredServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& required)
    {
    }

    void ScriptCanvasO3DConSystemComponent::GetDependentServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& dependent)
    {
    }

    ScriptCanvasO3DConSystemComponent::ScriptCanvasO3DConSystemComponent()
    {
        if (ScriptCanvasO3DConInterface::Get() == nullptr)
        {
            ScriptCanvasO3DConInterface::Register(this);
        }
    }

    ScriptCanvasO3DConSystemComponent::~ScriptCanvasO3DConSystemComponent()
    {
        if (ScriptCanvasO3DConInterface::Get() == this)
        {
            ScriptCanvasO3DConInterface::Unregister(this);
        }
    }

    void ScriptCanvasO3DConSystemComponent::Init()
    {
    }

    void ScriptCanvasO3DConSystemComponent::Activate()
    {
        ScriptCanvasO3DConRequestBus::Handler::BusConnect();
        AZ::TickBus::Handler::BusConnect();
    }

    void ScriptCanvasO3DConSystemComponent::Deactivate()
    {
        AZ::TickBus::Handler::BusDisconnect();
        ScriptCanvasO3DConRequestBus::Handler::BusDisconnect();
    }

    void ScriptCanvasO3DConSystemComponent::OnTick([[maybe_unused]] float deltaTime, [[maybe_unused]] AZ::ScriptTimePoint time)
    {
    }

} // namespace ScriptCanvasO3DCon
