/*
 **********************************************************
 *
 *  Programme : serveur.c
 *
 *  resume :    recoit une chaine de caracteres du programme client
 *
 *  date :      19 / 01 / 06
 *
 ***********************************************************
 */

#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>

/* taille du buffer de reception */
#define TAIL_BUF 500

int main(int argc, char** argv) {
  int  sockConx,        /* descripteur socket connexion */
       sockTrans,       /* descripteur socket transmission */
       port,            /* numero de port */
       sizeAddr,        /* taille de l'adresse d'une socket */
       err;	        /* code d'erreur */
  
  char buffer[TAIL_BUF]; /* buffer de reception */
  
  
  struct sockaddr_in nomTransmis;	/* adresse socket de transmission */
  struct sockaddr_in nomConnecte;	/* adresse de la sochet connectee*/
  
  
  /*
   * verification des arguments
   */
  if (argc != 2) {
    printf ("usage : serveurTCP no_port\n");
    return -1;
  }
  
  port  = atoi(argv[1]);
  sizeAddr = sizeof(struct sockaddr_in);
  
  /* 
   * creation de la socket, protocole TCP 
   */
  sockConx = socket(AF_INET, SOCK_STREAM, 0);
  if (sockConx < 0) {
    perror("serveurTCP: erreur de socket\n");
    return -2;
  }
  
  /* 
   * initialisation de l'adresse de la socket 
   */
  nomConnecte.sin_family = AF_INET;
  nomConnecte.sin_port = htons(port); // conversion en format réseau (big endian)
  nomConnecte.sin_addr.s_addr = INADDR_ANY; 
  // INADDR_ANY : 0.0.0.0 (IPv4) donc htonl inutile ici, car pas d'effet
  bzero(nomConnecte.sin_zero, 8);
  
  /* 
   * attribution de l'adresse a la socket
   */
  err = bind(sockConx, (struct sockaddr *)&nomConnecte, sizeAddr);
  if (err < 0) {
    perror("serveurTCP: erreur sur le bind");
    close(sockConx);
    return -3;
  }
  
  /* 
   * utilisation en socket de controle, puis attente de demandes de 
   * connexion.
   */
  err = listen(sockConx, 1);
  if (err < 0) {
    perror("serveurTCP: erreur dans listen");
    return -4;
  }
  
  /*
   * attente de connexion
   */
  sockTrans = accept(sockConx, 
		     (struct sockaddr *)&nomTransmis, 
		     (socklen_t *)&sizeAddr);
  if (sockTrans < 0) {
    perror("serveurTCP:  erreur sur accept");
    return -5;
  }
  
  printf("Connecte\n");
  while(1) { 
    scanf("%s", buffer);
    /*
     * reception et affichage du message en provenance du client
     */
    err = recv(sockTrans, buffer, TAIL_BUF, 0);
    if (err < 0) {
      perror("serveurTCP: erreur dans la reception");
      shutdown(sockTrans, 2); close(sockTrans);
      return -7;
    }
    printf("serveurTCP : voila le message recu: %s\n", buffer);
  }
  
  /* 
   * arret de la connexion et fermeture
   */
  shutdown(sockTrans, 2); close(sockTrans);
  close(sockConx);
  
  return 0;
}
