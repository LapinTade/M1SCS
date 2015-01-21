/*
 **********************************************************
 *
 *  Programme : fonctionsSocket.h
 *
 *  ecrit par : LP.
 *
 *  resume :    entete des fonction d'initialisation des sockets en mode 
 *              non connecte
 *
 *  date :      25 / 01 / 06
 *
 ***********************************************************
 */

/* include generaux */
#include <sys/types.h>
#include <strings.h>
#include <stdio.h>

/* include socket */
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>

struct sockaddr_in* initAddr(char* nom_machine, ushort no_port);
int adresseUDP(char* nom_machine, ushort no_port, struct sockaddr_in*);
int socketUDP(ushort no_port);
