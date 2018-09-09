// This file is a part of snoo-cue-tester project.
// Copyright 2018 Aleksander Gajewski <adiog@brainfuck.pl>.

#pragma once

#include <GL/glu.h>


namespace opengl {
struct Quad
{
    Quad()
    {
        gluObject = gluNewQuadric();
        gluQuadricTexture(gluObject, GL_TRUE);
        gluQuadricDrawStyle(gluObject, GLU_FILL);
    }

    ~Quad()
    {
        gluDeleteQuadric(gluObject);
    }

    Quad(const Quad&) = delete;
    Quad& operator=(const Quad&) = delete;

    Quad(Quad&& quad) noexcept
    {
        this->gluObject = quad.gluObject;
        quad.gluObject = nullptr;
    }
    Quad& operator=(Quad&& quad) noexcept
    {
        this->gluObject = quad.gluObject;
        quad.gluObject = nullptr;
    }

    GLUquadricObj* get() { return gluObject; }

    GLUquadricObj* gluObject = nullptr;
};
}