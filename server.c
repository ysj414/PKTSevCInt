#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>


#define BUF_SIZE	32

int main(void)
{
	int serv_sock, clnt_sock;
	char messgae[BUF_SIZE];
	int str_len, i;
	char clnt_ip[BUF_SIZE];

	struct sockaddr_in serv_adr;
	struct sockaddr_in clnt_adr;
	socklen_t clnta_adr_sz;


	serv_sock = socket(PF_INET, SOCK_STREAM, 0);
	if(serv_sock == -1)
		error_handling("socket init error\n");
	
	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY); /* INADDR_ANY : 서버의 IP를 자동으로 찾아서 대입해주는 함수 */
	serv_adr.sin_port = htons(atoi(argv[1]));

	if(bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1 )
		error_handling("bind() error\n");

	if(listen(serv_sock, 5) == -1 )
		error_handling("listen() error\n");


	for(i = 0; i < 5; i++)
	{
		clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_adr, &clnt_adr_sz);
		if(clnt_sock == -1)
			error_handling("accept() error");

	}

	return 0;
}
