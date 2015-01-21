#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>

#include "fonctionsTCP.h"

#define TAIL_BUF 256
main(int argc, char **argv) {
	char chaine[TAIL_BUF];
	char* nomMachine;
	int port;
	int sock;
	int err;

	nomMachine = argv[1];
	port = atoi(argv[2]);

	/* verification des arguments */
	if (argc != 3) {
		printf("usage : client nom_machine no_port\n");
		exit(1);
	}

	sock = sockClient(nomMachine, port);

	/* 
	* saisie de la chaine 
	*/
	printf("client : donner une chaine : ");
	scanf("%s", chaine);
	printf("client : envoi de - %s - \n", chaine);

	int i; 
	for(i=0 ; i<1000 ; i++) {

		/*
		 * envoi de la chaine
		 */
		//err = send(sock, chaine, strlen(chaine) + 1, 0);
		err = send(sock, chaine, TAIL_BUF, 0);
		if (err <= 0) {
			//if (err != strlen(chaine)+1) {
			perror("client : erreur sur le send");
			shutdown(sock, 2); close(sock);
			exit(3);
		}
		printf("client : envoi %d realise\n", i);
	}

	/* 
	* fermeture de la connexion et de la socket 
	*/
	shutdown(sock, 2);
	close(sock);
}
