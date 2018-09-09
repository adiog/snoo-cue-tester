// This file is a part of snoo-cue-tester project.
// Copyright 2018 Aleksander Gajewski <adiog@brainfuck.pl>.

#pragma once

#include <unordered_map>

#include <glm/glm.hpp>
#include <sensor/Segment.h>


namespace model {
struct Layout
{
    std::unordered_map<sensor::Segment, glm::vec4> segmentLayout;
};
}
