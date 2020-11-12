#include "../common/header.h"

using namespace std;

string lastUserPriv = "";
bool alive = true;
string nick = "";
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
        if(rcv.substr(0, 6) == "[PRIV]"){
            auto content = rcv.substr(6, rcv.size() - 6);
            decode_s(content);
            auto params = split(content, ",");
            lastUserPriv = params[0];
            printf("(PRIV) -> [%s]: %s\n", params[0].c_str(), params[1].c_str());
        }
        else if(rcv.substr(0, 5) == "[BYE]"){
            auto content = rcv.substr(5, rcv.size() - 5);
            decode_s(content);
            printf("[INFO] %s se fue del chat (seguro no le gusta c++, es inteligente ;) )\n", content.c_str());
        }
        else if(rcv.substr(0, 6) == "[LIST]"){
            auto content = rcv.substr(6, rcv.size() - 6);
            decode_s(content);
            auto lista = split(content, ",");
            printf("[INFO] Usuarios: \n");
            int i = 0;
            for (auto &&u : lista)
            {
                string itsYou = u == nick ? "(YOU)" : "";
                printf("%d - %s %s\n", i, u.c_str(), itsYou.c_str());
                i++;
            }
            printf("--------\n");
        }
        else if(rcv.substr(0, 5) == "[MSG]"){
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
    nick = pedir_nick(s);
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
                else if(cmd == "/list"){
                    enviar_a_socket(s, "[LIST]");
                }
                else if(cmd.substr(0, 6) == "/priv "){
                    auto content = cmd.substr(6, cmd.size() - 6);
                    auto params = vector<string>();
                    bool nick = true;
                    params.push_back("");
                    for (char c : content)
                    {
                        char space = (char)32;
                        if(nick){
                            if(c == space){
                                nick = false;
                                params.push_back("");
                                continue;
                            }
                            else{
                                params[0] += c;
                            }
                        }
                        else{
                            params[1] += c;
                        }
                    }
                    if(params.size() != 2){
                        printf("usage: /priv <user> <msg>");
                    }
                    else{
                        for (auto &&p : params) encode_s(p);
                        enviar_a_socket(s, "[PRIV]" + params[0] + "," + params[1]);
                    }
                }
            }
            else{
                string changedNick = nick, changedMsg = cmd;
                encode_s(changedNick);
                encode_s(changedMsg);
                auto msg = "[MSG]" + changedNick + "," + changedMsg;
                // printf("envio -> %s\n", msg.c_str());
                enviar_a_socket(s, msg);
            }
        }
    }while(!feof(stdin) && alive);

    msgThread.join();
    printf("Cierro la conexión con server.\n");

    /* Cerrar el socket. */
    close(s);
    return 0;
}
