/**
 * @file list.h
 * @author Ahmed Alaa
 * 
 * @brief Header file for a linked list implementation.
 * 
 * This file defines the structures and functions necessary to work with a linked list.
 * It includes functions for creating and destroying lists, inserting and removing nodes,
 * and accessing nodes by index or value.
 * 
 * @date 1 Mar 2024
 */

#ifndef _LIST_H_
#define _LIST_H_

#include <stdlib.h>
#include <stdint.h>

// Structure representing a node in the linked list
typedef struct node
{
    uint32_t ulKey;        /**< Key value stored in the node */
    struct node *pxNext;   /**< Pointer to the next node */

} list_t;

/**
 * @brief Creates a new linked list with a single node containing the given value.
 *
 * @param ppxHead Pointer to the pointer to the head of the list.
 * @param ulValue Value to be stored in the node.
 */
void vListCreateNode(list_t **ppxHead, const uint32_t ulValue);

/**
 * @brief Destroys the linked list and deallocates memory.
 *
 * @param ppxHead Pointer to the pointer to the head of the list.
 */
void vListDestroyList(list_t **ppxHead);

/**
 * @brief Inserts a new node with the given value at the specified index in the list.
 *
 * @param ppxHead Pointer to the pointer to the head of the list.
 * @param ulIndex Index at which the new node should be inserted.
 * @param ulValue Value to be stored in the new node.
 */
void vListInsertNode(list_t **ppxHead, const uint32_t ulIndex, const uint32_t ulValue);

/**
 * @brief Removes the node at the specified index from the list.
 *
 * @param ppxHead Pointer to the pointer to the head of the list.
 * @param ulIndex Index of the node to be removed.
 */
void vListRemoveNodeAtIndex(list_t **ppxHead, const uint32_t ulIndex);

/**
 * @brief Removes the first node with the given value from the list.
 *
 * @param ppxHead Pointer to the pointer to the head of the list.
 * @param ulValue Value of the node to be removed.
 */
void vListRemoveNodeWithValue(list_t **ppxHead, const uint32_t ulValue);

/**
 * @brief Returns a pointer to the node at the specified index in the list.
 *
 * @param ppxHead Pointer to the pointer to the head of the list.
 * @param ulIndex Index of the node to be retrieved.
 * @return Pointer to the node at the specified index, or NULL if the index is out of range.
 */
list_t* pxListGetNodeAtIndex(list_t **ppxHead, const uint32_t ulIndex);

/**
 * @brief Returns a pointer to the first node with the given value in the list.
 *
 * @param ppxHead Pointer to the pointer to the head of the list.
 * @param ulValue Value of the node to be retrieved.
 * @return Pointer to the first node with the given value, or NULL if the value is not found in the list.
 */
list_t* pxListGetNodeWithValue(list_t **ppxHead, const uint32_t ulValue);

#endif /* _LIST_H_ */
