#include<stdio.h>
#include <stdlib.h>
#include<sys/types.h>
#include<fcntl.h>
#include <unistd.h>

int main()
{
    int Fd;
    char Ubuff[]="This is the User Buffer ==> Sending Data to the Kernel.";
    char Kbuff[100];
    Fd=open("/dev/DESD_Device", O_RDWR, 0777);
    if(Fd < 0)
    {
        printf("\nError Opening Device.\n");
        exit(1);
    }

    write(Fd, Ubuff, sizeof(Ubuff));    // writing to the kernel
    read(Fd, Kbuff, 50);
    printf("\nThe Data read from the Kernel is ==> %s\n", Kbuff);   // reading data from kernel
    close(Fd);
}
