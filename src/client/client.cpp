#include "../common/header.h"

using namespace std;

bool alive = true;
// Funcion para establecer la conexion del cliente con el servidor.
// Devuelve el socket descriptor de la conexion

int connection_setup(int PORT){

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
    while(alive){
        auto rcv = leer_de_socket(s);
        // printf("recibo -> %s\n", rcv.c_str());
        if(rcv == "[BYE]"){
            break;
        }
        if(rcv.substr(0, 5) == "[MSG]"){
            struct Msg msg;
            msg = msg.parse(rcv);
            printf(" [%s] -> %s\n", msg.sender.c_str(), msg.msg.c_str());
            // printf("%s\n", rcv.c_str());
        }
    }
}

int main(int argc, char* argv[]){
    if(argc != 2){
        printf("Usage: ./tp <PORT>\n");
        exit(1);
    }
    /* Conectarse al server (usando INET) */
    int s = connection_setup(atoi(argv[1]));
    // Pido nick
    auto nick = pedir_nick(s);
    // escucho mensajes
    thread msgThread = thread(lookForMsgs, s);
    /* Loop principal que envía mensajes al servidor */
    do{
        // checkeo mensajes
        cout << ">";
        string cmd;
        getline(cin, cmd);
        if(cmd != ""){
            if(cmd.substr(0, 1) == "/"){
                if(cmd == "/leave"){
                    enviar_a_socket(s, "[BYE]");
                    alive = false;
                    break;
                }
                if(cmd == "/list"){
                    
                }
            }

            auto changedNick = nick;
            auto changedMsg = cmd;
            // change the commas for asc
            findAndReplaceAll(changedNick, ",", "&asc44;");
            findAndReplaceAll(changedMsg, ",", "&asc44;");
            auto msg = "[MSG]" + changedNick + "," + changedMsg;
            // printf("envio -> %s\n", msg.c_str());
            enviar_a_socket(s, msg);
        }
    }while(!feof(stdin) && alive);

    msgThread.join();
    printf("Cierro la conexión con server.\n");

    /* Cerrar el socket. */
    close(s);
    return 0;
}
