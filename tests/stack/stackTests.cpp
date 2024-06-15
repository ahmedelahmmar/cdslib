#include "CppUTest/TestHarness.h"



extern "C"
{
    #include "stack.h"
}



#if 1
TEST_GROUP(stackTests)
{
    StackTop_t xStack;

    void setup(void)
    {
        xStack = NULL;
    }

    void teardown(void)
    {
        /* Free created stack after each test. 
        Tests will fail if memory is allocated inside a test and not freed before exit */
        vStackDestroyStack(&xStack);
    }
};



TEST(stackTests, isEmptyReturnsTrue)
{
    POINTERS_EQUAL(NULL, xStack);
    CHECK_TRUE(ucStackIsStackEmpty(&xStack));
}



TEST(stackTests, isEmptyReturnsFalse)
{
    vListCreateNode(&xStack, 0);
    CHECK_FALSE(ucStackIsStackEmpty(&xStack));
}



TEST(stackTests, pushInsertsTheCorrectValue)
{
    vStackPush(&xStack, 0xAAAAFFFF);

    LONGS_EQUAL(0xAAAAFFFF, xStack->ulKey);
    POINTERS_EQUAL(NULL, xStack->pxNext);
}



TEST(stackTests, pushInsertsAtHeadOnly)
{
    vStackPush(&xStack, 3);
    vStackPush(&xStack, 2);
    vStackPush(&xStack, 1);

    LONGS_EQUAL(1, xStack->ulKey);
    LONGS_EQUAL(2, xStack->pxNext->ulKey);
    LONGS_EQUAL(3, xStack->pxNext->pxNext->ulKey);
    POINTERS_EQUAL(NULL, xStack->pxNext->pxNext->pxNext);
}



TEST(stackTests, topReturnsMagicValueWhenEmpty)
{
    CHECK_TRUE(ucStackIsStackEmpty(&xStack));
    LONGS_EQUAL(STACK_NULL_TOP_MAGIC_VALUE, ulStackTop(&xStack));
    CHECK_TRUE(ucStackIsStackEmpty(&xStack));
}



TEST(stackTests, topReturnsTopOfStack)
{
    vStackPush(&xStack, 3);
    LONGS_EQUAL(3, ulStackTop(&xStack));

    vStackPush(&xStack, 5);
    LONGS_EQUAL(5, ulStackTop(&xStack));

    vStackPush(&xStack, 0);
    LONGS_EQUAL(0, ulStackTop(&xStack));
}



TEST(stackTests, popReturnsMagicValueOnEmptyStack)
{
    CHECK_TRUE(ucStackIsStackEmpty(&xStack));
    LONGS_EQUAL(STACK_NULL_TOP_MAGIC_VALUE, ulStackPop(&xStack));
    CHECK_TRUE(ucStackIsStackEmpty(&xStack));
}



TEST(stackTests, popRemovesHeadAndReturnsTop)
{
    vStackPush(&xStack, 3);
    vStackPush(&xStack, 2);
    vStackPush(&xStack, 1);
    vStackPush(&xStack, 0);

    LONGS_EQUAL(0, ulStackPop(&xStack));
    LONGS_EQUAL(1, ulStackTop(&xStack));

    LONGS_EQUAL(1, ulStackPop(&xStack));
    LONGS_EQUAL(2, ulStackTop(&xStack));

    LONGS_EQUAL(2, ulStackPop(&xStack));
    LONGS_EQUAL(3, ulStackTop(&xStack));

    LONGS_EQUAL(3, ulStackPop(&xStack));
    LONGS_EQUAL(STACK_NULL_TOP_MAGIC_VALUE, ulStackTop(&xStack));
    CHECK_TRUE(ucStackIsStackEmpty(&xStack));
}

#endif /* Conditional macro to Include/Exclude unit tests in the test run */