// This file is a part of snoo-cue-tester project.
// Copyright 2018 Aleksander Gajewski <adiog@brainfuck.pl>.

#pragma once

#include "Display.h"
#include <GL/glut.h>


struct ContextMenu
{
    enum class ContextMenuOption
    {
        RESET,
        QUIT,
        CONTEXT_MENU_SIZE
    };

    static void createContextMenu()
    {
        glutCreateMenu(contextMenuCallback);
        glutAddMenuEntry("reset", static_cast<int>(ContextMenuOption::RESET));
        glutAddMenuEntry("quit", static_cast<int>(ContextMenuOption::QUIT));
        glutAttachMenu(GLUT_MIDDLE_BUTTON);
    }

    static void contextMenuCallback(int id)
    {
        switch (static_cast<ContextMenuOption>(id))
        {
            case ContextMenuOption::RESET:
            {
                OrbitCamera::resetCamera();
                Display::redisplay();
                break;
            }
            case ContextMenuOption::QUIT:
            {
                exit(0);
            }
            default:
                break;
        }
    }
};