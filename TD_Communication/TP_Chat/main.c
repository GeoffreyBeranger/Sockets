#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

/*
 * 
 */
int main(int argc, char** argv) {

    int socketServeur;
    struct sockaddr_in infosServeur;
    struct sockaddr_in infosClient;
    int tailleClient;
    int retourBind;
    int retourListen;
    int SocketClient;
    int retourWrite;
    char protocolHTML[1024] = "HTTP/1.1 200 OK\nContent-Lenght: 3301\nContent-Type: text/html;\n\n <html></head><body><center><h1>C'est Notre serveur http</h1></center></body></html>";

    socketServeur = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (socketServeur == -1) {
        printf("Erreur de creation de la socket \n");
    }

    infosServeur.sin_family = AF_INET;
    infosServeur.sin_port = htons(8888);
    infosServeur.sin_addr.s_addr = htonl(INADDR_ANY);

    tailleClient = sizeof (infosClient);

    retourBind = bind(socketServeur, (struct sockaddr*) &infosServeur, sizeof (infosServeur));
    if (retourBind == -1) {
        printf("Erreur Bind \n");
    }
    retourListen = listen(socketServeur, 10);
    if (retourListen == -1) {
        printf("Erreur Listen \n");
    }

    while (1) {
        SocketClient = accept(socketServeur, (struct sockaddr*) &infosClient, &tailleClient);
        if (SocketClient == -1) {
            printf("Erreur de connexion \n");
        }
        printf("%s", protocolHTML);
        retourWrite = write(SocketClient, &protocolHTML, strlen(protocolHTML));
        if (retourWrite == -1) {
            printf("Erreur écriture");
        }
        close(SocketClient);
    }

    close(socketServeur);
    return (EXIT_SUCCESS);
}
