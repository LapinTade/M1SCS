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
#include "donnee.h"

#define TAIL_BUF 100
main(int argc, char **argv) {
	Data a;
	Resultat res;
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
  
  a.op1 = 40;
  a.op2 = 0;
  a.operateur = 3;
  
  /*
   * envoi de la chaine
   */
  err = send(sock, &a, sizeof(Data), 0);
  if (err < 0) {
    perror("client : erreur sur le send");
    shutdown(sock, 2); close(sock);
    exit(3);
  }
  printf("client : envoi realise: %d %d %d\n",a.op1,a.operateur,a.op2);
  
  res.result = 0;
  res.error = 0;
  err = recv(sock, &res, TAIL_BUF, 0);
  if (err < 0) {
    perror("client : erreur sur le recv");
    shutdown(sock, 2); close(sock);
    exit(3);
  }
  
  if(res.error < 0) {
  	printf("ERROR DANS L'OPERATION. CODE ERROR: %d\n",res.error);
  } else {
  	printf("Resultat de l'operation: %d\n", res.result);
  }
  
  
  /* 
   * fermeture de la connexion et de la socket 
   */
  shutdown(sock, 2);
  close(sock);
}
 

