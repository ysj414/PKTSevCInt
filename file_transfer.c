#include "lib/lib.h"
#include "config.h"

#define BUF_SIZE 100
#define SOCK_SIZE	4
#define READ_MODE	"r"
#define WRITE_MODE	"w"

/* 0 is OK
  -1 is NOT OK
  */

char name[BUF_SIZE];

int file_name_get()
{
	int len = 0;
	int ret = 0;
	printf("Enter a file name(max:100):");
	fgets(name,BUF_SIZE,stdin);
	len = strlen(name);
	name[len-1]='\0';
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

	strcpy(buf,name);
	write(fd,buf, BUF_SIZE);
//	printf("file name send %s\n",buf);
    return 0;
}

int file_name_recv(int fd, char *buf)
{
	int ret = 0;
	
	read(fd,buf,BUF_SIZE);
//	printf("file name read:%s\n",buf);
	ret = access(buf,F_OK);
	return ret;
}

void file_transfer_send(int fd, char *buf)
{
	FILE *fp = NULL;
	int count =0;
	int len=0;
	printf("name:%s\n",buf);
	fp = fopen(buf,READ_MODE);
	if(fp == NULL)
		return;
	printf("file read\n");
	while(!feof(fp))
	{
		fgets(buf,BUF_SIZE,fp);
		printf("%s",buf);
		len = strlen(buf);
		while(count<len)
		{
			count+=write(fd, buf, BUF_SIZE);
			printf("count:%d content:%c\n",count,buf[0]);
		}
		count = 0;
		memset(buf,0,sizeof(buf)/sizeof(char));
	}
	fclose(fp);
}

void file_transfer_no_send(int fd, char* buf)
{
	printf("no send\n");
	buf[0]='0';
	write(fd,buf,SOCK_SIZE);
}

int file_transfer_recv(int fd, char* buf)
{
	FILE *fp = NULL;
	int count =0;

	fp = fopen(name,WRITE_MODE);

	if(fp == NULL)
		return -1;

	while(1)
	{
		count=0;
		count+=read(fd, buf, BUF_SIZE);
		if(count == 0 || buf[0] =='0') /* There is a problem when file contents starts '0' */
			break;
		fputs(buf,fp);
//		printf("read: %d, %s\n",count,buf);
	}
	fclose(fp);

	return 0;
}
