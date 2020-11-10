#include "header.h"


string Client::askNickname() {
    string str = enviar_y_esperar_respuesta(s, "[LOGIN]");
    return str;
}

void Client::rechazarNickname(){
    enviar_a_socket(s, "[!]");
}

void Client::aceptarNickname(){
    enviar_a_socket(s, "[OK]");
}

Client::Client(int _s, vector<Client>* _clients){
    s = _s;
    clients = _clients;
    while(1){
        nickname = askNickname();
        if(checkNickname()) break;
        else{
            rechazarNickname();
        }
    }
    aceptarNickname();
    clients->push_back((Client)(*this));
    
    
    printf("Conexion aceptada de: %s\n", nickname.c_str());
}

bool Client::checkNickname(){
    for (size_t i = 0; i < clients->size(); i++)
    {
        Client c = clients->at(i);
        if(c.getNickname() == nickname){
            return false;
        }
    }
    return true;
}

void Client::spread(string msg){
    for (size_t i = 0; i < clients->size(); i++)
    {
        Client c = clients->at(i);
        if(c.nickname != nickname){
            c.inform(msg);
        }
    }
}

void Client::inform(string msg){
    printf("envio a %s -> %s\n", nickname.c_str(), msg.c_str());
    enviar_a_socket(s, msg);
}


void Client::close_conn() {
    close(s);
}