//
// Created by 2st on 2020/12/22.
//

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cerrno>
#include <cstring>

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#define buffer_length 1024

#ifndef LINUX_CLIENT_MONITOR_HPP
#define LINUX_CLIENT_MONITOR_HPP

class Monitor{
private:
    int client;
    struct sockaddr_in serverAddr;
    char data[buffer_length];
    char buf[buffer_length];
public:
    Monitor(const char*,int,const char*);
    ~Monitor();
};

Monitor::Monitor(const char* ip,int port,const char* buf) {
    client = socket(AF_INET,SOCK_STREAM,0);
    if (client == -1){
        perror("socket");
    }
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = inet_addr(ip);
    if(connect(client,(struct sockaddr*)&serverAddr,sizeof(serverAddr))<0){
        perror("connect");
    }
    memcpy(data,buf,strlen(buf));
    send(client,data,strlen(data),0);
}

Monitor::~Monitor() {
    close(client);
}

#endif //LINUX_CLIENT_MONITOR_HPP
