#ifndef __CONFIG_H__
#define __CONFIG_H__
/* server / client module management file */


/* define calculator module */
#undef CAL 

/* define Three way handshake */
#define THREEWAY_HANDSHAKE	1

int threeway_handshake_send(int fd, char *msg, int count, int type);
int threeway_handshake_recv(int fd, char *msg);




#endif /* __CONFIG_H__ */
