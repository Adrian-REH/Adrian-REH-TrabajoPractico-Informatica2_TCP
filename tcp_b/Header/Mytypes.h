#ifndef _MYTYPES
#define _MYTYPES
#include <windows.h>

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include<stdbool.h>
typedef struct {
    char ACK[6];
    char SYN[6];
    char FIN[6];

}control_t;


FILE *datos,*servicio;
typedef struct {
	char portip_origen[64];
    char portip_destino[64];
    char NS[32];
    char ACK[32];

    control_t CTRL;
    char datos[32];
} segmento_t;


int seleccionar(void);
segmento_t escribe_servicio(char *);
//ACTIVE CLOSE
int SYN_SENT(segmento_t segmentos);
//PASSIVE CLOSE
int STABLISHED(segmento_t segmentos,char*);
int LISTEN(segmento_t segmentos);
int SYN_RCVD(segmento_t segmentos);
//ACTIVE CLOSE
int FIN_WAIT_1(void);
int FIN_WAIT_2(segmento_t segmentos);
int TIME_WAIT(segmento_t segmentos);
//PASSIVE CLOSE
int CLOSING_WAIT(void);
int LAST_ACK(segmento_t segmentos);
//FIN TOTAL
int CLOSED(void);

//DESCOMPONE EL ACK
char * ns_ack(char *);
#endif /* HEADERS_MYLIB_H_ */

