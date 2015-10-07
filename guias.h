#ifndef _GD_H_
#define _GD_H_

typedef struct GDinfo
{
	int id;
	int dia;
	int mes;
	int anho;
	int monto;
	char tipo[80];
	int idfact;
	 
}GDInfo;

typedef struct gnodo
{
	GDInfo *datos;
	struct gnodo *siguiente;
	struct gnodo *anterior;
}GDnodo;
 
typedef struct guias 
{
	GDnodo *inicio;
	GDnodo *fin;
	int tamano;
}Guias;

Guias *creaGD();
void destruirGD(Guias *lGD);
int eliminarGD(Guias *lGD, int pos);
GDInfo *agregarGD(int id,  int dia, int mes, int anho, char tipo[80],int factid);
GDnodo *crearNodoGD(GDInfo *dato, GDnodo *anterior, GDnodo *siguiente);
int insertarGD(Guias *lGD,Clientes * sd);
int recorrerG(Guias *lGD, GDnodo*i);
int buscaridG(Guias *lGD,GDnodo*i, int id);
int leerGD(Guias *lGD);
int eliminarG(Guias *lGD, int id);
int muestraGDId(Guias *lGD, GDnodo*i, int id);
int muestraGDPr(Guias *lGD, GDnodo*i, char proveedor[]);
int muestraGDfec(Guias *lGD, GDnodo*i, int opc, int dia, int mes, int anho);
int muestraGDMT(Guias *lGD, GDnodo*i, int opc, int monto);
int muestraGDFac(Guias *lGD, GDnodo*i, int idfact);
void ordenarGD(Guias *lGD);
#endif /*_GD_H_*/
