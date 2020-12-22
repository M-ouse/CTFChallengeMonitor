//
// Created by 2st on 2020/12/21.
//

#ifndef CTFCHALLENGEMONITOR_PARSER_HPP
#define CTFCHALLENGEMONITOR_PARSER_HPP

#include "basic.hpp"
#include <fstream>
class parser{
private:
    char ipv4[17];
    char ChallengeName[256];
public:
    void parse(char *Src);
    void out();
    void log();
    parser();
    ~parser();
};

void parser::parse(char *Src) {
    int ptr=0;
    for(int i=0;Src[ptr]!='/';i++)
    {
        ipv4[i]=Src[ptr++];
    }
    ptr++;
    for(int i=0;Src[ptr]!='#';i++)//如果以后增加字段，则应该在此修改
    {
        ChallengeName[i]=Src[ptr++];
    }
    ptr++;
}

void parser::out(){
    std::cout<<ipv4<<std::endl;
    std::cout<<ChallengeName<<std::endl;
}
void parser::log() {
    std::ofstream write;
    write.open("challenge.log",std::ios::app);
    write<<"[+]Time: "<<GetTime()<<" Source： "<<ipv4<<" Challenge: "<<ChallengeName<<" Activated."<<std::endl;

}

parser::parser() {
    memset(ipv4,0,sizeof(ipv4));
    memset(ChallengeName,0,sizeof(ChallengeName));
}

parser::~parser() {
    memset(ipv4,0,sizeof(ipv4));
    memset(ChallengeName,0,sizeof(ChallengeName));
}
#endif //CTFCHALLENGEMONITOR_PARSER_HPP
