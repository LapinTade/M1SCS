
/*
**********************************************************
*
* Programme : serveur.c
*
* ecrit par : LP.
*
* resume : recoit une chaine de caracteres du programme client
* en mode connecte
*
* date : 25 / 01 / 06
*
***********************************************************
*/
/* include generaux */
#include &lt;
string.h&gt;
#include &lt;
stdio.h&gt;
#include &lt;
stdlib.h&gt;
/* include fonctions TCP */
#include "donnees.h"
#include "../fonctionsTCP.h"
/* taille du buffer de reception */
#define TAIL_BUF 100
Resultat calcul(Data b){
    Resultat rep;
    switch(b.operateur){
        case 0 :
        rep.err=0;
        rep.result = b.op1 + b.op2;
        break;
        case 1 :
        rep.err=0;
        rep.result = b.op1 - b.op2;
        break;
        case 2 :
        rep.err=0;
        rep.result = b.op1 * b.op2;
        break;
        case 3 :
        if(b.op2 == 0){
            rep.err = -2;
        }
        else{
            rep.result = b.op1 / b.op2;
        }
        break;
        default :
        rep.err=-1;
        break;
    }
    return rep;
}
main(int argc, char** argv) {
    Data b;
    int sock, err;
    int sock_trans[15];
    int acc=0;
    fd_set readfs;
    Resultat rep;
    struct sockaddr_in nom_transmis;
    /* adresse de la socket de */
    /* transmission */
    socklen_t size_addr_trans;
    /* taille de l'adresse d'une socket */
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
    sock = socketServeur(atoi(argv[1]));
    if (sock &lt;
    0) {
        printf("serveur : erreur socketServeur\n");
        exit(2);
    }
    /*
    * attente de connexion
    */
    sock_trans[0] = accept(sock,
    NULL,
    NULL);
    if (sock_trans &lt;
    0) {
        perror("serveur : erreur sur accept");
        close(sock);
        exit(3);
    }
    int i=0;
    while(1){
        if(i&lt;
        15){
            i++;
        }
        else{
            i=0;
        }
        FD_ZERO(&readfs);
        FD_SET(sock, &readfs);
        if(acc){
            FD_SET(sock_trans[i], &readfs);
        }
        if((err = select(FD_SETSIZE, &readfs, NULL, NULL, NULL)) &lt;
        0){
            perror("select()");
            exit(errno);
        }
        if(FD_ISSET(sock, &readfs)){
            acc=1;
            //accept
            sock_trans[i] = accept(sock,
            NULL,
            NULL);
            FD_SET(sock_trans[i], &readfs);
        }
        if(FD_ISSET(sock_trans[i], &readfs) && acc){
            //recv
            err = recv(sock_trans[i], &b, sizeof(Data), 0);
            if (err &lt;
            0) {
                perror("serveur : erreur dans la reception");
                shutdown(sock_trans[i], 2);
                close(sock_trans[i]);
                close(sock);
                exit(4);
            }
            rep=calcul(b);
            err = send(sock_trans[i], &rep, sizeof(Resultat), 0);
            if (err &lt;
            = 0) {
                perror("client : erreur sur le send");
                shutdown(sock_trans[i], 2);
                close(sock_trans[i]);
                exit(3);
            }
        }
        /*
        * arret de la connexion et fermeture
        */
        shutdown(sock_trans[i], 2);
        close(sock_trans[i]);
    }
    close(sock);
} 
