//
// Created by 2st on 2020/12/21.
//

#ifndef CTFCHALLENGEMONITOR_BASIC_HPP
#define CTFCHALLENGEMONITOR_BASIC_HPP

#define listen_port 8000
#define buffer_length 1024
#include <cstring>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>

std::string GetTime() {
    time_t timep;
    time (&timep);
    char tmp[64];
    strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S",localtime(&timep) );
    return tmp;
}

#endif //CTFCHALLENGEMONITOR_BASIC_HPP
