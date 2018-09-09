// This file is a part of snoo-cue-tester project.
// Copyright 2018 Aleksander Gajewski <adiog@brainfuck.pl>.

#pragma once

#include <opengl/ContextPreserver.h>


struct Axis
{
    static void render()
    {
        ContextPreserver contextPreserver;
        glLoadIdentity();
        glPointSize(5.0);
        glBegin(GL_POINTS);
        glColor3f(1, 1, 1);
        glVertex3f(0.0F, 0.0F, 0.0F);
        glColor3f(1, 0, 0);
        glVertex3f(0.2F, 0.0F, 0.0F);
        glVertex3f(0.4F, 0.0F, 0.0F);
        glVertex3f(0.6F, 0.0F, 0.0F);
        glVertex3f(0.8F, 0.0F, 0.0F);
        glVertex3f(1.0F, 0.0F, 0.0F);
        glColor3f(0, 1, 0);
        glVertex3f(0.0F, 0.2F, 0.0F);
        glVertex3f(0.0F, 0.4F, 0.0F);
        glVertex3f(0.0F, 0.6F, 0.0F);
        glVertex3f(0.0F, 0.8F, 0.0F);
        glVertex3f(0.0F, 1.0F, 0.0F);
        glColor3f(0, 0, 1);
        glVertex3f(0.0F, 0.0F, 0.2F);
        glVertex3f(0.0F, 0.0F, 0.4F);
        glVertex3f(0.0F, 0.0F, 0.6F);
        glVertex3f(0.0F, 0.0F, 0.8F);
        glVertex3f(0.0F, 0.0F, 1.0F);
        glEnd();
    }
};