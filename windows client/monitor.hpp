#pragma once

#include <WinSock2.h>
#include <cstdio>
#include <Windows.h>
#include <iostream>
#include <WS2tcpip.h>

#pragma  comment(lib,"ws2_32.lib")


class Monitor {
public:
	Monitor(const char*,int,const char *);
	~Monitor();
private:
	WORD sockVersion;
	WSADATA data;
	SOCKET sclient;
	sockaddr_in serAddr;
};

Monitor::Monitor(const char *ip,int port,const char * buf) {
	sockVersion = MAKEWORD(2, 2);
	if (WSAStartup(sockVersion, &data) != 0) {
		fprintf(stderr, "%s" , "WSAStartup failed \n");
	}
	sclient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sclient == INVALID_SOCKET) {
		fprintf(stderr, "%s", "invalid socket \n");
	}
	serAddr.sin_family = AF_INET;
	serAddr.sin_port = htons(port);
	serAddr.sin_addr.S_un.S_addr = inet_addr(ip);
	if (connect(sclient, (sockaddr*)&serAddr, sizeof(serAddr)) == SOCKET_ERROR) {
		fprintf(stderr, "%s", "connect error \n");
		closesocket(sclient);
	}
	send(sclient, buf, strlen(buf), 0);
}
Monitor::~Monitor(){
	closesocket(sclient);
	WSACleanup();
}
