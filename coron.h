/*
 * coron.h
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

#ifndef _CORON_H_
#define _CORON_H_

#include <stdbool.h>

/* Macros to enable PC (program counter) initializing, saving and reseting */

#define TOKENPASTE(x, y) x ## y
#define L_NAME(x, y) TOKENPASTE(x, y)

/* PC_INIT() initializes the static variable for saving the PC. Next instruction
 * called after the PC_INIT will be the last saved PC, all above will always
 * execute on function call
 */
#define PC_INIT() static void *__l_state = &&__lab_init__;                     \
                  bool __yield_flag = false;                                   \
                  goto *__l_state;                                             \
                  __lab_init__:

/* PC_SAVE() saves the current PC and next time the function is called this line
 * will be the entry point
 */
#define PC_SAVE() __l_state = &&L_NAME(__lab, __LINE__ );                      \
                  if(__yield_flag) return;                                     \
                  L_NAME(__lab, __LINE__):                                     \
                  __yield_flag = true;                                         \

/* PC_RESET() resets the entry back to PC_INIT */
#define PC_RESET() __l_state = &&__lab_init__;                                 \


typedef void (*main_loop_t)(void);
/*
 * add_to_main_loop adds the function pointer to the section "sec_main_loop"
 * from where all functions are going to be called using
 * call_main_loop_fns macro
 */
#define add_to_main_loop(fn)                                                   \
        static main_loop_t __main_loop_##fn                                    \
        __attribute((used, section("sec_main_loop"))) = fn

/*
 * __start_sec_main_loop and __stop_sec_main_loop exports the
 * variable for accessing the beginning and the end of the
 * sec_main_loop section
 */
extern main_loop_t __start_sec_main_loop[], __stop_sec_main_loop[];

/*
 * call_main_loop_fns used to cycle over the added functionsd and execute
 * one by one
 */
#define call_main_loop_fns()                                                    \
    for (main_loop_t * call = __start_sec_main_loop;                            \
         call < __stop_sec_main_loop;                                           \
         call++) (*call)();

#endif /* _CORON_H_ */
