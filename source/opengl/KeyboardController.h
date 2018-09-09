// This file is a part of snoo-cue-tester project.
// Copyright 2018 Aleksander Gajewski <adiog@brainfuck.pl>.

#pragma once


struct KeyboardController
{
    static void keyboardCallback(unsigned char key, int x, int y)
    {
        if (key == 'n')
        {
            std::cout << "NORMAL" << std::endl;
            openGLContext.sampleModel[sensor::Segment::SegmentY].calibrate(sensor::CalibrationStep::NPose);
        }
        else
        if (key == 's')
        {
            openGLContext.sampleModel[sensor::Segment::SegmentY].calibrate(sensor::CalibrationStep::SPose);
            std::cout << "SQUAD" << std::endl;
        }
        else
        if (key == 'q')
        {
            exit(0);
        }
        else
        {
            openGLContext.lastKey = key;
        }
        Display::redisplay();
    }
};
