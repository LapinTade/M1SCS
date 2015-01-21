/* inclusions standards */
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
  port=atoi(argv[1]);
  size_addr = sizeof(struct sockaddr_in);
  sock=adresseUDP(nomMachine, port, &adrDest);

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
 

