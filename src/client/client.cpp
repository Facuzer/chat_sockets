#include "../common/header.h"

using namespace std;

// Funcion para establecer la conexion del cliente con el servidor.
// Devuelve el socket descriptor de la conexion

int connection_setup(){

    int socket_fd;
    struct sockaddr_in remote;
    /* Crear un socket de dominio INET con TCP (SOCK_STREAM).  */
    socket_fd = socket(PF_INET, SOCK_STREAM, 0);
    if(socket_fd == -1){
        perror("Creando el socket");
        exit(1);
    }
    /* Establecer la dirección a la cual conectarse. */
    remote.sin_port = htons( PORT );
    remote.sin_family = AF_INET;
    inet_pton(AF_INET, "127.0.0.1", &(remote.sin_addr));
    /* Conectarse. */
    if (connect(socket_fd, ( sockaddr* ) &remote, sizeof(remote)) == -1) {
        perror("Conectando el socket");
        exit(1);
    }
    return socket_fd;
}

string pedir_nick(int s){
    string nick;
    while (1)
    {
        string msg = leer_de_socket(s);
        if(msg == "[LOGIN]" || msg == "[!]"){
            auto o = msg == "[!]" ? "Nick ya tomado, elija otro: " : "Elija su nick: ";
            cout << o;
            cin >> nick;
            enviar_a_socket(s, nick);
        }
        if(msg == "[OK]"){
            break;
        }
    }
    return nick;
}

// vector<string> getParams(string msg, string cmd) {
//     return vector
// }

// Funcion principal de un cliente.
// El siguiente esquema puede servir como guia. Aprovechen las funciones de string!
void lookForMsgs(int s){
    auto msg = leer_de_socket(s);
    if(msg.substr(0, 4) == "[MSG"){
        cout << msg << endl;
    }
}

int main(){
    /* Conectarse al server (usando INET) */
    int s = connection_setup();
    // Pido nick
    auto nick = pedir_nick(s);
    // escucho mensajes
    thread msgThread = thread(lookForMsgs, s);
    /* Loop principal que envía mensajes al servidor */
    while(1) {
        // checkeo mensajes
        cout << ">";
        string cmd;
        cin >> cmd;
        if(true){
            auto msg = "[MSG," + nick + "]" + cmd;
            send(s, msg.c_str(), sizeof(msg.c_str()), 0);
            cout << "mande -> " << msg;
        }
    }

    /* Cerrar el socket. */
    close(s);

}
