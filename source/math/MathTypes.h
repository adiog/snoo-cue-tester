// This file is a part of snoo-cue-tester project.
// Copyright 2018 Aleksander Gajewski <adiog@brainfuck.pl>.

#pragma once

#include <array>
#include <cmath>
#include <cstdint>


extern const uint8_t X;
extern const uint8_t Y;
extern const uint8_t Z;

using axis = uint8_t;

using Real = float;

template <typename DegreeType>
float rad(DegreeType deg)
{
    return static_cast<float>(deg) / 180.0F * static_cast<float>(M_PI);
}
