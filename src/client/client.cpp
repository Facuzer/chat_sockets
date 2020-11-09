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


// Funcion principal de un cliente.
// El siguiente esquema puede servir como guia. Aprovechen las funciones de string!

int main(){
    string nick;
    cout << "Dame un nick: ";
    cin >> nick;
    /* Conectarse al server (usando INET) */
    int s = connection_setup();
    
    /* Loop principal que envía mensajes al servidor */
    // while(1) {
        // checkeo mensajes
        auto msg = leer_de_socket(s);
        cout << msg;
        if(msg == "[LOGIN]"){
            enviar_a_socket(s, nick);
            printf("Mande %s", nick.c_str());
        }    
    // }

    /* Cerrar el socket. */
    close(s);

}
