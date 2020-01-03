#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( 8888 );
    int bn = bind(sockfd, (struct sockaddr *)&address, sizeof(address));
    int ln = listen(sockfd, 1);
    for(;;){
        int session_fd=accept(sockfd,0,0);
        if (session_fd==-1) {
            if (errno==EINTR) continue;
            printf("failed to accept connection (errno=%d)",errno);
            exit(1);
        } else {
            printf("Created connection!\n");
            break;
        }
    }
    return 0;
}
