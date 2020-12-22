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
    bool RecvBuf = false;

    fprintf(stdout,"Start Monitoring...\n");
    Delay(1);
    while(true) {
        NetworkManager A;
        parser P;
        A.Recv(buffer,&RecvBuf);
        if(RecvBuf == true){
            P.parse(buffer);
            P.log();
        }
    }
    //Delay(1); // unit second
    fprintf(stdout,"Exit.\n");
    return 0;
}
