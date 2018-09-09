// This file is a part of snoo-cue-tester project.
// Copyright 2018 Aleksander Gajewski <adiog@brainfuck.pl>.

#include "googletest"


TEST(suite, case)
{
    // given
    int two = 2;

    // when
    int result = two * two;

    // then
    EXPECT_EQ(result, 4);
}


GTEST_MAIN()
