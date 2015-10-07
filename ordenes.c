
int mainOC(){
	system("clear");//Limpiamos la pantalla
	Ordenes * O = NULL;//Declaramos la variable que vamos a usar para las ordenes.
	
	
	
		//====Inicializamos las funciones iniciales===
		//-> La lista de ordenes para manejarnos.
		O = creaOrd();//-> Inicia la lista para poder insertar las ordenes
		leerOrd(O);//->Inserta en la lista anteriormente creada las facturas que estan en Ordenes.txt
		ordenarOrd(O);
		//->La lista de clientes con su informacion.
		Clientes * CL;
		CL = creaCL();
		leerclientes(CL);
		//=========fin de funciones iniciales=========
		
		
		
	int a;//->Variable para manejarnos por el menu
	int no = 0;//->Variable de ayuda para menu en seccion de busqueda
	int opc1=0, opc2=0;//->Mas opciones de menu para un amplio manejo de este
	int dia, mes, anho;//->Mas ayuda para la busqueda
	char proveedor[13];
	do{
			printf("Elegir opción deseada:\n");
			printf ("1.- Ver ordenes\n2.- Ingresar nueva orden\n3.- Eliminar orden del registro\n4.- Buscar orden\n5.- Modificar orden\n6.- Menu principal\nOpción: ");
			scanf ("%d",&a);
			if(a == 1){
				printf("Ordenes:\n");
				recorrerO(O, O->fin);//->Funcion que muestra todas las ordenes. P°1: la lista, P°2: La posicion final para recorrerla de la ultima hacia la primera.
				printf("\n");
				
			}
			
			else if(a == 2){
				insertarOrd(O,CL);//Funcion para generar una nueva orden
			}
			
			else if(a == 3){
				printf("N° de orden a eliminar: ");
				scanf("%d",&no);
				if(buscaridO(O,O->fin,no) != 1){//Antes de eliminar, se comprueba de que la orden existe. (Igualmente en la funcion, pero de esta forma nos ahorramos bugs).
					printf("Error: Orden no existe.");
				}
				else
					eliminarO(O,no);//Procedemos a eliminar la orden con id deseada
			}
			
			else if(a == 4){
				//Aqui buscaremos tanto por fecha, monto, proveedor e id.
				system("clear");
				printf("Buscar orden por:\n1)Numero de orden\n2)Proveedor\n3)Fecha\n4)Monto\n5)Cancelar\nOpción: ");
				scanf("%d",&opc1);
					if (opc1 == 1){
						printf("Ingrese el numero de la orden: ");
						scanf("%d",&opc2);
						if (buscaridO(O,O->fin,opc2) != 1)printf("La orden de compra n° %d no existe.",opc2);
						else muestraOrdId(O,O->fin,opc2);
					}
					else if(opc1 == 2){
						printf("Ingrese el proveedor: ");
						getchar();
						fgets(proveedor,21,stdin);
						if ((strlen(proveedor)>0) && (proveedor[strlen(proveedor)- 1] == '\n'))//Sacamos la nueva linea del final-
						proveedor[strlen(proveedor)-1] = '\0';
						muestraOrdPr(O,O->fin,proveedor);
					}
					else if(opc1 == 3){
						printf("Ingrese la fecha (dia mes año): ");
						scanf("%d %d %d",&dia, &mes, &anho);
						printf("Mostrar: \n1)%d/%d/%d y anteriores\n2)%d/%d/%d y siguientes\n3)Solo %d/%d/%d\nOpcion: ",dia, mes, anho,dia, mes, anho,dia, mes, anho);
						scanf("%d",&opc2);
						muestraOrdfec(O,O->fin,opc2,dia,mes,anho);
					}
					
					else if(opc1 == 4){
						printf("Ingrese el monto sin puntos ni comas: ");
						scanf("%d",&anho);
						printf("Mostrar: \n1)%d y menores\n2)%d y mayores\n3)Solo %d\nOpcion: ",anho,anho,anho);
						scanf("%d",&opc2);
						muestraOrdMT(O,O->fin,opc2,anho);
					}
				
			}
				else if(a == 5){
					printf("Ingrese el numero de la orden: ");
					scanf("%d",&no);
					if (buscaridO(O,O->fin,no) != 0){
						muestraOrdId(O,O->fin,no);
						eliminarO(O,no);
						insertarOrd(O,CL);					
					}
					else printf("No existe la orden N° %d",no);
				}
			
			else if(a != 6)printf("Opcion invalida.");
			
	}while(a != 6);
	if (CL != NULL)destruyeCL(CL);
	if (O != NULL)destruirOrd(O);
	/*Destruimos las listas antes de salir para evitar memoria que no se podra volver a ocupar. 
	*Cuando se reingrese en el programa de ordenes, se generara todo nuevamente sin problemas en tiempos optimos.
	*/
	return 0;
}//Terminamos el main de las ordenes




//Funcion que crea la lista de ordenes (vacia)
Ordenes *creaOrd(){
  Ordenes *nuevo;

  if((nuevo = (Ordenes *) malloc(sizeof(Ordenes)))) // Pide memoria para la lista de ordenes
    {
      nuevo->tamano = 0; // Lista vacía
      nuevo->inicio = nuevo->fin = NULL; // Inicio y Fin apuntan a NULL
    }
  return nuevo;
}

//Funcion que elimina la lista de ordenes
void destruirOrd(Ordenes *lOrd){
   while(lOrd->tamano > 0)
    {
     eliminarOrd(lOrd, 0);
    }
  free(lOrd);
}


//Elimina ordenes en la posicion deseada de la lista, ocupada generalmente para destruir la lista entera.
int eliminarOrd(Ordenes *lOrd, int pos){
	int count=0;
  if(lOrd->tamano != 0){
		Ordnodo *aux; int dato;
		aux = lOrd->inicio; //se pone la lista al inicio 
		while(count != pos){
		 aux = aux->siguiente; 
		 count++;
	  }

		    dato = aux->datos->id; //sus datos también
		  if(aux == lOrd->inicio)
			lOrd->inicio = aux->siguiente;
		  if(aux == lOrd->fin)
			lOrd->fin = aux->anterior;
		  aux->siguiente->anterior = aux->anterior;
		  aux->anterior->siguiente = aux->siguiente;
		  lOrd->tamano--;
		  free(aux->datos); free(aux);  //liberar Info y después nodo
		  return dato;
	  
    }
  else
    {
      printf("Error, no hay ordenes disponibles.\n");
      return -1;
    }
    return 0;
}


//Remueve una ordenn definitivamente del archivo que tenga la id especificada.
int eliminarO(Ordenes *lOrd, int id){
  if(lOrd->tamano != 0){
		Ordnodo *aux, *temp; 
		int dato;
		aux = lOrd->inicio; //se pone la lista al inicio
		//======================================
		//===Espacio para eliminarlo del archivo
		FILE * fp = fopen("Ordenes.txt","r");
	  
		if (fp == NULL){
			printf("Error, el archivo no se encontro. informe al administrador.");
			return -1;
		}
		FILE * fp2 = fopen("Ordenestemp.txt","a"); 
		char Ord[150] = "";
		char *prt;
		int idn = 0, dia = 0, mes = 0, anho = 0, monto=0,iva=0;
		char proveedor[21],descripcion[200];
		while(aux->siguiente != lOrd->inicio){
		
		while( fgets(Ord,300,fp) != NULL ){ 
			prt = strtok (Ord, ",");
			if(prt)idn = atoi(prt);
			
			prt = strtok (NULL, ",");
			strcpy (proveedor, prt);

			prt = strtok (NULL, ",");
			if(prt)dia = atoi(prt);

			prt = strtok (NULL, ",");
			if(prt)mes = atoi(prt);
			
			prt = strtok (NULL, ",");
			if(prt)anho = atoi(prt);
			
			prt = strtok (NULL, ",");
			if(prt)monto = atoi(prt);
			
			prt = strtok (NULL, ",");
			if(prt)iva = atoi(prt);
			
			prt = strtok (NULL, ",");
			strcpy (descripcion, prt);
		  
			if (id != idn){
				fprintf(fp2,"%d,%s,%d,%d,%d,%d,%d,%s",idn,proveedor,dia,mes,anho,monto,iva,descripcion);
			}
			else if (id == idn){
				temp = aux;
			  }
		  }
		  aux = aux->siguiente;
	  }  
	  fclose(fp);
	  remove("Ordenes.txt");
	  fclose(fp2);
	  rename("Ordenestemp.txt","Ordenes.txt");
	  //=======================================
	  //===Espacio para eliminarlo de la lista
	  aux = temp;


	//Comprobamos una vez mas...
	if (aux->datos->id != id){
		aux= lOrd->inicio;
		while(aux->datos->id != id){
		aux = aux->siguiente;
		}
		
	}

		    dato = aux->datos->id; //sus datos también
		  if(aux == lOrd->inicio)
			lOrd->inicio = aux->siguiente;
		  if(aux == lOrd->fin)
			lOrd->fin = aux->anterior;
		  aux->siguiente->anterior = aux->anterior;
		  aux->anterior->siguiente = aux->siguiente;
		  lOrd->tamano--;
		  free(aux->datos); free(aux);  //liberar Info y después nodo
		  ordenarOrd(lOrd);
		  return dato;
	  
    }
  else
    {
      printf("Error, la orden no existe.\n");
      return -1;
    }
    return 0;
}


//Crea el nodo en la lista enlazada para poder ingresar una nueva orden en la lista.
Ordnodo *crearNodoOrd(OInfo *dato, Ordnodo *anterior, Ordnodo *siguiente){
  Ordnodo *nuevo;
  if((nuevo = (Ordnodo *) malloc(sizeof(Ordnodo)))) // Pide memoria para el nodo
    {
      nuevo->datos = dato;
      nuevo->anterior = anterior;
      nuevo->siguiente = siguiente;
      
  
    }
  return nuevo;
}

//Agrega la informacion a la lista en ejecucion sobre la orden.
OInfo *agregarOrd(int id, char proveedor[], int dia, int mes, int anho, int monto, int iva, char descripcion[]){
  OInfo *pdato;
  if((pdato = (OInfo *) malloc(sizeof(OInfo))))
    {
      /* Se almacena la información en Info */
      pdato->id = id;
      
      strcpy(pdato->proveedor,proveedor);
      pdato->dia = dia;
      pdato->mes =mes;
      pdato->anho =anho;
      pdato->monto =monto;
      pdato->iva = iva;
      strcpy(pdato->descripcion,descripcion);
      return pdato;
    }
  else
    {
      printf("problemas en la inserción de la orden, reintente.-\n");
      exit(0);
    }
}


//Funcion para agregar una nueva orden, que se mostrara tanto en la lista luego de agregarla como en el archivo.
int insertarOrd(Ordenes *lOrd,Clientes * sd){
  Ordnodo *aux, *ultimo;
  int id = 0, dia = 0, mes = 0, anho = 0, monto=0,iva=0;
  char proveedor[15],descripcion[200];
  int verif = 0;//Funcion para verificar si una instancia ya es correcta.
  int id2;
  //===
  do{
	  printf("Ingrese el numero de orden: ");
	  scanf("%d",&id);
	  if (id == 0)return 0;
	  if(buscaridO(lOrd,lOrd->fin,id) == 0)verif = 1;
	  else printf("La orden ya existe. ingrese 0 para salir.\n");
  }while(verif != 1);
  getchar();
  verif = 0;
  do{
	printf("Indique el proveedor: ");
	fgets(proveedor,21,stdin);
	if ((strlen(proveedor)>0) && (proveedor[strlen(proveedor)- 1] == '\n'))//Sacamos la nueva linea del final-
        proveedor[strlen(proveedor)-1] = '\0';

	if(strcmp(proveedor, "0") == 0)return 0;
	id2 = buscarnomcl(sd,sd->fin,proveedor);
	if (id2 > 0)verif = 1;
	else printf("Cliente %s no esta en la lista.\nAgregelo antes de insertar la orden en el programa de clientes.\n(0 = salir)\n",proveedor);
	}while(verif == 0);
	verif = 0;
	
	do{	
		printf("Ingrese la fecha de la orden (dia mes año): ");
		scanf("%d %d %d",&dia,&mes,&anho);
		if(!(dia > 31 && mes > 12 && (anho < 1900 || anho > 2999)))verif = 1;
	}while(verif == 0);
	
  printf("Indique el monto total de la orden: ");
  scanf("%d",&monto);
  verif = 0;
  do{
	  printf("Ingrese el IVA de la orden: ");
	  scanf("%d",&iva);
	  if (!(iva > 99 || iva < 0))verif = 1;
	  else printf("IVA invalido.\n");
	}while(verif == 0);
  printf("Descripcion de la orden: ");
  getchar();
  fgets(descripcion,200,stdin);
  if ((strlen(descripcion)>0) && (descripcion[strlen(descripcion)- 1] == '\n'))//Sacamos la nueva linea del final-
        descripcion[strlen(descripcion)-1] = '\0';
  //===
  OInfo *dato = agregarOrd(id,proveedor,dia,mes,anho,monto,iva,descripcion);
  // Se crea un nodo con datos y apunta al siguiente nodo
  if((aux = crearNodoOrd(dato, NULL, lOrd->inicio))) //además, se almacena en aux
    {
      if(lOrd->tamano == 0){
        lOrd->fin = aux;
        lOrd->inicio = aux;
	}
        ultimo = lOrd->fin;
			aux->siguiente =lOrd->inicio;
			aux->anterior = ultimo;
			aux->siguiente->anterior=aux;
			ultimo->siguiente = aux;
			lOrd->fin = aux;
      lOrd->tamano++;
      printf("Se inserta la orden %d\n", aux->datos->id);



	FILE * fp = fopen("Ordenes.txt","a");
	if (fp == NULL){
		printf("Error, el archivo Ordenes.txt no se encontro. informe al administrador.");
		return -1;
	}
	fprintf(fp,"%d,%s,%d,%d,%d,%d,%d,%s\n",aux->datos->id,aux->datos->proveedor,aux->datos->dia,aux->datos->mes,aux->datos->anho,aux->datos->monto,aux->datos->iva,aux->datos->descripcion);
	fclose(fp);


ordenarOrd(lOrd);
      return 1;
    }
  else
    return -1;
}

//Recorre toda la lista mostrando las ordenes en ella.
//El primer parametro es la lista, el segundo el nodo del cual empezara a recorrer. usualmente el nodo final.
//La mayoria de los for utilizados en la lista son para que esta mantenga un orden sin importar la diferencia de largo de los datos
int recorrerO(Ordenes *lOrd, Ordnodo*i){
	if(i == NULL){
		printf("No hay ordenes disponibles.");
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
 	
 	printf(" |Proveedor: %s",i->datos->proveedor);
 	len = strlen(i->datos->proveedor);
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
	printf("%d\n",i->datos->monto);
	
	if (i == lOrd->inicio)return 1;
	return recorrerO(lOrd, i->anterior);
}

//Muestra una orden directamente. Mostramos tambien la info agregada por cliente.
int muestraOrdId(Ordenes *lOrd, Ordnodo*i, int id){
if(i == NULL){
		printf("No hay ordenes disponibles.");
		return 0;
	}
	if(id == i->datos->id){
	system("clear");
	int j, len;
	
	//=== Buscamos al cliente.
	Clientes * CL;
	CL = creaCL();
	leerclientes(CL);
	int id = buscarnomcl(CL,CL->fin,i->datos->proveedor);
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
 		
 	for(j = 0; j < (63); j++){
		printf(" ");
	}
	printf("Fecha: %d/%d/%d\n", i->datos->dia,i->datos->mes, i->datos->anho);
 	printf("Proveedor: %s  | Rut: %s | Giro: %s\n",i->datos->proveedor,sd->datos->rut,sd->datos->giro);
 	printf("Domicilio: %s | Contacto: %d\n",sd->datos->direccion,sd->datos->telefono);
 	printf("Descripcion: %s\n",i->datos->descripcion);
 	printf("Valor neto: %d | IVA: %d%% | Valor total: %d\n",((i->datos->monto*(100-(i->datos->iva)))/100),i->datos->iva,i->datos->monto);
	destruyeCL(CL);
	}

	if (i == lOrd->inicio)return 0;
	return muestraOrdId(lOrd, i->anterior,id);
}


//Muestra todas las ordenes de un proveedor.
int muestraOrdPr(Ordenes *lOrd, Ordnodo*i, char proveedor[13]){
	if(i == NULL){
		printf("No hay ordenes disponibles.");
		return 0;
	}
	if(strcmp(proveedor, i->datos->proveedor) == 0){
	int j, len = 0;
 	printf("N°: %d",i->datos->id);
 	if (i->datos->id >= 1000)len = 4;
 	else if(i->datos->id >= 100)len = 3;
 	else if(i->datos->id >= 10)len = 2;
 	else len = 1;
 	for(j = 0; j < (4-len); j++){
		printf(" ");
	}
 	
 	printf(" |Proveedor: %s",i->datos->proveedor);
 	len = strlen(i->datos->proveedor);
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
	printf("%d\n",i->datos->monto);
}
	
	if (i == lOrd->inicio)return 0;
	return muestraOrdPr(lOrd, i->anterior, proveedor);
}


//====
//==Muestra las ordenes segun su fecha y en el orden deseado segun la opcion.

int muestraOrdfec(Ordenes *lOrd, Ordnodo*i, int opc, int dia, int mes, int anho){
	if(i == NULL){
		printf("No hay ordenes disponibles.");
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
 	
 	printf(" |Proveedor: %s",i->datos->proveedor);
 	len = strlen(i->datos->proveedor);
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
	printf("%d\n",i->datos->monto);
}
	
	
	if (i == lOrd->inicio)return 0;
	return muestraOrdfec(lOrd, i->anterior, opc, dia, mes, anho);
}


//Muestra ordenes segun el monto.
int muestraOrdMT(Ordenes *lOrd, Ordnodo*i, int opc, int monto){
	if(i == NULL){
		printf("No hay ordenes disponibles.");
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
 	
 	printf(" |Proveedor: %s",i->datos->proveedor);
 	len = strlen(i->datos->proveedor);
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
	printf("%d\n",i->datos->monto);
}
	
	
	if (i == lOrd->inicio)return 0;
	return muestraOrdMT(lOrd, i->anterior, opc, monto);
}


Ordnodo * Onodo(Ordenes *lOrd, Ordnodo *i, int id){
	if(i == NULL)return 0;
 	if (i->datos->id == id) return i;
	if (i == lOrd->inicio)return 0;
	return Onodo(lOrd, i->anterior, id);
}






//Busca si el id introducido es correcto y existe en la lista, si lo es, retorna 1, si no lo es, retorna 0.
//Sirve para ver si no se esta introduciendo una ordenes con id's repetidos.
//(El id juega como numero de orden)
int buscaridO(Ordenes *lOrd,Ordnodo*i, int id){
	if(i == NULL)return 0;
 	if (i->datos->id == id) return 1;
	if (i == lOrd->inicio)return 0;
	return buscaridO(lOrd, i->anterior, id);
}

//Lee las ordenes de Ordenes.txt y las inserta en la lista indicada.
int leerOrd(Ordenes *lOrd){//Devuelve 0 si no pudo abrir el archivo.
	FILE * fp = fopen("Ordenes.txt","r");
	if (fp == NULL){
		printf("Error, el archivo no se encontro. informe al administrador.");
		return -1;
	}
	
	char ord[150] = "";
	char *prt;
	int id = 0, dia = 0, mes = 0, anho = 0, monto=0, iva = 0;
	char proveedor[21], descripcion[200];


	while( fgets(ord,300,fp) != NULL ){ 
		prt = strtok (ord, ",");
		if(prt)id = atoi(prt);
		
		prt = strtok (NULL, ",");
		strcpy (proveedor, prt);

		prt = strtok (NULL, ",");
		if(prt)dia = atoi(prt);

		prt = strtok (NULL, ",");
		if(prt)mes = atoi(prt);
		
		prt = strtok (NULL, ",");
		if(prt)anho = atoi(prt);
		
		prt = strtok (NULL, ",");
		if(prt)monto = atoi(prt);
		
		prt = strtok (NULL, ",");
		if(prt)iva = atoi(prt);
		
		prt = strtok (NULL, ",");
		strcpy(descripcion, prt);

	 Ordnodo *aux, *ultimo;

  OInfo *dato = agregarOrd(id,proveedor,dia,mes,anho,monto,iva, descripcion);
  // Se crea un nodo con datos y apunta al siguiente nodo
  
  if((aux = crearNodoOrd(dato, NULL, lOrd->inicio))) //además, se almacena en aux
    {
      if(lOrd->tamano == 0){
        lOrd->fin = aux;
        lOrd->inicio = aux;
	}
        ultimo = lOrd->fin;
			aux->siguiente =lOrd->inicio;
			aux->anterior = ultimo;
			aux->siguiente->anterior=aux;
			ultimo->siguiente = aux;
			lOrd->fin = aux;
			
      lOrd->tamano++;
      
    }
  else{
	  fclose(fp);
    return -1;
}

}
fclose(fp);
return 0;	
}



void ordenarOrd(Ordenes *lOrd){
	Ordnodo * i = lOrd->inicio;
	Ordnodo * temp = NULL;
	temp = lOrd->inicio;
	do{
	do{			
		if(i->datos->id > (i->siguiente)->datos->id){
			(i->siguiente)->anterior = i->anterior;//
			(i->anterior)->siguiente = i->siguiente;//
			i->anterior = i->siguiente;//
			i->siguiente = (i->siguiente)->siguiente;//
			(i->siguiente)->anterior = i;//
			(i->anterior)->siguiente = i;//
		if (lOrd->inicio == i)//Nuestro nodo esta como inicio, debemos cambiarlo
			lOrd->inicio = i->anterior;
		if (lOrd->fin == i->anterior)//El nodo siguiente que cambiamos por el anterior era el final de la lista, ahora lo somos nosotros.
			lOrd->fin = i;
		}
		i = i->siguiente;
	}while(i != lOrd->fin);
	i = temp;	
	temp = temp->siguiente;
	
	}while(temp != lOrd->fin);
}
