# Máquina de Estado
### Memoria descriptiva

### Máquina de estado de Protocolo de Control de Transmisión y Descripcion de estados de conexion

 ![./recursos/tcp-state-machine.png](https://github.com/Adrian-REH/Adrian-REH-TrabajoPractico-Informatica2_TCP/blob/main/recursos/tcp-state-machine.png)

__ACTIVE OPEN__

- __SYN_SENT__: La aplicación local ha emitido una llamada abierta de socket. 
  Esto da como resultado un paquete **_SYN_** que fluye hacia la pila remota.
  La pila local luego espera un paquete **_ACKSYN_**. La conexión permanece en estado **_SYN_SENT_** cuando se recibe este paquete.
- __STABLISHED__: Sigue del estado **_SYN_SENT_** cuando la pila local envía un reconocimiento por el paquete **_ACKSYN_** recibido, completando el protocolo de enlace de tres vías. Ambos lados ahora pueden enviar y recibir datos.

__PASSIVE OPEN__

- __LISTEN__: Esperando una solicitud de conexión de la dirección y el puerto enumerados en la columna Foreign Socket de **_NETSTAT_**.
- __SYN_RCVD__: La aplicación remota ha emitido una llamada abierta de socket. Esto da como resultado un paquete **_SYN_** que fluye hacia la pila local. Cuando la pila local recibe el paquete **_SYN_**, se envía un mensaje **_ACKSYN_** a la aplicación remota. La conexión permanece en estado **_SYN_RCVD_** cuando se envía este paquete.
- __STABLISHED__: Sigue del estado **_SYN_RCVD_** cuando la pila local recibe un reconocimiento del paquete **_ACKSYN enviado_**, completando el protocolo de enlace de tres vías. los lados ahora pueden enviar y recibir datos.

 __ACTIVE CLOSE__

- __FIN_WAIT_1__: Sigue del estado **_ESTABLECIDO_** cuando la aplicación local emite un cierre o apagado de socket. Esto da como resultado un paquete **_FIN_** que fluye hacia la pila remota. La pila local ahora está esperando un reconocimiento de **_FIN_**.
- __FIN_WAIT_2__: Sigue del estado **_FIN_WAIT_1_** cuando la pila local recibe un reconocimiento por el **_FIN_** que se envió. El número de acuse de recibo debe ser 1 mayor que el número de secuencia del **_FIN enviado para provocar la transición de estado.
- __CLOSING__: Sigue del estado **_FIN_WAIT_1_** cuando la pila local recibe un reconocimiento por el **_FIN_** que se envió y el indicador **_FIN_** también se establece (cierre simultáneo). El número de acuse de recibo debe ser 1 mayor que el número de secuencia del **_FIN_** enviado para provocar la transición de estado.
- __TIME_WAIT__:Sigue del estado **_FIN_WAIT_2_** o del estado **_CLOSING_** cuando la pila local recibe un **_FIN_** y envía un acuse de recibo. El número de acuse de recibo debe ser 1 mayor que el número de secuencia del **_FIN_** recibido para provocar la transición de estado.
- __CLOSED__: Sigue del estado **_TIME_WAIT_** cuando ha pasado 2MSL _(el doble de la duración máxima del segmento) (MSL = 60 segundos)_.

 __PASSIVE CLOSE__

- __CLOSING_WAIT__: 
- __LAST_ACK__: 
- __CLOSED__: 


__CABECERA__
> __ACK__: Indica que el Número de Reconocimiento es válido.
> 
> __SYN__: Permite sincronizar los Números de Secuencia al iniciar una conexión o
después de una reinicialización.
> 
> __FIN__: Indica la finalización del envío de datos. Puede estar activo tanto en los
segmentos de origen a destino como en los pertenecientes al flujo contrario ya
que se trata de una comunicación full-duplex

### Código
