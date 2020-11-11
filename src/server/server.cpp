#include "../common/header.h"
using namespace std;
thread thread_pool[MAX_CLIENTS];  
vector<Client> clients;

/* Funcion que ejecutan los threads */
void connection_handler(int socket_desc){
    int s = socket_desc;
    auto client = Client(s, &clients);
    
    /* Main loop */
    while(1) {

        /* leer socket, salir si hubo error*/
        auto msg = leer_de_socket(s);
        if(client.isAlive()){
            cout << "recibo -> " << msg << endl;
            /* Parsear el buffer recibido*/
            if(msg == "[BYE]"){
                client.bye();
                break;
            }
            /* Detectar el tipo de mensaje (crudo(solo texto) o comando interno(/..),
            y ejecutar la funcion correspondiente segun el caso */
            if(msg.substr(0, 5) == "[MSG]"){
                client.spread(msg);
            }
        }
    }
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
    // while(1){
    //     string a;
    //     printf("Ingresa str: ");
    //     getline(cin, a);
    //     auto v = split(a, " ");
    //     printf("lista -> [");
    //     for (size_t i = 0; i < v.size(); i++)
    //     {
    //         printf("%s", v[i].c_str());
    //         if(i != v.size() - 1){
    //             printf(",");
    //         }
    //     }
    //     printf("]\n");
        
    // }


    struct sockaddr_in client;

    // Abrimos un socket para escuchar conexiones entrantes
    int s = connection_setup();
    int i = 0;
    while(i < MAX_CLIENTS){  
        // Main loop del servidor
        // Aqui se aceptan conexiones y handlea a cada cliente a partir de un thread
        int s1;
        if((s1 = accept(s, NULL, NULL)) == -1){
            perror("Aceptando la conexion");
            exit(1);
        }
        else{
            thread_pool[i] = thread(connection_handler, s1);
            i++;
        }
    }

    // /* Cerramos las conexiones pendientes. */
    for (size_t i = 0; i < clients.size(); i++)
    {
        Client c = clients.at(i);
        c.close_conn();
    }
    /* Cerramos la conexión que escucha. */
    printf("Cierro la conexión del server.\n");
    close(s);
    
    
    
  

    return 0;
}
