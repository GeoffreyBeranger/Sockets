/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: gberanger
 *
 * Created on 10 septembre 2019, 11:37
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>

/*
 * 
 */

typedef struct
{
    unsigned char jour;
    unsigned char mois;
    unsigned short int annee;
    char jourDeLaSemaine[10]; // Le Jour en Toute Lettre
}datePerso;


int main(int argc, char** argv) {

    int socketClient;
    struct sockaddr_in informationsServeur;
    int monEntier;
    int retourSendto;
    
    datePerso date;
    date.jour = 17;
    date.mois =  9;
    date.annee = 2019;
    strcpy(date.jourDeLaSemaine,"Mardi");

    socketClient = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if (socketClient == -1) {

        printf("pb socket : %s\n", strerror(errno));
        exit(errno);
    }
    // init de informationsServeur avec les infos du serveur
    //IP Port Type
    informationsServeur.sin_family = AF_INET;
    informationsServeur.sin_port = htons(4444);
    informationsServeur.sin_addr.s_addr = inet_addr("172.18.58.93");
    memset(&informationsServeur.sin_zero,0,sizeof(informationsServeur.sin_zero));

    monEntier = 1234;
    //Envoyer monEntier au serveur
    retourSendto = sendto(socketClient,&date,sizeof(date),0,&informationsServeur,sizeof(informationsServeur));
    if (retourSendto)
    {
       
    }
    
    
        return (EXIT_SUCCESS);
}

