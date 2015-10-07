typedef struct clinfo {
	int id;
	int telefono;
	char rut[11];
	char nombre[21];
	char direccion[34];
	char giro[25];
}CLnfo;

 
typedef struct clnodo {
	CLnfo *datos;
	struct clnodo *siguiente;
	struct clnodo *anterior;
}CLnodo;
 
typedef struct clientes {
	CLnodo *inicio;
	CLnodo *fin;
	int tamano;
}Clientes;



//Listamos todas las funciones
	int leerclientes(Clientes *sd);
	CLnodo *crearNodocli(CLnfo *dato, CLnodo *anterior, CLnodo *siguiente);
	CLnfo *agregarcli(int id, char rut[], char nombre[], int telefono, char giro[], char direccion[]);
	int valida_rut(int rut, char dv);
	int buscaridcl(Clientes *sd,CLnodo*i, int id);
	Clientes *creaCL();
	void destruyeCL(Clientes *sd);
	int eliminarcl(Clientes *sd, int pos);
	int recorrerCL(Clientes *sd, CLnodo*i);
	int insertarCli(Clientes *sd);
	int buscarnomcl(Clientes *sd,CLnodo*i, char nombre[]);
	int buscarrutcl(Clientes *sd,CLnodo*i, int rut);
	char * nom2rut(Clientes *sd,CLnodo*i, char nombre[]);
	int muestraCLnom(Clientes *sd, CLnodo *i, char nombre[]);
	int muestraCLrut(Clientes *sd, CLnodo *i, int rut);
	int muestraCLgiros(Clientes *sd, CLnodo *i, char giro[]);
	CLnodo * id2sd(Clientes * sd, CLnodo * i, int id);
