#include "header.h"


string Client::askNickname() {
    string str = enviar_y_esperar_respuesta(s, "[LOGIN]");
    cout << str;
    return str;
}

Client::Client(int _s){
    s = _s;
    nickname = askNickname();
    printf("%s", nickname.c_str());
    cout << "asdkasjdas";
}
