
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

/*
 *
 */

int main(int argc, char** argv) {

    int socketClient;
    struct sockaddr_in infosServeur;
    int monEntier = 444;
    int entierRecu;
    int retourConnect;
    int retourWrite;
    int retourRead;

    /* Création de la socket client */
    socketClient = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (socketClient == -1) {
        printf("Problème création socket client : %s \n", strerror(errno));
    }


    infosServeur.sin_addr.s_addr = inet_addr("172.18.58.90");
    infosServeur.sin_family = AF_INET;
    infosServeur.sin_port = htons(5555);
    int addrlen = sizeof (infosServeur);


    retourConnect = connect(socketClient, (struct sockaddr *) &infosServeur, addrlen);


    retourWrite = write(socketClient, &monEntier, sizeof (monEntier));


    retourRead = read(socketClient, &entierRecu, sizeof (entierRecu));

    int close(int socketClient);


    printf("Entier recu : %i", entierRecu);

    return (EXIT_SUCCESS);
}