#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>                                                             
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>


#define TAIL_BUF 256

main(int argc, char **argv) {

  char chaine[TAIL_BUF];   /* buffer */
  int sock, 
            sockServ,
            sockTrans,               /* descripteur de la socket locale */
      port,                /* variables de lecture */
      err;                 /* code d'erreur */
  char* nomMachine;
;

  /* verification des arguments */
  if (argc != 3) {
    printf("usage : client nom_machine no_port\n");
    exit(1);
  }
  int sizeAddr = sizeof(struct sockaddr_in);
  nomMachine = argv[1];
  port = atoi(argv[2]);
  sock = sockClient(nomMachine, port);
  
  
  /* 
   * saisie de la chaine 
   */
  printf("client : donner une chaine : ");
  scanf("%s", chaine);
  printf("client : envoi de - %s - \n", chaine);

  int i; 
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
    sockServ = sockServeur(33333);
    sockTrans = accept(sockServ, 
                     (struct sockaddr *)&nomMachine, 
                     (socklen_t *)&sizeAddr);
        if (sockTrans < 0) {
            perror("serveurTCP:  erreur sur accept");
            return -5;
          }
          int cpt=0;
          while(cpt<1000){
                /*
                * Attente de reponse
                */
                char res[TAIL_BUF];
                err = recv(sockTrans, res, TAIL_BUF, 0);
                if (err < 0) {
                  perror("clientTCP: erreur dans la reception");
                  shutdown(sockTrans, 2); close(sockTrans);
                  return -7;
                }
                printf("clientTCP : voila le message recu: %s\n", res);
                //renvoi
                err = send(sock, res, TAIL_BUF, 0);
                if (err <= 0) {
                  //if (err != strlen(chaine)+1) {
                  perror("client : erreur sur le send");
                  shutdown(sock, 2); close(sock);
                  exit(3);
                }
                cpt++;
          }
  
  /* 
   * fermeture de la connexion et de la socket 
   */
  shutdown(sockTrans, 2);
  close(sock);
  close(sockServ);
  close(sockTrans);
}
