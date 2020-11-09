#include "../common/header.h"
using namespace std;
thread thread_pool[MAX_CLIENTS];  


/* Dado un socket, un nickname y el estado de login, registra un nuevo cliente con el nickname dado si el 
   mismo no se encuentra en uso. 
   En caso contrario, envia un mensaje indicando la falla. Además, actualiza 
   la variable log con el nuevo estado de login del cliente. */
// Client addClient(int s, const string& nickname){aq

//     /* COMPLETAR */
// }


/* Dado un cliente, lo elimina del sistema y cierra su socket adecuadamanete(ver shutdown()) */
// void deleteClient(Client& c){

//    /* COMPLETAR */
// }

/* Dado un nick, devuelve un puntero al cliente encontrado con dicho nickname. En caso de no existir,
   el puntero es NULL */
// Client* getClient(const string& nick) {
//     /* COMPLETAR */
// }

/* Dado un cliente y un mensaje, envía dicho mensaje a traves del socket asociado al cliente */
// void send(Client* c, const string& msg) {
//     /* COMPLETAR */
// }


/* Funcion que ejecutan los threads */
void connection_handler(int socket_desc){
    int s = socket_desc;
    auto client = Client(s);
    printf("Conexion aceptada");

    /* Main loop */
    // while(1) {

    //     /* leer socket, salir si hubo error*/
    //     /* COMPLETAR */

    //     /* Parsear el buffer recibido*/
    //     /* COMPLETAR */

    //     /* Detectar el tipo de mensaje (crudo(solo texto) o comando interno(/..),
    //        y ejecutar la funcion correspondiente segun el caso */
    //     /* COMPLETAR */

    // }
}


int connection_setup(){

	int listening_socket;
    struct sockaddr_in local, remote;
    /* Crear un socket de dominio INET con TCP (SOCK_STREAM).  */
    listening_socket = socket(PF_INET, SOCK_STREAM, 0);
    if(listening_socket == -1) {
        perror("Creando el socket");
        exit(1);
    }
    /* Establecer la dirección a la cual conectarse para escuchar. */
    local.sin_family = AF_INET;
    local.sin_port = htons(PORT);
    local.sin_addr.s_addr = INADDR_ANY;
    if (bind(listening_socket, (struct sockaddr *)&local, sizeof(local)) < 0) {
        perror("Bindeando el socket");
        exit(1);
    }
    /* Escuchar en el socket y permitir 5 conexiones en espera. */
    if (listen(listening_socket, 5) == -1){
        perror("Leyendo el socket");
        exit(1);
    };

    printf("Server is on! \n");
    return listening_socket;
}


int main(void)
{
    cout << "askjdjkashdkashda";
    struct sockaddr_in client;

    // Abrimos un socket para escuchar conexiones entrantes
    int s = connection_setup();
    printf("trolo de mierda");
    int i = 0;
    while(1) {  
        printf("asd");
        // Main loop del servidor
        // Aqui se aceptan conexiones y handlea a cada cliente a partir de un thread
        int s1;
        if((s1 = accept(s, NULL, NULL)) == -1){
            perror("Aceptando la conexion");
            exit(1);
        }
        else{
            thread_pool[i] = thread(connection_handler, s1);
            cout << "as";
            i++;
        }
    }

    /* Cerramos las conexiones pendientes. */
    // for (size_t i = 0; i < thread_pool.size(); i++)
    // {
    //     thread_pool[i].join()
    // }
    
    
    
  
    /* Cerramos la conexión que escucha. */
    close(s);

    return 0;
}

