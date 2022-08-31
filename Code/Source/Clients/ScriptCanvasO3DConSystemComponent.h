
#pragma once

#include <AzCore/Component/Component.h>
#include <AzCore/Component/TickBus.h>
#include <ScriptCanvasO3DCon/ScriptCanvasO3DConBus.h>

namespace ScriptCanvasO3DCon
{
    class ScriptCanvasO3DConSystemComponent
        : public AZ::Component
        , protected ScriptCanvasO3DConRequestBus::Handler
        , public AZ::TickBus::Handler
    {
    public:
        AZ_COMPONENT(ScriptCanvasO3DConSystemComponent, "{E795F2AB-DDE3-4FB0-A846-569918302686}");

        static void Reflect(AZ::ReflectContext* context);

        static void GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided);
        static void GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible);
        static void GetRequiredServices(AZ::ComponentDescriptor::DependencyArrayType& required);
        static void GetDependentServices(AZ::ComponentDescriptor::DependencyArrayType& dependent);

        ScriptCanvasO3DConSystemComponent();
        ~ScriptCanvasO3DConSystemComponent();

    protected:
        ////////////////////////////////////////////////////////////////////////
        // ScriptCanvasO3DConRequestBus interface implementation

        ////////////////////////////////////////////////////////////////////////

        ////////////////////////////////////////////////////////////////////////
        // AZ::Component interface implementation
        void Init() override;
        void Activate() override;
        void Deactivate() override;
        ////////////////////////////////////////////////////////////////////////

        ////////////////////////////////////////////////////////////////////////
        // AZTickBus interface implementation
        void OnTick(float deltaTime, AZ::ScriptTimePoint time) override;
        ////////////////////////////////////////////////////////////////////////
    };

} // namespace ScriptCanvasO3DCon
