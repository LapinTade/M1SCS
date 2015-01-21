/*
 **********************************************************
 *
 *  Programme : emetteur.c
 *
 *  ecrit par : LP.
 *
 *  resume : socket UDP 
 *
 *  date :      25 / 01 / 06
 *
 ***********************************************************
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

/* fonctions des sockets UDP */
#include "fonctionsUDP.h"

#define TAIL_BUF 100
#define T_NOM 20
main(int argc, char** argv) {
  int sock,               /* descripteur de la socket locale */
      port,               /* variables de lecture */
      err;                /* code d'erreur */
  char chaine[TAIL_BUF];

  char nomMachine[T_NOM]; /* nom de la machine dest */
  
  struct sockaddr_in addrDest;

  if (argc != 2) {
    printf("usage : %s no_port\n", argv[0]);
    exit(1);
  }

  /* 
   * creation d'une socket, domaine AF_INET, protocole TCP 
   */
  printf("emetteur : creation de la socket sur %d\n", atoi(argv[1]));
  sock = socketUDP(atoi(argv[1]));
  if (sock < 0) {
    printf("emetteur : erreur %d de socketUDP \n", sock);
    exit(2);
  }
  
  /*
   * saisie et initialisation de l'adresse du destinataire
   */
  printf("emetteur : donner la machine dest : ");
  scanf("%s", nomMachine);
  printf("emetteur : donner le port dest : ");
  scanf("%d", &port);
  printf("emetteur : initaddr pour %s, %d\n",  nomMachine, port);
  err = adresseUDP(nomMachine, port, &addrDest);
  if (err  == -1) {
    perror("emetteur : erreur adresse");
    close(sock);
    exit(3);
  }
  
  /* 
   * saisie et envoi de la chaine 
   */
  printf("emetteur : donner la chaine : ");
  scanf("%s", chaine);
  printf("emetteur : envoi de - %s - \n", chaine);
  
  err = sendto(sock, chaine, strlen(chaine)+1, 0, 
               (struct sockaddr*)&addrDest, sizeof(struct sockaddr_in));
  if (err != strlen(chaine)+1) {
    perror("emetteur : erreur sur le send");
    close(sock);
    exit(4);
  }
  
  printf("emetteur : chaine envoyee\n");

  /* fermeture de la socket */
  close(sock);
}
 

