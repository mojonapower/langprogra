#include <time.h>
int mainfact(){
	system("clear");//Limpiamos la pantalla
	Factura * F = NULL;//Declaramos la variable que vamos a usar para las facturas.
		//====Inicializamos las funciones iniciales===
		//-> La lista de facturas para manejarnos.
		F = creaFacts();//-> Inicia la lista para poder insertar las facturas
		leerFacts(F);//->Inserta en la lista anteriormente creada las facturas que estan en factura.txt
		ordenarFac(F);
		//->La lista de clientes con su informacion.
		Clientes * CL;
		CL = creaCL();
		leerclientes(CL);
		//=========fin de funciones iniciales=========
		
		
		
	int a;//->Variable para manejarnos por el menu
	int nf = 0;//->Variable de ayuda para menu en seccion de busqueda
	int opc1=0, opc2=0;//->Mas opciones de menu para un amplio manejo de este
	int dia, mes, anho;//->Mas ayuda para la busqueda
	char proveedor[13];
	do{
			printf("Elegir opción deseada:\n");//->Un menu ;D
			printf ("1.- Ver facturas\n");
			printf ("2.- Ingresar factura\n");
			printf ("3.- Eliminar factura\n");
			printf ("4.- Buscar factura\n");
			printf ("5.- Modificar factura\n");
			printf ("6.- Menu principal\nOpción: ");
			scanf ("%d",&a);
			
			if(a == 1){
				printf("facturas:\n");
				recorrerF(F, F->fin);//->Funcion que muestra todas las facturas. P°1: la lista, P°2: La posicion final para recorrerla de la ultima hacia la primera.
				printf("\n");
				
			}
			
			else if(a == 2){
				insertarfac(F,CL);//Funcion para generar una nueva factura
			}
			
			else if(a == 3){
				printf("N° Factura a eliminar: ");
				scanf("%d",&nf);
				if(buscaridf(F,F->fin,nf) != 1){//Antes de eliminar, se comprueba de que la factura existe. (Igualmente en la funcion, pero de esta forma nos ahorramos bugs).
					printf("Error: Factura no existe.");
				}
				else
					eliminarF(F,nf);//Procedemos a eliminar la factura con id deseada
			}
			
			else if(a == 4){
				//Aqui buscaremos tanto por fecha, monto, proveedor e id.
				system("clear");
				printf("Buscar factura por:\n1)Numero de factura\n2)Proveedor\n3)Fecha\n4)Monto\n5)Cancelar\nOpción: ");
				scanf("%d",&opc1);
					if (opc1 == 1){
						printf("Ingrese el numero de factura: ");
						scanf("%d",&opc2);
						if (buscaridf(F,F->fin,opc2) != 1)printf("La factura n° %d no existe.",opc2);
						else muestraFacId(F,F->fin,opc2);
					}
					else if(opc1 == 2){
						printf("Ingrese el proveedor: ");
						getchar();
						fgets(proveedor,21,stdin);
						if ((strlen(proveedor)>0) && (proveedor[strlen(proveedor)- 1] == '\n'))//Sacamos la nueva linea del final-
						proveedor[strlen(proveedor)-1] = '\0';
						muestraFacPr(F,F->fin,proveedor);
					}
					else if(opc1 == 3){
						printf("Ingrese la fecha (dia mes año): ");
						scanf("%d %d %d",&dia, &mes, &anho);
						printf("Mostrar: \n1)%d/%d/%d y anteriores\n2)%d/%d/%d y siguientes\n3)Solo %d/%d/%d\nOpcion: ",dia, mes, anho,dia, mes, anho,dia, mes, anho);
						scanf("%d",&opc2);
						muestraFacfec(F,F->fin,opc2,dia,mes,anho);
					}
					
					else if(opc1 == 4){
						printf("Ingrese el monto sin puntos ni comas: ");
						scanf("%d",&anho);
						printf("Mostrar: \n1)%d y menores\n2)%d y mayores\n3)Solo %d\nOpcion: ",anho,anho,anho);
						scanf("%d",&opc2);
						muestraFacMT(F,F->fin,opc2,anho);
					}
				
			}
				else if(a == 5){
					printf("Ingrese el numero de la factura: ");
					scanf("%d",&nf);
					if (buscaridf(F,F->fin,nf) != 0){
						muestraFacId(F,F->fin,nf);
						eliminarF(F,nf);
						insertarfac(F,CL);					
					}
					else printf("No existe la factura N° %d",nf);
				}
			
			else if(a != 6)printf("Opcion invalida.");
			
	}while(a != 6);
	//->Al finalizar el programa de facturas, antes de retornar al MP destruimos todas las listas generadas.
	if (CL != NULL)destruyeCL(CL);
	if (F != NULL)destruirFacts(F);
	return 0;
}//Terminamos el main de las facturas




//Funcion que crea la lista de facturas (vacia)
Factura *creaFacts(){
  Factura *nuevo;

  if((nuevo = (Factura *) malloc(sizeof(Factura)))) // Pide memoria para la lista de facturas
    {
      nuevo->tamano = 0; // Lista vacía
      nuevo->inicio = nuevo->fin = NULL; // Inicio y Fin apuntan a NULL
    }
  return nuevo;
}

//Funcion que elimina la lista de facturas, recibe la lista a eliminar
void destruirFacts(Factura *lfact){
   while(lfact->tamano > 0)
    {
     eliminarfac(lfact, 0);
    }
  free(lfact);//->Libera la lista
}


//Elimina facturas en la posicion deseada de la lista, ocupada generalmente para destruir la lista entera.
int eliminarfac(Factura *lfact, int pos){
	int count=0;
  if(lfact->tamano != 0){
		Factnodo *aux; int dato;
		aux = lfact->inicio; //se pone la lista al inicio 
		while(count != pos){
		 aux = aux->siguiente; 
		 count++;
	  }

		    dato = aux->datos->id; //sus datos también
		  if(aux == lfact->inicio)
			lfact->inicio = aux->siguiente;
		  if(aux == lfact->fin)
			lfact->fin = aux->anterior;
		  aux->siguiente->anterior = aux->anterior;
		  aux->anterior->siguiente = aux->siguiente;
		  lfact->tamano--;//Disminuye el tamaño en 1 de la lista
		  free(aux->datos); free(aux);  //liberar Info y después nodo
		  return dato;
	  
    }
  else
    {
      printf("Error, no hay facturas disponibles.\n");//Si no hay facturas, mostramos el mensaje de error.
      return -1;
    }
    return 0;
}


//Remueve una factura definitivamente del archivo que tenga la id especificada, recibe la lista y la id del archivo.
int eliminarF(Factura *lfact, int id){
  if(lfact->tamano != 0){
		Factnodo *aux, *temp; 
		int dato;
		aux = lfact->inicio; //se pone la lista al inicio
		//======================================
		//===Espacio para eliminarlo del archivo
		FILE * fp = fopen("factura.txt","r");
	  
		if (fp == NULL){
			printf("Error, el archivo no se encontro. informe al administrador.");
			return -1;
		}
		FILE * fp2 = fopen("facturatemp.txt","a");//Creamos un archivo "temporal" donde escribiremos toda la info.
		char fact[150] = "";
		char *prt;
		int idn = 0, dia = 0, mes = 0, anho = 0, monto=0,iva=0;
		char proveedor[21],descripcion[200];
		while(aux->siguiente != lfact->inicio){//Recorremos el archivo original
		
		while( fgets(fact,300,fp) != NULL ){ 
			prt = strtok (fact, ",");
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
		  
			if (id != idn){//Escribimos en el archivo "temporal" todas las facturas menos la que tenga la id especificada.
				fprintf(fp2,"%d,%s,%d,%d,%d,%d,%d,%s",idn,proveedor,dia,mes,anho,monto,iva,descripcion);
			}
			else if (id == idn){
				temp = aux;//Guarda en un nodo temporal la linea.
			  }
		  }
		  aux = aux->siguiente;
	  }  
	  fclose(fp);
	  remove("factura.txt");//removemos el archivo original
	  fclose(fp2);
	  rename("facturatemp.txt","factura.txt");//renombramos el archivo temporal a por el original.
	  //=======================================
	  //===Espacio para eliminarlo de la lista
	  aux = temp;//asignamos al nodo auxiliar el nodo temporal declarado anteriormente.


	//Comprobamos una vez mas...
	if (aux->datos->id != id){
		aux= lfact->inicio;
		while(aux->datos->id != id){
		aux = aux->siguiente;
		}
		
	}
		//Modificamos la lista en ejecucion.
		    dato = aux->datos->id; //sus datos también
		  if(aux == lfact->inicio)
			lfact->inicio = aux->siguiente;
		  if(aux == lfact->fin)
			lfact->fin = aux->anterior;
		  aux->siguiente->anterior = aux->anterior;
		  aux->anterior->siguiente = aux->siguiente;
		  lfact->tamano--;
		  free(aux->datos); free(aux);  //liberar Info y después nodo
		  ordenarFac(lfact);//Una vez listo, ordenamos la lista una vez mas.
		  return dato;
	  
    }
  else
    {
      printf("Error, la factura no existe.\n");
      return -1;
    }
    return 0;
}


//Crea el nodo en la lista enlazada para poder ingresar una nueva factura en la lista.
//->Recibe los datos, el nodo al que apuntara como anterior y el nodo que apuntara como siguiente.
Factnodo *crearNodofac(FInfo *dato, Factnodo *anterior, Factnodo *siguiente){
  Factnodo *nuevo;
  if((nuevo = (Factnodo *) malloc(sizeof(Factnodo)))) // Pide memoria para el nodo
    {
      nuevo->datos = dato;
      nuevo->anterior = anterior;
      nuevo->siguiente = siguiente;
      
  
    }
  return nuevo;
}

//crea la informacion a la lista en ejecucion sobre la factura.
//->recibe el numero de factura, cliente, dia, mes, año, monto, iva y la descripcion.
//->Devuelve la estructura que se insertaran en el nodo.
FInfo *agregarfac(int id, char proveedor[], int dia, int mes, int anho, int monto, int iva, char descripcion[]){
  FInfo *pdato;
  if((pdato = (FInfo *) malloc(sizeof(FInfo))))
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
      printf("problemas en la inserción de la factura, reintente.-\n");
      exit(0);
    }
}


//Funcion para agregar una nueva factura, que se mostrara tanto en la lista luego de agregarla como en el archivo.
//Solo necesita recibir la lista de facturas y la lista de clientes.
int insertarfac(Factura *lfact,Clientes * sd){
  Factnodo *aux, *ultimo;
  int id = 0, dia = 0, mes = 0, anho = 0, monto=0,iva=0;
  char proveedor[15],descripcion[200];
  int verif = 0;//Funcion para verificar si una instancia ya es correcta.
  int id2;
  //===

  do{
	  printf("Ingrese el numero de factura: ");
	  scanf("%d",&id);
	  if (id == 0)return 0;
	  if(buscaridf(lfact,lfact->fin,id) == 0)verif = 1;//Se comprueba de que la factura no exista y no haya corrupcion de datos.
	  else printf("La factura ya existe. ingrese 0 para salir.\n");//Se lo decimos hasta que indique un numero correcto.
  }while(verif != 1);
  getchar();//agregamos nueva linea al buffer con este comando para que fgets funcione sin problemas. (altercado con scanf y fgets)
  verif = 0;
  do{
	printf("Indique el cliente: ");
	fgets(proveedor,21,stdin);
	if ((strlen(proveedor)>0) && (proveedor[strlen(proveedor)- 1] == '\n'))//Sacamos la nueva linea del final ya que no la necesitamos
        proveedor[strlen(proveedor)-1] = '\0';//Reemplazamos la nueva linea por caracter de termino.

	if(strcmp(proveedor, "0") == 0)return 0;
	id2 = buscarnomcl(sd,sd->fin,proveedor);//Busca la id de un cliente en la lista basado en el nombre de este.
	if (id2 > 0)verif = 1;
	else printf("Cliente %s no esta en la lista.\nAgregelo antes de insertar factura en el programa de clientes.\n(0 = salir)\n",proveedor);
	}while(verif == 0);
	verif = 0;
	
	do{	
		printf("Ingrese la fecha de la factura (dia mes año): ");
		scanf("%d %d %d",&dia,&mes,&anho);
		if(!(dia > 31 && mes > 12 && (anho < 1900 || anho > 2999)))verif = 1;//Comprueba de que la fecha sea valida.
	}while(verif == 0);
	
  printf("Indique el monto total de la factura: ");
  scanf("%d",&monto);//Se solicita el monto total, luego se calcula el neto segun IVA.
  verif = 0;
  do{
	  printf("Ingrese IVA de la factura: ");
	  scanf("%d",&iva);
	  if (!(iva > 99 || iva < 0))verif = 1;//El IVA no puede ser negativo ni mayor a 100%
	  else printf("IVA fuera de rangos posibles.\n");
	}while(verif == 0);
  printf("Descripcion de la factura: ");
  getchar();
  fgets(descripcion,200,stdin);
  if ((strlen(descripcion)>0) && (descripcion[strlen(descripcion)- 1] == '\n'))//Sacamos la nueva linea del final-
        descripcion[strlen(descripcion)-1] = '\0';
  //===
  FInfo *dato = agregarfac(id,proveedor,dia,mes,anho,monto,iva,descripcion);//Se rellena la estructura de informacion con los datos
  // Se crea un nodo con datos y apunta al siguiente nodo
  if((aux = crearNodofac(dato, NULL, lfact->inicio))) //además, se almacena en un nodo auxiliar para poder agregarlo a la lista.
    {
      if(lfact->tamano == 0){
        lfact->fin = aux;
        lfact->inicio = aux;
	}
        ultimo = lfact->fin;
			aux->siguiente =lfact->inicio;
			aux->anterior = ultimo;
			aux->siguiente->anterior=aux;
			ultimo->siguiente = aux;
			lfact->fin = aux;
      lfact->tamano++;
      printf("Se inserta la factura %d\n", aux->datos->id);



	FILE * fp = fopen("factura.txt","a");
	if (fp == NULL){
		printf("Error, el archivo factura.txt no se encontro. informe al administrador.");
		return -1;
	}
	fprintf(fp,"%d,%s,%d,%d,%d,%d,%d,%s\n",aux->datos->id,aux->datos->proveedor,aux->datos->dia,aux->datos->mes,aux->datos->anho,aux->datos->monto,aux->datos->iva,aux->datos->descripcion);
	fclose(fp);

	//Cuando terminamos de insertar la lista, la ordenamos para que quede en orden correcto segun Numero de factura.
	ordenarFac(lfact);
      return 1;
    }
  else
    return -1;
}

//Recorre toda la lista mostrando las facturas en ella.
//Es una funcion RECURSIVA como la mayoria de las funciones de busqueda del programa.
//El primer parametro es la lista, el segundo el nodo del cual empezara a recorrer. usualmente el nodo final.
//La mayoria de los for utilizados en la lista son para que esta mantenga un orden sin importar la diferencia de largo de los datos
int recorrerF(Factura *lfact, Factnodo*i){
	if(i == NULL){
		printf("No hay facturas disponibles.");
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
 	
 	printf(" |Cliente: %s",i->datos->proveedor);
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
	printf("%d\n",i->datos->monto);
	
	if (i == lfact->inicio)return 1;
	return recorrerF(lfact, i->anterior);
}

//Muestra una factura directamente con todos sus datos. Mostramos tambien la info agregada del cliente.
int muestraFacId(Factura *lfact, Factnodo*i, int id){
if(i == NULL){
		printf("No hay facturas disponibles.");
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
 	printf("Cliente: %s  | Rut: %s | Giro: %s\n",i->datos->proveedor,sd->datos->rut,sd->datos->giro);
 	printf("Domicilio: %s | Contacto: %d\n",sd->datos->direccion,sd->datos->telefono);
 	printf("Descripcion: %s\n",i->datos->descripcion);
 	printf("Valor neto: %d | IVA: %d%% | Valor total: %d\n",((i->datos->monto*(100-(i->datos->iva)))/100),i->datos->iva,i->datos->monto);
	destruyeCL(CL);//Destruimos la lista de clientes generada, para liberar la memoria.
	return 1;//Al encontrar la factura deseada, finalizamos la busqueda.
	}

	if (i == lfact->inicio)return 0;//Si ha llegado al final (o inicio, ya que partimos del final), retornamos 0.
	return muestraFacId(lfact, i->anterior,id);//Al ser una funcion recursiva para encontrar la factura que buscamos,  seguimos con la busqueda.
}


//Muestra todas las facturas de un proveedor.
//Funcion RECURSIVA que busca cada factura con cliente 
int muestraFacPr(Factura *lfact, Factnodo*i, char proveedor[13]){
	if(i == NULL){
		printf("No hay facturas disponibles.");
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
 	
 	printf(" |Cliente: %s",i->datos->proveedor);
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
	printf("%d\n",i->datos->monto);
}
	
	if (i == lfact->inicio)return 0;
	return muestraFacPr(lfact, i->anterior, proveedor);
}


//====
//==Muestra las facturas segun su fecha y en el orden deseado segun la opcion.

int muestraFacfec(Factura *lfact, Factnodo*i, int opc, int dia, int mes, int anho){
	if(i == NULL){
		printf("No hay facturas disponibles.");
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
 	
 	printf(" |Cliente: %s",i->datos->proveedor);
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
	printf("%d\n",i->datos->monto);
}
	
	
	if (i == lfact->inicio)return 0;
	return muestraFacfec(lfact, i->anterior, opc, dia, mes, anho);
}


//Muestra facturas segun el monto.
int muestraFacMT(Factura *lfact, Factnodo*i, int opc, int monto){
	if(i == NULL){
		printf("No hay facturas disponibles.");
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
 	
 	printf(" |Cliente: %s",i->datos->proveedor);
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
	printf("%d\n",i->datos->monto);
}
	
	
	if (i == lfact->inicio)return 0;
	return muestraFacMT(lfact, i->anterior, opc, monto);
}


Factnodo * fnodo(Factura *lfact, Factnodo *i, int id){
	if(i == NULL)return 0;
 	if (i->datos->id == id) return i;
	if (i == lfact->inicio)return 0;
	return fnodo(lfact, i->anterior, id);
}






//Busca si el id introducido es correcto y existe en la lista, si lo es, retorna 1, si no lo es, retorna 0.
//Sirve para ver si no se esta introduciendo una factura con id's repetidos.
//(El id juega como numero de factura)
int buscaridf(Factura *lfact,Factnodo*i, int id){
	if(i == NULL)return 0;
 	if (i->datos->id == id) return 1;
	if (i == lfact->inicio)return 0;
	return buscaridf(lfact, i->anterior, id);
}


//Lee las facturas de factura.txt y las inserta en la lista indicada.
int leerFacts(Factura *lfact){//Devuelve -1 si no pudo abrir el archivo.
	FILE * fp = fopen("factura.txt","r");
	if (fp == NULL){
		printf("Error, el archivo no se encontro. informe al administrador.");
		return -1;
	}
	//Mezcla(fp);
	char fact[150] = "";
	char *prt;
	int id = 0, dia = 0, mes = 0, anho = 0, monto=0, iva = 0;
	char proveedor[21], descripcion[200];


	while( fgets(fact,300,fp) != NULL ){ 
		prt = strtok (fact, ",");
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

	 Factnodo *aux, *ultimo;

  FInfo *dato = agregarfac(id,proveedor,dia,mes,anho,monto,iva, descripcion);
  // Se crea un nodo con datos y apunta al siguiente nodo
  //crearNodofac (dato, dato->anterior, dato->siguiente)
  
  if((aux = crearNodofac(dato, NULL, lfact->inicio))) //además, se almacena en aux
    {
      if(lfact->tamano == 0){
        lfact->fin = aux;
        lfact->inicio = aux;
	}
        ultimo = lfact->fin;
			aux->siguiente =lfact->inicio;
			aux->anterior = ultimo;
			aux->siguiente->anterior=aux;
			ultimo->siguiente = aux;
			lfact->fin = aux;
			
      lfact->tamano++;
      
    }
  else{
	  fclose(fp);
    return -1;
}

}
fclose(fp);
return 0;	
}




//============================================================
//====FUNCION OBSOLETA, NO SE LLAMA.
int modificaFact(Factura* lfact, Factnodo *i, Clientes *sd){
	 Factnodo *aux = NULL;
  int id = 0, dia = 0, mes = 0, anho = 0, monto=0,iva=0;
  char proveedor[15],descripcion[200];
  int verif = 0;//Funcion para verificar si una instancia ya es correcta.
  int id2;
  //===
  system("clear");
	printf ("Numero: %d | Cliente: %s | Fecha: %d/%d/%d\nIVA: %d%% |Monto total: %d\nDescripcion: %s\n",i->datos->id,i->datos->proveedor,i->datos->dia,i->datos->mes,i->datos->anho,i->datos->iva,i->datos->monto,i->datos->descripcion);
  do{
	  printf("Ingrese el nuevo numero de factura: ");
	  scanf("%d",&id);
	  if (id == 0)return 0;
	  if(buscaridf(lfact,lfact->fin,id) == 0 || i->datos->id == id)verif = 1;
	  else printf("Ya hay otra factura con el mismo numero. ingrese 0 para salir.\n");
  }while(verif != 1);
  getchar();
  verif = 0;
  do{
	printf("Indique el cliente: ");
	fgets(proveedor,21,stdin);
	if ((strlen(proveedor)>0) && (proveedor[strlen(proveedor)- 1] == '\n'))//Sacamos la nueva linea del final-
        proveedor[strlen(proveedor)-1] = '\0';

	if(strcmp(proveedor, "0") == 0)return 0;
	id2 = buscarnomcl(sd,sd->fin,proveedor);
	if (id2 > 0)verif = 1;
	else printf("cliente %s no esta en la lista.\nAgregelo antes de insertar factura en el programa de clientes.\n(0 = salir)\n",proveedor);
	}while(verif == 0);
	verif = 0;
	
	do{	
		printf("Ingrese la fecha de la factura (dia mes año): ");
		scanf("%d %d %d",&dia,&mes,&anho);
		if(!(dia > 31 || mes > 12 || (anho < 1900 && anho > 2999)))verif = 1;
	}while(verif == 0);
	
  printf("Indique el monto total de la factura: ");
  scanf("%d",&monto);
  printf("El iva de la factura: ");
  scanf("%d",&iva);
  printf("Descripcion de la factura: ");
  getchar();
  fgets(descripcion,200,stdin);
  if ((strlen(descripcion)>0) && (descripcion[strlen(descripcion)- 1] == '\n'))//Sacamos la nueva linea del final-
        descripcion[strlen(descripcion)-1] = '\0';
        
  printf ("Numero: %d | Cliente: %s | Fecha: %d/%d/%d\nIVA: %d%% |Monto total: %d\nDescripcion: %s\n\n",id,proveedor,dia,mes,anho,iva,monto,descripcion);
		printf("Error.\n");
		
		//=================
		//===Espacio para modificarlo del archivo
		FILE * fp = NULL; 
	  printf("Error.");
		if ((fp = fopen("factura.txt","r")) == NULL){
			printf("Error, el archivo no se encontro. informe al administrador.");
			fclose(fp); 
			return -1;
		}
		
		FILE * fp2 = NULL;
		if((fp2 = fopen("facturatemp.txt","a"))  == NULL){
		printf("Error.");
		fclose(fp2);
		return -1;
		 }
		char fact[200] = "";
		char *prt;
		int idn = 0, diat = 0, mest = 0, anhot = 0, montot=0, ivat=0;
		char proveedort[21],descripciont[200];
		while(aux->siguiente != lfact->inicio){
		
		while( fgets(fact,300,fp) != NULL ){ 

			prt = strtok (fact, ",");
			if(prt)idn = atoi(prt);
			
			prt = strtok (NULL, ",");
			strcpy (proveedort, prt);

			prt = strtok (NULL, ",");
			if(prt)diat = atoi(prt);

			prt = strtok (NULL, ",");
			if(prt)mest = atoi(prt);
			
			prt = strtok (NULL, ",");
			if(prt)anhot = atoi(prt);
			
			prt = strtok (NULL, ",");
			if(prt)montot = atoi(prt);
			
			prt = strtok (NULL, ",");
			if(prt)ivat = atoi(prt);
			
			prt = strtok(NULL,",");
			strcpy(descripcion,prt);
		  
			if (i->datos->id != idn){
				fprintf(fp2,"%d,%s,%d,%d,%d,%d,%d,%s\n",idn,proveedort,diat,mest,anhot,montot,ivat,descripciont);
			}
			else if (i->datos->id == idn){
				fprintf(fp2,"%d,%s,%d,%d,%d,%d,%d,%s\n",id,proveedor,dia,mes,anho,monto,iva,descripcion);
			  }
		  }
		  aux = aux->siguiente;
	  }  
	  fclose(fp);
	  remove("factura.txt");
	  fclose(fp2);
	  rename("facturatemp.txt","factura.txt");
	  
	  //=======================================
	 //===Espacio para modificarlo en la lista
		i->datos->id = id;
		i->datos->dia = dia;
		i->datos->mes = mes;
		i->datos->anho = anho;
		i->datos->monto = monto;
		i->datos->iva = iva;
		strcpy(i->datos->proveedor,proveedor);
		strcpy(i->datos->descripcion,descripcion);
		
		printf("Factura modificada.");
return  0;	
}


//============================
//=====Funcion para ordenar la lista de forma ascendente
void ordenarFac(Factura *lfact){
	Factnodo * i = lfact->inicio;
	Factnodo * temp = NULL;
	temp = lfact->inicio;
	do{
	do{			
		if(i->datos->id > (i->siguiente)->datos->id){
			(i->siguiente)->anterior = i->anterior;//
			(i->anterior)->siguiente = i->siguiente;//
			i->anterior = i->siguiente;//
			i->siguiente = (i->siguiente)->siguiente;//
			(i->siguiente)->anterior = i;//
			(i->anterior)->siguiente = i;//
		if (lfact->inicio == i)//Nuestro nodo esta como inicio, debemos cambiarlo
			lfact->inicio = i->anterior;
		if (lfact->fin == i->anterior)//El nodo siguiente que cambiamos por el anterior era el final de la lista, ahora lo somos nosotros.
			lfact->fin = i;
		}
		i = i->siguiente;
	}while(i != lfact->fin);
	i = temp;	
	temp = temp->siguiente;
	
	}while(temp != lfact->fin);
}








/*
 * Codigo OBSOLETO
// Algoritmo de mezcla:
void Mezcla(FILE *fich)
{
   int ordenado;
   FILE *aux[2];

   // Bucle que se repite hasta que el fichero esté ordenado:
   do {
      // Crea los dos ficheros auxiliares para separar los tramos:
      aux[0] = fopen("aux1.txt", "w+");
      aux[1] = fopen("aux2.txt", "w+");
      rewind(fich);
      Separar(fich, aux);
      rewind(aux[0]);
      rewind(aux[1]);
      rewind(fich);
      ordenado = Mezclar(fich, aux);
      fclose(aux[0]);
      fclose(aux[1]);
   } while(!ordenado);
   // Elimina los ficheros auxiliares:
   remove("aux1.txt");
   remove("aux2.txt");
}

// Separa los tramos ordenados alternando entre los ficheros auxiliares:
void Separar(FILE *fich, FILE **aux)
{
   char linea[128], anterior[2][128];
   int salida = 0;

   // Volores iniciales para los últimos valores 
   // almacenados en los ficheros auxiliares
   strcpy(anterior[0], "");
   strcpy(anterior[1], "");
   // Captura la primero línea:
   fgets(linea, 128, fich);
   while(!feof(fich)) {
      // Decide a qué fichero de salida corresponde la línea leída:
      if(salida == 0 && strcmp(linea, anterior[0]) < 0) salida = 1;
      else if(salida == 1 && strcmp(linea, anterior[1]) < 0) salida = 0;
      // Almacena la línea actual como la última añadida:
      strcpy(anterior[salida], linea);
      // Añade la línea al fichero auxiliar:
      fputs(linea, aux[salida]);
      // Lee la siguiente línea:
      fgets(linea, 128, fich);
   }
}

// Mezcla los ficheros auxiliares:
int Mezclar(FILE *fich, FILE **aux)
{
   char ultima[128], linea[2][128], anterior[2][128];
   int entrada;
   int tramos = 0;

   // Lee la primera línea de cada fichero auxiliar:
   fgets(linea[0], 128, aux[0]);
   fgets(linea[1], 128, aux[1]);
   // Valores iniciales;
   strcpy(ultima, "");
   strcpy(anterior[0], "");
   strcpy(anterior[1], "");
   // Bucle, mientras no se acabe ninguno de los ficheros auxiliares (quedan tramos por mezclar):
   while(!feof(aux[0]) && !feof(aux[1])) {
      // Selecciona la línea que se añadirá:
      if(strcmp(linea[0], linea[1]) <= 0) entrada = 0; else entrada = 1;
      // Almacena el valor como el último añadido:
      strcpy(anterior[entrada], linea[entrada]);
      // Añade la línea al fichero:
      fputs(linea[entrada], fich);
      // Lee la siguiente línea del fichero auxiliar:
      fgets(linea[entrada], 128, aux[entrada]);
      // Verificar fin de tramo, si es así copiar el resto del otro tramo:
      if(strcmp(anterior[entrada], linea[entrada]) > 0) {
         if(!entrada) entrada = 1; else entrada = 0;
         tramos++;
         // Copia lo que queda del tramo actual al fichero de salida:
         do {
            strcpy(anterior[entrada], linea[entrada]);
            fputs(linea[entrada], fich);
            fgets(linea[entrada], 128, aux[entrada]);
         } while(!feof(aux[entrada]) && strcmp(anterior[entrada], linea[entrada]) <= 0);
      }
   }

   // Añadir tramos que queden sin mezclar:
   if(!feof(aux[0])) tramos++;
   while(!feof(aux[0])) {
      fputs(linea[0], fich);
      fgets(linea[0], 128, aux[0]);
   }
   if(!feof(aux[1])) tramos++;
   while(!feof(aux[1])) {
      fputs(linea[1], fich);
      fgets(linea[1], 128, aux[1]);
   }
   return(tramos == 1);
}
*/

