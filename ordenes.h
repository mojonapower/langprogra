
#ifndef _ORD_H_
#define _ORD_H_

typedef struct Oinfo
{
	int id;
	char proveedor[15];
	int dia;
	int mes;
	int anho;
	int monto;
	int iva;
	char descripcion[200]; 
}OInfo;

typedef struct onodo
{
	OInfo *datos;
	struct onodo *siguiente;
	struct onodo *anterior;
}Ordnodo;
 
typedef struct ordenes 
{
	Ordnodo *inicio;
	Ordnodo *fin;
	int tamano;
}Ordenes;

Ordenes *creaOrd();
void destruirOrd(Ordenes *lOrd);
int eliminarOrd(Ordenes *lOrd, int pos);
OInfo *agregarOrd(int id, char proveedor[21], int dia, int mes, int anho, int monto, int iva, char descripcion[200]);
Ordnodo *crearNodoOrd(OInfo *dato, Ordnodo *anterior, Ordnodo *siguiente);
int insertarOrd(Ordenes *lOrd,Clientes * sd);
int recorrerO(Ordenes *lOrd, Ordnodo*i);
int buscaridO(Ordenes *lOrd,Ordnodo*i, int id);
int leerOrd(Ordenes *lOrd);
int eliminarO(Ordenes *lOrd, int id);
int muestraOrdId(Ordenes *lOrd, Ordnodo*i, int id);
int muestraOrdPr(Ordenes *lOrd, Ordnodo*i, char proveedor[]);
int muestraOrdfec(Ordenes *lOrd, Ordnodo*i, int opc, int dia, int mes, int anho);
int muestraOrdMT(Ordenes *lOrd, Ordnodo*i, int opc, int monto);
void ordenarOrd(Ordenes *lOrd);
#endif /*_ORD_H_*/
