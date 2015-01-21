#########
#
# fonctionsTCP
#
#########

# For Solaris
#LD_FLAGS = -lsocket -lnsl

# For Linux
LD_FLAGS =

all:  server

fonctionsSocket.o: fonctionsTCP.c fonctionsTCP.h
	gcc -c -o fonctionsTCP.o fonctionsTCP.c


server: server.c fonctionsSocket.o
	gcc server.c -o server fonctionsTCP.o  $(LD_FLAGS)

clean:
	rm *~ ; rm -i \#* ; rm *.o; \
        rm client ; rm server
