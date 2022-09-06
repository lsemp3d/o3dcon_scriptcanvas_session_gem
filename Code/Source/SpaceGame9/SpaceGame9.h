/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#pragma once

#include <SpaceGame9.generated.h>
#include <ScriptCanvas/CodeGen/NodeableCodegen.h>
#include <ScriptCanvas/Core/Node.h>
#include <ScriptCanvas/Core/Nodeable.h>

#include <AutoGenNodeableRegistry.generated.h>

namespace ScriptCanvas::Nodes
{
    class SpaceGame9
        : public Nodeable
    {
        SCRIPTCANVAS_NODE(SpaceGame9);
    public:
        SpaceGame9() = default;

    };
}
