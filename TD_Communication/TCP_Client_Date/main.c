

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

typedef struct {
    unsigned char jour;
    unsigned char mois;
    unsigned short int annee;
    char jourDeLaSemaine[10];
} datePerso;

int main(int argc, char** argv) {

    int socketClient;
    struct sockaddr_in infosServeur;
    datePerso date;
    int retourConnect;
    int retourWrite;
    int retourRead;

    date.annee = 2019;
    date.jour = 13;
    strcpy(date.jourDeLaSemaine, "Vendredi");
    date.mois = 9;

    socketClient = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (socketClient == -1) {
        printf("Problème création socket client : %s \n", strerror(errno));
    }


    infosServeur.sin_addr.s_addr = inet_addr("172.18.58.90");
    infosServeur.sin_family = AF_INET;
    infosServeur.sin_port = htons(7777);
    int addrlen = sizeof (infosServeur);


    retourConnect = connect(socketClient, (struct sockaddr *) &infosServeur, addrlen);


    retourWrite = write(socketClient, &date, sizeof (date));

    int close(int socketClient);

    return (EXIT_SUCCESS);
}
