#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

using namespace std;

int main(int argc, char *argv[]){
    if(argc != 2) 
    {
        cout << "Invalid amount of arguments!" << endl;
        return -1;
    }

    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if(listenfd == -1){
        cerr << "Socket creation failed." << endl;
        return -1;
    }

    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
    servaddr.sin_port = htons(atoi(argv[1]));
    
    // Bind the ip addr and port
    if(bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1){
        cerr << "Binding failed!" << endl;
        close(listenfd);
        return -1;
    }

    // Set the socket to the listening status
    if(listen(listenfd, 5) == -1){
        cerr << "Listening failed!" << endl;
        close(listenfd);
        return -1;
    }

    // Await a connection from client
    int clientfd = accept(listenfd, 0, 0);
    if(clientfd == -1){
        cerr << "Await connection failed!" << endl;
        return -1;
    }

    cout << "The client has connected." << endl;

    char buffer[1024];

    while(true){
        int iret;
        memset(buffer, 0, sizeof(buffer));
        if( (iret = recv(clientfd, buffer, sizeof(buffer), 0)) <= 0){
            cout << "iret: " << endl;
            break;
        }

        cout << "Receive: " << buffer << endl;

        strcpy(buffer, "ok");
        if( (iret = send(clientfd, buffer, sizeof(buffer), 0)) <= 0){
            cerr << "Server reply failed." << endl;
            break;
        }
        
        cout << "Send: " << buffer << endl;

    }

    close(listenfd);
    close(clientfd);
    return 0;
}