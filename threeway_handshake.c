#include "lib/lib.h"
#include "config.h"


#define SIZE		4
#define BUF_SIZE	32
#define HELLO_S		"Hello world Server"
#define HELLO_C 	"Hello world Clinet"
#define CON_S		"Server is beautiful!"
#define CON_C		"Client is beautiful too!"
#define BYE_S		"Server Bye!"
#define BYE_C		"Client Bye!"
#define SVR			0
#define CLNT		1


int threeway_handshake_send(int fd, char *msg, int count, int type)
{
	int size,i;
	char buf[32];

	assert(type == SVR || type == CLNT);

	if(type == SVR)
	{
		switch(count)
		{
			case 0:
				strcpy(buf,HELLO_S);
				break;
			case 1:
				strcpy(buf,CON_S);
				break;
			case 2:
				strcpy(buf,BYE_S);
				break;
			default:
				break;
		}	
	}
	else
	{
		switch(count)
		{
			case 0:
				strcpy(buf,HELLO_C);
				break;
			case 1:
				strcpy(buf,CON_C);
				break;
			case 2:
				strcpy(buf,BYE_C);
				break;
			default:
				break;
		}

	}

	size = strlen(buf);
	
	snprintf(msg,SIZE,"%d",size);  /* 0 1 2 3 */
	for(i = SIZE; i < SIZE + size; i++)
		msg[i] = buf[i - SIZE];
	
	write(fd, msg, BUF_SIZE);

	return 0;
}



int threeway_handshake_recv(int fd, char *msg)
{
	int size=strlen(msg);
	int count = 0;
	while(count < size)
	{
		read(fd, msg,SIZE);
		count+=SIZE;
		printf("%s\n",msg); /* debug */
	}
	printf("Message: %s\n",msg);

	return 0;
}


