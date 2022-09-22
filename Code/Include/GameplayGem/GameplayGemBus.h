
#pragma once

#include <AzCore/EBus/EBus.h>
#include <AzCore/Interface/Interface.h>

namespace GameplayGem
{
    class GameplayGemRequests
    {
    public:
        AZ_RTTI(GameplayGemRequests, "{FAB71F2A-FC2A-4DAA-BE33-97C489388A3A}");
        virtual ~GameplayGemRequests() = default;
        // Put your public methods here
    };
    
    class GameplayGemBusTraits
        : public AZ::EBusTraits
    {
    public:
        //////////////////////////////////////////////////////////////////////////
        // EBusTraits overrides
        static constexpr AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Single;
        static constexpr AZ::EBusAddressPolicy AddressPolicy = AZ::EBusAddressPolicy::Single;
        //////////////////////////////////////////////////////////////////////////
    };

    using GameplayGemRequestBus = AZ::EBus<GameplayGemRequests, GameplayGemBusTraits>;
    using GameplayGemInterface = AZ::Interface<GameplayGemRequests>;

} // namespace GameplayGem
