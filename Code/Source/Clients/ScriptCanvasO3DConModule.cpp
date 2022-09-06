

#include <ScriptCanvasO3DConModuleInterface.h>
#include "ScriptCanvasO3DConSystemComponent.h"



namespace ScriptCanvasO3DCon
{
    class ScriptCanvasO3DConModule
        : public ScriptCanvasO3DConModuleInterface
    {
    public:
        AZ_RTTI(ScriptCanvasO3DConModule, "{45EF915D-1F71-47AF-A7B2-8CA0E9AA3CC4}", ScriptCanvasO3DConModuleInterface);
        AZ_CLASS_ALLOCATOR(ScriptCanvasO3DConModule, AZ::SystemAllocator, 0);
    };
}// namespace ScriptCanvasO3DCon

AZ_DECLARE_MODULE_CLASS(Gem_ScriptCanvasO3DCon, ScriptCanvasO3DCon::ScriptCanvasO3DConModule)
