#########
#
# Makefile pour mini
#
#########

# For Solaris
#LD_FLAGS = -lsocket -lnsl

# For Linux
LD_FLAGS =

LIB= libfonctionsTCP.a

all: clientTCP1 clientTCP2 clientTCP3

clientTCP1: 
	gcc client1TCP.c -o client1TCP  $(LD_FLAGS) $(LIB)
	
clientTCP2:
	gcc client2TCP.c -o client2TCP $(LD_FLAGS) $(LIB)

clientTCP3:
	gcc client3TCP.c -o client3TCP  $(LD_FLAGS) $(LIB)


clean:
	rm *~ ; rm -i \#* ; rm *.o; \
        rm client1TCP ; rm client2TCP ; rm client3TCP;
