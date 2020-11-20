#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>

#define BUF_SIZE 1024
void error_handling(char *message);


int main(int argc, char *argv[])
{

	int sock;
	char msg[BUF_SIZE];
	int str_len, recv_len, recv_cnt;
	struct sockaddr_in serv_adr;

	
	sock = socket(PF_INET, SOCK_STREAM, 0);
	if(sock == -1)
		error_handling("socket() error");


    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family=AF_INET;
    serv_adr.sin_addr.s_addr=inet_addr(argv[1]);
    serv_adr.sin_port=htons(atoi(argv[2]));

    if(connect(sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr))==-1)
        error_handling("connect() error!");
    else
        puts("Connected...........");

    while(1)
    {
        fputs("Input message(Q to quit): ", stdout);
        fgets(msg, BUF_SIZE, stdin);

        if(!strcmp(msg,"q\n") || !strcmp(msg,"Q\n"))
            break;

        str_len=write(sock, msg, strlen(msg));

        recv_len=0;
        while(recv_len<str_len)
        {
            recv_cnt=read(sock, &msg[recv_len], BUF_SIZE-1);
            if(recv_cnt==-1)
                error_handling("read() error!");
            recv_len+=recv_cnt;
        }

        msg[recv_len]=0;
        printf("Message from server: %s", msg);
    }

    close(sock);
    return 0;
}

void error_handling(char *message)
{
    printf("%s\n",message);
    exit(1);
}
