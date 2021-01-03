#ifndef __CONFIG_H__
#define __CONFIG_H__
/* server / client module management file */


/* define calculator module */
#undef CAL 

/* define Three way handshake module */
#undef THREEWAY_HANDSHAKE	

/* define File Transfer module */ 
#define FILE_TRANSFER	1

int threeway_handshake_send(int fd, char *msg, int count, int type);
int threeway_handshake_recv(int fd, char *msg);

int file_name_get();
int file_name_send(int fd, char *buf);
int file_name_recv(int fd, char *buf);
void file_transfer_send(int fd, char *buf);
void file_transfer_no_send(int fd, char* buf);
int file_transfer_recv(int fd, char* buf);





#endif /* __CONFIG_H__ */
