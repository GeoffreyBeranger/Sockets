/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: gberanger
 *
 * Created on 10 septembre 2019, 11:36
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>

/*
 * 
 */

typedef struct{
    unsigned char jour;
    unsigned char mois;
    unsigned short int annee;
    char jourDeLaSemaine[10];	// le jour en toute lettre
}datePerso;
    
int main(int argc, char** argv) {
    datePerso dateDuClient;
    int socketServer;
    struct sockaddr_in informationsServeur;
    struct sockaddr_in informationsClient;
    int retourRecvfrom;
    int retourBind;
    int tailleAdr;
    
    socketServer=socket(PF_INET,SOCK_DGRAM,IPPROTO_UDP);
    if(socketServer==-1){
        printf("pb socket : %s\n",strerror(errno));
        exit errno;
    }
    // init de informationsServeur avec les infos du serveur
    // IP, port, type
    informationsServeur.sin_family = AF_INET;
    informationsServeur.sin_port = ntohs (4444);
    informationsServeur.sin_addr.s_addr = inet_addr("172.18.58.90");
    
    memset(informationsClient.sin_zero,0,sizeof(informationsClient.sin_zero));
    
    retourBind = bind(socketServer,(struct sockaddr*) &informationsServeur, sizeof(informationsServeur));
    if(retourBind==-1){
        printf("pb bind : %s\n",strerror(errno));
        exit errno;
    }        
    do{
        tailleAdr = sizeof(informationsClient);
        // recevoir l'entier en provenance du serveur
        retourRecvfrom = recvfrom(socketServer,
                &dateDuClient,
                sizeof(dateDuClient),
                0,
                (struct sockaddr*)&informationsClient,
                &tailleAdr);
        if(retourRecvfrom==-1){
            printf("pb reception : %s\n",strerror(errno));
            exit errno;
        }
        printf("Message du client : %s %d/%d/%d \n",dateDuClient.jourDeLaSemaine, dateDuClient.jour,dateDuClient.mois,dateDuClient.annee);
        
    }while(1);
    
    return (EXIT_SUCCESS);
}
