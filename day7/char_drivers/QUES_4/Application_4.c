#include<stdio.h>
#include <stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include <unistd.h>

int main()
{
    int Fd;
    char Ubuff[2]={10,20};
    char Kbuff[100];
    Fd=open("/dev/MyAddDevice", O_RDWR, 0777);
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
