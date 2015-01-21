/*
 **********************************************************
 *
 *  Programme : recepteur.c
 *
 *  ecrit par : LP.
 *
 *  resume :    recoit une chaine de caracteres du programme emetteur
 *
 *  date :      05 / 02 / 06
 *
 ***********************************************************
 */

/* Include standards */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

/* Include socket */
#include <sys/socket.h>
#include <netinet/in.h>

/* taille du buffeur de reception */
#define TAIL_BUF 100


main(int argc, char** argv) {
    int             sock,	        /* descripteur de socket locale */
                    err;	        /* code d'erreur */

    struct sockaddr_in adr_recep,	/* adresse de la socket */
                       adr_emet;        /* adresse emetteur */

    char buffer[TAIL_BUF];       	/* buffer de reception */
                  

    int size_addr;	                /* taille de l'adresse d'une socket */

   
    if (argc != 2) {
      printf("usage : %s no_port\n", argv[0]);
      exit(1);
    }

    size_addr = sizeof(struct sockaddr_in);

   /* creation de la socket, protocole UDP */
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
	perror("socketUDP : erreur de socket\n");
	exit(2);
    }

    /* 
     * initialisation de l'adresse de la socket 
     */
    adr_recep.sin_family = AF_INET;
    adr_recep.sin_port = htons(atoi(argv[1]));
    adr_recep.sin_addr.s_addr = INADDR_ANY;
	// INADDR_ANY : 0.0.0.0 (IPv4) donc htonl inutile ici, car pas d'effet
    bzero(adr_recep.sin_zero, 8);

    /* 
     * attribution de l'adresse a la socket
     */
    err = bind(sock, (struct sockaddr *)&adr_recep, size_addr);
    if (err < 0) {
	perror("socketUDP : erreur sur le bind");
	exit(3);
    }

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
