/*
 **********************************************************
 *
 *  Programme : fonctionUDP.c
 *
 *  ecrit par : LP.
 *
 *  resume :    fonctions d'initialisation pour les sockets
 *                 en mode non connecte
 *
 *  date :      25 / 01 / 06
 *
 ***********************************************************
 */

/* includes generaux */
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>

/* includes socket */
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

/*******************************************
 *
 * fonction d'initialisation d'une socket locale
 *
 *******************************************/
int socketUDP (ushort port) {         
  int sock,      /* descripteur de la socket */
      err;	 /* code d'erreur */

  struct sockaddr_in nom;	/* adresse de la socket */
  
  socklen_t       size_addr;  	/* taille de l'adresse d'une socket */
  
  size_addr = sizeof(struct sockaddr_in);
  
  /* Creation de la socket, protocole UDP */
  sock = socket(AF_INET, SOCK_DGRAM, 0);
  if (sock < 0) {
    perror("socketUDP : erreur de socket\n");
    return -1;
  }
  
  /* 
   * Initialisation de l'adresse de la socket 
   */
  nom.sin_family = AF_INET;
  nom.sin_port = htons(port);
  nom.sin_addr.s_addr = INADDR_ANY;
  bzero(nom.sin_zero, 8);
  
  
  /*
   * mode SO_REUSEADDR pour eviter les: "address already in use"
   */
  int on = 1;
  err = setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
  if (err < 0) {
    perror("socketUDP : erreur setsockopt");
    return -2;  
  }
  
  /* 
   * attribution de l'adresse a la socket
   */
  err = bind(sock, (struct sockaddr *)&nom, size_addr);
  if (err < 0) {
    perror("socketUDP : erreur sur le bind");
    return -3;
  }
  
  /*
   * retourne le descripteur de socket
   */
  return sock;
}

/*******************************************
 *
 * fonction d'initialisation d'une structure d'adresse
 *
 *   Attention, dans cette fonction l'adresse est allouee dynamiquement
 *   il faut eventuellement penser a la liberer
 *
 *******************************************/
int adresseUDP(char* nom_machine, ushort no_port, struct sockaddr_in* paddr) {
  struct hostent* host;
  
  /* cherche l'adresse de la machine */
  host = gethostbyname(nom_machine);
  if (host == NULL) {
    printf("addresseUDP : erreur gethostbyname\n");
    return -1;
  }
  
  /*
   * recopie de l'adresse IP
   */
  paddr->sin_addr.s_addr = ((struct in_addr *) (host->h_addr_list[0]))->s_addr;
  
  /* initialisation de l'adresse de la socket */
  paddr->sin_family = AF_INET;
  bzero(paddr->sin_zero, 8);
  paddr->sin_port = htons(no_port);

  return 0;
}

/*******************************************
 *
 * fonction de creation d'une structure d'adresse
 *
 *   Attention, dans cette fonction l'adresse 
 *   est allouee dynamiquement ;
 *   il faut eventuellement penser a la liberer
 *
 *******************************************/
struct sockaddr_in* initAddr(char* nom_machine, ushort no_port){
  struct sockaddr_in *paddr;
  struct hostent* host;
  
  /* allocation de la structure d'adresse */
  paddr = (struct sockaddr_in*) malloc(sizeof(struct sockaddr_in));
  if (paddr == NULL) {
    perror("initAddr : erreur malloc");
    return NULL;
  }
  
  /* cherche l'adresse de la machine 
   */
  host = gethostbyname(nom_machine);
  if (host == NULL) {
    printf("initAddr : erreur gethostbyname\n");
    return NULL;
  }

  /*
   * recopie de l'adresse IP
   */
  paddr->sin_addr.s_addr = ((struct in_addr *) (host->h_addr_list[0]))->s_addr;
      
  /* initialisation de l'adresse de la socket */
  paddr->sin_family = AF_INET;
  bzero(paddr->sin_zero, 8);
  paddr->sin_port = htons(no_port);
  
  return paddr;
}
