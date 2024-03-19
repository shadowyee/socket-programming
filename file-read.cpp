#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

int main(){
    int fd = open("data.txt", O_RDONLY);
    if(fd == -1){
        cerr << "Open data.txt failed!" << endl;
        return -1;
    }

    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));

    if(read(fd, buffer, sizeof(buffer)) == -1){
        cerr << "Read data.txt failed!" << endl;
        return -1;
    }

    cout << "The content of the data.txt: " << buffer << endl;

    return 0;
}
