// This file is a part of snoo-cue-tester project.
// Copyright 2018 Aleksander Gajewski <adiog@brainfuck.pl>.

#pragma once

#include <udpbox.h>
#include <model/Model.h>


namespace network {
struct Matcher
{
    static sensor::Segment match(const udpbox::Datagram& datagram)
    {
        static std::unordered_map<std::string, sensor::Segment> mapping = {
            std::make_pair(std::string("192.168.42.12"), sensor::Segment::SegmentX),
            std::make_pair(std::string("192.168.42.13"), sensor::Segment::SegmentY),
            std::make_pair(std::string("192.168.42.14"), sensor::Segment::SegmentZ)};

        if (mapping.find(datagram.sender) == mapping.end())
        {
            return sensor::Segment::UNKNOWN;
        }
        else
        {
            return mapping[datagram.sender];
        }
    }
};
}
