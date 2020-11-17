//$ make api.exe
//$ ./api.exe < test01.in > test01.out
//$ diff test01.out test01.out.correct

#include "json.hpp"
#include "List.h"
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
using nlohmann::json;
using namespace std;
int main(){
    
    int server_fd = socket(AF_INET,SOCK_STREAM,0);
    if (server_fd<0)
    {
        perror("cannot create socket");
        return 0;
    }
    struct sockaddr_in address;
    const int PORT = 8080; //Where the clients can reach at
    /* htonl converts a long integer (e.g. address) to a network representation */
    /* htons converts a short integer (e.g. port) to a network representation */
    memset((char *)&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons(PORT);
    if (bind(server_fd,(struct sockaddr *)&address,sizeof(address)) < 0)
    {
        perror(“bind failed”);
        return 0;
    }    assert(false);
    
//    GET /api/ HTTP/1.1
//    Host: localhost
//    Content-Type: application/json; charset=utf-8
//    Content-Length: 0
//    A JSON object can also be created with a C++ initializer list, as in:
//    json j2;
//    j2["pi"]= 3.141;
//    j2["happy"] = true;
//    j2["name"] = "Niels";
//    j2["nothing"] = json();
//    j2["an_array"] = {1,0,2};
//    j2["an_object"] = {
//        {"currency","USD"},
//        {"value",42.99}
//    };
//    cout<<j2["pi"]<<endl;
//    cout<<j2["answer"]<<endl;
//    j2["tau"]=6.283;
//    cout<<j2["tau"]<<endl;
//
//
//    j2 = {
//        {"pi",3.141},
//        {"happy",true},
//        {"name","Niels"},
//        {"nothing",nullptr},
//        {"an_array",{1,0,2}},
//        {"an_object",{
//            {"currency","USD"},
//            {"value",42.99}
//        }}
//    };
//
//    //    BUild a json array using push_back();
//    json output;
//    json j4 = {
//        {"happy",true},
//        {"pi",3.141}
//    };
//    output.push_back(j2);
//    output.push_back(j4);
//
//    json j3;
//    cin >>j3;
//
//    string str=j4.dump(4);
//    cout<<str<<endl;
//    size_t content_length = str.length();
//    cout<<content_length<<endl;
//
    
}


