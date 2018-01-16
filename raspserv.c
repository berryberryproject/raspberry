#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <fcntl.h>


#define MAX_BUFFER_SIZE 1000


int main(int argc, char* argv[])
{
int data_fd;
char data[MAX_BUFFER_SIZE];
memset(data,0,sizeof(data));






printf("RASPBERRY SERVER STARTED\n\n ");

if(argc != 2)
{
printf("SERVER PORT: REQUIRED\n");
exit(1);
}

int serv_fd;
int clnt_fd;
int serv_port=atoi(argv[1]);


printf("서버 포트: %d\n",serv_port);

serv_fd=socket(AF_INET,SOCK_STREAM,0);

if(serv_fd ==-1)
{
printf("SOCKET ERROR");
exit(1);
}

struct sockaddr_in serv_addr, clnt_addr;
memset(&serv_addr,0,sizeof(serv_addr));
memset(&clnt_addr,0,sizeof(clnt_addr));

serv_addr.sin_family =AF_INET;
serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
serv_addr.sin_port=htons(serv_port);

printf("RASPBERRY IS CURRENTLY BINDING ...\n");


if(bind(serv_fd,(struct sockaddr*)&serv_addr,sizeof(serv_addr)) < 0)
{
printf("RASPBERRY BIND() FAILED!!!!!!!!!!!!!!!!!!!!! ...\n");
exit(1);
}

if(listen(serv_fd,5)<0)
{
printf("RASPBERRY LISTEN() FAILED!!!!!!!!!!!!!!!!!!!\n");
exit(1);
}

printf("RASPBERRY IS CURRENTLY LISTENING.\n");


//char  sendbuff[MAX_BUFFER_SIZE]="SERVER: CONNECTION SUCESSFUL!!!\n";
char  recevbuff[MAX_BUFFER_SIZE];

int len=sizeof(clnt_addr);

while(1)
{       
        data_fd=open("serv_out",O_RDONLY);
        clnt_fd=accept(serv_fd,(struct sockaddr*)&clnt_addr,&len);

        if(clnt_fd <0)
        {
        printf("RASPBERRY ACCEPT() FAILED \n");
        exit(1);
        }

        char clnt_ip_addr[100];



        inet_ntop(AF_INET,&clnt_addr.sin_addr.s_addr,clnt_ip_addr,sizeof(clnt_ip_addr));
        printf("SERVER: %s client connected \n",clnt_ip_addr);
        while(read(data_fd,data,MAX_BUFFER_SIZE-1))
        {
        write(clnt_fd,data,sizeof(data));
        }
        close(clnt_fd);
        printf("SERVER: Connection Sucessfully Closed\n");
}


return 0;

}





