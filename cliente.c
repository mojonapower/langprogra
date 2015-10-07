#include "cliente.h"
#include "facturas.h"
#include "ordenes.h"
#include "guias.h"
//Codigo main de clientes.
int mainCL(){
	Clientes * CL;
	CL = creaCL();
	leerclientes(CL);
	
	system("clear");
	int opc, opc2; 
	char buscastr[35];
	int buscaint;
	do{
		
		printf("Selecciona la opcion deseada:\n1)Ver clientes\n2)Ingresar cliente\n3)Buscar cliente\n4)Salir\nOpcion: ");
		scanf("%d",&opc);
		if(opc == 1)
			recorrerCL(CL,CL->fin);
		else if(opc == 2)
			insertarCli(CL);
		else if(opc == 3)
			do{
				//Podremos buscar al cliente por Nombre, rut, telefono o giro
				printf("Buscar cliente por:\n1)Nombre\n2)Rut\n3)Giro\n4)Salir\nOpcion: ");
				scanf("%d",&opc2);
				if(opc2 == 1){
					printf("Nombre del cliente: ");
					getchar();
					fgets(buscastr,21,stdin);
					if ((strlen(buscastr)>0) && (buscastr[strlen(buscastr)- 1] == '\n'))//Sacamos la nueva linea del final-
						buscastr[strlen(buscastr)-1] = '\0';
					muestraCLnom(CL,CL->fin,buscastr);
				}
				else if(opc2 == 2){
					printf("Rut del cliente sin DV: ");
					scanf("%d",&buscaint);
					if(muestraCLrut(CL,CL->fin,buscaint) == 0)printf("Cliente no encontrado.\n");
				}
				else if(opc2 == 3){
					printf("Indique el giro a buscar: ");
					getchar();
					fgets(buscastr,21,stdin);
					if ((strlen(buscastr)>0) && (buscastr[strlen(buscastr)- 1] == '\n'))//Sacamos la nueva linea del final-
					buscastr[strlen(buscastr)-1] = '\0';
					muestraCLgiros(CL,CL->fin,buscastr);
				}
				
			}while(opc2 != 4);
		
		
	}while(opc <= 3);
	system("clear");
	destruyeCL(CL);
	
	return 0;
}



//Funcion que crea (inicializa) la lista de clientes (vacia) 
Clientes *creaCL(){
  Clientes *nuevo;

  if((nuevo = (Clientes *) malloc(sizeof(Clientes)))) // Pide memoria para la lista de facturas
    {
      nuevo->tamano = 0; // Lista vacía
      nuevo->inicio = nuevo->fin = NULL; // Inicio y Fin apuntan a NULL
    }
  return nuevo;
}


//Funcion que destruye la lista y libera la memoria.
void destruyeCL(Clientes *sd){
   while(sd->tamano > 0)
    {
     eliminarcl(sd, 0);
    }
  free(sd);
}

//Funcion que elimina de la base de datos (no del archivo) al cliente en la posicion indicada.

int eliminarcl(Clientes *sd, int pos){
	int count=0;
  if(sd->tamano != 0){
		CLnodo *aux; int dato;
		aux = sd->inicio; //se pone la lista al inicio 
		while(count != pos){
		 aux = aux->siguiente; 
		 count++;
	  }

		    dato = aux->datos->id; //sus datos también
		  if(aux == sd->inicio)
			sd->inicio = aux->siguiente;
		  if(aux == sd->fin)
			sd->fin = aux->anterior;
		  aux->siguiente->anterior = aux->anterior;
		  aux->anterior->siguiente = aux->siguiente;
		  sd->tamano--;
		  free(aux->datos); free(aux);  //liberar Info y después nodo
		  return dato;
	  
    }
  else
    {
      printf("Error, no hay clientes disponibles.\n");
      return -1;
    }
    return 0;
}


//====
//==Crea un nuevo cliente




//Funcion que lee el archivo cliente.txt para agregarlo a la lista enlazada como base de datos.
int leerclientes(Clientes *sd){//Devuelve 0 si no pudo abrir el archivo.
	FILE * fp = fopen("cliente.txt","r");
	if (fp == NULL){
		printf("Error, el archivo ''cliente.txt'' no se encontro. informe al administrador.");
		return -1;
	}
	
	char clie[150] = "";
	char *prt;
	int id = 0, telefono=0;
	char nombre[21],direccion[34],giro[25],rut[11];


	while( fgets(clie,300,fp) != NULL ){ 
		prt = strtok (clie, ",");
		if(prt)id = atoi(prt);
		
		prt = strtok (NULL, ",");
		strcpy (rut, prt);

		prt = strtok (NULL, ",");
		strcpy (nombre, prt);		
		
		prt = strtok (NULL, ",");
		if(prt)telefono = atoi(prt);

		prt = strtok (NULL, ",");
		strcpy (giro, prt);
		
		prt = strtok (NULL, ",");
		strcpy (direccion, prt);
		if ((strlen(direccion)>0) && (direccion[strlen(direccion)- 1] == '\n'))//Sacamos la nueva linea del final-
        direccion[strlen(direccion)-1] = '\0';
	 CLnodo *aux, *ultimo;

  CLnfo *dato = agregarcli(id,rut,nombre,telefono,giro,direccion);
  // Se crea un nodo con datos y apunta al siguiente nodo
  if((aux = crearNodocli(dato, NULL, sd->inicio))) //además, se almacena en aux
    {
      if(sd->tamano == 0){
        sd->fin = aux;
        sd->inicio = aux;
	}
        ultimo = sd->fin;
			aux->siguiente =sd->inicio;
			aux->anterior = ultimo;
			aux->siguiente->anterior=aux;
			ultimo->siguiente = aux;
			sd->fin = aux;
			
      sd->tamano++;
      
    }
  else{
	  fclose(fp);
    return -1;
}

}
fclose(fp);
return 0;	
}





//Funcion que crea un nodo para poder asignarle informacion.
CLnodo *crearNodocli(CLnfo *dato, CLnodo *anterior, CLnodo *siguiente){
  CLnodo *nuevo;
  if((nuevo = (CLnodo *) malloc(sizeof(CLnodo)))) // Pide memoria para el nodo
    {
      nuevo->datos = dato;
      nuevo->anterior = anterior;
      nuevo->siguiente = siguiente;
    }
  return nuevo;
}

//Funcion interna que agrega la informacion del cliente en la lista enlazada
CLnfo *agregarcli(int id, char rut[], char nombre[], int telefono, char giro[], char direccion[]){
  CLnfo *pdato;
  if((pdato = (CLnfo *) malloc(sizeof(CLnfo))))
    {
      /* Se almacena la información en Info */
      pdato->id = id;
      strcpy(pdato->rut,rut);
      strcpy(pdato->nombre,nombre);
      pdato->telefono = telefono;
      strcpy(pdato->giro,giro);
      strcpy(pdato->direccion,direccion);
      return pdato;
    }
  else
    {
      printf("problemas en la inserción del cliente, reintente.-\n");
      exit(0);
    }
}





//Funcion para crear un cliente e insertarlo en la base de datos.
int insertarCli(Clientes *sd){
  CLnodo *aux, *ultimo;
  
  int verif = 0;//Variable para identificar si el rut es correcto.
   
  int id = 0, telefono = 0;
  char rut[11],nombre[15],giro[14],direccion[20], dv[3];
  //===
	int rut2;

	do{//Procedemos a comprobar el digito verificador del rut del cliente.
	  printf("Ingrese el rut del cliente separando el DV con un guion (xxxxxxxx-DV): ");
	  scanf("%i-%s",&rut2,dv);
	  if (rut2 == 0)return 0;//Salimos del loop si no queremos continuar intentado (por que ya existe o no recuerda rut por ejemplo)
	  else if(buscarrutcl(sd,sd->fin,rut2))printf("El rut ya esta en la base de datos.");
	  else if (valida_rut(rut2,(char)dv[0]) == 1)verif = 1;//El rut es veridico, procedemos a salir del loop. 
	  else printf("El rut es incorrecto, reintente.(0 = salir)\n");
	}while(verif == 0);
	sprintf(rut,"%d",rut2);//Funcion para pasar int a string
	char aux2[3] = "";
	strcpy (aux2, "-");
	strcat(aux2,dv);
	strcat(rut,aux2);
	
	verif = 0;
	int auxid = 1;
	do{//Aqui lo que se hace es proceder a buscar una id desocupada en los clientes para asignarla al nuevo cliente (usuario no elige id)
		if (buscaridcl(sd,sd->fin,auxid) == 0){
			id = auxid;
			verif = 1;
		}
		auxid++;
	}while(verif == 0);
	verif = 0;
	do{
		printf("Indique el nombre: ");
		getchar();
		fgets(nombre,21,stdin);
		if ((strlen(nombre)>0) && (nombre[strlen(nombre)- 1] == '\n'))//Sacamos la nueva linea del final-
        nombre[strlen(nombre)-1] = '\0';

		if (strcmp(nombre,"0") == 0)return 0;
		else if(buscarnomcl(sd,sd->fin,nombre) > 0) printf("Ya hay un cliente con ese nombre. (0 = salir).\n");
		else if(buscarnomcl(sd,sd->fin,nombre) == 0)verif = 1;
	}while(verif == 0);
  printf("Ingrese el telefono del cliente: ");
  scanf("%d",&telefono);
  printf("Indique el giro del cliente(si no posee, digite 0): ");
  getchar();
		fgets(giro,25,stdin);
		if ((strlen(giro)>0) && (giro[strlen(giro)- 1] == '\n'))//Sacamos la nueva linea del final-
        giro[strlen(giro)-1] = '\0';
  printf("Ingrese la direccion del cliente: ");
		fgets(direccion,34,stdin);
		if ((strlen(direccion)>0) && (direccion[strlen(direccion)- 1] == '\n'))//Sacamos la nueva linea del final-
        direccion[strlen(direccion)-1] = '\0';
  //===
  CLnfo *dato = agregarcli(id,rut,nombre,telefono,giro,direccion);
  // Se crea un nodo con datos y apunta al siguiente nodo
  if((aux = crearNodocli(dato, NULL, sd->inicio))) //además, se almacena en aux
    {
      if(sd->tamano == 0){
        sd->fin = aux;
        sd->inicio = aux;
	}
        ultimo = sd->fin;
			aux->siguiente =sd->inicio;
			aux->anterior = ultimo;
			aux->siguiente->anterior=aux;
			ultimo->siguiente = aux;
			sd->fin = aux;
      sd->tamano++;
      printf("Cliente %s guardado correctamente\n", aux->datos->nombre);



	FILE * fp = fopen("cliente.txt","a");
	if (fp == NULL){
		printf("Error, el archivo cliente.txt no se encontro. informe al administrador.");
		return -1;
	}
	//id, rut, nombre, telefono, giro, direccion
	fprintf(fp,"%d,%d-%c,%s,%d,%s,%s\n",aux->datos->id,rut2,(char)dv[0],aux->datos->nombre,aux->datos->telefono,aux->datos->giro,aux->datos->direccion);
	fclose(fp);



      return 1;
    }
  else
    return -1;
}

//Funcion que devuelve el rut si le entregamos el nombre
char * nom2rut(Clientes *sd,CLnodo*i, char nombre[]){
	if(i == NULL)return NULL;
	if (strcmp(i->datos->nombre, nombre) == 0) return i->datos->rut;
	if (i == sd->inicio)return NULL;
	return nom2rut(sd, i->anterior, nombre);
}

//=================
//====Funcion que devuelve el nodo que tenga la id especificada para que podamos trabajar con ella de forma facil
CLnodo * id2sd(Clientes * sd, CLnodo * i, int id){
	if(i == NULL)return NULL;
	if (i->datos->id == id) return i;
	if (i == sd->inicio)return NULL;
	return id2sd(sd, i->anterior, id);
	
	
}







//======
//==Funcion para comprobar si el rut es valido.
//==Retorna 1 si es valido, -1 si no lo es.
int valida_rut(int rut, char dv){
	char rut2[10];
	int aux, i, suma = 0, x;
	char mult[8]={2,3,4,5,6,7,2,3};//Vector para logaritmo de comprobacion
	int j = 0;
	
	sprintf(rut2,"%d",rut);
	
	
	if (rut >= 10000000)aux = 8;
	else if (rut >= 1000000)aux = 7;
	else{
		printf("El rut no es correcto.");
		return -1;
	}

	if (aux == 7)
		j = 6;
	else if(aux == 8)
		j = 7;
	suma = 0;
	for(i = 0; i < aux; i++){
		
		suma += ((rut2[i]-48)*(mult[j]));
		j--;	
	}
	int x2;
	x2 = dv - '0';
	x = 11-(suma%11);
	if (x > 9){
		if(dv == 'k' || dv == 'K')
			return 1;
		else
			return -1;
	}
	else{
		if (x2 == x)return 1;//No fallo
		else return -1;//Fallo
	}
	
	
	return 1;
}



//Funcion que busca si existe el cliente con determinado ID.
//Si existe, retorna 1, si no, retorna 0.
int buscaridcl(Clientes *sd,CLnodo*i, int id){
	if(i == NULL)return 0;
 	if (i->datos->id == id) return 1;
	if (i == sd->inicio)return 0;
	return buscaridcl(sd, i->anterior, id);
}


//Funcion que busca si existe el cliente en la base de datos
//Si existe, retorna el id, si no, retorna 0.
int buscarnomcl(Clientes *sd,CLnodo*i, char nombre[]){
	if(i == NULL)return 0;
 	if (strcmp(i->datos->nombre, nombre) == 0) return i->datos->id;
	if (i == sd->inicio)return 0;
	return buscarnomcl(sd, i->anterior, nombre);
}



int buscarrutcl(Clientes *sd,CLnodo*i, int rut){//Busca al cliente por su rut sin digito verificador, devuelve id si encontro, 0 si no existe.
	if(i == NULL)return 0;
	char rut2[10];
	sprintf(rut2,"%d",rut);
 	if (strstr(i->datos->rut, rut2)) return i->datos->id;
	if (i == sd->inicio)return 0;
	return buscarrutcl(sd, i->anterior, rut);
}




int recorrerCL(Clientes *sd, CLnodo*i){
	if(i == NULL){
		printf("No hay clientes disponibles.");
		return 0;
	}
	printf("------------------------------------------------------------------------\n");
	int j, len = 0;
 	printf("N°: %d",i->datos->id);
 	if (i->datos->id >= 1000)len = 4;
 	else if(i->datos->id >= 100)len = 3;
 	else if(i->datos->id >= 10)len = 2;
 	else len = 1;
 	for(j = 0; j < (4-len); j++){
		printf(" ");
	}
 	
 	printf(" |Nombre: %s",i->datos->nombre);
 	len = strlen(i->datos->nombre);
 	for (j = 0; j < (15-len); j++){
		printf(" ");
	}
	printf(" |Rut: %s", i->datos->rut);
	for (j = 0; j < (10-strlen(i->datos->rut)); j++){
		printf(" ");
	}
	printf(" |Telefono: %d\n", i->datos->telefono);
	printf("Giro: ");
	printf("%s",i->datos->giro);
	printf("|Direccion: ");
	printf("%s\n",i->datos->direccion);
	printf("------------------------------------------------------------------------\n");
	
	if (i == sd->inicio)return 1;
	return recorrerCL(sd, i->anterior);
}


//=====
//==Funcion que nos muestra la info segun el nombre ingresado, pondremos mas opciones al finalizar.
int muestraCLnom(Clientes *sd, CLnodo *i, char nombre[21]){
if(i == NULL){
		return 0;
	}
	int opc1;
	if(strcmp(nombre, i->datos->nombre) == 0){
	printf("N°: %d | Nombre: %s | Rut: %s | Giro: %s\nTelefono: %d | Direccion: %s\n\n",i->datos->id,i->datos->nombre,i->datos->rut,i->datos->giro,i->datos->telefono,i->datos->direccion);
	printf("¿Desea mostrar mas informacion del cliente?\n1)Facturas\n2)Guias\n3)Ordenes de compra\n4)Volver al menu\nOpcion: ");
	scanf("%d",&opc1);
	if (opc1 == 4)
		return 1;
	else if(opc1 == 1){
		Factura * Fc;
		Fc = creaFacts();
		leerFacts(Fc);
		muestraFacPr(Fc,Fc->fin,i->datos->nombre);
		destruirFacts(Fc);
	}
	else if(opc1 == 2){
		Guias * Gc;
		Gc = creaGD();
		leerGD(Gc);
		muestraGDPr(Gc,Gc->fin,i->datos->nombre);
		destruirGD(Gc);
	}
	else if(opc1 == 3){
		Ordenes * Oc;
		Oc = creaOrd();
		leerOrd(Oc);
		muestraOrdPr(Oc,Oc->fin,i->datos->nombre);
		destruirOrd(Oc);
		
	}
	}
	
	if (i == sd->inicio)return 0;
	return muestraCLnom(sd, i->anterior, nombre);
}


int muestraCLrut(Clientes *sd, CLnodo *i, int rut){
char rut2[10];
	sprintf(rut2,"%d",rut);
	if(i == NULL){
		return 0;
	}
	if(strstr(i->datos->rut, rut2)){
	printf("N°: %d | Nombre: %s | Rut: %s | Giro: %s\nTelefono: %d | Direccion: %s\n\n",i->datos->id,i->datos->nombre,i->datos->rut,i->datos->giro,i->datos->telefono,i->datos->direccion);
	return 1;
	}
	
	if (i == sd->inicio)return 0;
	return muestraCLrut(sd, i->anterior, rut);
	
}


int muestraCLgiros(Clientes *sd, CLnodo *i, char giro[]){
	if(i == NULL){
		return 0;
	}
	if(strcmp(giro, i->datos->giro) == 0){
	printf("N°: %d | Nombre: %s | Rut: %s | Giro: %s\nTelefono: %d | Direccion: %s\n\n",i->datos->id,i->datos->nombre,i->datos->rut,i->datos->giro,i->datos->telefono,i->datos->direccion);
	}
	
	if (i == sd->inicio)return 0;
	
	
	return muestraCLgiros(sd, i->anterior,giro);
}
