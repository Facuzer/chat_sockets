#include "header.h" 

/* Lee un mensaje del socket s y lo guarda en buf. Tener en cuenta que posiblemente sea necesario
   agregar el caracter de terminacion */
string leer_de_socket(int s) {
	int n;
	char str[MENSAJE_MAXIMO];
    n = recv(s, str, MENSAJE_MAXIMO, 0);
    if (n == 0) 
        return "";
    if (n < 0) { 
    	perror("recibiendo");
    	exit(0);
    }
    str[n] = '\0'; /* Agregar caracter de fin de cadena a lo recibido. */
    return str;
}

void enviar_a_socket(int s, string mensaje) {
    if (send(s, mensaje.c_str(), sizeof(mensaje), 0) == -1){
        perror("Mandando el mensaje ");
        exit(1);
    };
}

string enviar_y_esperar_respuesta(int s, string mensaje) {
    enviar_a_socket(s, mensaje);
    return leer_de_socket(s);
}

bool includes(vector<string> vector, string element){
    for(auto e: vector) {
        if(e == element) return true;
    }
    return false;
}

/* Dado un string y un delimitador como " ", devuelve un vector de strings donde los elementos son los tokens que
   resultan de la separación segun el delimitador. */

// vector<string> split(const string& str, const string& delim)
// {
//      /* COMPLETAR */
// }

