
#pragma once

#include <AzCore/EBus/EBus.h>
#include <AzCore/Interface/Interface.h>

namespace ScriptCanvasO3DCon
{
    class ScriptCanvasO3DConRequests
    {
    public:
        AZ_RTTI(ScriptCanvasO3DConRequests, "{769B2B2B-A5EC-4D56-A77F-251698A4835C}");
        virtual ~ScriptCanvasO3DConRequests() = default;
        // Put your public methods here
    };
    
    class ScriptCanvasO3DConBusTraits
        : public AZ::EBusTraits
    {
    public:
        //////////////////////////////////////////////////////////////////////////
        // EBusTraits overrides
        static constexpr AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Single;
        static constexpr AZ::EBusAddressPolicy AddressPolicy = AZ::EBusAddressPolicy::Single;
        //////////////////////////////////////////////////////////////////////////
    };

    using ScriptCanvasO3DConRequestBus = AZ::EBus<ScriptCanvasO3DConRequests, ScriptCanvasO3DConBusTraits>;
    using ScriptCanvasO3DConInterface = AZ::Interface<ScriptCanvasO3DConRequests>;

} // namespace ScriptCanvasO3DCon
