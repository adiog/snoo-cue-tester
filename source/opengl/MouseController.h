// This file is a part of snoo-cue-tester project.
// Copyright 2018 Aleksander Gajewski <adiog@brainfuck.pl>.

#pragma once

#include "Display.h"
#include "OpenGLContext.h"


struct MouseController
{
    enum class MouseButton
    {
        WheelUp = 3,
        WheelDown = 4
    };

    static void mouseWheel(int button, int state, int x, int y)
    {
        MouseButton mouseButton = static_cast<MouseButton>(button);

        if (mouseButton == MouseButton::WheelUp)
        {
            openGLContext.cameraDistance -= openGLContext.cameraDistanceStep;
        }
        else if (mouseButton == MouseButton::WheelDown)
        {
            openGLContext.cameraDistance += openGLContext.cameraDistanceStep;
        }

        Display::redisplay();
    }

    static void mouseCallback(int button, int state, int x, int y)
    {
        openGLContext.old_y = y;
        openGLContext.old_x = x;
        openGLContext.mouse_x = x;
        openGLContext.mouse_y = y;
        mouseWheel(button, state, x, y);
    }

    static void pressedMouseCallback(int x, int y)
    {
        openGLContext.gyaw += 360 + openGLContext.old_x - x;
        openGLContext.gpitch += 360 + openGLContext.old_y - y;
        openGLContext.gyaw %= 360;
        openGLContext.gpitch %= 360;
        openGLContext.old_y = y;
        openGLContext.old_x = x;

        Display::redisplay();
    }

    static void passiveMouseCallback(int x, int y)
    {
        openGLContext.pas_mouse_x = x;
        openGLContext.pas_mouse_y = y;
    }
};
