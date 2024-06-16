#include "CppUTest/TestHarness.h"



extern "C"
{
    #include "queue.h"
}


#if 1
TEST_GROUP(queueTests)
{
    QueueHandle_t xQueue;

    void setup(void)
    {
        xQueue = xQueueCreateQueue(3);
    }

    void teardown(void)
    {
        vQueueDestroyQueue(&xQueue);
    }
};



TEST(queueTests, QueueCreationInitializesCorrectValues)
{
    CHECK_FALSE(NULL == xQueue);
    POINTERS_EQUAL(NULL, xQueue->pxFront);
    POINTERS_EQUAL(NULL, xQueue->pxBack);
    LONGS_EQUAL(3, xQueue->ulQueueMaxSize);
    LONGS_EQUAL(0, xQueue->ulQueueCurrentSize);
}



TEST(queueTests, IsQueueEmptyReturnsTrue)
{
    CHECK_TRUE(ucQueueIsQueueEmpty(&xQueue));
}



TEST(queueTests, IsQueueFullReturnsFalse)
{
    CHECK_FALSE(ucQueueIsQueueFull(&xQueue));
}



TEST(queueTests, EnqueueFirstElement)
{
    vQueueEnqueue(&xQueue, 10);

    LONGS_EQUAL(10, xQueue->pxFront->ulKey);
    POINTERS_EQUAL(xQueue->pxFront, xQueue->pxBack);
    POINTERS_EQUAL(NULL, xQueue->pxBack->pxNext);
    LONGS_EQUAL(1, xQueue->ulQueueCurrentSize);
}



TEST(queueTests, IsFullAndIsEmptyReturnFalse)
{
    vQueueEnqueue(&xQueue, 10);

    CHECK_FALSE(ucQueueIsQueueEmpty(&xQueue));
    CHECK_FALSE(ucQueueIsQueueFull(&xQueue));
}



TEST(queueTests, EnqueueInsertsAtBack)
{
    vQueueEnqueue(&xQueue, 10);
    vQueueEnqueue(&xQueue, 20);

    LONGS_EQUAL(10, xQueue->pxFront->ulKey);
    LONGS_EQUAL(20, xQueue->pxBack->ulKey);
    POINTERS_EQUAL(NULL, xQueue->pxFront->pxNext->pxNext);
    LONGS_EQUAL(2, xQueue->ulQueueCurrentSize);
}



TEST(queueTests, EnqueueDoesNothingWhenFull)
{
    vQueueEnqueue(&xQueue, 10);
    vQueueEnqueue(&xQueue, 20);
    vQueueEnqueue(&xQueue, 30);
    vQueueEnqueue(&xQueue, 40);
    vQueueEnqueue(&xQueue, 50);
    
    LONGS_EQUAL(3, xQueue->ulQueueCurrentSize);
}



TEST(queueTests, IsFullReturnsTrue)
{
    vQueueEnqueue(&xQueue, 10);
    vQueueEnqueue(&xQueue, 20);
    vQueueEnqueue(&xQueue, 30);

    CHECK_TRUE(ucQueueIsQueueFull(&xQueue));
}



TEST(queueTests, DequeuReturnsMagicValueWhenEmpty)
{
    LONGS_EQUAL(QUEUE_EMPTY_QUEUE_MAGIC_VALUE, ulQueueDequeue(&xQueue));
}



TEST(queueTests, DequeueRemovesFront)
{
    vQueueEnqueue(&xQueue, 10);
    vQueueEnqueue(&xQueue, 20);
    vQueueEnqueue(&xQueue, 30);

    LONGS_EQUAL(3, xQueue->ulQueueCurrentSize);

    LONGS_EQUAL(10, ulQueueDequeue(&xQueue));
    LONGS_EQUAL(20, xQueue->pxFront->ulKey);
    LONGS_EQUAL(30, xQueue->pxBack->ulKey);
    POINTERS_EQUAL(NULL, xQueue->pxFront->pxNext->pxNext);

    LONGS_EQUAL(2, xQueue->ulQueueCurrentSize);
}



TEST(queueTests, MultipleDequeuesFollowFIFO)
{
    vQueueEnqueue(&xQueue, 10);
    vQueueEnqueue(&xQueue, 20);
    vQueueEnqueue(&xQueue, 30);

    LONGS_EQUAL(10, ulQueueDequeue(&xQueue));
    LONGS_EQUAL(20, ulQueueDequeue(&xQueue));
    LONGS_EQUAL(30, ulQueueDequeue(&xQueue));
    LONGS_EQUAL(QUEUE_EMPTY_QUEUE_MAGIC_VALUE, ulQueueDequeue(&xQueue));
    
    LONGS_EQUAL(0, xQueue->ulQueueCurrentSize);
}
#endif /* Conditional macro to Include/Exclude unit tests in the test run */