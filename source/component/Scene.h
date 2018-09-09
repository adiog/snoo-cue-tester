// This file is a part of snoo-cue-tester project.
// Copyright 2018 Aleksander Gajewski <adiog@brainfuck.pl>.

#pragma once

#include "Bone.h"
#include <component/Axis.h>
#include <component/Floor.h>
#include <model/Layout.h>
#include <opengl/ContextPreserver.h>


namespace component {
struct Scene
{
    Floor floor;
    Bone bone;

    model::Layout layout;

    Scene()
            : bone(sensor::Segment::SegmentX, 0.30F, 0.4F)
    {
    }

    void apply(model::Layout&& newLayout)
    {
        layout = newLayout;
    }

    void render()
    {
        Axis::render();
        floor.render();
        bone.render(layout);
    }
};
}