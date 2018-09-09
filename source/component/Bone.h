// This file is a part of snoo-cue-tester project.
// Copyright 2018 Aleksander Gajewski <adiog@brainfuck.pl>.

#pragma once

#include <GL/glu.h>
#include <glm/gtx/rotate_vector.hpp>
#include <math/MathTypes.h>
#include <model/Layout.h>
#include <glm/gtc/type_ptr.hpp>
#include <opengl/Quad.h>
#include <opengl/ContextPreserver.h>

namespace component {
class Bone
{
public:
    static constexpr const Real thicknessRatio = 0.20;
    Real thickness;
    Real lengthPart;
    Real lengthRemain;

    Bone(sensor::Segment segment, Real length, Real weight)
            : segment(segment)
            , length(length)
            , weight(weight)
    {
        thickness = length * thicknessRatio;
        lengthPart = length * weight;
        lengthRemain = length * (1.0F - weight);
    }

    Real getThickness()
    {
        return thickness;
    }

    Real getThicknessOffset()
    {
        return lengthPart;
    }

    void rotate(const model::Layout& layout)
    {
        auto it = layout.segmentLayout.find(segment);
        if (it != layout.segmentLayout.end())
        {
            auto& q4 = it->second;

            float x = q4[0];
            float y = q4[1];
            float z = q4[2];
            float roll = q4[3];

            float pitch = atan2(x, sqrt(z * z + y * y));
            /*
            float yaw = atan2(y, x);

            glm::vec3 init{1.0, 0.0, 0.0};
            glm::vec3 positionXZ = glm::rotateY(init, rad(yaw));
            glm::vec3 positionXZPerpendicular = glm::rotateY(init, rad(yaw + 90.0));
            glm::vec3 positionNormalized = glm::rotate(positionXZ, rad(pitch), positionXZPerpendicular);
*/

            float yangle = 90-glm::degrees(pitch);
            if (yangle != 0)
            {
                glRotatef(yangle, 0, 1, 0);
            }
            /*
            if (y != 0)
            {
                glRotatef(-y, 0, 1, 0);
            }
            if (z != 0)
            {
                glRotatef(z, 0, 0, 1);
            }*/
            /*
            glRotatef(glm::degrees(yaw), 0, 0, 1);
            glRotatef(glm::degrees(pitch),
                      positionXZPerpendicular[0],
                      positionXZPerpendicular[1],
                      positionXZPerpendicular[2]);
            glRotatef(glm::degrees(q4[3]),
                      positionNormalized[0],
                      positionNormalized[1],
                      positionNormalized[2]);*/
        }
    }

    void triangle(glm::vec3 aVertex, glm::vec3 bVertex, glm::vec3 cVertex, uint8_t *aColor, uint8_t * bColor, uint8_t *cColor)
    {
        glBegin(GL_TRIANGLES);
        glColor4ubv(aColor);
        glVertex3fv(glm::value_ptr(aVertex));
        glColor4ubv(bColor);
        glVertex3fv(glm::value_ptr(bVertex));
        glColor4ubv(cColor);
        glVertex3fv(glm::value_ptr(cVertex));
        glEnd();
    }

    void render(const model::Layout& layout)
    {
        ContextPreserver contextPreserver;
        glTranslatef(0, 1.0, 0);
        rotate(layout);
        gluSphere(quads[2].get(), 0.02, 20, 50);

        uint8_t colors[][3] =
                /*
            {
                {0x59, 0xc3, 0xc3},
                {0x52, 0x48, 0x9c},
                {0x84, 0xa9, 0x8c},
                {0xeb, 0xeb, 0xeb},
                {0xca, 0xd2, 0xc5}};*/
        {
        {0xcf, 0x5c, 0x36},
        {0xee, 0xe5, 0xe9},
        {0x7c, 0x7c, 0x7c},
        {0xef, 0xc8, 0x8b}};

            int C = 4;

        glm::vec3 zero = {0, 0, 0};

        glm::vec3 verticesTop[] = {
            {-thickness, -thickness, lengthPart},
            {-thickness, thickness, lengthPart},
            {thickness, thickness, lengthPart},
            {thickness, -thickness, lengthPart}};

        for(int i = 0; i < 4; i++)
        {
            triangle(zero, verticesTop[i%4], verticesTop[(i+1)%4], colors[i%C], colors[(i+1)%C], colors[(i+2)%C]);
        }

        glTranslatef(0.0, 0.0, length);

        glm::vec3 verticesBottom[] = {
                {-thickness, -thickness, -lengthRemain},
                {-thickness, thickness, -lengthRemain},
                {thickness, thickness, -lengthRemain},
                {thickness, -thickness, -lengthRemain}};

        for(int i = 0; i < 4; i++)
        {
            triangle(zero, verticesBottom[i%4], verticesBottom[(i+1)%4], colors[(i+1)%C], colors[(i+2)%C], colors[i%C]);
        }
    }

    void follow(const model::Layout& layout)
    {
        rotate(layout);
        glTranslatef(0.0, 0.0, length);
    }

private:
    sensor::Segment segment;
    Real length;
    Real weight;

    opengl::Quad quads[3];
};
}