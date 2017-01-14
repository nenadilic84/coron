/*
 * test_coron.c
 *
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

/* time tracking */
uint64_t timer_10ms = 0;

/* example function */
static void coron_1s_loop_test(void)
{

    static uint8_t timer_counter = 0;

    PC_INIT(); /* initializes static variable for saving the PC.
                * Next instruction called after the PC_INIT will be
                * the last saved PC, all above will alsways executed
                * upon function call
                */

    printf("entering 1s loop\n");

    while(1) {
        PC_SAVE(); /* saves the current PC and next time the function is called
                    * this line will be the entry point
                    */

        if(timer_10ms % 100) { /* only continue every second */
            return;
        }

        printf("hello from 1s loop!\n");

        timer_counter++;
        if(!(timer_counter % 10)) { /* every 10s break the loop */
            timer_counter = 0;
            break;
        }
    }

    printf("back to beginning of 1s loop\n");
    PC_RESET(); /* resets the entry back to PC_INIT */

    /* PC_SAVE(); return;
     * We can also choose to exit here each time
     * or do nothing, which will go back to the last saved PC
     */

}

/*
 * Adds the function pointer to the section "sec_main_loop" from where all
 * functions are going to be called latter using call_main_loop_fns macro
 */
add_to_main_loop(coron_1s_loop_test);

/* example function */
static void coron_100ms_loop_test(void)
{

    PC_INIT();

    printf("entering 100ms loop\n"); /* will only be printed first time
                                      * function is called
                                      */
    while(1) {
        PC_SAVE();

        if(timer_10ms % 10) { /* only continue every 100ms */
            return;
        }

        printf("hello from 100ms loop!\n");
    }
}
add_to_main_loop(coron_100ms_loop_test);
