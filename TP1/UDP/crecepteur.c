/* Include standards */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

/* Include socket */
#include <sys/socket.h>
#include <netinet/in.h>


#include "fonctionsUDP.h"

/* taille du buffeur de reception */
#define TAIL_BUF 100


main(int argc, char** argv) {
    int             sock,	        /* descripteur de socket locale */
    				port,
                    err;	        /* code d'erreur */

    struct sockaddr_in adr_recep,	/* adresse de la socket */
                       adr_emet;        /* adresse emetteur */

    char buffer[TAIL_BUF];       	/* buffer de reception */
                  

    int size_addr;	                /* taille de l'adresse d'une socket */

   
    if (argc != 2) {
      printf("usage : %s no_port\n", argv[0]);
      exit(1);
    }
	port=atoi(argv[1]);
    size_addr = sizeof(struct sockaddr_in);
	sock=socketUDP(port);
   	

    /*
     * reception et affichage du message en provenance du client
     */
    err = recvfrom(sock, buffer, TAIL_BUF, 0, (struct sockaddr*)&adr_emet, 
		    (socklen_t *)&size_addr);
    if (err < 0) {
        perror("recepteur :  erreur dans la reception");
        exit(6);
    }
    printf("Voila le message recu: %s\n", buffer);

    /* fermeture de la socket */
    close(sock);
}
