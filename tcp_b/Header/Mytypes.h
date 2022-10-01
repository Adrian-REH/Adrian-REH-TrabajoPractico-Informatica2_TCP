#ifndef _MYTYPES
#define _MYTYPES
#include <windows.h>

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include<stdbool.h>
typedef struct {
    char ACK[6];//FALSE
    char SYN[6];//TRUE
    char FIN[6];//FALSE

}control_t; //USO ESTA ESTRUCTURA PARA FORMALIZAR EL CODIGO DE CONTROL HACIENDO LA SEÑALACION DE UNA FUNCION PARA COMUNICAR


FILE *datos,*servicio;
typedef struct {
	char portip_origen[64]; //255.255.255.255:4040(No tiene funcion)
    char portip_destino[64]; //255.255.255.255:8080(No tiene funcion)
    char NS[32]; //sera un caracter aleatorio para cada segmento en una comunicacion(Creo una funcion)
    char ACK[32]; //SECUENCIA DE DATOS EN CADENADOS COMO BLOCKCHAIN(Creo una funcion)

    control_t CTRL; //verifico la funcion que tiene e inicio la respectiva funcion
    char datos[32]; //(Creo una funcion)
} segmento_t;




//ACTIVE_OPEN QUIERO SER CLIENTE(SYN_SENT,STABLISHED)
//PASSIVE_OPEN QUIERO SER SERVIDOR (LISTEN,SYN_RCVD,STABLISHED)


int seleccionar(void);//PREGUNTA SI SERAS EL SERVIDOR O CLIENTE Y PIDE LLENAR EL SEGMENTO LO GUARDA en servicio.dat
segmento_t escribe_servicio(char *);//TE PIDE LLENAR EL SEGMENTO Y REDIRECCIONA SERVIDOR(LISTEN) Y CLIENTE(SYN_SENT)

int SYN_SENT(segmento_t segmentos);//LEE EL ARCHIVO servicio.dat Y GUARDA EL DATO EN EL ARCHIVO datos.dat y ESPERA (EL SYN/ACK DEL SERVIDOR) al completarse va a ESTABLISHED
int STABLISHED(segmento_t segmentos,char*);//AHORA PUEDO MOSTRAR LOS DATOS
int LISTEN(segmento_t segmentos);//RECONOCE QUE LE ENVIARON UN SYN(EL SYN DEL CLIENTE) Y GUARDA TEMPORALMENTE LA IP Y PORT
int SYN_RCVD(segmento_t segmentos);//GUARDA EL SYN(SN DEL CLIENTE) EN ACK EN servicios.dat [MUESTRA EN CONSOLA LA LECTURA]Y ESPERO EL ACK DEL CLIENTE al completarse va a ESTABLISHED

int FIN_WAIT_1(void);
int FIN_WAIT_2(segmento_t segmentos);
int CLOSING(segmento_t segmentos);
int CLOSED(void);


int TIME_WAIT(segmento_t segmentos);
int CLOSING_WAIT(void);
int LAST_ACK(segmento_t segmentos);


char * ns_ack(char *);//DESCOMPONE EL ACK
#endif /* HEADERS_MYLIB_H_ */

