#include "header.h"
using namespace std;

/* Dado un socket, un nickname y el estado de login, registra un nuevo cliente con el nickname dado si el 
   mismo no se encuentra en uso. 
   En caso contrario, envia un mensaje indicando la falla. Además, actualiza 
   la variable log con el nuevo estado de login del cliente. */
Client addClient(int s, const string& nickname){

    /* COMPLETAR */
}


/* Dado un cliente, lo elimina del sistema y cierra su socket adecuadamanete(ver shutdown()) */
void deleteClient(Client& c){

   /* COMPLETAR */
}

/* Dado un nick, devuelve un puntero al cliente encontrado con dicho nickname. En caso de no existir,
   el puntero es NULL */
Client* getClient(const string& nick) {
    /* COMPLETAR */
}

/* Dado un cliente y un mensaje, envía dicho mensaje a traves del socket asociado al cliente */
void send(Client* c, const string& msg) {
    /* COMPLETAR */
}


/* Funcion que ejecutan los threads */
void connection_handler(int socket_desc){

    int s = *((int*) socket_desc);
    
    /* Pedir login */
    

    /* Main loop */
    while(1) {

        /* leer socket, salir si hubo error*/
        /* COMPLETAR */

        /* Parsear el buffer recibido*/
        /* COMPLETAR */

        /* Detectar el tipo de mensaje (crudo(solo texto) o comando interno(/..),
           y ejecutar la funcion correspondiente segun el caso */
        /* COMPLETAR */

    }
   
    return NULL;  
}


int connection_setup(){

	int listening_socket;

    /* Crear un socket de dominio INET con TCP (SOCK_STREAM).  */
    /* COMPLETAR */

    /* Establecer la dirección a la cual conectarse para escuchar. */
   /* COMPLETAR */

    /* Escuchar en el socket y permitir 5 conexiones en espera. */
    /* COMPLETAR */

    printf("Server is on! \n");
    return listening_socket;
}


int main(void)
{
      

    // Abrimos un socket para escuchar conexiones entrantes
    int s = connection_setup();
  
    while(1) {  

        // Main loop del servidor
        // Aqui se aceptan conexiones y handlea a cada cliente a partir de un thread

        /* COMPLETAR */

    }

    /* Cerramos las conexiones pendientes. */
    /* COMPLETAR */
  
    /* Cerramos la conexión que escucha. */
    close(s);

    return 0;
}

