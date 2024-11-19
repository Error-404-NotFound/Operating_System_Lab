/* exec.c
 *	Simple program to test the exec system call.
 */

#include "syscall.h"
#define stdin 0
#define stdout 1

int main() {
    int pid1;
    int pid2;
    int i;
    pid1 = Exec("../test/num_io",4);
    pid2 = Exec("../test/help",4);
    Wait2(pid1);
    if(pid2<0)
    {
        Write("Exec failed: ",14,stdout);
        PrintNum(pid2);
    }
    if (pid1 < 0) {
        Write("Exec failed: ", 14, stdout);
        PrintNum(pid1);
    }
    while(1)
    {
        for(i=0;i<10000;i++);
        PrintString("exec.c\n");
    }
}
