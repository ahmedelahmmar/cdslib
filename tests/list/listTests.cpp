#include "CppUTest/TestHarness.h"



extern "C"
{
    #include "list.h"
}



#if 1
TEST_GROUP(listTests)
{
    list_t *pxHead;

    void setup(void)
    {
        pxHead = NULL;
    }
    
    void teardown(void)
    {
        /* Free created lists after each test. 
        Tests will fail if memory is allocated inside a test and not freed before exit */
        if (NULL != pxHead)
        {
            vListDestroyList(&pxHead);
        }
    }
};



TEST(listTests, InitializeHeadWithRandomValue)
{
    vListCreateNode(&pxHead, 12345678);

    CHECK_TRUE(pxHead);
    LONGS_EQUAL(12345678, pxHead->ulKey);
    POINTERS_EQUAL(NULL, pxHead->pxNext);
}



TEST(listTests, InitializeHeadWithMinimumValue)
{
    vListCreateNode(&pxHead, 0);

    CHECK_TRUE(pxHead);
    LONGS_EQUAL(0, pxHead->ulKey);
    POINTERS_EQUAL(NULL, pxHead->pxNext);
}



TEST(listTests, InitializeHeadWithMaximumValue)
{
    vListCreateNode(&pxHead, UINT32_MAX);

    CHECK_TRUE(pxHead);
    LONGS_EQUAL(UINT32_MAX, pxHead->ulKey);
    POINTERS_EQUAL(NULL, pxHead->pxNext);
}



TEST(listTests, InsertNodeAsTheNewHead)
{
    vListCreateNode(&pxHead, 0);
    /* pxHead -> 0 -> NULL */

    vListInsertNode(&pxHead, 0, 10);
    /* pxHead -> 10 -> 0 -> NULL */

    LONGS_EQUAL(10, pxHead->ulKey);
    LONGS_EQUAL(0, pxHead->pxNext->ulKey);
    POINTERS_EQUAL(NULL, pxHead->pxNext->pxNext);
}



TEST(listTests, InsertNodeAfterHead)
{
    vListCreateNode(&pxHead, 0);
    /* pxHead -> 0 -> NULL */

    vListInsertNode(&pxHead, 1, 10);
    /* pxHead -> 0 -> 10 -> NULL */

    LONGS_EQUAL(0, pxHead->ulKey);
    LONGS_EQUAL(10, pxHead->pxNext->ulKey);
    POINTERS_EQUAL(NULL, pxHead->pxNext->pxNext);
}   



TEST(listTests, InsertNodeAsTheNewTail)
{
    vListCreateNode(&pxHead, 0);
    vListInsertNode(&pxHead, 0, 10);
    vListInsertNode(&pxHead, 0, 20);
    vListInsertNode(&pxHead, 0, 30);
    vListInsertNode(&pxHead, 0, 40);
    /* pxHead -> 40 -> 30 -> 20 -> 10 -> 0 -> NULL */

    vListInsertNode(&pxHead, 5, 50);
    /* pxHead -> 40 -> 30 -> 20 -> 10 -> 0 -> 50 -> NULL*/

    uint32_t ulValues[6] = {40, 30, 20, 10, 0, 50};

    list_t *pxTemp = pxHead;
    for (uint32_t ulCounter = 0; ulCounter < 6; pxTemp = pxTemp->pxNext, ulCounter++)
    {
        LONGS_EQUAL(ulValues[ulCounter], pxTemp->ulKey);
    }

    POINTERS_EQUAL(NULL, pxTemp);
}



TEST(listTests, InsertNodeBeforeTail)
{
    vListCreateNode(&pxHead, 0);
    vListInsertNode(&pxHead, 1, 10);
    vListInsertNode(&pxHead, 1, 20);
    vListInsertNode(&pxHead, 1, 30);
    vListInsertNode(&pxHead, 1, 40);
    /* pxHead -> 0 -> 40 -> 30 -> 20 -> 10 -> NULL */

    vListInsertNode(&pxHead, 4, 420);
    /* pxHead -> 0 -> 40 -> 30 -> 20 -> 420 -> 10 -> NULL */

    uint32_t ulValues[6] = {0, 40, 30, 20, 420, 10};

    list_t *pxTemp = pxHead;
    for (uint32_t ulCounter = 0; ulCounter < 6; pxTemp = pxTemp->pxNext, ulCounter++)
    {
        LONGS_EQUAL(ulValues[ulCounter], pxTemp->ulKey);
    }

    POINTERS_EQUAL(NULL, pxTemp);
}



TEST(listTests, InsertNodeIntoAnEmptyList)
{
    vListInsertNode(&pxHead, 0, 10);

    LONGS_EQUAL(10, pxHead->ulKey);
    POINTERS_EQUAL(NULL, pxHead->pxNext);
}



TEST(listTests, RemoveHeadNode)
{
    vListCreateNode(&pxHead, 10);
    vListInsertNode(&pxHead, 1, 20);
    vListInsertNode(&pxHead, 2, 30);
    /* pxHead -> 10 -> 20 -> 30 -> NULL */

    vListRemoveNodeAtIndex(&pxHead, 0);
    /* pxHead -> 20 -> 30 -> NULL */

    LONGS_EQUAL(20, pxHead->ulKey);
    LONGS_EQUAL(30, pxHead->pxNext->ulKey);
    POINTERS_EQUAL(NULL, pxHead->pxNext->pxNext);
}



TEST(listTests, RemoveTailNode)
{
    vListCreateNode(&pxHead, 25);
    vListInsertNode(&pxHead, 1, 50);
    vListInsertNode(&pxHead, 2, 75);
    /* pxHead -> 25 -> 50 -> 75 -> NULL */
    
    vListRemoveNodeAtIndex(&pxHead, 2);
    /* pxHead -> 25 -> 50 -> NULL */

    LONGS_EQUAL(25, pxHead->ulKey);
    LONGS_EQUAL(50, pxHead->pxNext->ulKey);
    POINTERS_EQUAL(NULL, pxHead->pxNext->pxNext);
}



TEST(listTests, RemoveNormalNode)
{
    vListCreateNode(&pxHead, 0xFFFF);
    vListInsertNode(&pxHead, 1, 0xAAAA);
    vListInsertNode(&pxHead, 2, 0x5555);
    /* pxHead -> 0xFFFF -> 0xAAAA -> 0x5555 -> NULL */
    
    vListRemoveNodeAtIndex(&pxHead, 1);
    /* pxHead -> 0xFFFF -> 0x5555 -> NULL */

    LONGS_EQUAL(0xFFFF, pxHead->ulKey);
    LONGS_EQUAL(0x5555, pxHead->pxNext->ulKey);
    POINTERS_EQUAL(NULL, pxHead->pxNext->pxNext);
}



TEST(listTests, RemoveValueOfHead)
{
    vListCreateNode(&pxHead, 0x1111);
    vListInsertNode(&pxHead, 1, 0x2222);
    vListInsertNode(&pxHead, 2, 0x3333);
    /* pxHead -> 0x1111 -> 0x2222 -> 0x3333 -> NULL */
    
    vListRemoveNodeWithValue(&pxHead, 0x1111);
    /* pxHead -> 0x2222 -> 0x3333 -> NULL */

    LONGS_EQUAL(0x2222, pxHead->ulKey);
    LONGS_EQUAL(0x3333, pxHead->pxNext->ulKey);
    POINTERS_EQUAL(NULL, pxHead->pxNext->pxNext);
}



TEST(listTests, RemoveValueOfTail)
{
    vListCreateNode(&pxHead, 0x1111);
    vListInsertNode(&pxHead, 1, 0x2222);
    vListInsertNode(&pxHead, 2, 0x3333);
    /* pxHead -> 0x1111 -> 0x2222 -> 0x3333 -> NULL */
    
    vListRemoveNodeWithValue(&pxHead, 0x3333);
    /* pxHead -> 0x1111 -> 0x2222 -> NULL */

    LONGS_EQUAL(0x1111, pxHead->ulKey);
    LONGS_EQUAL(0x2222, pxHead->pxNext->ulKey);
    POINTERS_EQUAL(NULL, pxHead->pxNext->pxNext);
}



TEST(listTests, RemoveValueRemovesFirstInstanceOnly)
{
    vListCreateNode(&pxHead, 0xAAAA);
    vListInsertNode(&pxHead, 1, 0x5555);
    vListInsertNode(&pxHead, 2, 0xBBBB);
    vListInsertNode(&pxHead, 3, 0x5555);
    /* pxHead -> 0xAAAA -> 0x5555 -> 0xBBBB -> 0x5555 -> NULL */

    vListRemoveNodeWithValue(&pxHead, 0x5555);
    /* pxHead -> 0xAAAA -> 0xBBBB -> 0x5555 -> NULL */

    LONGS_EQUAL(0xAAAA, pxHead->ulKey);
    LONGS_EQUAL(0xBBBB, pxHead->pxNext->ulKey);
    LONGS_EQUAL(0x5555, pxHead->pxNext->pxNext->ulKey);   
    POINTERS_EQUAL(NULL, pxHead->pxNext->pxNext->pxNext);
}



TEST(listTests, RemoveValueDoesNothingIfValueNotFound)
{
    vListCreateNode(&pxHead, 0xAAAA);
    vListInsertNode(&pxHead, 1, 0xBBBB);
    vListInsertNode(&pxHead, 2, 0xCCCC);
    vListInsertNode(&pxHead, 3, 0xDDDD);
    /* pxHead -> 0xAAAA -> 0xBBBB -> 0xCCCC -> 0xDDDD -> NULL */

    vListRemoveNodeWithValue(&pxHead, 0xABCD);
    /* pxHead -> 0xAAAA -> 0xBBBB -> 0xCCCC -> 0xDDDD -> NULL */

    LONGS_EQUAL(0xAAAA, pxHead->ulKey);
    LONGS_EQUAL(0xBBBB, pxHead->pxNext->ulKey);
    LONGS_EQUAL(0xCCCC, pxHead->pxNext->pxNext->ulKey);   
    LONGS_EQUAL(0xDDDD, pxHead->pxNext->pxNext->pxNext->ulKey);
    POINTERS_EQUAL(NULL, pxHead->pxNext->pxNext->pxNext->pxNext);
}



TEST(listTests, GetValueReturnsHead)
{
    vListCreateNode(&pxHead, 0xFFFF);
    vListInsertNode(&pxHead, 1, 0xAAAA);
    /* pxHead -> 0xFFFF -> 0xAAAA -> NULL */

    list_t *pxGetValueReturn = pxListGetNodeWithValue(&pxHead, 0xFFFF);

    POINTERS_EQUAL(pxHead, pxGetValueReturn);
}



TEST(listTests, GetValueReturnsTail)
{
    vListCreateNode(&pxHead, 0xFFFF);
    vListInsertNode(&pxHead, 1, 0xAAAA);
    vListInsertNode(&pxHead, 1, 0x5555);
    /* pxHead -> 0xFFFF -> 0x5555 -> 0xAAAA -> NULL */

    list_t *pxGetValueReturn = pxListGetNodeWithValue(&pxHead, 0xAAAA);

    POINTERS_EQUAL(pxHead->pxNext->pxNext, pxGetValueReturn);
    POINTERS_EQUAL(NULL, pxGetValueReturn->pxNext);
}



TEST(listTests, GetValueReturnsNULLIfValueNotFound)
{
    vListCreateNode(&pxHead, 0x00);
    vListInsertNode(&pxHead, 1, 0x20);
    vListInsertNode(&pxHead, 2, 0x40);
    vListInsertNode(&pxHead, 3, 0x60);
    vListInsertNode(&pxHead, 4, 0x80);
    /* pxHead -> 0x00 -> 0x20 -> 0x40 -> 0x60 -> 0x80 -> NULL */

    list_t *pxGetValueReturn = pxListGetNodeWithValue(&pxHead, 0x70);

    POINTERS_EQUAL(NULL, pxGetValueReturn);
}



TEST(listTests, DestroyingAnEmptyListCausesNoFaults)
{
    POINTERS_EQUAL(NULL, pxHead);

    vListDestroyList(&pxHead);
}



TEST(listTests, DestroyingASingleNodeCausesNoFaults)
{
    vListInsertNode(&pxHead, 0, 0xFFFFFFFF);
    vListDestroyList(&pxHead);
}
#endif /* Conditional macro to Include/Exclude unit tests in the test run */