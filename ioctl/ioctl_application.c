#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<asm/ioctl.h>
#include "ioctl.h"

struct DefaultData {
    int Baudrate;
    int StopBits;
    int Parity;
};

int main()
{
    int FileDesc, Result, BAUD_RATE = 9600, STP_BITS = 8, *test;
    struct DefaultData ToSend={9800,1,0};
    char Ubuff[]="This is the User Buffer......Sending Data to the Kernel....";
    char Kbuff[100];
    FileDesc=open("/dev/IOCTL0",O_RDWR,0777);
    if(FileDesc<0)
    {
        printf("\nError Opening Device\n");
        exit(1);
    }
    Result = ioctl(FileDesc, SET_BAUD_RATE, &BAUD_RATE);
    if(Result<0){
        printf("\nIOCTL Error\n");
        return (-1);
    }
    printf("The baud confirmation: %d",BAUD_RATE);
    test = &STP_BITS;
    ioctl(FileDesc, SET_NO_STOP_BITS, &STP_BITS);
    ioctl(FileDesc, SET_DIRECTION_WRITE, NULL);
    ioctl(FileDesc, DEFAULT_DATA, &ToSend);
    
    write(FileDesc,Ubuff,sizeof(Ubuff));
    read(FileDesc,Kbuff,50);
    printf("\n The Data read from the Kernel is\n>>>> %s <<<<<\n",Kbuff);
    close(FileDesc);
}
