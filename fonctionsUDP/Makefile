#########
#
# fonctionsUDP
#
#########


all: emetteur recepteur

fonctionsUDP.o: fonctionsUDP.c fonctionsUDP.h
	gcc -c fonctionsUDP.c 

emetteur: emetteur.c fonctionsUDP.o
	gcc emetteur.c -o emetteur fonctionsUDP.o 

recepteur: recepteur.c fonctionsUDP.o
	gcc recepteur.c -o recepteur fonctionsUDP.o 

clean:
	rm  *~ ; rm -i \#* ; rm *.o; \
        rm emetteur ; rm recepteur
