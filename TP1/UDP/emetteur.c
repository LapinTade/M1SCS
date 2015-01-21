/*
 **********************************************************
 *
 *  Programme : emetteur.c
 *
 *  ecrit par : LP.
 *
 *  resume : socket UDP 
 *
 *  date :      05 / 02 / 06
 *
 ***********************************************************
 */

/* inclusions standards */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

/* inclusions socket */
#include <sys/socket.h>
#include <netdb.h>

#define TAIL_BUF 100
#define T_NOM 20
main(int argc, char** argv) {
  int sock,               /* descipteur de la socket locale */
      port,               /* variables de lecture */
      size_addr, 	  /* taille de l'adresse d'une socket */
      err;                /* code d'erreur */
  char chaine[TAIL_BUF];
  
  char nomMachine[T_NOM];   /* nom de la machine dest */
  
  struct sockaddr_in adrDest;     /* adresse de la socket distante */
  struct sockaddr_in adrLocal;	  /* adresse de la socket locale */

  struct hostent* host;    /* pour l'adresse du dest */
  
  
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
  adrLocal.sin_family = AF_INET;
  adrLocal.sin_port = htons(atoi(argv[1]));
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
  scanf("%d", &port);
  printf("client : initaddr pour %s, %d\n",  nomMachine, port);


  host = gethostbyname(nomMachine);
  if (host == NULL) {
    printf("initAddr : erreur gethostbyname\n");
    exit(4);
  }

  /* recopie de l'adresse IP */
  adrDest.sin_addr.s_addr = ((struct in_addr *) (host->h_addr_list[0]))->s_addr;
      
  /* initialisation de l'adresse de la socket */
  adrDest.sin_family = AF_INET;
  bzero(adrDest.sin_zero, 8);
  adrDest.sin_port = htons(port);


  /* 
   * saisie et envoi de la chaine 
   */
  printf("client : donner la chaine : ");
  scanf("%s", chaine);
  printf("client : envoi de - %s - \n", chaine);
  
  err = sendto(sock, chaine, strlen(chaine)+1, 0, 
               (struct sockaddr*)&adrDest, sizeof(struct sockaddr_in));
  if (err != strlen(chaine)+1) {
      perror("client : erreur sur le send\n");
      exit(4);
  }

  printf("client : chaine envoyee\n");

  /* fermeture de la socket */
  close(sock);
}
 

