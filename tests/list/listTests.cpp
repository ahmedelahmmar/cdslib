#include "CppUTest/TestHarness.h"

extern "C"
{
    #include "list.h"
}

#if 1

TEST_GROUP(listTests)
{
    void setup(void);
    void teardown(void);
};


#endif /* Conditional macro to Include/Exclude unit tests */