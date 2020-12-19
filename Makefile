CC=gcc


server: server.o
	rm -rf server 
	${CC} -o server server.o 
server.o: server.c 
	${CC} -c server.c threeway_handshake.c

client: client.o
	rm -rf client 
	${CC} -o client client.o

client.o: client.c 
	${CC} -c client.c threeway_handshake.c



clean : 
	@rm -rf server client server.o client.o threeway_handshake.o
	@echo "all files remove"

