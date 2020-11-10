#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <algorithm>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/un.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/time.h>
#include <pthread.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

#define MENSAJE_MAXIMO  100000
#define MAX_CLIENTS 10
#define BUF_SIZE 4096
#define PORT 3006


using namespace std;
string leer_de_socket(int s);
void enviar_a_socket(int s, string mensaje);
string enviar_y_esperar_respuesta(int s, string mensaje);
bool includes(vector<string> vector, string element);


vector<string> split(const string& str, const string& delim);
class Client
{
    private:
        int s;
        string nickname;
        vector<Client>* clients;
    public:
        string getNickname(){
            return nickname;
        }
        string askNickname();
        void rechazarNickname();
        void aceptarNickname();
        bool checkNickname();
        Client(int _s, vector<Client>* clients);
        void spread(string msg);
        void inform(string msg);
};

