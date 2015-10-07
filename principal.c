#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//===== Se procede a incluir todos los programas necesarios.
#include "cliente.c"
#include "facturas.c"
#include "guias.c"
#include "ordenes.c"

int main(){
	int opc=0;
	do{
		system("clear");
		printf("Elegir programa deseado:\n");
		printf("1)Facturas\n2)Guias\n3)Ordenes\n4)Clientes\n5)Cerrar programa\nOpción: ");
		scanf("%d",&opc);
		if(opc == 1)
			mainfact();
		else if(opc == 2)
			mainGD();
		else if (opc == 3)
			mainOC();
		else if (opc == 4)
			mainCL();
		else if(opc == 5)
			break;
		else printf("Opcion invalida\n");
 }while(opc != 5);
//Fin del fin
	 
	return 0;
}






/*
 * valgrind --leak-check=full --error-exit=1 --log-file=logerror.txt principal
 * compilacion: -g -ggdb
 * 
 */
