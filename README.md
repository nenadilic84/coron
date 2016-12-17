# CORON
One of the most missed things when migrating from assembly language to C is a way to branch off from one point to another with ease.
The intention of the *coron* is to provide a simple and efficient way to enable coroutine-like functions in C language. Usually, this kind of behavior is needed when developing on a constrained embedded device and dealing with some type of asynchronous communication.
> Note: It uses GCC [Labels as Values](https://gcc.gnu.org/onlinedocs/gcc/Labels-as-Values.html) extension in order to achieve this.

# Usage
As *coron* consists of only one **coron.h** header file providing the macros, there is straight forward way to use it any project developed in C99 that uses GCC or CLANG.

Example:
```
void foo(void) {
...
    PC_INIT(); /* initializes the static variable for saving the PC.
                * Next instruction called after the PC_INIT will be
                * the last saved PC, all above will always
                * execute on function call
                */
...
    PC_SAVE(); /* saves the current PC and next time
                * the function is called this line will
                * be the entry point
                */
...
    PC_RESET(); /* resets the entry back to PC_INIT (optional) */
}
```
# Comparison between protothreads
There is an intentional similarity with [Adam Dunkel's Protothreads](http://dunkels.com/adam/pt/), where the main differences are:
* no switch-case statements are used to enable the functionality and thus switch is allowed to be placed in the function body
* information about the entry and exit is declared in the function scope so there is no need to pass it as a function argument allowing the function prototype to be defined without limitations
* Only `PC_INIT();` at the beginning of the function is needed to allow the function to save the PC state
