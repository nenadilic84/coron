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
#include <stdlib.h>
#include "msgq.h"

void msgq_init(struct msgq *m, void **dataptr, size_t size)
{
    m->data = dataptr;
    m->mask = size - 1;
    m->put_ptr = 0;
    m->get_ptr = 0;
}

bool msgq_put(struct msgq *m, void *msg)
{
    /* Check if buffer is full. If it is full, return false to indicate that
     the element was not inserted into the buffer.
     */

    if(((m->put_ptr - m->get_ptr) & m->mask) == m->mask) {
        return false;
    }

    m->data[m->put_ptr] = msg;
    m->put_ptr = (m->put_ptr + 1) & m->mask;
    return true;
}

void *msgq_get(struct msgq *m)
{
    void *msg;

    /* Check if there are bytes in the buffer. If so, we return the
     first one and increase the pointer. If there are no bytes left, we
     return NULL.
     */
    if(((m->put_ptr - m->get_ptr) & m->mask) > 0) {

        msg = m->data[m->get_ptr];
        m->get_ptr = (m->get_ptr + 1) & m->mask;
        return msg;
    } else {
        return NULL;
    }
}

size_t msgq_size(const struct msgq *m)
{
    return m->mask + 1;
}

size_t msgq_elements(const struct msgq *m)
{
    return (m->put_ptr - m->get_ptr) & m->mask;
}

bool msgq_empty(const struct msgq *m)
{
    return msgq_elements(m) == 0;
}
