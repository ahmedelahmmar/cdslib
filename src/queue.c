/**
 * @file queue.c
 * @author Ahmed Alaa
 * @date 16 Jun 2024
 */



#include "queue.h"



QueueHandle_t xQueueCreateQueue(uint32_t ulQueueMaxSize)
{
    QueueHandle_t xReturn = (QueueHandle_t)malloc(sizeof(Queue_t));

    if (xReturn)
    {
        xReturn->pxFront = NULL;
        xReturn->pxBack = NULL;
        xReturn->ulQueueMaxSize = ulQueueMaxSize;
        xReturn->ulQueueCurrentSize = 0;
    }

    return xReturn;
}



void vQueueDestroyQueue(QueueHandle_t *pxQueueHandle)
{
    if (pxQueueHandle)
    {
        vListDestroyList( &(*pxQueueHandle)->pxFront );
        free(*pxQueueHandle);
        *pxQueueHandle = NULL;
    }
}



void vQueueEnqueue(QueueHandle_t *pxQueueHandle, uint32_t ulKey)
{
    if (pxQueueHandle)
    {
        if (!ucQueueIsQueueFull(pxQueueHandle))
        {
            if (0 == (*pxQueueHandle)->ulQueueCurrentSize)
            {
                vListCreateNode(&(*pxQueueHandle)->pxBack, ulKey);
                
                (*pxQueueHandle)->pxFront = (*pxQueueHandle)->pxBack;
                (*pxQueueHandle)->ulQueueCurrentSize = 1;

                return;
            }

            vListCreateNode(&(*pxQueueHandle)->pxBack->pxNext, ulKey);

            (*pxQueueHandle)->pxBack = (*pxQueueHandle)->pxBack->pxNext;
            (*pxQueueHandle)->ulQueueCurrentSize += 1;
        }
    }
}



uint32_t ulQueueDequeue(QueueHandle_t *pxQueueHandle)
{
    uint32_t ulReturn = QUEUE_EMPTY_QUEUE_MAGIC_VALUE;

    if (pxQueueHandle)
    {
        if (!ucQueueIsQueueEmpty(pxQueueHandle))
        {
            ulReturn = (*pxQueueHandle)->pxFront->ulKey;

            vListRemoveNodeAtIndex(&(*pxQueueHandle)->pxFront, 0);

            (*pxQueueHandle)->ulQueueCurrentSize -= 1;
        }
    }

    return ulReturn;
}



uint8_t ucQueueIsQueueEmpty(QueueHandle_t *pxQueueHandle)
{
    if (pxQueueHandle)
    {
        return (0 == (*pxQueueHandle)->ulQueueCurrentSize);
    }
}



uint8_t ucQueueIsQueueFull(QueueHandle_t *pxQueueHandle)
{
    if (pxQueueHandle)
    {
        return ((*pxQueueHandle)->ulQueueMaxSize == (*pxQueueHandle)->ulQueueCurrentSize);
    }
}