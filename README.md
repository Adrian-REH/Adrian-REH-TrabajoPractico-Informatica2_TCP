# Máquina de Estado
## Memoria descriptiva
 El sistema ha representar es del Protocolo de Control de Transmisión el cual se encarga de informar del destino de los datos permitiendo la creación de conexiones en 3 etapas.
 
 ### Conexiones TCP etapas
  __Establecimiento de conexión (3-way handshake)__: 
 >  - Una maquina abre un socket en un determinado puerto tcp y se queda a la escucha de nuevas conexiones (**_PASSIVE OPEN_**).
 >  - El cliente envia un segmento **_SYN_** inicial al servidor como parte de la negociación(**_ACTIVE OPEN_**). 
 >  - El lado servidor respondería a la petición **_SYN_** válida con un paquete **_SYN/ACK_**. 
 >  - Finalmente, el cliente debería responderle al servidor con un **_ACK_**, completando así la negociación en tres pasos **_(SYN, SYN/ACK y ACK)_** y la fase de establecimiento de conexión.
>
>   <p align="center"><img  src="https://user-images.githubusercontent.com/64231248/193424047-244a354a-fb86-4eca-9a27-0d72fc27fbe0.gif"> </p>
>   
>  _referencia de lo que sucedera en tus consolas de forma automatica.[GIF creado por mi ahre]_
 
 __Fin de la conexión (4-way handshake)__: 

>  - Una maquina llama al cierre, enviando un paquete **_FIN_** (**_ACTIVE CLOSE_**).
 >  - El cliente que recibe este FIN realiza un (**_PASSIVE CLOSE_**). Este **_FIN_** es confirmado por la maquina enviando un caracter fin de archivo.
 >  - El cliente recibió el carácter fin de archivo y llama a close para cerrar su socket, respondiendo un **_FIN_**.
 >  - La maquina que recibió este **_FIN_** final confirma este **_FIN_**.
 >
 >  <p align="center"><img  src="https://user-images.githubusercontent.com/64231248/193422432-fe214588-eec4-41a9-86ce-b9f601c271c7.gif"> </p>
 >  
 >  _referencia de lo que sucedera en tus consolas de forma automatica.[GIF creado por mi ahre]_

  __Transferencia de datos__: _El segmento TCP consta de una cabecera y un cuerpo para encapsular datos(solo describire 4):_

 <p align="center"><img height="400" src="https://github.com/Adrian-REH/Adrian-REH-TrabajoPractico-Informatica2_TCP/blob/main/recursos/Opera%20Captura%20de%20pantalla_2022-09-15_180002_cv.uoc.edu.png"> </p>

 >   1. _Número de Secuencia (32 bits)_: identifica el primer byte de los datos que envía el segmento. Al principio de la conexión se asigna un número de secuencia >inicial. A partir de este momento, el TCP numera los bytes consecutivamente a partir del ISN.
 >   
 >   2. _checksums (16 bits)_: Es calculado por el emisor y se incluye una pseudo-cabecera que incluye la dirección IP origen y
 >destino, e incluido en la transmisión del segmento. El cliente recalcula el checksum sobre las cabeceras y datos recibidos, la suma en complemento a uno con el >checksum incluido, y el resultado debe ser -0. Si es así, se asume que el segmento ha llegado intacto y sin errores.
 >
 >   3. _Campo control (6 bits)_:s eñala una función específica del protocolo cuando está activo(**_URG_**, **_ACK_**, **_PSH_**, **_RST_**, **_SYN_**, **_FIN_**)
 >   
 >   4. _número **_ACK_** (32 bits)._: Al activar un bit de la cabecera (el bit **_ACK_**), el TCP tiene en cuenta el número de secuencia ACK que indica al otro extremo >TCP el próximo byte que está dispuesto a recibir. Dicho de otro modo, el número **_ACK_** menos uno indica el último byte reconocido.



## Máquina de estado de Protocolo de Control de Transmisión 
<p align="center"><img src="https://github.com/Adrian-REH/Adrian-REH-TrabajoPractico-Informatica2_TCP/blob/main/recursos/tcp-state-machine.png"> </p>

 ### Apertura y Cierre de Puerto
 __ACTIVE OPEN__

 - __SYN_SENT__: La aplicación local ha emitido una llamada abierta de socket en un determinado puerto. Esto da como resultado un paquete **_SYN_** que fluye hacia la pila remota.
   La pila local luego espera un paquete **_ACK SYN_**. La conexión permanece en estado **_SYN_SENT_** cuando se recibe este paquete.
 - __STABLISHED__: Sigue del estado **_SYN_SENT_** cuando la pila local envía un reconocimiento por el paquete **_ACKSYN_** recibido, completando el protocolo de enlace  **_(3-way handshake)_**. Ambos lados ahora pueden enviar y recibir datos.

 __PASSIVE OPEN__

 - __LISTEN__: Esperando una solicitud de conexión de la dirección y el puerto enumerados en la columna Foreign Socket de **_NETSTAT_**.
 - __SYN_RCVD__: La aplicación remota ha emitido una llamada abierta de socket. Esto da como resultado un paquete **_SYN_** que fluye hacia la pila local. Cuando la pila local recibe el paquete **_SYN_**, se envía un mensaje **_ACKSYN_** a la aplicación remota. La conexión permanece en estado **_SYN_RCVD_** cuando se envía este paquete.
 - __STABLISHED__: Sigue del estado **_SYN_RCVD_** cuando la pila local recibe un reconocimiento del paquete **_ACKSYN enviado_**, completando el protocolo de enlace de tres vías. los lados ahora pueden enviar y recibir datos.

  __ACTIVE CLOSE__

 - __FIN_WAIT_1__: Sigue del estado **_STABLISHED_** cuando la aplicación local emite un cierre o apagado de socket. Esto da como resultado un paquete **_FIN_** que fluye hacia la pila remota. La pila local ahora está esperando un reconocimiento de **_FIN_**.
 - __FIN_WAIT_2__: Sigue del estado **_FIN_WAIT_1_** cuando la pila local recibe un reconocimiento por el **_FIN_** que se envió. El número de acuse de recibo debe ser 1 mayor que el número de secuencia del **_FIN_** enviado para provocar la transición de estado.
 - __CLOSING__: Sigue del estado **_FIN_WAIT_1_** cuando la pila local recibe un reconocimiento por el **_FIN_** que se envió y el indicador **_FIN_** también se establece (cierre simultáneo). El número de acuse de recibo debe ser 1 mayor que el número de secuencia del **_FIN_** enviado para provocar la transición de estado.
 - __TIME_WAIT__:Sigue del estado **_FIN_WAIT_2_** o del estado **_CLOSING_** cuando la pila local recibe un **_FIN_** y envía un acuse de recibo. El número de acuse de recibo debe ser 1 mayor que el número de secuencia del **_FIN_** recibido para provocar la transición de estado.
 - __CLOSED__: Sigue del estado **_TIME_WAIT_** cuando ha pasado 2MSL _(el doble de la duración máxima del segmento) (MSL = 60 segundos)_.

  __PASSIVE CLOSE__

 - __CLOSING_WAIT__: Sigue del estado **_STABLISHED_** cuando la aplicación remota emite un cierre o apagado de socket. Esto da como resultado un paquete **_FIN_** que fluye desde la aplicación remota. La pila local debe recibir el **_FIN_** y reconocerlo. El número de acuse de recibo debe ser 1 mayor que el número de secuencia del **_FIN_** recibido para provocar la transición de estado.
 - __LAST_ACK__: Sigue del estado **_CLOSE_WAIT_** cuando la aplicación local emite un cierre o apagado de socket. Esto da como resultado un paquete **_FIN_** que fluye hacia la pila remota.
 - __CLOSED__: Sigue del estado **_LAST_ACK_** cuando la pila local recibe un reconocimiento por el **_FIN_** enviado. El número de reconocimiento debe ser 1 mayor que el número de secuencia del **_FIN_** enviado para provocar la transición de estado



 > __ACK__: Indica que el Número de Reconocimiento es válido.
 > 
 > __SYN__: Permite sincronizar los Números de Secuencia al iniciar una conexión o
 después de una reinicialización.
 > 
 > __FIN__: Indica la finalización del envío de datos. Puede estar activo tanto en los
 segmentos de origen a destino como en los pertenecientes al flujo contrario ya
 que se trata de una comunicación full-duplex

## Código
- Archivo de cabecera __mylib.h__

```c
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
int LISTEN(segmento_t segmentos);
int SYN_RCVD(segmento_t segmentos);
//ESPERA DE SEGMENTO O FIN
int STABLISHED(segmento_t segmentos,char*);
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
```
 ## Puesta en marcha
 
 **CMD 1**: 
- PASSIVE OPEN
```
---------------------------------------------------------
Hola Jefe!. Que quiere ser?
1.Servidor
2.Cliente
3.Salir
: 1
---------------------------------------------------------
*SEGMENTO*:  
 Texto a enviar: perro
---------------------------------------------------------
*SOCKET*:
	 IP:PORT(Origen): 255.255.255.255:4040
	 IP:PORT(Destino):
---------------------------------------------------------
```
```
---------------------------------------------------------
*SERVIDOR*: SYN Recibido 0ms
	 IP:PORT(Origen): 182.110.4.53:4040
	 IP:PORT(Destino): 255.255.255.255:4040
	 NS: B
	 ACK:
	 CTRL.ACK: FALSE
	 CTRL.SYN: TRUE
	 CTRL.FIN: FALSE
---------------------------------------------------------
*SERVIDOR*: SYN/ACK Enviado
---------------------------------------------------------
*SERVIDOR*: ACK Recibido 1ms
	*RECIBE*:
		 IP:PORT(Origen): 182.110.4.53:4040
		 IP:PORT(Destino): 255.255.255.255:4040
		 NS: B
		 ACK: B,A
		 CTRL.ACK: TRUE
		 CTRL.SYN: FALSE
		 CTRL.FIN: FALSE
---------------------------------------------------------
*SEGMENTO RESPALDADO*
---------------------------------------------------------
*CONEXION ESTABLECIDA*:
*TEXTO RECIBIDO*: gato
Desea enviar mas datos? 1.No 2.Si: 1
---------------------------------------------------------
```
- ACTIVE CLOSE
```
---------------------------------------------------------
*FIN*: Enviado
---------------------------------------------------------
*ACK*: Recibido 3ms
	*RECIBE*:
		 IP:PORT(Origen): 255.255.255.255:4040
		 IP:PORT(Destino): 182.110.4.53:4040
		 NS: D
		 ACK: D,C
		 CTRL.ACK: TRUE
		 CTRL.SYN: FALSE
		 CTRL.FIN: FALSE
---------------------------------------------------------
*FIN*: Recibido 2ms
	*RECIBE*:
		 IP:PORT(Origen): 255.255.255.255:4040
		 IP:PORT(Destino): 182.110.4.53:4040
		 NS: D
		 ACK: D,C
		 CTRL.ACK: FALSE
		 CTRL.SYN: FALSE
		 CTRL.FIN: TRUE
---------------------------------------------------------
*ACK*: Enviado
---------------------------------------------------------
*FIN DE LA COMUNICACION*
---------------------------------------------------------
```

**CMD 2**: 
- ACTIVE OPEN
```
---------------------------------------------------------
Hola Jefe!. Que quiere ser?
1.Servidor
2.Cliente
3.Salir
: 2
---------------------------------------------------------
*SEGMENTO*:  
 Texto a enviar: perro
 ---------------------------------------------------------
*SOCKET*:
	 IP:PORT(Origen): 182.110.4.53:4040
	 IP:PORT(Destino): 255.255.255.255:4040
---------------------------------------------------------
```
```
---------------------------------------------------------
*CLIENTE*: SYN Enviado
---------------------------------------------------------
*CLIENTE*: SYN/ACK Recibido 9ms
	*RECIBE*:
		 IP:PORT(Origen): 255.255.255.255:4040
		 IP:PORT(Destino): 182.110.4.53:4040
		 NS: A
		 ACK: A,B
		 CTRL.ACK: TRUE
		 CTRL.SYN: TRUE
		 CTRL.FIN: FALSE
---------------------------------------------------------
*SEGMENTO RESPALDADO*
---------------------------------------------------------
*CONEXION ESTABLECIDA*:
---------------------------------------------------------
*TEXTO RECIBIDO*: perro
---------------------------------------------------------
Desea enviar mas datos? 1.No 2.Si: 2
---------------------------------------------------------
```
- PASSIVE CLOSE

```
---------------------------------------------------------
*FIN*: Recibido 0ms
	*RECIBE*:
		 IP:PORT(Origen): 182.110.4.53:4040
		 IP:PORT(Destino): 255.255.255.255:4040
		 NS: C
		 ACK:
		 CTRL.ACK: FALSE
		 CTRL.SYN: FALSE
		 CTRL.FIN: TRUE
---------------------------------------------------------
*ACK*: Enviado
---------------------------------------------------------
*FIN*: Enviado
---------------------------------------------------------
*ACK*: Recibido 2ms
	*RECIBE*:
		 IP:PORT(Origen): 182.110.4.53:4040
		 IP:PORT(Destino): 255.255.255.255:4040
		 NS: C
		 ACK: C,D
		 CTRL.ACK: TRUE
		 CTRL.SYN: FALSE
		 CTRL.FIN: FALSE
---------------------------------------------------------
*FIN DE LA COMUNICACION*
---------------------------------------------------------
```
 ### Tiempo
 Tiempo total : 22hs
- Para el codigo: 14hs
- - OPEN: 10hs
- - CLOSE: 4hs
- Para la investigacion: 8 hs
