/**
 * @file queue.h
 * @author Ahmed Alaa
 * 
 * @brief Header file for a linked list implementation of a queue.
 * 
 * This file contains the function declarations for queue operations 
 * implemented using a linked list. The queue supports enqueue, dequeue,
 * checking if it is empty, checking if it is full, and destroying the queue.
 *
 * @date 16 Jun 2024
 */

#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "list.h"

#define QUEUE_EMPTY_QUEUE_MAGIC_VALUE   0xFFFFFFFF

/**
 * @brief Structure representing a queue.
 */
typedef struct
{
    list_t *pxFront;            /**< Pointer to the front node of the queue. */
    list_t *pxBack;             /**< Pointer to the back node of the queue. */
    uint32_t ulQueueMaxSize;    /**< Maximum size of the queue. */
    uint32_t ulQueueCurrentSize;/**< Current size of the queue. */
} Queue_t;

typedef Queue_t* QueueHandle_t;

/**
 * @brief Creates a queue with a specified maximum size.
 *
 * @param ulQueueMaxSize Maximum size of the queue.
 * @return Handle to the created queue.
 */
QueueHandle_t xQueueCreateQueue(uint32_t ulQueueMaxSize);

/**
 * @brief Destroys the queue and deallocates memory.
 *
 * @param pxQueueHandle Pointer to the handle of the queue to be destroyed.
 */
void vQueueDestroyQueue(QueueHandle_t *pxQueueHandle);

/**
 * @brief Adds an element to the back of the queue.
 *
 * @param pxQueueHandle Pointer to the handle of the queue.
 * @param ulKey Value to be enqueued.
 */
void vQueueEnqueue(QueueHandle_t *pxQueueHandle, uint32_t ulKey);

/**
 * @brief Removes an element from the front of the queue.
 *
 * @param pxQueueHandle Pointer to the handle of the queue.
 * @return The value of the dequeued element. If the queue is empty, it returns QUEUE_EMPTY_QUEUE_MAGIC_VALUE.
 */
uint32_t ulQueueDequeue(QueueHandle_t *pxQueueHandle);

/**
 * @brief Checks if the queue is empty.
 *
 * @param pxQueueHandle Pointer to the handle of the queue.
 * @return 1 if the queue is empty, 0 otherwise.
 */
uint8_t ucQueueIsQueueEmpty(QueueHandle_t *pxQueueHandle);

/**
 * @brief Checks if the queue is full.
 *
 * @param pxQueueHandle Pointer to the handle of the queue.
 * @return 1 if the queue is full, 0 otherwise.
 */
uint8_t ucQueueIsQueueFull(QueueHandle_t *pxQueueHandle);

#endif /* _QUEUE_H_ */
