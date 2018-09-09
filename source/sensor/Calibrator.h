// This file is a part of snoo-cue-tester project.
// Copyright 2018 Aleksander Gajewski <adiog@brainfuck.pl>.

#pragma once

#include <math/LinearAlgebra.h>
#include <math/MathTypes.h>

#include <optional>
#include <SensorData.h>
#include <glm/detail/type_mat3x3.hpp>


namespace sensor {

enum class CalibrationStep
{
    NPose,
    SPose
};

class Calibrator
{
public:
    Calibrator()
            : rotationCalibrationMatrix(glm::mat3{})
    {
    }

    void calibrate(glm::vec3 referenceV3, CalibrationStep calibrationStep)
    {
        switch (calibrationStep)
        {
            case CalibrationStep::NPose:
                referenceZCalibrationVector = referenceV3;
                break;
            case CalibrationStep::SPose:
                referenceXZCalibrationVector = referenceV3;
                break;
        }
        if (referenceZCalibrationVector && referenceXZCalibrationVector)
        {
            rotationCalibrationMatrix = math::getCalibrationMatrix(*referenceZCalibrationVector, *referenceXZCalibrationVector);
        }
    }

    sensorFusion::SensorData transform(const sensorFusion::SensorData &rawData)
    {
        sensorFusion::SensorData transformedData;
        transformedData.accelerometer = rawData.accelerometer * rotationCalibrationMatrix;
        transformedData.gyroscope = rawData.gyroscope * rotationCalibrationMatrix;
        transformedData.magnetometer = rawData.magnetometer * rotationCalibrationMatrix;
        return transformedData;
    }

private:
    std::optional<glm::vec3> referenceZCalibrationVector;
    std::optional<glm::vec3> referenceXZCalibrationVector;
    glm::mat3 rotationCalibrationMatrix;
};
}
