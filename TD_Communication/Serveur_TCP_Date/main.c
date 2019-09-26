


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

/*
 * 
 */

typedef struct {
    unsigned char jour;
    unsigned char mois;
    unsigned short int annee;
    char jourDeLaSemaine[10]; // le jour en toute lettre
} datePerso;

int main(int argc, char** argv) {
    
    struct sockaddr_in infosServeur;
    struct sockaddr_in infosClient;
    int socketServeur;
    int retourBind;
    int retourListen;
    int retourAccept;
    int retourRead;
    int tailleClient;
    datePerso date;

    printf("serveur TCP sur port 7777 attend une structure\n");
    socketServeur = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    infosServeur.sin_family = AF_INET;
    infosServeur.sin_port = htons(7777);
    infosServeur.sin_addr.s_addr = htonl(INADDR_ANY);



    retourBind = bind(socketServeur, (struct sockaddr*) &infosServeur, sizeof (infosServeur));
    tailleClient = sizeof (infosClient);

    retourListen = listen(socketServeur, 10);

    while (1) {

        retourAccept = accept(socketServeur, (struct sockaddr*) &infosClient, &tailleClient);
        retourRead = read(retourAccept, &date, sizeof (date));
        printf("message Reçu du client %s : %s %hhu/%hhu/%hu \n", inet_ntoa(infosClient.sin_addr), date.jourDeLaSemaine, date.jour, date.mois, date.annee);

        close(retourAccept);
    }

    close(socketServeur);
    return (EXIT_SUCCESS);
}