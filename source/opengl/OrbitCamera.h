// This file is a part of snoo-cue-tester project.
// Copyright 2018 Aleksander Gajewski <adiog@brainfuck.pl>.

#pragma once

#include "OpenGLContext.h"
#include <GL/glu.h>
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <math/MathTypes.h>


struct OrbitCamera
{
    static void resetCamera()
    {
        openGLContext.gyaw = 90;
        openGLContext.gpitch = 180;
        openGLContext.cameraDistance = 25.0;
    }

    // yaw in (0, 360)
    // pitch in (-90,90)
    static void updateCamera(Real yaw, Real pitch, Real zoom, glm::vec3 &cam, glm::vec3 &top)
    {
        glm::vec3 center{0.0, 1.0, 0.0};
        glm::vec3 init{1.0, 0.0, 0.0};
        glm::vec3 cameraPositionXZ = glm::rotateY(init, rad(yaw));
        glm::vec3 cameraPositionXZPerpendicular = glm::rotateY(init, rad(yaw + 90.0));
        glm::vec3 cameraPositionNormalized = glm::rotate(cameraPositionXZ, rad(pitch), cameraPositionXZPerpendicular);
        glm::vec3 cameraUp = glm::rotate(cameraPositionXZ, rad(pitch + 90.0), cameraPositionXZPerpendicular);
        glm::vec3 cameraPosition = cameraPositionNormalized * zoom + center;
        glm::vec3 cameraDirection = cameraPositionNormalized * -1.0F + center;
        cam = cameraPosition;
        top = cameraUp;
        gluLookAt(
            cameraPosition[0],
            cameraPosition[1],
            cameraPosition[2],
            cameraDirection[0],
            cameraDirection[1],
            cameraDirection[2],
            cameraUp[0],
            cameraUp[1],
            cameraUp[2]);
    }
};