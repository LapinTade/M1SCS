/*
 **********************************************************
 *
 *  Programme : client.c
 *
 *  ecrit par : LP.
 *
 *  resume :    envoi une chaine de caracteres a un programme serveur
 *               en mode connecte
 *
 *  date :      25 / 01 / 06
 *
 ***********************************************************
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fonctionsTCP.h"

#define TAIL_BUF 100
main(int argc, char **argv) {
  char chaine[TAIL_BUF];
  int sock,               /* descripteur de la socket locale */
      err;                /* code d'erreur */
  /*
   * verification des arguments
   */
  if (argc != 3) {
    printf("usage : client nom_machine no_port\n");
    exit(1);
  }
  
  /* 
   * creation d'une socket, domaine AF_INET, protocole TCP 
   */
  printf("client : connect to %s, %d\n", argv[1], atoi(argv[2]));
  sock = socketClient(argv[1], atoi(argv[2]));
  if (sock < 0) { 
    printf("client : erreur socketClient\n");
    exit(2);
  }
  
  /* 
   * saisie de la chaine 
   */
  printf("client : donner une chaine : ");
  scanf("%s", chaine);
  printf("client : envoi de - %s - \n", chaine);
  
  
  /*
   * envoi de la chaine
   */
  err = send(sock, chaine, strlen(chaine)+1, 0);
  if (err != strlen(chaine)+1) {
    perror("client : erreur sur le send");
    shutdown(sock, 2); close(sock);
    exit(3);
  }
  printf("client : envoi realise\n");
  
  /* 
   * fermeture de la connexion et de la socket 
   */
  shutdown(sock, 2);
  close(sock);
}
 

