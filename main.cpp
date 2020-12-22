#include "basic.hpp"
#include "socket.hpp"
#include "parser.hpp"

void Delay(int time){
    time *= 1000000;
    clock_t now = clock();
    while(clock()-now<time){

    }
}

int main() {
    char buffer[buffer_length];
    int connect_id=0;
    //std::cout << "[+]Detecing file..." << std::endl;
    for(int i=0;i<5;i++) {
        NetworkManager A;
        parser P;
        A.Recv(buffer);
        P.parse(buffer);
        P.log();
    }
    //Delay(1); // unit second
    std::cout<<"next."<<std::endl;
    return 0;
}
