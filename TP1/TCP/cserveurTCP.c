#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "fonctionsTCP.h"


#define TAIL_BUF 256
main(int argc, char **argv) {
	int  sockConx,        /* descripteur socket connexion */
	sockTrans,       /* descripteur socket transmission */
	port,            /* numero de port */
	sizeAddr,        /* taille de l'adresse d'une socket */
	err;	        /* code d'erreur */

	char buffer[TAIL_BUF]; /* buffer de reception */


	struct sockaddr_in nomTransmis;	/* adresse socket de transmission */
	struct sockaddr_in nomConnecte;	/* adresse de la sochet connectee*/


	/*
	* verification des arguments
	*/
	if (argc != 2) {
	printf ("usage : serveurTCP no_port\n");
	return -1;
	}

	port  = atoi(argv[1]);
	sizeAddr = sizeof(struct sockaddr_in);

	sockConx = sockServeur(port);

	/*
	* attente de connexion
	*/
	sockTrans = accept(sockConx, 
		 (struct sockaddr *)&nomTransmis, (socklen_t *)&sizeAddr);
	if (sockTrans < 0) {
	perror("serveurTCP:  erreur sur accept");
	return -5;
	}

	printf("Connecte\n");
	while(1) { 
		scanf("%s", buffer);
		/*
		* reception et affichage du message en provenance du client
		*/
		err = recv(sockTrans, buffer, TAIL_BUF, 0);
		if (err < 0) {
			perror("serveurTCP: erreur dans la reception");
			shutdown(sockTrans, 2); close(sockTrans);
			return -7;
		}
		printf("serveurTCP : voila le message recu: %s\n", buffer);
	}

	/* 
	* arret de la connexion et fermeture
	*/
	shutdown(sockTrans, 2); close(sockTrans);
	close(sockConx);

	return 0;
}
