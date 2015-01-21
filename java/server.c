/*
 **********************************************************
 *
 *  Programme : serveur.c
 *
 *  ecrit par : LP.
 *
 *  resume :    recoit une chaine de caracteres du programme client
 *                en mode connecte
 *
 *  date :      25 / 01 / 06
 *
 ***********************************************************
 */

/* include generaux */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/* include fonctions TCP */
#include "fonctionsTCP.h"

/* taille du buffer de reception */
#define TAIL_BUF 100

main(int argc, char** argv) {
	char a[50];
	char* res;
  int sock_cont, 
      sock_trans,       /* descripteurs des sockets locales */
      err;	            /* code d'erreur */

  struct sockaddr_in nom_transmis;	/* adresse de la socket de */
					                     /* transmission */
  
  char            buffer[TAIL_BUF];	/* buffer de reception */
  
  socklen_t      size_addr_trans;	/* taille de l'adresse d'une socket */
  
  
  
  /*
   * verification des arguments
   */
  if (argc != 2) {
    printf ("usage : serveur no_port\n");
    exit(1);
  }
  
  size_addr_trans = sizeof(struct sockaddr_in);
  
  /* 
   * creation de la socket, protocole TCP 
   */
  printf("serveur : creation de la socket sur %d\n", atoi(argv[1]));
  sock_cont = socketServeur(atoi(argv[1]));
  if (sock_cont < 0) {
    printf("serveur : erreur socketServeur\n");
    exit(2);
  }
  
  /*
   * attente de connexion
   */
  sock_trans = accept(sock_cont, 
		      (struct sockaddr *)&nom_transmis, 
		      &size_addr_trans);
  if (sock_trans < 0) {
    perror("serveur :  erreur sur accept");
    close(sock_cont);
    exit(3); 
  }
  
  /*
   * reception et affichage du message en provenance du client
   */
  err = recv(sock_trans, a, 50, 0);
  if (err < 0) {
    perror("serveur : erreur dans la reception");
    shutdown(sock_trans, 2); close(sock_trans); close(sock_cont);
    exit(4);
  }
  a[err+1]='\0';
  printf("Message reçut: -[%s]-\n", a);
  
  /*
   * REP
   */
  /*
  err = send(sock_trans, &res, sizeof(Data), 0);
  if (err < 0) {
    perror("client : erreur sur le send");
    shutdown(sock_trans, 2); close(sock_trans);
    exit(3);
  }
  */
  
  /* 
   * arret de la connexion et fermeture
   */
  shutdown(sock_trans, 2);
  close(sock_trans);
  close(sock_cont);
}
