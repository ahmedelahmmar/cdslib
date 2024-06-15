/**
 * @file stack.c
 * @author Ahmed Alaa
 * @date 15 Jun 2024
 */


#include "stack.h"



void vStackPush(StackTop_t *pxTop, uint32_t ulKey)
{
    vListInsertNode(pxTop, 0, ulKey);
}



uint32_t ulStackPop(StackTop_t *pxTop)
{
    uint32_t ulReturn = ulStackTop(pxTop);

    if (STACK_NULL_TOP_MAGIC_VALUE != ulReturn)
    {
        vListRemoveNodeAtIndex(pxTop, 0);
    }

    return ulReturn;
}



uint32_t ulStackTop(StackTop_t *pxTop)
{
    uint32_t ulReturn = STACK_NULL_TOP_MAGIC_VALUE;
    
    if (!ucStackIsStackEmpty(pxTop))
    {
        ulReturn = (*pxTop)->ulKey;
    }

    return ulReturn;
}



uint8_t ucStackIsStackEmpty(StackTop_t *pxTop)
{
    return (NULL == *pxTop);
}



void vStackDestroyStack(StackTop_t *pxTop)
{
    vListDestroyList(pxTop);
}