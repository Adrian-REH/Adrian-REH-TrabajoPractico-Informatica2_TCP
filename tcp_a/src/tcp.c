/*
 ============================================================================
 Name        : tcp.c
 Author      : Adrian Herrera
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "../Header/Mytypes.h"

int main(void) {

	int opc;
	int siguiente=0,crack=4;

	segmento_t pedidos;

	segmento_t (*entregas[4])(segmento_t pedidos)={LISTEN,SYN_SENT,FIN_WAIT_1,CLOSING_WAIT};
	opc=seleccionar();
	do{
		pedidos=(*entregas[opc-1])(escribe_servicio(opc));

		if(!strcmp(pedidos.CTRL.FIN,"FALSE")&&!strcmp(pedidos.CTRL.SYN,"FALSE")){
			crack=1;
			siguiente=3;
		}else if(!strcmp(pedidos.CTRL.FIN,"TRUE")&&!strcmp(pedidos.CTRL.SYN,"FALSE")){
			crack=1;

			siguiente=2;//ACTIVO
		}else if(!strcmp(pedidos.CTRL.FIN,"FALSE")&&!strcmp(pedidos.CTRL.SYN,"TRUE")){

			crack=0;
			siguiente=2;
		}
	}while(crack!=1);


	(*entregas[siguiente])(pedidos);





	/*LLENO LOS DATOS*/



	/**/





	return 0;
}
