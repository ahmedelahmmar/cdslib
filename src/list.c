/**
 * @file list.h
 * @author Ahmed Alaa
 * @date 1 Mar 2024
 */


#include "list.h"


void vListCreate(list_t **ppxHead, const uint32_t ulValue)
{
    if (ppxHead)
    {
        *ppxHead = (list_t*)malloc(sizeof(list_t));

        if (*ppxHead)
        {
            (*ppxHead)->ulKey = ulValue;
            (*ppxHead)->pxNext = NULL;
        }
    }
}



void vListDestroy(list_t **ppxHead)
{   
    if (ppxHead && *ppxHead)
    {
        list_t *pxPrevious = NULL;
        list_t *pxCurrent = *ppxHead;

        while (pxCurrent->pxNext)
        {
            pxPrevious = pxCurrent;
            pxCurrent = pxCurrent->pxNext;

            free(pxPrevious);
        }

        free(pxCurrent);
    }
}   



void vListInsert(list_t **ppxHead, const uint32_t ulIndex, const uint32_t ulValue)
{
    if (ppxHead)
    {
        if (*ppxHead)
        {
            list_t *pxPrevious = (0 == ulIndex) ? NULL : pxListGetIndex(ppxHead, ulIndex - 1);
            list_t *pxNew;
            
            /* Allocate memory for a new node and let pxNew point to it */
            vListCreate(&pxNew, ulValue);

            if (pxNew)
            {
                if (pxPrevious)
                {
                    /* if the new node is going to be anywhere in the middle or at the end of the list */
                    pxNew->pxNext = pxPrevious->pxNext;
                    pxPrevious->pxNext = pxNew;
                }
                else
                {
                    /* if the new node is going to be the new head */
                    pxNew->pxNext = *ppxHead;
                    *ppxHead = pxNew;
                }
            }
        }
        else
        {
            /* The program reaches this block if tried to insert a node into an empty list */
            vListCreate(ppxHead, ulValue);
        }
    }
}


void vListRemoveIndex(list_t **ppxHead, const uint32_t ulIndex)
{
    if (ppxHead && *ppxHead)
    {
        list_t *pxPrevious = (0 == ulIndex) ? NULL : pxListGetIndex(ppxHead, ulIndex - 1);
        list_t *pxCurrent = (NULL == pxPrevious) ? *ppxHead : pxPrevious->pxNext;

        if (pxPrevious)
        {
            pxPrevious->pxNext = pxPrevious->pxNext->pxNext;
        }
        else
        {
            *ppxHead = (*ppxHead)->pxNext;
        }
        
        free(pxCurrent);
    }
}


void vListRemoveValue(list_t **ppxHead, const uint32_t ulValue)
{
    if (ppxHead && *ppxHead)
    {
        list_t *pxPrevious = NULL;
        list_t *pxCurrent = *ppxHead;

        while ((ulValue != pxCurrent->ulKey) && pxCurrent->pxNext)
        {
            pxPrevious = pxCurrent;
            pxCurrent = pxCurrent->pxNext;
        }

        if (ulValue == pxCurrent->ulKey)
        {
            if (pxPrevious)
            {
                pxPrevious->pxNext = pxCurrent->pxNext;
            }
            else 
            {
                *ppxHead = pxCurrent->pxNext;
            }

            free(pxCurrent);
        }
    }
}


list_t* pxListGetIndex(list_t **ppxHead, const uint32_t ulIndex)
{   
    list_t *pxReturn = NULL;

    if (ppxHead && *ppxHead)
    {   
        list_t *pxCurrent = *ppxHead;

        uint32_t ulCounter = 0;
        while ((ulCounter++ < ulIndex) && pxCurrent->pxNext)
        {   
            pxCurrent = pxCurrent->pxNext;
        }

        pxReturn = pxCurrent;
    }

    return pxReturn;
}


list_t* pxListGetValue(list_t **ppxHead, const uint32_t ulValue)
{
    list_t *pxReturn = NULL;

    if (ppxHead && *ppxHead)
    {
        list_t *pxCurrent = *ppxHead;

        while ((ulValue != pxCurrent->ulKey) && pxCurrent->pxNext)
        {
            pxCurrent = pxCurrent->pxNext;
        }

        if (ulValue == pxCurrent->ulKey)
        {
            pxReturn = pxCurrent;
        }
    }

    return pxReturn;
}