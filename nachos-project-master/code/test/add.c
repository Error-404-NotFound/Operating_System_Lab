/* add.c
 *	Simple program to test whether the systemcall interface works.
 *
 *	Just do a add syscall that adds two values and returns the result.
 *
 */

#include "syscall.h"
#define stdin 0
#define stdout 1

int main() {
    int result;
    // int result2;
    // int result3;
    // int result4;
    // int pid2;

    result = Add(42, 23);
    PrintNum(result);
    // result2=Sub(42,23);
    // PrintNum(result2);
    // PrintString("\n");
    // result3=Mul(2,3);
    // PrintNum(result3);
    // PrintString("\n");
    // result4=Div(100,5);
    // PrintNum(result4);
    PrintString("\n");
    PrintString("Hello World\n");
    // OSSleep(10);
    // PrintHashString("                     Hello                   World                            \n");
    // pid2 = Exec("../test/help");
    // PrintString("\n");
    // Exec("../test/ascii");
    // PrintString("\n");
    // PrintNum(pid2);

    // PrintString("Hello World\n");
    Exec("../test/help",2);
    Exec("../test/help2",56);

    PrintString("\n");

    Halt();
    /* not reached */
}
