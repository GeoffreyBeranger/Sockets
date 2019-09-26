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
int main(int argc, char** argv) {

    struct sockaddr_in infosServeur;
    struct sockaddr_in infosClient;
    int socketServeur;
    int retourBind;
    int retourListen;
    int retourAccept;
    int retourRead;
    int retourWrite;
    int tailleClient;
    int entierRecu;
 


    printf("serveur TCP sur port 5555 attend un entier\n");
    socketServeur = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    infosServeur.sin_family = AF_INET;
    infosServeur.sin_port = htons(5555);
    infosServeur.sin_addr.s_addr = htonl(INADDR_ANY);



    retourBind = bind(socketServeur, (struct sockaddr*) &infosServeur, sizeof (infosServeur));
    tailleClient = sizeof (infosClient);

    retourListen = listen(socketServeur,10);

    while (1) {
        
        retourAccept = accept(socketServeur, (struct sockaddr*) &infosClient, &tailleClient);
        retourRead = read(retourAccept, &entierRecu, sizeof (entierRecu));
        printf("message Reçu du client %s : %i\n", inet_ntoa(infosClient.sin_addr), entierRecu);
        entierRecu = -entierRecu;
        retourWrite = write(retourAccept, &entierRecu, sizeof (entierRecu));

       close(retourAccept);
    }

    close(socketServeur);
    return (EXIT_SUCCESS);
}
