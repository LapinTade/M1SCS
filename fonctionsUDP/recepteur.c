/*
 **********************************************************
 *
 *  Programme : recepteur.c
 *
 *  ecrit par : LP.
 *
 *  resume :    recoit une chaine de caracteres du programme client
 *
 *  date :      25 / 01 / 06
 *
 ***********************************************************
 */

/* include generaux */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/* include socket */
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>

/* taille du buffer de reception */
#define TAIL_BUF 100

main(int argc, char** argv) {
  int sock,	        /* descripteur de socket locale */
      err;	        /* code d'erreur */

  struct sockaddr_in nomEmet;	    /* adresse de la socket */
  
  char            buffer[TAIL_BUF]; /* buffer de reception */
  
  socklen_t       sizeAddr;	    /* taille de l'adresse d'une socket */
  
  
  if (argc != 2) {
    printf("usage : %s no_port\n", argv[0]);
    exit(1);
  }
  
  sizeAddr = sizeof(nomEmet);
  
  /* creation de la socket, protocole UDP */
  printf("recepteur : creation de socket sur %d\n", atoi(argv[1]));
  sock = socketUDP(atoi(argv[1]));
  if (sock < 0) {
    perror("recepteur : erreur socketUDP");
    exit(2);
  }
  
  /*
   * reception et affichage du message en provenance du client
   */
  err = recvfrom(sock, buffer, TAIL_BUF, 0, 
		 (struct sockaddr*) &nomEmet, 
		 &sizeAddr);
  if (err < 0) {
    perror("recepteur, erreur dans la reception");
    close(sock);
    exit(3);
  }
  printf("Voila le message recu: %s\n", buffer);
  
  /* fermeture de la socket */
  close(sock);
}

