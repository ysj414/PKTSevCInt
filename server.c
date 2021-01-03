#include "lib/lib.h"
#include "config.h"

#define BUF_SIZE	1024
void error_handling(char *message);

int main(int argc, char* argv[])
{
	int serv_sock, c_sock;
	char message[BUF_SIZE];
	char message_to[BUF_SIZE];
	char buf[64];
	int str_len, i;
#ifdef CAL
	int result=0;
	char oper=0;
	int len=0;
#endif
#ifdef FILE_TRANSFER
	int f_check=0;
#endif
	struct sockaddr_in serv_adr;
	struct sockaddr_in c_adr;
	socklen_t c_adr_sz;


	serv_sock = socket(PF_INET, SOCK_STREAM, 0);
	if(serv_sock == -1)
		error_handling("socket init error\n");
	printf("socket create succuess\n");

/* Server init */	
	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY); /* INADDR_ANY : 서버의 IP를 자동으로 찾아서 대입해주는 함수 */
	serv_adr.sin_port = htons(atoi(argv[1]));


	printf("Hello! I'am Server\n");
	if(bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1 )
		error_handling("bind() error\n");

/* Print Server Information.
 * Server Port print correctly but IP address can't print.
 * Later, this part will be fixed.
 */


/*  
	inet_ntop(AF_INET,&serv_adr.sin_addr,sbuf,INET_ADDRSTRLEN);
	printf("Port %d\n",ntohs(serv_adr.sin_port));
	printf("Server Info : IP: %s\n",sbuf);
*/
	if(listen(serv_sock, 5) == -1 )
		error_handling("listen() error\n");
	while(1)
	{
	printf("Server wait Client connection......\n");	
	c_sock = accept(serv_sock, (struct sockaddr *)&c_adr, &c_adr_sz);

	if(c_sock == -1)
	{
		 printf("accept() error\n");
		 continue;
	}
	inet_ntop(AF_INET,&c_adr.sin_addr,buf,INET_ADDRSTRLEN);
	printf("Client has Connected!!\n");
	printf("Client Info : IP: %s\n",buf);
#if defined(CAL)
	while( (str_len = read(c_sock, message, BUF_SIZE)) != 0)
	{
	  result = (int)message[0];
	  len = strlen(message);
	  for(i=0;i<len;i++)
	  {
		  if(message[i] == '+')
		  {
			  oper = '+';
			  len = i;
			  break;
		  }
		  else if(message[i] =='-')
		  {
			  oper = '-';
			  len = i;
			  break;
		  }
		  else if(message[i] =='*')
		  {
			  oper = '*';
			  len = i;
			  break;
		  }
	  }

	  switch(oper)
	  {
		case '+':
		for(i = 1; i<len; i++)
			result+=(int)message[i];
		break;
		case '-':
		for(i = 1; i<len; i++)
			result-=(int)message[i];
		break;
		case '*':
		for(i = 1; i<len; i++)
			result*=(int)message[i];
		default:
		break;
	  }
	  message_to[0] = (int)result;
  	  write(c_sock,message_to,str_len);
	  memset(message,0,sizeof(message));	 
	  memset(message_to,0,sizeof(message_to));
	  printf("The Result is %d.\n",result); 
	}
#elif defined(THREEWAY_HANDSHAKE)
	 for(i = 0 ; i < 3; i++)
	 {
	  threeway_handshake_send(c_sock, message, i, 0);
	  memset(message,0,sizeof(message));
	  threeway_handshake_recv(c_sock, message);
	  memset(message,0,sizeof(message));
	 }
	 return 0;
#elif defined(FILE_TRANSFER)
	 f_check = file_name_recv(c_sock, message);
	 if(f_check == -1)
		 file_transfer_no_send(c_sock, message);
	 else
		 file_transfer_send(c_sock,message);
	 close(c_sock);

	 return 0;
#else
	while( (str_len = read(c_sock, message, BUF_SIZE)) != 0 )
	{
			printf("Server received data: %s",message);
			printf("Transfer this data toward client again.\n");
			write(c_sock, message_to, str_len);
			memset(message_to,0,sizeof(message_to));
			memset(message,0,sizeof(message));
	}
#endif
	printf("Client has closed the connection\n");
	close(c_sock);
	}
	close(serv_sock);

	return 0;
}

void error_handling(char *message)
{
	printf("%s\n",message);
	exit(1);
}
