#ifndef _MYTYPES
#define _MYTYPES
#include <windows.h>

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include<stdbool.h>

FILE *datos,*servicio, *conf;

typedef struct {
    char ACK[6];
    char SYN[6];
    char FIN[6];

}control_t;

typedef struct {
	char portip_origen[64];
    char portip_destino[64];
    char NS[32];
    char ACK[32];

    control_t CTRL;
    char datos[32];
} segmento_t;

segmento_t (*seg)(segmento_t segmentos);
char * getkey(char *key);
int seleccionar(void);
segmento_t escribe_servicio(int);
//ACTIVE CLOSE
segmento_t SYN_SENT(segmento_t segmentos);
//PASSIVE CLOSE
segmento_t STABLISHED(segmento_t segmentos,char*);
segmento_t LISTEN(segmento_t segmentos);
segmento_t SYN_RCVD(segmento_t segmentos);
//ACTIVE CLOSE
segmento_t FIN_WAIT_1(segmento_t segmento);
int FIN_WAIT_2(segmento_t segmentos);
int TIME_WAIT(segmento_t segmentos);
//PASSIVE CLOSE
segmento_t CLOSING_WAIT(segmento_t segmento);
int LAST_ACK(segmento_t segmentos);
//FIN TOTAL
int CLOSED(void);

//DESCOMPONE EL ACK
char * ns_ack(char *);
#endif /* HEADERS_MYLIB_H_ */

