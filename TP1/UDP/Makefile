all: emetteur recepteur

emetteur: emetteur.c
	gcc emetteur.c -o emetteur

recepteur: recepteur.c
	gcc recepteur.c -o recepteur

clean:
	rm  *~ ; rm -i \#* ; rm *.o; \
        rm emetteur ; rm recepteur
