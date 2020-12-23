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

	size = strlen(buf)+1;
	for(i = 0; i < size; i++)
		msg[i] = buf[i];
	write(fd, (char *)(&size),SIZE);
	write(fd, msg, sizeof(char)*size);

	return 0;
}



int threeway_handshake_recv(int fd, char *msg)
{
	int size=strlen(msg)+1;

	assert(size > 0);

	read(fd, (char *)&size, SIZE);
    read(fd, msg,sizeof(char)*size);
	printf("%4d",size);
	puts(msg);

	return 0;
}


