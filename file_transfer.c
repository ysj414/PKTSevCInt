#include "lib/lib.h"
#include "config.h"

#define BUF_SIZE 100
#define SOCK_SIZE	4
#define READ_MODE	"r"

/* 0 is OK
  -1 is NOT OK
  */

char name[BUF_SIZE];

int file_name_get()
{
	int len = 0;
	int ret = 0;
	printf("Enter a file name(max:100):\n");
	fgets(name,BUF_SIZE,stdin);
	len = strlen(name);
	if(len > 101)
	{
		printf("Input File name is too Large!\n");
		ret = -1;
		return ret;
	}
	return ret;
}

int file_name_send(int fd, char *buf)
{
	int len = strlen(name);
	int count = 0;

	strcpy(buf,name);

	while(count < len)
	{
		count+=write(fd,buf, SOCK_SIZE);
	}
	
    return 0;
}

int file_name_recv(int fd, char *buf)
{
	int count = 0;
	int ret = 0;
	int len = 0;
	
	len = strlen(buf);
	while(count < len)
	{
		count += read(fd,buf,SOCK_SIZE);
	}
	ret = access(buf,F_OK);
	return ret;
}

void file_transfer_send(int fd, char *buf)
{
	FILE *fp = NULL;

	while(!feof(fp))
	{
		fgets(buf,BUF_SIZE,fp);
		write(fd, buf, BUF_SIZE);
		memset(buf,0,sizeof(buf)/sizeof(char));
	}
	fclose(fp);
}

void file_transfer_no_send(int fd, char* buf)
{
	buf[0]='0'; // no file
	write(fd,buf,SOCK_SIZE);
}

int file_transfer_recv(int fd, char* buf)
{
	FILE *fp = NULL;
	int count =0;
	fp = fopen(name,"w");

	if(fp == NULL)
		return -1;

	while(!feof(fp))
	{
		read(fd, buf, BUF_SIZE);
		fputs(buf,fp);
		memset(buf,0,sizeof(buf)/sizeof(char));
	}
	fclose(fp);

	if(buf[0] == '0')
	{
		printf("There is no file.\n");
		return -1;
	}
	return 0;
}
