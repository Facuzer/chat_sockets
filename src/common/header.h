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
using namespace std;
#define MENSAJE_MAXIMO  4096
#define MAX_CLIENTS 10
#define BUF_SIZE 4096


void encode_s(string &data);
void decode_s(string &encoded_data);

vector<string> split(const string str, const string delim);
string join(vector<string> v, const string delim);

using namespace std;
string leer_de_socket(int s);
void enviar_a_socket(int s, string mensaje);
string enviar_y_esperar_respuesta(int s, string mensaje);
bool includes(vector<string> vector, string element);
void findAndReplaceAll(string &data, string toSearch, string replaceStr);
// Tipos de mensajes
struct Msg{
    Msg parse(string rawMsg);
    bool isMsg(string rawMsg){
        return rawMsg.substr(0, 5) == "[MSG]";
    }
    string sender;
    string msg;
};
// ----


class Client
{
    private:
        int s;
        bool alive = true;
        string nickname;
        vector<Client>* clients;
    public:
        Client(int _s, vector<Client>* clients);
        string getNickname(){ return nickname; }
        bool isAlive() { return alive; }

        string askNickname();
        void rechazarNickname();
        void aceptarNickname();
        bool checkNickname();

        void spread(string msg);
        void inform(string msg);

        void bye();
        void close_conn();
};
vector<string> convert_clients_to_nicks(vector<Client> *v);

