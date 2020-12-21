#include "lib/lib.h"
#include "config.h"
#define BUF_SIZE 1024
void error_handling(char *message);


int main(int argc, char *argv[])
{

	int sock;
	char msg[BUF_SIZE];
	int str_len, recv_len, recv_cnt;
	struct sockaddr_in serv_adr;
	int i=0;
#ifdef CAL
	int count=0;
	int operand;
	char operator;
#endif
	
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
//        fputs("Input message(Q to quit): ", stdout);
//        fgets(msg, BUF_SIZE, stdin);

//        if(!strcmp(msg,"q\n") || !strcmp(msg,"Q\n"))
//            break;

#if defined (CAL)
	printf("Operand Count: ");
	scanf("%d",&count);
	if(count == -1)
		break;
	if(count < 0)
	{
		printf("Wrong Input\n");
		continue;
	}
	for(i = 0; i< count; i++)
	{
		printf("Operand %d: ",i+1);
		scanf("%d",&operand);
		//add to exception
		msg[i]=(char)operand;
	}
	getchar();
	printf("Operator: ");
	scanf("%c",&operator);
	//add to exception handling
	msg[count] = operator;

#elif defined(THREEWAY_HANDSHAKE)
	   for(i=0; i<3; i++)
	   {
		 threeway_handshake_recv(sock,msg);
		 sleep(3);
		 memset(msg,0,sizeof(msg));
		 threeway_handshake_send(sock,msg,i,1);
		 memset(msg,0,sizeof(msg));
	   }
	   return 0;
#endif
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
#ifdef CAL
        printf("Operation result: %d\n",(int)msg[0]);
#else
        printf("Message from server: %s", msg);
#endif

    }

    close(sock);
    return 0;
}

void error_handling(char *message)
{
    printf("%s\n",message);
    exit(1);
}
