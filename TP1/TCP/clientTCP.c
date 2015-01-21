/*
 **********************************************************
 *
 *  Programme : client.c
 *
 *  ecrit par : LP.
 *
 *  resume :    envoi une chaine de caracteres a un programme serveur
 *              dont le nom de machine et le numero de port son lus
 *              au clavier. 
 *
 *  date :      19 / 01 / 06
 *
 ***********************************************************
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>

#define TAIL_BUF 50
main(int argc, char **argv) {

  char chaine[TAIL_BUF];   /* buffer */
  int sock,                /* descripteur de la socket locale */
      port,                /* variables de lecture */
      err;                 /* code d'erreur */
  char* nomMachine;
  struct hostent*    host; /* description de la machine serveur */
  struct sockaddr_in nom;  /* adresse de la sochet du serveur */

  int size_addr_in = sizeof(struct sockaddr_in);

  /* verification des arguments */
  if (argc != 3) {
    printf("usage : client nom_machine no_port\n");
    exit(1);
  }
  
  nomMachine = argv[1];
  port = atoi(argv[2]);

  /* 
   * creation d'une socket, domaine AF_INET, protocole TCP 
   */
  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0) {
    perror("client : erreur sur la creation de socket");
    return -1;
  }
  
  /* 
   * initialisation de l'adresse de la socket 
   */
  nom.sin_family = AF_INET;
  bzero(nom.sin_zero, 8);
  nom.sin_port = htons(port);
  
  /* recherche de l'adresse de la machine */
  host = gethostbyname (nomMachine);
  if (host == NULL) {   
    printf("client : erreur gethostbyname %d\n", errno);
    return -2;
  }
  
  /* recopie de l'adresse IP */
  nom.sin_addr.s_addr = ((struct in_addr *) (host->h_addr_list[0]))->s_addr;
					     
  /* 
   * connection au serveur 
   */
  err = connect(sock, (struct sockaddr *)&nom, size_addr_in);
  if (err < 0) {
    perror("client : erreur a la connection de socket\n");
    return -3;
  }
  
  /* 
   * saisie de la chaine 
   */
  printf("client : donner une chaine : ");
  scanf("%s", chaine);
  printf("client : envoi de - %s - \n", chaine);

  int i; 
  for(i=0 ; i<1000 ; i++) {
    
    /*
     * envoi de la chaine
     */
    //err = send(sock, chaine, strlen(chaine) + 1, 0);
    err = send(sock, chaine, TAIL_BUF, 0);
    if (err <= 0) {
      //if (err != strlen(chaine)+1) {
      perror("client : erreur sur le send");
      shutdown(sock, 2); close(sock);
      exit(3);
    }
    printf("client : envoi %d realise\n", i);
  }
  
  /* 
   * fermeture de la connexion et de la socket 
   */
  shutdown(sock, 2);
  close(sock);
}
 

