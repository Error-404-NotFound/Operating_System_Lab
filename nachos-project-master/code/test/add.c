/* add.c
 *	Simple program to test whether the systemcall interface works.
 *
 *	Just do a add syscall that adds two values and returns the result.
 *
 */

#include "syscall.h"

int main() {
    int result;
    int result2;
    int result3;
    int result4;

    result = Add(42, 23);
    result2=Sub(42,23);
    PrintNum(result2);
    PrintString("\n");
    result3=Mul(2,3);
    PrintNum(result3);
    PrintString("\n");
    result4=Div(100,5);
    PrintNum(result4);
    PrintString("\n");
    PrintString("Hello World\n");
    OSSleep(10);
    PrintHashString("                     Hello                   World                            \n");


    Halt();
    /* not reached */
}
