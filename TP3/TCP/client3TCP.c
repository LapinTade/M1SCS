#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>

//#include <fonctionsTCP.h>

#define TAIL_BUF 256
main(int argc, char **argv) {
	int portRec;
	int portEnv;
	char* nomMachine;
	int sizeAddr;
	int sockConx;
	int sockTrans;
	int sockCli;
	int err;
	
	char buffer[TAIL_BUF];
	
	struct sockaddr_in nomTransmis;	/* adresse socket de transmission */
	struct sockaddr_in nomConnecte;	/* adresse de la sochet connectee*/
	
		/*
	* verification des arguments
	*/
	if (argc != 4) {
		printf ("usage : serveurTCP adress no_portRec no_portEnv\n");
		return -1;
	}

	nomMachine = argv[1];
	portRec  = atoi(argv[2]);
	portEnv = atoi(argv[3]);
	sizeAddr = sizeof(struct sockaddr_in);

	//sockServeur
	sockConx = sockServeur(portRec);
	
	/*
	* attente de connexion
	*/
	//accept
	sockTrans = accept(sockConx, 
		 (struct sockaddr *)&nomTransmis, (socklen_t *)&sizeAddr);
	if (sockTrans < 0) {
		perror("serveurTCP:  erreur sur accept");
		return -5;
	}
	
	//recv
	err = recv(sockTrans, buffer, TAIL_BUF, 0);
	
	//sockCli
	sockCli = sockClient(nomMachine, portEnv);
	
	while(1) {
		//send
		err = send(sockCli, buffer, TAIL_BUF, 0);
		if (err <= 0) {
			//if (err != strlen(buffer)+1) {
			perror("client : erreur sur le send");
			shutdown(sockCli, 2);
			 close(sockCli);
			exit(3);
		}
	
		//recv
		err = recv(sockTrans, buffer, TAIL_BUF, 0);
		if (err < 0) {
			perror("serveurTCP: erreur dans la reception");
			shutdown(sockTrans, 2); close(sockTrans);
			return -7;
		}
		printf("serveurTCP : voila le message recu: %s\n", buffer);
	}
}
