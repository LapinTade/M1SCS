/* fonctions UDP */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

/* inclusions socket */
#include <sys/socket.h>
#include <netdb.h>

#include "fonctionsUDP.h"

#define TAIL_BUF 100
#define T_NOM 20
int socketUDP(ushort nbPort) {
  int sock,               /* descipteur de la socket locale */
      port,               /* variables de lecture */
      size_addr, 	  /* taille de l'adresse d'une socket */
      err;                /* code d'erreur */
  char chaine[TAIL_BUF];
  
  struct sockaddr_in adrDest;     /* adresse de la socket distante */
  struct sockaddr_in adrLocal;	  /* adresse de la socket locale */

  struct hostent* host;

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
    adrDest.sin_family = AF_INET;
    adrDest.sin_port = htons(nbPort);
    adrDest.sin_addr.s_addr = INADDR_ANY;
	// INADDR_ANY : 0.0.0.0 (IPv4) donc htonl inutile ici, car pas d'effet
    bzero(adrDest.sin_zero, 8);

    /* 
     * attribution de l'adresse a la socket
     */
    err = bind(sock, (struct sockaddr *)&adrDest, size_addr);
    if (err < 0) {
	perror("socketUDP : erreur sur le bind");
	exit(3);
    }
	return sock;
}

int adresseUDP(char* nomMachine, ushort nbPort, struct sockaddr_in* addr){
    int sock,               /* descipteur de la socket locale */
      size_addr, 	  /* taille de l'adresse d'une socket */
      err;                /* code d'erreur */
  char chaine[TAIL_BUF];
  
  //struct sockaddr_in adrDest;     /* adresse de la socket distante */
  
  struct sockaddr_in adrLocal;	  /* adresse de la socket locale */

  struct hostent* host;
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
  adrLocal.sin_family = AF_INET;
  adrLocal.sin_port = htons(nbPort);
  adrLocal.sin_addr.s_addr = INADDR_ANY;
  	// INADDR_ANY : 0.0.0.0 (IPv4) donc htonl inutile ici, car pas d'effet
  bzero(adrLocal.sin_zero, 8);

  /* 
   * attribution de l'adresse a la socket
   */
  err = bind(sock, (struct sockaddr *)&adrLocal, size_addr);
  if (err < 0) {
    perror("socketUDP : erreur sur le bind");
    exit(3);
  }

  /*
   * saisie et initialisation de l'adresse du destinataire
   */
  printf("client : donner la machine dest : ");
  scanf("%s", nomMachine);
  printf("client : donner le port dest : ");
  scanf("%d", &nbPort);
  printf("client : initaddr pour %s, %d\n",  nomMachine, nbPort);


  host = gethostbyname(nomMachine);
  if (host == NULL) {
    printf("initAddr : erreur gethostbyname\n");
    exit(4);
  }

  /* recopie de l'adresse IP */
  addr->sin_addr.s_addr = ((struct in_addr *) (host->h_addr_list[0]))->s_addr;
      
  /* initialisation de l'adresse de la socket */
  addr->sin_family = AF_INET;
  bzero(addr->sin_zero, 8);
  addr->sin_port = htons(nbPort);
  
  return sock;
}

