/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: abourrelly
 *
 * Created on 10 septembre 2019, 11:37
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

int main(int argc, char** argv) {
    int serveurSocket;
    struct sockaddr_in informationsServeur;
    struct sockaddr_in informationsClient;
    int monEntier;
    int messageClient;
    int retourSendto;
    int retourRecvfrom;
    int retourBind;
    int tailleClient;

    serveurSocket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (serveurSocket == -1) {
        printf("pb socket : %s\n", strerror(errno));
        exit errno;
    }
    // init de informationsServeur
    // IP, port, type
    informationsServeur.sin_family = AF_INET;
    informationsServeur.sin_port = htons(2222);
    informationsServeur.sin_addr.s_addr = inet_addr("172.18.58.90");

    memset(&informationsServeur.sin_zero, 0, sizeof (informationsServeur.sin_zero));

    retourBind = bind(serveurSocket, (struct sockaddr *) &informationsServeur, sizeof (informationsServeur));
    if (retourBind == -1) {
        printf("pb bind : %s\n", strerror(errno));
        exit errno;
    }
    do {

        tailleClient = sizeof (informationsClient);

        retourRecvfrom = recvfrom(serveurSocket, &messageClient, sizeof (messageClient), 0, (struct sockaddr *) &informationsClient, &tailleClient);
        if (retourRecvfrom == -1) {
            printf("pb recvfrom : %s\n", strerror(errno));
            exit errno;
        }
        monEntier = messageClient * -1;
        retourSendto = sendto(serveurSocket, &monEntier, sizeof (monEntier), 0, (struct sockaddr *) &informationsClient, sizeof (informationsClient));
        if (retourSendto == -1) {
            printf("pb retourSendto : %s\n", strerror(errno));
            exit errno;
        }
        char *ip = inet_ntoa(informationsClient.sin_addr);
        printf("Message de %s: %d\n", ip, messageClient);
    } while (1);
    return (EXIT_SUCCESS);
}
