#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

int main(){
    int fd;
    fd = open("data.txt", O_CREAT | O_RDWR | O_TRUNC);
    if(fd == -1){
        cerr << "Open data.txt failed!" << endl;
    }

    char buffer[1024];
    strcpy(buffer, "Hello world!\n");

    if(write(fd, buffer, strlen(buffer)) == -1){
        cerr << "Write into data.txt failed!" << endl;
    }

    close(fd);
    return 0;
}