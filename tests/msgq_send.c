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

#include <stdio.h>
#include <stdint.h>
#include "coron/coron.h"

struct msgq test_txbuf = {0};
#define TXBUF_SIZE 2
static void *txbuf_data[TXBUF_SIZE];

static void test_msgq_send(void)
{
    static struct timer timer_100ms;

    PC_INIT();

    timer_set(&timer_100ms, CLOCK_SECOND / 10);
    msgq_init(&test_txbuf, txbuf_data, TXBUF_SIZE);

    while(1) {
        PC_SAVE();

        if(!timer_expired(&timer_100ms)) {
            return;
        }

        timer_reset(&timer_100ms);

        msgq_put(&test_txbuf, "test_msgq_send says hello");
    }
}
add_to_main_loop(test_msgq_send);
