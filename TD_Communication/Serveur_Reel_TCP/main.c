/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: gberanger
 *
 * Created on 26 septembre 2019, 16:30
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char** argv) {

    struct sockaddr_in infosServeur;
    struct sockaddr_in infosClient;
    int socketServeur;
    int socketClient;
    int retourBind;
    int retourListen;
    int retourRead;
    int retourWrite;
    int tailleClient;
    float entierRecu;
   


    printf("serveur UDP sur le port 5555 \n");
    socketServeur = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    infosServeur.sin_family = AF_INET;
    infosServeur.sin_port = htons(5555);
    infosServeur.sin_addr.s_addr = htonl(INADDR_ANY);



    retourBind = bind(socketServeur, (struct sockaddr*) &infosServeur, sizeof (infosServeur));
    tailleClient = sizeof (infosClient);

    retourListen = listen(socketServeur, 5);

    while (1) {
        socketClient = accept(socketServeur, (struct sockaddr*) &infosClient, sizeof (infosClient));
        retourRead = read(socketClient, (struct sockaddr*) &entierRecu, sizeof (entierRecu));
        printf("Message reçu : %f", entierRecu);
        entierRecu = -entierRecu;
        retourWrite = write(socketClient, (struct sockaddr*) &entierRecu, sizeof (entierRecu));

       
    }

   int close(int socketClient);
    return (EXIT_SUCCESS);
}
