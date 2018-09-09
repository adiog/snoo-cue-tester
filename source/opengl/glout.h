// This file is a part of snoo-cue-tester project.
// Copyright 2018 Aleksander Gajewski <adiog@brainfuck.pl>.

#pragma once

#include <sstream>
#include <GL/gl.h>
#include <GL/glut.h>
#include <absl/strings/str_split.h>


struct GLFlushContextPreserver
{
    GLFlushContextPreserver()
    {
        // backup current model-view matrix
        glPushMatrix();    // save current modelview matrix
        glLoadIdentity();  // reset modelview matrix

        // set to 2D orthogonal projection
        glMatrixMode(GL_PROJECTION);  // switch to projection matrix
        glPushMatrix();               // save current projection matrix
        glLoadIdentity();             // reset projection matrix
        gluOrtho2D(0, 640, 0, 480);   // set to orthogonal projection
    }

    ~GLFlushContextPreserver()
    {
        // restore projection matrix
        glPopMatrix();  // restore to previous projection matrix

        // restore modelview matrix
        glMatrixMode(GL_MODELVIEW);  // switch to modelview matrix
        glPopMatrix();               // restore to previous modelview matrix
    }
};

struct GLLineContextPreserver
{
    GLLineContextPreserver()
    {
        glPushAttrib(GL_LIGHTING_BIT | GL_CURRENT_BIT);  // lighting and color mask
        glDisable(GL_LIGHTING);                          // need to disable lighting for proper text color
        glDisable(GL_TEXTURE_2D);
        glDepthFunc(GL_ALWAYS);
    }

    ~GLLineContextPreserver()
    {
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_LIGHTING);
        glDepthFunc(GL_LEQUAL);
        glPopAttrib();
    }
};

struct glout
{
    glout()
            : column(0)
            , row(0)
            , textBuffer{}
    {
        resetCaret();
    }

    ~glout()
    {
        flush();
    }

    void flush()
    {
        GLFlushContextPreserver contextPreserver;

        auto splitBuffer = absl::StrSplit(textBuffer.str(), absl::ByChar('\n'));

        for (auto& line : splitBuffer)
        {
            drawLine(line);
        }
        textBuffer.str("");
        resetCaret();
    }

    template <typename T>
    glout& operator<<(const T lineElement)
    {
        textBuffer << lineElement;
        return *this;
    }

private:
    void resetCaret()
    {
        column = 0;
        row = 0;
    }

    template <typename T>
    void drawLine(const T& line)
    {
        drawString(line, row, column);
        row++;
    }

    template <typename T>
    void drawString(const T& str, int row, int column)
    {
        GLLineContextPreserver contextPreserver;
        void* font = GLUT_BITMAP_8_BY_13;
        float color[4] = {1, 1, 1, 1};
        const int TEXT_WIDTH = 8;
        const int TEXT_HEIGHT = 13;
        const int xOffset = TEXT_HEIGHT;
        const int yOffset = TEXT_HEIGHT;
        int y = xOffset + row * TEXT_HEIGHT;
        int x = yOffset + column * TEXT_WIDTH;
        glColor4fv(color);
        glRasterPos2i(x, y);

        for (auto c : str)
        {
            glutBitmapCharacter(font, c);
        }
    }

private:
    int column;
    int row;
    std::stringstream textBuffer;
};