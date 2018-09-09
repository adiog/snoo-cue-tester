// This file is a part of snoo-cue-tester project.
// Copyright 2018 Aleksander Gajewski <adiog@brainfuck.pl>.


#pragma once

#include <udpbox.h>
#include <SensorData.h>


namespace network {
struct Dispatcher
{
    static float dispatchFloat(const uint8_t* buffer)
    {
        return *reinterpret_cast<const float*>(buffer);
    }

    static sensorFusion::SensorData dispatch(udpbox::Datagram& datagram)
    {
        return sensorFusion::SensorData{
            {
                dispatchFloat(&datagram.payload[0]),
                dispatchFloat(&datagram.payload[4]),
                dispatchFloat(&datagram.payload[8]),
            },
            {
                dispatchFloat(&datagram.payload[12]),
                dispatchFloat(&datagram.payload[16]),
                dispatchFloat(&datagram.payload[20]),
            },
            {
                dispatchFloat(&datagram.payload[24]),
                dispatchFloat(&datagram.payload[28]),
                dispatchFloat(&datagram.payload[32]),
            },
        };
    }
};
}
