

ly_add_target(
    NAME ScriptCanvasGameplay.Object OBJECT
    NAMESPACE ScriptCanvasNodes
    FILES_CMAKE
        ScriptCanvasGameplay_files.cmake
    INCLUDE_DIRECTORIES
        PRIVATE
            Source
        PUBLIC
            Include
    BUILD_DEPENDENCIES
        PUBLIC
            AZ::AzCore
            AZ::AzFramework
            Gem::ScriptCanvas
            Gem::ScriptCanvas.Extensions
            Gem::PhysX.Static
    AUTOGEN_RULES
        *.ScriptCanvasNodeable.xml,ScriptCanvasNodeable_Header.jinja,$path/$fileprefix.generated.h
        *.ScriptCanvasNodeable.xml,ScriptCanvasNodeable_Source.jinja,$path/$fileprefix.generated.cpp
        *.ScriptCanvasNodeable.xml,ScriptCanvasNodeableRegistry_Header.jinja,$path/$fileprefix_Nodeables.generated.h
        *.ScriptCanvasNodeable.xml,ScriptCanvasNodeableRegistry_Source.jinja,$path/$fileprefix_Nodeables.generated.cpp
)

set (dependent_targets GameplayGem.Private.Object;GameplayGem;GameplayGem.Editor)

foreach (dependent_target IN LISTS dependent_targets)
    if (TARGET ${dependent_target})
        target_link_libraries(${dependent_target} PRIVATE ScriptCanvasNodes::ScriptCanvasGameplay.Object)
    else()
        message(FATAL_ERROR "The target ${dependent_target} was not found, if the gem was not created using scripts/o3de create-gem"
            " you may update dependent_targets to match the corresponding targets in your gem")
    endif()
endforeach()
