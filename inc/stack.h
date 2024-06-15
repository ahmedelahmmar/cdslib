/**
 * @file stack.h
 * @author Ahmed Alaa
 * 
 * @brief Header file for a linked list implementation of stack.
 * 
 * This file contains the function declarations for stack operations 
 * implemented using a linked list. The stack supports push, pop, 
 * top (peek), checking if it is empty, and destroying the stack.
 *
 * @date 15 Jun 2024
 */

#ifndef _STACK_H_
#define _STACK_H_

#include "list.h"

#define STACK_NULL_TOP_MAGIC_VALUE    0xFFFFFFFF

typedef list_t* StackTop_t;

/**
 * @brief Pushes an element onto the stack.
 *
 * @param pxTop Pointer to the top of the stack.
 * @param ulKey Value to be pushed onto the stack.
 */
void vStackPush(StackTop_t *pxTop, uint32_t ulKey);

/**
 * @brief Pops an element from the stack.
 *
 * @param pxTop Pointer to the top of the stack.
 * @return The value of the popped element. If the stack is empty, it returns STACK_NULL_TOP_MAGIC_VALUE.
 */
uint32_t ulStackPop(StackTop_t *pxTop);

/**
 * @brief Returns the top element of the stack without removing it.
 *
 * @param pxTop Pointer to the top of the stack.
 * @return The value of the top element. If the stack is empty, it returns STACK_NULL_TOP_MAGIC_VALUE.
 */
uint32_t ulStackTop(StackTop_t *pxTop);

/**
 * @brief Checks if the stack is empty.
 *
 * @param pxTop Pointer to the top of the stack.
 * @return 1 if the stack is empty, 0 otherwise.
 */
uint8_t ucStackIsStackEmpty(StackTop_t *pxTop);

/**
 * @brief Destroys the stack and deallocates memory.
 *
 * @param pxTop Pointer to the top of the stack.
 */
void vStackDestroyStack(StackTop_t *pxTop);

#endif /* _STACK_H_ */
