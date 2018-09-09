// This file is a part of snoo-cue-tester project.
// Copyright 2018 Aleksander Gajewski <adiog@brainfuck.pl>.

#pragma once

#include "OpenGLContext.h"
#include "OrbitCamera.h"
#include "glout.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>


struct Display
{
    static void intialization()
    {
        glDepthFunc(GL_LEQUAL);
        glEnable(GL_DEPTH_TEST);
    }

    static void rashape(int width, int height)
    {
        openGLContext.gwidth = width;
        openGLContext.gheight = height;

        glViewport(0, 0, width, height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        if (width <= height)
        {
            glOrtho(-8.0,
                    8.0,
                    -8.0 * (GLfloat)height / (GLfloat)width,
                    8.0 * (GLfloat)height / (GLfloat)width,
                    -200,
                    200);
        }
        else
        {
            glOrtho(-7.0 * (GLfloat)width / (GLfloat)height,
                    7.0 * (GLfloat)width / (GLfloat)height,
                    -7.0,
                    7.0,
                    -200,
                    200);
        }

        gluPerspective(1.0, (float)width / height, 1.0, 30.0);

        OrbitCamera::updateCamera(openGLContext.gyaw, openGLContext.gpitch, openGLContext.cameraDistance, openGLContext.cam, openGLContext.top);

        glMatrixMode(GL_MODELVIEW);
    }

    static void redisplay()
    {
        rashape(openGLContext.gwidth, openGLContext.gheight);
        glutPostRedisplay();
    }

    static void display()
    {
        //glClearColor(0.4, 0.8, 0.4, 0.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        glColor3f(0.0, 0.0, 0.0);

        {
            openGLContext.scene.render();
        }
        {
            glout& out = openGLContext.out;
            out << "Window dimension: " << openGLContext.gwidth << " " << openGLContext.gheight << '\n';
            out << "mouseCallback: " << openGLContext.mouse_x << " " << openGLContext.mouse_y << '\n';
            out << "mousePressedCallback: " << openGLContext.old_x << " " << openGLContext.old_y << '\n';
            out << "passiveMouseCallback: " << openGLContext.pas_mouse_x << " " << openGLContext.pas_mouse_y << '\n';
            out << "camera position: " << openGLContext.cam[0] << " " << openGLContext.cam[1] << " " << openGLContext.cam[2] << '\n';
            out << "camera top: " << openGLContext.top[0] << " " << openGLContext.top[1] << " " << openGLContext.top[2] << '\n';
            out << "yaw pitch: " << (openGLContext.gyaw % 360) << "deg " << (openGLContext.gpitch % 360) << "deg\n";
            out << "cameraDistance: " << openGLContext.cameraDistance << '\n';
            out << "keyboard character: " << openGLContext.lastKey << " (" << (int)openGLContext.lastKey << ")\n";
            for (const auto& arrow : openGLContext.scene.layout.segmentLayout)
            {
                out << "["
                    << arrow.second[0] << ", "
                    << arrow.second[1] << ", "
                    << arrow.second[2] << ", "
                    << arrow.second[3]
                    << "] " << '\n';
            }
            out.flush();
        }

        glFlush();
        glutSwapBuffers();
    }
};
