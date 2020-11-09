#include "header.h"
using namespace std;

// Funcion para establecer la conexion del cliente con el servidor.
// Devuelve el socket descriptor de la conexion

int connection_setup(){

    int socket_fd;
    /* Crear un socket de dominio INET con TCP (SOCK_STREAM).  */
    /* ... */

    /* Establecer la dirección a la cual conectarse. */
    /* ... */

    /* Conectarse. */
    /* ... */

    return socket_fd;
}


// Funcion principal de un cliente.
// El siguiente esquema puede servir como guia. Aprovechen las funciones de string!

int main(void){
    
    /* Conectarse al server (usando INET) */
    int socket_fd = connection_setup();
    

    /* Loop principal que envía mensajes al servidor */
    string msg;

    while(1) {
        cout << "> ";
        getline(cin, msg);
        if(send(socket_fd, msg.data(), msg.length(), 0) < 0) {
            perror("Sending to server");
            exit(1);
        }
    }

    /* Cerrar el socket. */
    close(socket_fd);

}
