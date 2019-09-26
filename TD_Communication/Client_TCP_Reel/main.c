

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
    struct sockaddr_in informationsServeur;
    float monEntier;
    int entierDuServeur;
    int retourConnect;
    int retourWrite;
    int retourRead;
    
    socketClient=socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(socketClient==-1){
        printf("pb socket : %s\n",strerror(errno));
        exit errno;
    }
    // init de informationsServeur avec les infos du serveur
    // IP, port, type
    informationsServeur.sin_family = AF_INET;
    informationsServeur.sin_port = htons (5555);
    informationsServeur.sin_addr.s_addr = inet_addr("172.18.58.90");
    
    memset(informationsServeur.sin_zero,0,sizeof(informationsServeur.sin_zero)) ;
    
    monEntier=123.456;   // Definition de monEntier
    
    retourConnect = connect(socketClient,(struct sockaddr*)&informationsServeur, sizeof(informationsServeur));
    if(retourConnect==-1){
        printf("pb connexion : %s\n",strerror(errno));
        exit errno;
    }
    
    retourWrite = write(socketClient,&monEntier,sizeof(informationsServeur));
    if(retourWrite==-1){
        printf("pb écriture : %s\n",strerror(errno));
        exit errno;
    }
    
    retourRead = read(socketClient,&entierDuServeur,sizeof(informationsServeur));
    if(retourRead==-1){
        printf("pb lecture : %s\n",strerror(errno));
        exit errno;
    }
    close(socketClient);
    return (EXIT_SUCCESS);
}
