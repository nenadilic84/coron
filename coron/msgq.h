/*
 * Copyright (C) 2016 Nenad Ilic.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#ifndef MSGQ_H_
#define MSGQ_H_

#include <stdint.h>
#include <stdbool.h>

/**
 * \brief      Structure that holds the state of a message queue.
 *
 *             This structure holds the state of a message queue. The
 *             actual buffer needs to be defined separately. This
 *             struct is an opaque structure with no user-visible
 *             elements.
 *
 */
struct msgq {
    void **data;
    size_t mask;
    size_t put_ptr, get_ptr;
};

/**
 * \brief      Initialize a message queue
 * \param m    A pointer to a struct msgq to hold the state of the message queue
 * \param data A pointer to an array pointers to hold the data in the buffer
 * \param size_power_of_two The size of the message queue, which must be a power of two
 *
 *             This function initiates a message queue. The data in the
 *             buffer is stored in an external array, to which a
 *             pointer must be supplied. The size of the message queue
 *             must be a power of two.
 *
 */
void msgq_init(struct msgq *m, void **data,
               size_t size_power_of_two);

/**
 * \brief      Insert a message into the message queue
 * \param m    A pointer to a struct msgq to hold the state of the message queue
 * \param msg  pointer to be written to the buffer
 * \return     true if there data could be written, or false if the buffer was full.
 *
 */
bool msgq_put(struct msgq *m, void *msg);


/**
 * \brief      Get a message from the message queue
 * \param m    A pointer to a struct msgq to hold the state of the message queue
 * \return     The data from the buffer, or NULL if the buffer was empty
 *
 */
void *msgq_get(struct msgq *m);

/**
 * \brief      Get the size of a message queue
 * \param m    A pointer to a struct msgq to hold the state of the message queue
 * \return     The size of the buffer.
 */
size_t msgq_size(const struct msgq *m);

/**
 * \brief      Get the number of elements currently in the message queue
 * \param m    A pointer to a struct msgq to hold the state of the message queue
 * \return     The number of elements in the buffer.
 */
size_t msgq_elements(const struct msgq *m);

/**
 * \brief      Check if the message queue is empty
 * \param m    A pointer to a struct msgq to hold the state of the message queue
 * \return     true if message queue is empty, false if not.
 */
bool msgq_empty(const struct msgq *m);

#endif /* MSGQ_H_ */
