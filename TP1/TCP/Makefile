#########
#
# Makefile pour mini
#
#########

# For Solaris
#LD_FLAGS = -lsocket -lnsl

# For Linux
LD_FLAGS =

all: clientTCP serveurTCP

clientTCP: clientTCP.c
	gcc clientTCP.c -o clientTCP  $(LD_FLAGS)

serveurTCP: serveurTCP.c
	gcc serveurTCP.c -o serveurTCP   $(LD_FLAGS)

clean:
	rm *~ ; rm -i \#* ; rm *.o; \
        rm clientTCP ; rm serveurTCP
