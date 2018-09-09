// This file is a part of snoo-cue-tester project.
// Copyright 2018 Aleksander Gajewski <adiog@brainfuck.pl>.

#include <glm/detail/type_mat.hpp>
#include <glm/detail/type_mat3x3.hpp>
#include "LinearAlgebra.h"


namespace math {
glm::mat3 getRotationMatrix(Real angle, axis index)
{
    glm::mat3 result;
    switch (index)
    {
        case 0:
            result = glm::mat3{
                glm::vec3{1.0, 0.0, 0.0},
                glm::vec3{0.0, cos(angle), -sin(angle)},
                glm::vec3{0.0, sin(angle), cos(angle)}};
            break;
        case 1:
            result = glm::mat3{
                glm::vec3{cos(angle), 0.0, -sin(angle)},
                glm::vec3{0.0, 1.0, 0.0},
                glm::vec3{sin(angle), 0.0, cos(angle)}};
            break;
        case 2:
            result = glm::mat3{
                glm::vec3{cos(angle), -sin(angle), 0.0},
                glm::vec3{sin(angle), cos(angle), 0.0},
                glm::vec3{0.0, 0.0, 1.0}};
            break;
    }
#ifdef DO_NOT_KNOW_HOW_TO_FLOAT
    return preventNan(result);
#else
    return result;
#endif
}

glm::mat3 getRotationMatrix(glm::vec3 v, axis keepIndex, axis reduceIndex)
{
    Real dir = (reduceIndex == Y) ? -1.0F : ((reduceIndex == Z) ? -1.0F : 1.0F);
    Real x = v[reduceIndex];
    Real y = v[0] + v[1] + v[2] - v[reduceIndex] - v[keepIndex];
    Real angle = dir * atan2f(x, y);
    return getRotationMatrix(angle, keepIndex);
}

glm::mat3 getRotationMatrixReducingYAndX(glm::vec3 v)
{
#ifdef DO_NOT_KNOW_HOW_TO_FLOAT
    glm::mat3 supersedeYKeepZRotation = preventNan(getRotationMatrix(v, Z, Y));
    glm::vec3 supersedeYKeepZVector = preventNan(v * supersedeYKeepZRotation);
    glm::mat3 supersedeXRotation = preventNan(getRotationMatrix(supersedeYKeepZVector, Y, X));
    glm::vec3 test = preventNan(supersedeYKeepZVector * supersedeXRotation);
    return preventNan(supersedeYKeepZRotation * supersedeXRotation);
#else
    glm::mat3 supersedeYKeepZRotation = getRotationMatrix(v, Z, Y);
    glm::vec3 supersedeYKeepZVector = v * supersedeYKeepZRotation;
    glm::mat3 supersedeXRotation = getRotationMatrix(supersedeYKeepZVector, Y, X);
    glm::vec3 test = supersedeYKeepZVector * supersedeXRotation;
    return supersedeYKeepZRotation * supersedeXRotation;
#endif
}

glm::mat3 getCalibrationMatrix(glm::vec3 vZ, glm::vec3 vXZ)
{
    glm::mat3 vZCalibrationMatrix = getRotationMatrixReducingYAndX(vZ);
    glm::vec3 vXZSubCalibrated = vXZ * vZCalibrationMatrix;
    glm::mat3 vXZCalibrationMatrix = getRotationMatrix(vXZSubCalibrated, Z, Y);

    return vZCalibrationMatrix * vXZCalibrationMatrix;
}
}