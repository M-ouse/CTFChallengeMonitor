//
// Created by 2st on 2020/12/21.
//
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "basic.hpp"

#ifndef CTFCHALLENGEMONITOR_SOCKET_HPP
#define CTFCHALLENGEMONITOR_SOCKET_HPP

class NetworkManager{
private:
    struct sockaddr_in addr;
    struct sockaddr_in clientAddr;
    int listenfd;
    int conn;
    char clientIP[INET_ADDRSTRLEN];
    socklen_t clientAddrLen;
    char buf[buffer_length];
    int opt;
public:
    NetworkManager();
    void Recv(char* buffer);
    ~NetworkManager();
};

NetworkManager::NetworkManager() {
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd == -1) {
        std::cout << "Error: socket" << std::endl;
    }
    addr.sin_family = AF_INET;
    addr.sin_port = htons(listen_port);
    addr.sin_addr.s_addr = INADDR_ANY;
    opt=1;
    if(setsockopt(listenfd, SOL_SOCKET,SO_REUSEADDR, (const void *) &opt, sizeof(opt))){
        perror("setsockopt");
    }
    if (bind(listenfd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
        std::cout << "Error: bind" << std::endl;
    }
    if(listen(listenfd, 5) == -1) {
        std::cout << "Error: listen" << std::endl;
    }
    clientAddrLen = sizeof(clientAddr);
    //std::cout<<"Initialize successfully"<<std::endl;
}

void NetworkManager::Recv(char * Dst) {
    std::cout << "...listening" << std::endl;
    conn = accept(listenfd, (struct sockaddr*)&clientAddr, &clientAddrLen);
    if (conn < 0) {
        std::cout << "Error: accept" << std::endl;
    }
    inet_ntop(AF_INET, &clientAddr.sin_addr, clientIP, INET_ADDRSTRLEN);
    std::cout <<"[+] "<<GetTime()<< " connect " << clientIP << ":" << ntohs(clientAddr.sin_port) << std::endl;

    while (true) {
        memset(buf, 0, sizeof(buf));
        int len = recv(conn, buf, sizeof(buf), 0);
        if(len == 0){
            break;// in case of client close socket unexpectly
        }
        buf[len] = '\0';
        if (strstr(buf, "#") != 0) {
            //std::cout << "...disconnect " << clientIP << ":" << ntohs(clientAddr.sin_port) << std::endl;
            //memcpy(Dst,buf,sizeof(buf));//assume that only receive message from your challenge once
            memcpy(Dst,clientIP,sizeof(clientIP));
            strcat(Dst,"/");//insecure
            strcat(Dst,buf);//insecure
            //strcat(Dst,"/");

            break;
        }
        //std::cout << buf << std::endl;
        /*send(conn, buf, len, 0);*/
    }
}

NetworkManager::~NetworkManager() {
    std::cout<<"connection finished."<<std::endl;
    close(conn);
    close(listenfd);
}

#endif //CTFCHALLENGEMONITOR_SOCKET_HPP
