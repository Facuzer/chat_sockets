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
    if (send(s, mensaje.c_str(), MENSAJE_MAXIMO, 0) == -1){
        perror("Mandando el mensaje ");
        exit(1);
    };
}

string enviar_y_esperar_respuesta(int s, string mensaje) {
    enviar_a_socket(s, mensaje);
    return leer_de_socket(s);
}

/**
 *  Convierte el string normal, en un string que no afecte a la forma de enviar el mensaje
 * por ejemplo, saca las comas que molestan para enviar parametros y las convierte en 
 * un similar, pero codeado. 
*/ 
void encode_s(string &data){
    findAndReplaceAll(data, ",", "&asc44;");
}

/**
 *  Inverso de encode_s
*/ 
void decode_s(string &encoded_data){
    findAndReplaceAll(encoded_data, "&asc44;", ",");
}

vector<string> convert_clients_to_nicks(vector<Client> *v){
    vector<string> ret;
    for (size_t i = 0; i < v->size(); i++)
    {
        Client c = v->at(i);
        ret.push_back(c.getNickname());
    }
    return ret;
}

bool includes(vector<string> vector, string element){
    for(auto e: vector) {
        if(e == element) return true;
    }
    return false;
}

vector<string> split(const string str, const string delim){
    auto ret = vector<string>();
    string actualStr = str;
    int pos = 0;
    string part = "";
    while((pos = actualStr.find(delim)) != string::npos){
        part = actualStr.substr(0, pos);
        if(part != "")
            ret.push_back(part);
        actualStr.erase(0, pos + delim.length());
    }
    if(actualStr != ""){
        ret.push_back(actualStr);
    }
    return ret;
};

string join(vector<string> v, const string delim){
    string ret = "";
    for (size_t i = 0; i < v.size(); i++)
    {
        ret += v[i];
        if(i != v.size() - 1){
            ret += delim;
        }
    }
    return ret;
}

Msg Msg::parse(string rawMsg){
    if(isMsg(rawMsg)){
        auto content = rawMsg.substr(5, rawMsg.size() - 5);
        vector<string> params = split(content, ",");
        struct Msg ret;
        for (auto &&param :params)
        {
            // Replace all , in text.
            findAndReplaceAll(param, "&asc44;", ",");
        }
        
        ret.sender = params[0];
        ret.msg = params[1];
        return ret;
    }
    else{
        return {};
    }
}

void findAndReplaceAll(string &data, string toSearch, string replaceStr)
{
    // Get the first occurrence
    size_t pos = data.find(toSearch);
    // Repeat till end is reached
    while( pos != std::string::npos)
    {
        // Replace this occurrence of Sub String
        data.replace(pos, toSearch.size(), replaceStr);
        // Get the next occurrence from the current position
        pos =data.find(toSearch, pos + replaceStr.size());
    }
}
