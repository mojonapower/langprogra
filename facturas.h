#ifndef _FACT_H_
#define _FACT_H_

typedef struct Finfo {
	int id;
	char proveedor[21];
	//Fecha
	int dia;
	int mes;
	int anho;
	//==
	int monto; 
	int iva;
	//==
	char descripcion[200];
}FInfo;

 
typedef struct nodo {
	FInfo *datos;
	struct nodo *siguiente;
	struct nodo *anterior;
}Factnodo;
 
typedef struct factura {
	Factnodo *inicio;
	Factnodo *fin;
	int tamano;
}Factura;



//Listamos todas las funciones
Factura *creaFacts();
void destruirFacts(Factura *lfact);
int eliminarfac(Factura *lfact, int pos);
FInfo *agregarfac(int id, char proveedor[], int dia, int mes, int anho, int monto, int iva, char descripcion[]);
Factnodo *crearNodofac(FInfo *dato, Factnodo *anterior, Factnodo *siguiente);
int insertarfac(Factura *lfact,Clientes * sd);
int recorrerF(Factura *lfact, Factnodo*i);
int buscaridf(Factura *lfact,Factnodo*i, int id);
int leerFacts(Factura *lfact);
int eliminarF(Factura *lfact, int id);
int muestraFacId(Factura *lfact, Factnodo*i, int id);
int muestraFacPr(Factura *lfact, Factnodo*i, char proveedor[]);
int muestraFacfec(Factura *lfact, Factnodo*i, int opc, int dia, int mes, int anho);
int muestraFacMT(Factura *lfact, Factnodo*i, int opc, int monto);
int modificaFact(Factura *lfact, Factnodo *i,Clientes *sd);
Factnodo * fnodo(Factura *lfact, Factnodo *i, int id);
void ordenarFac(Factura *lfact);
//Comandos para ordenar segun su id (numero)
#endif /*_FACT_H_*/
