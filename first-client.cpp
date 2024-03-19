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
	if(argc != 3){
		cout << "Wrong amount of arguments!" << endl;
		return -1;
	}

	// 指定ipv4协议族，流套接字(TCP), 根据前两个宏变量自动选择协议
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if(sockfd == -1){
		cerr << "Socket creating failed!" << endl;
		return -1;
	}

	
	struct hostent* h;				// Description of data base entry for a single host.
	if( (h = gethostbyname(argv[1])) == 0){
		cout << "Get hostname failed." << endl;
		close(sockfd);
		return -1;
	}

	struct sockaddr_in servaddr;	// Structure describing an Internet socket address. 
	memset(&servaddr, 0, sizeof(servaddr));
	
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(atoi(argv[2]));
	memcpy(&servaddr.sin_addr, h->h_addr, h->h_length);

	if(connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr))){
		cerr << "Connect failed." << endl;
		close(sockfd);
		return -1;
	}

	char buffer[1024];			// 1024 * 2 bytes buffer, store the input pernamently

	for(int i = 0; i < 3; ++i){
		int iret;
		
		memset(buffer, 0, sizeof(buffer));
		sprintf(buffer, "this the %d time message send.", i+1);

		if(send(sockfd, buffer, strlen(buffer), 0) == -1)
		{
			cerr << "Message sending failed." << endl;
			break;
		}	

		cout << "Send: " << buffer << " successfully!" << endl;

		memset(buffer, 0, sizeof(buffer));  			// Receive the answer.

		if( (iret = recv(sockfd, buffer, sizeof(buffer), 0)) <= 0){
			cout << "iret= " << endl;
			break;
		}

		cout << "Receive: " << buffer << " successfully!" << endl;

		sleep(1);
	}

	close(sockfd);

	return 0;
}
