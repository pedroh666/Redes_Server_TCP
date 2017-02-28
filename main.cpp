#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "message.h"
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <netdb.h> //hostent
#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <fstream>
#include <iostream>
#include <iostream>
#include <fstream>
using namespace std;


int main(int argc, char **argv)
{

 struct sockaddr_in server_addr,client_addr;
    socklen_t clientlen = sizeof(client_addr);
    int option, port, reuse;
    int server, client;
    char *buf;
    int buflen;
    int nread;

    // setup default arguments
    port = 9002;



      // setup socket address structure
    memset(&server_addr,0,sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = (port);
    server_addr.sin_addr.s_addr = INADDR_ANY;

      // create socket
    server = socket(PF_INET,SOCK_STREAM,0);
    if (!server) {
        perror("socket");
        exit(-1);
    }

      // set socket to immediately reuse port when the application closes
    reuse = 1;
    if (setsockopt(server, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0) {
        perror("setsockopt");
        exit(-1);
    }

      // call bind to associate the socket with our local address and
      // port
    if (bind(server,(const struct sockaddr *)&server_addr,sizeof(server_addr)) < 0) {
        perror("bind");
        exit(-1);
    }

      // convert the socket to listen for incoming connections
    if (listen(server,SOMAXCONN) < 0) {
        perror("listen");
        exit(-1);
    }

    // allocate buffer
    buflen = 1024;
    buf = new char[buflen+1];

      // accept clients fsdfdsaew44 48BRN3o23IOP
    //while ((client = accept(server,(struct sockaddr *)&client_addr,&clientlen)) > 0) {
client = accept(server,(struct sockaddr *)&client_addr,&clientlen);
          // loop to handle all requests
        //while (1) {
            cout << "----" << endl;
              // read a request
            //memset(buf,0,buflen);
            //nread = recv(client,buf,buflen,0);
            msg_t returns;
            memset(&returns,0,BUF_SZ+100);
            recv(client,&returns,BUF_SZ+50,0);
            if(returns.msg_type == MSG_TYPE_FINISH)
            {
                return 0;
            }
            if(returns.msg_type != 1)
            {
                cout << "not a get" << endl;
                //continue;
            }
            cout << returns.payload << endl;

              streampos size;
              char * memblock;

             ifstream file (reinterpret_cast<const char*>(returns.payload) , ios::in|ios::binary|ios::ate);
              if (file.is_open())
              {
                size = file.tellg();
                memblock = new char [size];
                file.seekg (0, ios::beg);
                file.read (memblock, size);
                file.close();

                cout << "the entire file content is in memory" << size << endl;

                //delete[] memblock;
              }
              else
                {
                    cout << "Unable to open file";
                    return 1;
}

            //if (nread == 0)
            //    break;

            // send a response

            int maxlo = (size/BUF_SZ);


            for(int x = 0, x1 = 0; x1 <= maxlo; x+=BUF_SZ, x1++)
            {
                cout <<x1 <<"----"<< maxlo<< endl;
                msg_t aa;

                aa.msg_type =  MSG_TYPE_GET_RESP;
                aa.cur_seq = x1;                   /* current seq number */
                aa.max_seq = maxlo;                   /* max seq number */
                for(int y = 0; y < BUF_SZ; y++)
                {

                    aa.payload[y] = memblock[y + (x)];
                }
                aa.payload_len = size;


                send(client, &aa, BUF_SZ+50, 0);
                cout << "SENT" << endl;
                msg_t returnse2;
                memset(&returnse2,0,BUF_SZ+100);
                recv(client,&returnse2,BUF_SZ+50,0);
                cout << aa.cur_seq << " out of " << aa.max_seq  << endl;
                if(returnse2.msg_type != 4)
                {

                    cout << "NO ACK!?" << endl;
                    return 1;
                }
                cout << "ACK!" << endl;
            }
            cout <<"--oo--"<< endl;

        //}
            //return 0;
        cout << "DONE!" << endl;
        msg_t ack;
    ack.msg_type =  MSG_TYPE_FINISH;
    //ack.cur_seq = returns.max_seq;                   /* current seq number */
    //ack.max_seq = returns.cur_seq;
    //send(server, &ack, sizeof(ack), 0);
    send(client, &ack, sizeof(ack), 0);
    close(client);
    goto end;
    //}
    end:
    int yyy =6;
    close(server);
    cout << "DONE!2" << endl;
    return EXIT_SUCCESS;
}
