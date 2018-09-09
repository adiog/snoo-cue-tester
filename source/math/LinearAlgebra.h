// This file is a part of snoo-cue-tester project.
// Copyright 2018 Aleksander Gajewski <adiog@brainfuck.pl>.

#pragma once

#include <algorithm>
#include <numeric>

#include <math/MathTypes.h>

namespace math {
glm::mat3 getRotationMatrix(Real angle, axis index);

glm::mat3 getRotationMatrix(glm::vec3 v, axis keepIndex, axis reduceIndex);

glm::mat3 getRotationMatrixReducingYAndX(glm::vec3 v);

/** Returns calibration matrix
 *
 * @param vZ - first calibration vector glm::vec3
 * @param vXZ - second calibration vector glm::vec3
 * @return calibration matrix glm::mat3
 *
 * The calibration matrix is rotation matrix that:
 * - for vZ - supersedes X and Y axis, assuming that result vZ * M has form [0,0,Z]
 * - for vXZ - supersedes Y axis, assuming that result vXZ * M has form [X,0,Z]
 */
glm::mat3 getCalibrationMatrix(glm::vec3 vZ, glm::vec3 vXZ);
}
