#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<netinet/in.h>

#define BUF_SIZE	1024

void error_handling(char *message);

int main(int argc, char* argv[])
{
	int serv_sock, c_sock;
	char message[BUF_SIZE];
	int str_len, i;

	struct sockaddr_in serv_adr;
	struct sockaddr_in c_adr;
	socklen_t c_adr_sz;


	serv_sock = socket(PF_INET, SOCK_STREAM, 0);
	if(serv_sock == -1)
		error_handling("socket init error\n");
	printf("socket create succuess\n");
	
	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY); /* INADDR_ANY : 서버의 IP를 자동으로 찾아서 대입해주는 함수 */
	serv_adr.sin_port = htons(atoi(argv[1]));

	printf("Hello! I'am Server\n");
	printf("My IP:%s Port: %s\n",inet_ntoa(serv_adr.sin_addr),argv[1]);
                                
	if(bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1 )
		error_handling("bind() error\n");
	printf("bind success\n");

	if(listen(serv_sock, 5) == -1 )
		error_handling("listen() error\n");
	printf("listen success\n");


	
	c_sock = accept(serv_sock, (struct sockaddr *)&c_adr, &c_adr_sz);
	if(c_sock == -1)
		 error_handling("accept() error\n");
	printf("Client Info : IP: %s, Port %d\n",inet_ntoa(c_adr.sin_addr),ntohs(c_adr.sin_port));

	while((str_len = read(c_sock, message, BUF_SIZE)) != 0)
			write(c_sock, message, str_len);

	close(c_sock);

	close(serv_sock);
	

	return 0;
}

void error_handling(char *message)
{
	printf("%s\n",message);
	exit(1);
}
