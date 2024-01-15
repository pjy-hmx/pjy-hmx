#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>
#include"util.h"
int main()
{
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    
    struct sockaddr_in serv_addr;
    memset(&serv_addr,0,sizeof(sockaddr_in));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(1234);

    errif(bind(sockfd,(sockaddr*)&serv_addr,sizeof(serv_addr)) == -1,"bind error");

    errif(listen(sockfd,SOMAXCONN) == -1,"listen error");
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    memset(&client_addr,0,sizeof(client_addr));

    int client_sockfd = accept(sockfd,(sockaddr*)&client_addr,&client_addr_len);
    // errif(client_addr_len == -1,"accept error");
    // printf("new client fd : %d! \nIP: %s\nPort : %d\n",client_sockfd,inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
    while (true) {
        char buf[1024];
        bzero(&buf,sizeof(buf));
        //get the data from client fd and store in buf
        ssize_t read_bytes = read(client_sockfd,buf,sizeof(buf));
        if (read_bytes > 0) {
            printf("message from clien fd %d : %s\n",client_sockfd,buf);
            write(client_sockfd,buf,sizeof(buf));
        }
        else if (read_bytes == 0) {
            printf("client fd %d disconnected\n",client_sockfd);
            close(client_sockfd);
            break;
        }
        else if( read_bytes == -1) {
            close(client_sockfd);
            errif(true,"socket read error");
        }
    }
    return 0;


}
