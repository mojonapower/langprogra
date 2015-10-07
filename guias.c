
int mainGD(){
	system("clear");//Limpiamos la pantalla
	Guias * G = NULL;//Declaramos la variable que vamos a usar para las guias de despacho	
		//====Inicializamos las funciones iniciales===
		//-> La lista de facturas para manejarnos.
		G = creaGD();//-> Inicia la lista para poder insertar las facturas
		leerGD(G);//->Inserta en la lista anteriormente creada las facturas que estan en factura.txt
		ordenarGD(G);
		//->La lista de clientes con su informacion.
		Clientes * CL;
		CL = creaCL();
		leerclientes(CL);
		//=========fin de funciones iniciales=========
		
		
		
	int a;//->Variable para manejarnos por el menu
	int ng = 0;//->Variable de ayuda para menu en seccion de busqueda
	int opc1=0, opc2=0;//->Mas opciones de menu para un amplio manejo de este
	int dia, mes, anho;//->Mas ayuda para la busqueda
	char cliente[21];
	do{
			printf("Elegir opción deseada:\n");
			printf ("1.- Ver Guias de despacho\n2.- Ingresar nueva guia de despacho\n3.- Eliminar guia del registro\n4.- Buscar guia\n5.- Modificar guia de despacho\n6.- Menu principal\nOpción: ");
			scanf ("%d",&a);
			if(a == 1){
				printf("Guias de despacho:\n");
				recorrerG(G, G->fin);//->Funcion que muestra todas las guias. P°1: la lista, P°2: La posicion final para recorrerla de la ultima hacia la primera.
				printf("\n");
				
			}
			
			else if(a == 2){
				insertarGD(G,CL);//Funcion para generar una nueva guia
			}
			
			else if(a == 3){
				printf("N° de guia a eliminar: ");
				scanf("%d",&ng);
				if(buscaridG(G,G->fin,ng) != 1){//Antes de eliminar, se comprueba de que la guia existe. (Igualmente en la funcion, pero de esta forma nos ahorramos bugs).
					printf("Error: Guia no existe.");
				}
				else
					eliminarG(G,ng);//Procedemos a eliminar la factura con id deseada
			}
			
			else if(a == 4){
				//Aqui buscaremos tanto por fecha, monto, proveedor e id.
				system("clear");
				printf("Buscar guia por:\n1)Numero de guia\n2)Cliente\n3)Fecha\n4)Monto\n5)Factura\n6)Cancelar\nOpción: ");
				scanf("%d",&opc1);
					if (opc1 == 1){
						printf("Ingrese el numero de la guia: ");
						scanf("%d",&opc2);
						if (buscaridG(G,G->fin,opc2) != 1)printf("La guia de compra n° %d no existe.",opc2);
						else muestraGDId(G,G->fin,opc2);
					}
					else if(opc1 == 2){
						printf("Ingrese el cliente: ");
						getchar();
						fgets(cliente,21,stdin);
						if ((strlen(cliente)>0) && (cliente[strlen(cliente)- 1] == '\n'))//Sacamos la nueva linea del final-
						cliente[strlen(cliente)-1] = '\0';
						muestraGDPr(G,G->fin,cliente);
					}
					else if(opc1 == 3){
						printf("Ingrese la fecha de emision (dia mes año): ");
						scanf("%d %d %d",&dia, &mes, &anho);
						printf("Mostrar: \n1)%d/%d/%d y anteriores\n2)%d/%d/%d y siguientes\n3)Solo %d/%d/%d\nOpcion: ",dia, mes, anho,dia, mes, anho,dia, mes, anho);
						scanf("%d",&opc2);
						muestraGDfec(G,G->fin,opc2,dia,mes,anho);
					}
					
					else if(opc1 == 4){
						printf("Ingrese el monto sin puntos ni comas: ");
						scanf("%d",&anho);
						printf("Mostrar: \n1)%d y menores\n2)%d y mayores\n3)Solo %d\nOpcion: ",anho,anho,anho);
						scanf("%d",&opc2);
						muestraGDMT(G,G->fin,opc2,anho);
					}
					
					else if(opc1 == 5){
						printf("Ingrese el numero de la factura: ");
						scanf("%d",&ng);
						Factura * F = NULL;//Declaramos la variable que vamos a usar para las facturas.
						F = creaFacts();//-> Inicia la lista para poder insertar las facturas
						leerFacts(F);//->Inserta en la lista anteriormente creada las facturas que estan en factura.txt
						if(buscaridf(F,F->fin,ng)==1){
							if(!(muestraGDFac(G,G->fin,ng)))printf("Guia de despacho no existe.");
						}
						else printf("Factura no existe.");
						destruirFacts(F);
					}
				
			}
				else if(a == 5){
					printf("Ingrese el numero de la guia: ");
					scanf("%d",&ng);
					if (buscaridG(G,G->fin,ng) != 0){
						muestraGDId(G,G->fin,ng);
						eliminarG(G,ng);
						insertarGD(G,CL);					
					}
					else printf("No existe la guia N° %d",ng);
				}
			
			else if(a != 6)printf("Opcion invalida.");
			
	}while(a != 6);
	if (CL != NULL)destruyeCL(CL);
	if (G != NULL)destruirGD(G);
	/*Destruimos las listas antes de salir para evitar memoria que no se podra volver a ocupar. 
	*Cuando se reingrese en el programa de guias, se generara todo nuevamente sin problemas en tiempos optimos.
	*/
	return 0;
}//Terminamos el main de las guias




//Funcion que crea la lista de guias (vacia)
Guias *creaGD(){
  Guias *nuevo;

  if((nuevo = (Guias *) malloc(sizeof(Guias)))) // Pide memoria para la lista de guias
    {
      nuevo->tamano = 0; // Lista vacía
      nuevo->inicio = nuevo->fin = NULL; // Inicio y Fin apuntan a NULL
    }
  return nuevo;
}

//Funcion que elimina la lista de guias
void destruirGD(Guias *lGD){
   while(lGD->tamano > 0)
    {
     eliminarGD(lGD, 0);
    }
  free(lGD);
}


//Elimina guias en la posicion deseada de la lista, ocupada generalmente para destruir la lista entera.
int eliminarGD(Guias *lGD, int pos){
	int count=0;
  if(lGD->tamano != 0){
		GDnodo *aux; int dato;
		aux = lGD->inicio; //se pone la lista al inicio 
		while(count != pos){
		 aux = aux->siguiente; 
		 count++;
	  }

		    dato = aux->datos->id; //sus datos también
		  if(aux == lGD->inicio)
			lGD->inicio = aux->siguiente;
		  if(aux == lGD->fin)
			lGD->fin = aux->anterior;
		  aux->siguiente->anterior = aux->anterior;
		  aux->anterior->siguiente = aux->siguiente;
		  lGD->tamano--;
		  free(aux->datos); free(aux);  //liberar Info y después nodo
		  return dato;
	  
    }
  else
    {
      printf("Error, no hay facturas disponibles.\n");
      return -1;
    }
    return 0;
}


//Remueve una guia definitivamente del archivo que tenga la id especificada.
int eliminarG(Guias *lGD, int id){
  if(lGD->tamano != 0){
		GDnodo *aux, *temp; 
		int dato;
		aux = lGD->inicio; //se pone la lista al inicio
		//======================================
		//===Espacio para eliminarlo del archivo
		FILE * fp = fopen("Guias.txt","r");
	  
		if (fp == NULL){
			printf("Error, el archivo no se encontro. informe al administrador.");
			return -1;
		}
		FILE * fp2 = fopen("Guiastemp.txt","a"); 
		char GD[150] = "";
		char *prt;
		int idn = 0, dia = 0, mes = 0, anho = 0, idfact=0;
		char tipo[80];
		while(aux->siguiente != lGD->inicio){
		
		while( fgets(GD,300,fp) != NULL ){ 
			prt = strtok (GD, ",");
			if(prt)idn = atoi(prt);

			prt = strtok (NULL, ",");
			if(prt)dia = atoi(prt);

			prt = strtok (NULL, ",");
			if(prt)mes = atoi(prt);
			
			prt = strtok (NULL, ",");
			if(prt)anho = atoi(prt);
		  
			prt = strtok (NULL, ",");
			strcpy (tipo, prt);
			
			prt = strtok (NULL, ",");
			if(prt)idfact = atoi(prt);
			
			if (id != idn){
				fprintf(fp2,"%d,%d,%d,%d,%s,%d",idn,dia,mes,anho,tipo,idfact);
			}
			else if (id == idn){
				temp = aux;
			  }
		  }
		  aux = aux->siguiente;
	  }  
	  fclose(fp);
	  remove("Guias.txt");
	  fclose(fp2);
	  rename("Guiastemp.txt","Guias.txt");
	  //=======================================
	  //===Espacio para eliminarlo de la lista
	  aux = temp;


	//Comprobamos una vez mas...
	if (aux->datos->id != id){
		aux= lGD->inicio;
		while(aux->datos->id != id){
		aux = aux->siguiente;
		}
		
	}

		    dato = aux->datos->id; //sus datos también
		  if(aux == lGD->inicio)
			lGD->inicio = aux->siguiente;
		  if(aux == lGD->fin)
			lGD->fin = aux->anterior;
		  aux->siguiente->anterior = aux->anterior;
		  aux->anterior->siguiente = aux->siguiente;
		  lGD->tamano--;
		  free(aux->datos); free(aux);  //liberar Info y después nodo
		  ordenarGD(lGD);
		  return dato;
	  
    }
  else
    {
      printf("Error, la guia no existe.\n");
      return -1;
    }
    return 0;
}


//Crea el nodo en la lista enlazada para poder ingresar una nueva guia en la lista.
GDnodo *crearNodoGD(GDInfo *dato, GDnodo *anterior, GDnodo *siguiente){
  GDnodo *nuevo;
  if((nuevo = (GDnodo *) malloc(sizeof(GDnodo)))) // Pide memoria para el nodo
    {
      nuevo->datos = dato;
      nuevo->anterior = anterior;
      nuevo->siguiente = siguiente;
      
  
    }
  return nuevo;
}

//Agrega la informacion a la lista en ejecucion sobre la guia.
GDInfo *agregarGD(int id, int dia, int mes, int anho, char tipo[],int idfact){
  GDInfo *pdato;
  if((pdato = (GDInfo *) malloc(sizeof(GDInfo))))
    {
      /* Se almacena la información en Info */
      pdato->id = id;
      pdato->dia = dia;
      pdato->mes =mes;
      pdato->anho =anho;
      strcpy(pdato->tipo,tipo);
      pdato->idfact = idfact;
      return pdato;
    }
  else
    {
      printf("problemas en la inserción de la guia, reintente.-\n");
      exit(0);
    }
}


//Funcion para agregar una nueva guia, que se mostrara tanto en la lista luego de agregarla como en el archivo.
int insertarGD(Guias *lGD,Clientes * sd){
  GDnodo *aux, *ultimo;
  int id = 0, dia = 0, mes = 0, anho = 0, idfact=0;
  char tipo[80];
  int verif = 0;//Funcion para verificar si una instancia ya es correcta.
  //===
  do{
	  printf("Ingrese el numero de guia de despacho: ");
	  scanf("%d",&id);
	  if (id == 0)return 0;
	  if(buscaridG(lGD,lGD->fin,id) == 0)verif = 1;
	  else printf("La guia ya existe. ingrese 0 para salir.\n");
  }while(verif != 1);
		verif = 0;
	do{	
		printf("Ingrese la fecha de la guia (dia mes año): ");
		scanf("%d %d %d",&dia,&mes,&anho);
		if(!(dia > 31 && mes > 12 && (anho < 1900 || anho > 2999)))verif = 1;
	}while(verif == 0);
	getchar();
     printf("Tipo de traslado: ");
   fgets(tipo,80,stdin);
    if ((strlen(tipo)>0) && (tipo[strlen(tipo)- 1] == '\n'))//Sacamos la nueva linea del final-
        tipo[strlen(tipo)-1] = '\0';

     printf("Id de la factura asociada: ");
     scanf("%d",&idfact);
    
  //===
  GDInfo *dato = agregarGD(id,dia,mes,anho,tipo,idfact);
  // Se crea un nodo con datos y apunta al siguiente nodo
  if((aux = crearNodoGD(dato, NULL, lGD->inicio))) //además, se almacena en aux
    {
      if(lGD->tamano == 0){
        lGD->fin = aux;
        lGD->inicio = aux;
	}
        ultimo = lGD->fin;
			aux->siguiente =lGD->inicio;
			aux->anterior = ultimo;
			aux->siguiente->anterior=aux;
			ultimo->siguiente = aux;
			lGD->fin = aux;
      lGD->tamano++;
      printf("Se inserta la guia %d\n", aux->datos->id);



	FILE * fp = fopen("Guias.txt","a");
	if (fp == NULL){
		printf("Error, el archivo Guias.txt no se encontro. informe al administrador.");
		return -1;
	}
	fprintf(fp,"%d,%d,%d,%d,%s,%d\n",aux->datos->id,aux->datos->dia,aux->datos->mes,aux->datos->anho,aux->datos->tipo,aux->datos->idfact);
	fclose(fp);


ordenarGD(lGD);
      return 1;
    }
  else
    return -1;
}

//Recorre toda la lista mostrando las guias en ella.
//El primer parametro es la lista, el segundo el nodo del cual empezara a recorrer. usualmente el nodo final.
//La mayoria de los for utilizados en la lista son para que esta mantenga un orden sin importar la diferencia de largo de los datos
int recorrerG(Guias *lGD, GDnodo*i){
	if(i == NULL){
		printf("No hay guias disponibles.");
		return 0;
	}
	int j, len = 0;
 	printf("N°: %d",i->datos->id);
 	if (i->datos->id >= 1000)len = 4;
 	else if(i->datos->id >= 100)len = 3;
 	else if(i->datos->id >= 10)len = 2;
 	else len = 1;
 	for(j = 0; j < (4-len); j++){
		printf(" ");
	}
 	
 	//->Cargamos la lista de facturas para asociarle los datos de esta.
		Factura * F = NULL;
		F = creaFacts();
		leerFacts(F);
		Factnodo * ij = fnodo(F,F->fin,i->datos->idfact);
		//=============
 	
 	printf(" |Cliente: %s",ij->datos->proveedor);
 	len = strlen(ij->datos->proveedor);
 	for (j = 0; j < (17-len); j++){
		printf(" ");
	}
	len = 4;
	if(i->datos->dia >= 10)len += 2;
	else len += 1;
	if(i->datos->mes >=10)len += 2;
	else len += 1;
	printf(" |Fecha: %d/%d/%d", i->datos->dia,i->datos->mes, i->datos->anho);
	for (j = 0; j < (8-len); j++){
		printf(" ");
	}
	printf("|Monto: ");
	len = 0;
	if(i->datos->monto >= 1000000000)printf("$");
 	else if(i->datos->monto >= 100000000)printf(" $");
 	else if(i->datos->monto >= 10000000)printf("  $");
 	else if(i->datos->monto >= 1000000)printf("   $");
 	else if(i->datos->monto >= 100000)printf("    $");
 	else if(i->datos->monto >= 10000)printf("     $");
 	else if(i->datos->monto >= 1000)printf("      $");
 	else if(i->datos->monto >= 100)printf("       $");
 	else if(i->datos->monto >= 10)printf("        $");
 	else if(i->datos->monto <= 9)printf("         $");
	printf("%d\n",ij->datos->monto);
	destruirFacts(F);
	if (i == lGD->inicio)return 1;
	return recorrerG(lGD, i->anterior);
}

//Muestra una guia directamente. Mostramos tambien la info agregada por cliente.
int muestraGDId(Guias *lGD, GDnodo*i, int id){
if(i == NULL){
		printf("No hay guias disponibles.");
		return 0;
	}
	if(id == i->datos->id){
	system("clear");
	int j, len;
	
	
	//->Cargamos la lista de facturas para asociarle los datos de esta.
		Factura * F = NULL;
		F = creaFacts();
		leerFacts(F);
		Factnodo * ij = fnodo(F,F->fin,i->datos->idfact);
		//=============
	
	//=== Buscamos al cliente.
	Clientes * CL;
	CL = creaCL();
	leerclientes(CL);
	int id = buscarnomcl(CL,CL->fin,ij->datos->proveedor);
	CLnodo * sd;
	sd = id2sd(CL, CL->fin, id);
	//===
 	
 	
 	if (i->datos->id >= 1000)len = 4;
 	else if(i->datos->id >= 100)len = 3;
 	else if(i->datos->id >= 10)len = 2;
 	else len = 1;
 	
 	for(j = 0; j < (76-len); j++){
		printf(" ");
	}
 	printf("N°: %d\n",i->datos->id);
 		
 	for(j = 0; j < (52); j++){
		printf(" ");
	}
		
	printf("Fecha de emision: %d/%d/%d\n", i->datos->dia,i->datos->mes, i->datos->anho);
 	printf("Cliente: %s  | Rut: %s | Giro: %s\n",ij->datos->proveedor,sd->datos->rut,sd->datos->giro);
 	printf("Tipo traslado: %s\n",i->datos->tipo);
 	printf("Direccion: %s | Contacto: %d\n",sd->datos->direccion,sd->datos->telefono);
 	printf("ID factura asociada: %d\n",i->datos->idfact);
 	printf("Descripcion: %s\n",ij->datos->descripcion);
 	printf("Valor neto: %d | IVA: %d%% | Valor total: %d\n",((ij->datos->monto*(100-(ij->datos->iva)))/100),ij->datos->iva,ij->datos->monto);
	destruyeCL(CL);
	destruirFacts(F);
	}

	if (i == lGD->inicio)return 0;
	return muestraGDId(lGD, i->anterior,id);
}


//Muestra todas las guias de un cliente.
int muestraGDPr(Guias *lGD, GDnodo*i, char cliente[21]){
	if(i == NULL){
		printf("No hay guias disponibles.");
		return 0;
	}
	
	//->Cargamos la lista de facturas para asociarle los datos de esta.
		Factura * F = NULL;
		F = creaFacts();
		leerFacts(F);
		Factnodo * ij = fnodo(F,F->fin,i->datos->idfact);
		//=============
	
	if(strcmp(cliente, ij->datos->proveedor) == 0){
	int j, len = 0;
 	printf("N°: %d",i->datos->id);
 	if (i->datos->id >= 1000)len = 4;
 	else if(i->datos->id >= 100)len = 3;
 	else if(i->datos->id >= 10)len = 2;
 	else len = 1;
 	for(j = 0; j < (4-len); j++){
		printf(" ");
	}
 	
 	
 	
 	printf(" |Cliente: %s",ij->datos->proveedor);
 	len = strlen(ij->datos->proveedor);
 	for (j = 0; j < (21-len); j++){
		printf(" ");
	}
	len = 4;
	if(i->datos->dia >= 10)len += 2;
	else len += 1;
	if(i->datos->mes >=10)len += 2;
	else len += 1;
	printf(" |Fecha: %d/%d/%d", i->datos->dia,i->datos->mes, i->datos->anho);
	for (j = 0; j < (8-len); j++){
		printf(" ");
	}
	printf("|Monto: ");
	len = 0;
	if(i->datos->monto >= 1000000000)printf("$");
 	else if(i->datos->monto >= 100000000)printf(" $");
 	else if(i->datos->monto >= 10000000)printf("  $");
 	else if(i->datos->monto >= 1000000)printf("   $");
 	else if(i->datos->monto >= 100000)printf("    $");
 	else if(i->datos->monto >= 10000)printf("     $");
 	else if(i->datos->monto >= 1000)printf("      $");
 	else if(i->datos->monto >= 100)printf("       $");
 	else if(i->datos->monto >= 10)printf("        $");
 	else if(i->datos->monto <= 9)printf("         $");
	printf("%d\n",ij->datos->monto);
	destruirFacts(F);
}
	
	if (i == lGD->inicio)return 0;
	return muestraGDPr(lGD, i->anterior, cliente);
}


//====
//==Muestra las guias segun su fecha y en el orden deseado segun la opcion.

int muestraGDfec(Guias *lGD, GDnodo*i, int opc, int dia, int mes, int anho){
	if(i == NULL){
		printf("No hay guias disponibles.");
		return 0;
	}
	//opc == 3 -> Solo del mismo dia
	//opc == 2 -> De la fecha en adelante
	//opc == 1 -> De la fecha hacia atras
	if(((opc == 3) && (i->datos->dia == dia && i->datos->mes == mes && i->datos->anho == anho)) || 
	   ((opc == 2) && ((i->datos->anho > anho) || (i->datos->anho == anho && i->datos->mes > mes) || (i->datos->anho == anho && i->datos->mes ==  mes && i->datos->dia >= dia))) ||
	   ((opc == 1) && ((i->datos->anho < anho) || (i->datos->anho == anho && i->datos->mes < mes) || (i->datos->anho == anho && i->datos->mes ==  mes && i->datos->dia <= dia)))){
	int j, len = 0;
 	printf("N°: %d",i->datos->id);
 	if (i->datos->id >= 1000)len = 4;
 	else if(i->datos->id >= 100)len = 3;
 	else if(i->datos->id >= 10)len = 2;
 	else len = 1;
 	for(j = 0; j < (4-len); j++){
		printf(" ");
	}
 	
 	//->Cargamos la lista de facturas para asociarle los datos de esta.
		Factura * F = NULL;
		F = creaFacts();
		leerFacts(F);
		Factnodo * ij = fnodo(F,F->fin,i->datos->idfact);
		//=============
 	
 	printf(" |Cliente: %s",ij->datos->proveedor);
 	len = strlen(ij->datos->proveedor);
 	for (j = 0; j < (21-len); j++){
		printf(" ");
	}
	len = 4;
	if(i->datos->dia >= 10)len += 2;
	else len += 1;
	if(i->datos->mes >=10)len += 2;
	else len += 1;
	printf(" |Fecha: %d/%d/%d", i->datos->dia,i->datos->mes, i->datos->anho);
	for (j = 0; j < (8-len); j++){
		printf(" ");
	}
	printf(" | Monto: ");
	len = 0;
	if(i->datos->monto >= 1000000000)printf("$");
 	else if(i->datos->monto >= 100000000)printf(" $");
 	else if(i->datos->monto >= 10000000)printf("  $");
 	else if(i->datos->monto >= 1000000)printf("   $");
 	else if(i->datos->monto >= 100000)printf("    $");
 	else if(i->datos->monto >= 10000)printf("     $");
 	else if(i->datos->monto >= 1000)printf("      $");
 	else if(i->datos->monto >= 100)printf("       $");
 	else if(i->datos->monto >= 10)printf("        $");
 	else if(i->datos->monto <= 9)printf("         $");
	printf("%d\n",ij->datos->monto);
	destruirFacts(F);
}
	
	
	if (i == lGD->inicio)return 0;
	return muestraGDfec(lGD, i->anterior, opc, dia, mes, anho);
}


//Muestra guias segun el monto.
int muestraGDMT(Guias *lGD, GDnodo*i, int opc, int monto){
	if(i == NULL){
		printf("No hay guias disponibles.");
		return 0;
	}
	//opc == 3 -> Solo del mismo monto
	//opc == 2 -> Del monto hacia arriba
	//opc == 1 -> Del monto hacia abajo
	if(((opc == 3) && (i->datos->monto == monto)) || 
	   ((opc == 2) && (i->datos->monto >= monto)) || 
	   ((opc == 1) && (i->datos->monto <= monto))){
	int j, len = 0;
 	printf("N°: %d",i->datos->id);
 	if (i->datos->id >= 1000)len = 4;
 	else if(i->datos->id >= 100)len = 3;
 	else if(i->datos->id >= 10)len = 2;
 	else len = 1;
 	for(j = 0; j < (4-len); j++){
		printf(" ");
	}
 	//->Cargamos la lista de facturas para asociarle los datos de esta.
		Factura * F = NULL;
		F = creaFacts();
		leerFacts(F);
		Factnodo * ij = fnodo(F,F->fin,i->datos->idfact);
		//=============
 	printf(" |Cliente: %s",ij->datos->proveedor);
 	len = strlen(ij->datos->proveedor);
 	for (j = 0; j < (21-len); j++){
		printf(" ");
	}
	len = 4;
	if(i->datos->dia >= 10)len += 2;
	else len += 1;
	if(i->datos->mes >=10)len += 2;
	else len += 1;
	printf(" |Fecha: %d/%d/%d", i->datos->dia,i->datos->mes, i->datos->anho);
	for (j = 0; j < (8-len); j++){
		printf(" ");
	}
	printf("|Monto: ");
	len = 0;
	if(i->datos->monto >= 1000000000)printf("$");
 	else if(i->datos->monto >= 100000000)printf(" $");
 	else if(i->datos->monto >= 10000000)printf("  $");
 	else if(i->datos->monto >= 1000000)printf("   $");
 	else if(i->datos->monto >= 100000)printf("    $");
 	else if(i->datos->monto >= 10000)printf("     $");
 	else if(i->datos->monto >= 1000)printf("      $");
 	else if(i->datos->monto >= 100)printf("       $");
 	else if(i->datos->monto >= 10)printf("        $");
 	else if(i->datos->monto <= 9)printf("         $");
	printf("%d\n",ij->datos->monto);
	destruirFacts(F);
}
	
	
	if (i == lGD->inicio)return 0;
	return muestraGDMT(lGD, i->anterior, opc, monto);
}


GDnodo * Gnodo(Guias *lGD, GDnodo *i, int id){
	if(i == NULL)return 0;
 	if (i->datos->id == id) return i;
	if (i == lGD->inicio)return 0;
	return Gnodo(lGD, i->anterior, id);
}






//Busca si el id introducido es correcto y existe en la lista, si lo es, retorna 1, si no lo es, retorna 0.
//Sirve para ver si no se esta introduciendo una guia con id's repetidos.
//(El id juega como numero de guia)
int buscaridG(Guias *lGD,GDnodo*i, int id){
	if(i == NULL)return 0;
 	if (i->datos->id == id) return 1;
	if (i == lGD->inicio)return 0;
	return buscaridG(lGD, i->anterior, id);
}

//Lee las guias de Guias.txt y las inserta en la lista indicada.
int leerGD(Guias *lGD){//Devuelve 0 si no pudo abrir el archivo.
	FILE * fp = fopen("Guias.txt","r");
	if (fp == NULL){
		printf("Error, el archivo no se encontro. informe al administrador.");
		return -1;
	}
	
	char GD[150] = "";
	char *prt;
	int id = 0, dia = 0, mes = 0, anho = 0,idfact=0;
	char tipo[80];


	while( fgets(GD,300,fp) != NULL ){ 
		prt = strtok (GD, ",");
		if(prt)id = atoi(prt);

		prt = strtok (NULL, ",");
		if(prt)dia = atoi(prt);

		prt = strtok (NULL, ",");
		if(prt)mes = atoi(prt);
		
		prt = strtok (NULL, ",");
		if(prt)anho = atoi(prt);

		prt = strtok (NULL, ",");
		strcpy(tipo, prt);
		
		prt = strtok (NULL, ",");
		if(prt)idfact = atoi(prt);
		
	 GDnodo *aux, *ultimo;

  GDInfo *dato = agregarGD(id,dia,mes,anho,tipo,idfact);
  // Se crea un nodo con datos y apunta al siguiente nodo
  
  if((aux = crearNodoGD(dato, NULL, lGD->inicio))) //además, se almacena en aux
    {
      if(lGD->tamano == 0){
        lGD->fin = aux;
        lGD->inicio = aux;
	}
        ultimo = lGD->fin;
			aux->siguiente =lGD->inicio;
			aux->anterior = ultimo;
			aux->siguiente->anterior=aux;
			ultimo->siguiente = aux;
			lGD->fin = aux;
			
      lGD->tamano++;
      
    }
  else{
	  fclose(fp);
    return -1;
}

}
fclose(fp);
return 0;	
}






int muestraGDFac(Guias *lGD, GDnodo*i, int id){
if(i == NULL){
		printf("No hay guias disponibles.");
		return 0;
	}
	if(id == i->datos->idfact){
	system("clear");
	int j, len;
	
	
	//->Cargamos la lista de facturas para asociarle los datos de esta.
		Factura * F = NULL;
		F = creaFacts();
		leerFacts(F);
		Factnodo * ij = fnodo(F,F->fin,i->datos->idfact);
		//=============
	
	//=== Buscamos al cliente.
	Clientes * CL;
	CL = creaCL();
	leerclientes(CL);
	int id = buscarnomcl(CL,CL->fin,ij->datos->proveedor);
	CLnodo * sd;
	sd = id2sd(CL, CL->fin, id);
	//===
 	
 	
 	if (i->datos->id >= 1000)len = 4;
 	else if(i->datos->id >= 100)len = 3;
 	else if(i->datos->id >= 10)len = 2;
 	else len = 1;
 	
 	for(j = 0; j < (76-len); j++){
		printf(" ");
	}
 	printf("N°: %d\n",i->datos->id);
 		
 	for(j = 0; j < (52); j++){
		printf(" ");
	}
		
	printf("Fecha de emision: %d/%d/%d\n", i->datos->dia,i->datos->mes, i->datos->anho);
 	printf("Cliente: %s  | Rut: %s | Giro: %s\n",ij->datos->proveedor,sd->datos->rut,sd->datos->giro);
 	printf("Tipo traslado: %s\n",i->datos->tipo);
 	printf("Direccion: %s | Contacto: %d\n",sd->datos->direccion,sd->datos->telefono);
 	printf("ID factura asociada: %d\n",i->datos->idfact);
 	printf("Descripcion: %s\n",ij->datos->descripcion);
 	printf("Valor neto: %d | IVA: %d%% | Valor total: %d\n",((ij->datos->monto*(100-(ij->datos->iva)))/100),ij->datos->iva,ij->datos->monto);
	destruyeCL(CL);
	destruirFacts(F);
	return 1;
	}

	if (i == lGD->inicio)return 0;
	return muestraGDId(lGD, i->anterior,id);
}





//============================
//=====Funcion para ordenar la lista de forma ascendente
void ordenarGD(Guias *lGD){
	GDnodo * i = lGD->inicio;
	GDnodo * temp = NULL;
	temp = lGD->inicio;
	do{
	do{			
		if(i->datos->id > (i->siguiente)->datos->id){
			(i->siguiente)->anterior = i->anterior;//
			(i->anterior)->siguiente = i->siguiente;//
			i->anterior = i->siguiente;//
			i->siguiente = (i->siguiente)->siguiente;//
			(i->siguiente)->anterior = i;//
			(i->anterior)->siguiente = i;//
		if (lGD->inicio == i)//Nuestro nodo esta como inicio, debemos cambiarlo
			lGD->inicio = i->anterior;
		if (lGD->fin == i->anterior)//El nodo siguiente que cambiamos por el anterior era el final de la lista, ahora lo somos nosotros.
			lGD->fin = i;
		}
		i = i->siguiente;
	}while(i != lGD->fin);
	i = temp;	
	temp = temp->siguiente;
	
	}while(temp != lGD->fin);
}
