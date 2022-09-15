# Máquina de Estado
## Memoria descriptiva
 El sistema ha representar es del Protocolo de Control de Transmisión el cual se encarga de informar del destino de los datos permitiendo la creación de conexiones seguras.
 
### Conexiones TCP etapas
 __Establecimiento de conexión (3-way handshake)__: 
  - Una maquina abre un socket en un determinado puerto tcp y se queda a la escucha de nuevas conexiones (**_PASSIVE OPEN_**).
  - El cliente envia un segmento **_SYN_** inicial al servidor como parte de la negociación(**_ACTIVE OPEN_**). 
  - El lado servidor respondería a la petición **_SYN_** válida con un paquete **_SYN/ACK_**. 
  - Finalmente, el cliente debería responderle al servidor con un **_ACK_**, completando así la negociación en tres pasos **_(SYN, SYN/ACK y ACK)_** y la fase de establecimiento de conexión.
 
 __Transferencia de datos__:
  El segmento TCP consta de una cabecera y un cuerpo para encapsular datos(solo describire 3):
   ![./recursos/tcp-state-machine.png](https://github.com/Adrian-REH/Adrian-REH-TrabajoPractico-Informatica2_TCP/blob/main/recursos/tcp-state-machine.png)
   
   1. _Número de Secuencia (32 bits)_: para ordenar los segmentos TCP recibidos y detectar paquetes duplicados,
   2. _checksums (16 bits)_: Es calculado por el emisor y se incluye una pseudo-cabecera que incluye la dirección IP origen y
destino, e incluido en la transmisión del segmento. El cliente recalcula el checksum sobre las cabeceras y datos recibidos, la suma en complemento a uno con el checksum incluido, y el resultado debe ser -0. Si es así, se asume que el segmento ha llegado intacto y sin errores.
   3. _Campo control (6 bits)_:
   4. _número ACK (32 bits)._: para detectar pérdidas y retrasos.

Durante el establecimiento de conexión TCP, los números iniciales de secuencia son intercambiados entre las dos entidades TCP. Estos números de secuencia son usados para identificar los datos dentro del flujo de bytes, y poder identificar los bytes de los datos de la aplicación. 


Un emisor TCP se refiere a su propio número de secuencia cuando habla de número de secuencia, 
mientras que con el número de asentimiento se refiere al número de secuencia del receptor. Para mantener la fiabilidad, un receptor asiente los segmentos TCP indicando que ha recibido una parte del flujo continuo de bytes. Una mejora de TCP, llamada asentimiento selectivo (SACK, selective acknowledgement) permite a un receptor TCP asentir los datos que se han recibido de tal forma que el remitente solo retransmita los segmentos de datos que faltan.

A través del uso de números de secuencia y asentimiento, TCP puede pasar los segmentos recibidos en el orden correcto dentro del flujo de bytes a la aplicación receptora. Los números de secuencia son de 32 bits (sin signo), que vuelve a cero tras el siguiente byte después del 232-1. Una de las claves para mantener la robustez y la seguridad de las conexiones TCP es la selección del número inicial de secuencia (ISN, Initial Sequence Number).



verificando que el _checksum_ de TCP también cubre los 96 bit de la cabecera que contiene la dirección origen, la dirección destino, el protocolo y el tamaño TCP. Esto proporciona protección contra paquetes mal dirigidos por errores en las direcciones.



Los asentimientos de los datos enviados o la falta de ellos, son usados por los emisores para interpretar las condiciones de la red entre el emisor y receptor TCP. Unido a los temporizadores, los emisores y receptores TCP pueden alterar el comportamiento del movimiento de datos. TCP usa una serie de mecanismos para conseguir un alto rendimiento y evitar la congestión de la red (la idea es enviar tan rápido como el receptor pueda recibir). Estos mecanismos incluyen el uso de ventana deslizante, algoritmo de comienzo lento, algoritmo de control de congestion, la retransmisión rápida, la recuperación rápida, y más.
 
 __Fin de la conexión (4-way handshake)__: 
  - Una maquina llama al cierre, enviando una paquete **_FIN_** (**_ACTIVE CLOSE_**).
  - El cliente que recibe este FIN realiza un (**_PASSIVE CLOSE_**). Este **_FIN_** es confirmado por la maquina enviando un caracter fin de archivo.
  - El cliente recibió el carácter fin de archivo y llama a close para cerrar su socket, respondiendo un **_FIN_**.
  - La maquina que recibió este **_FIN_** final confirma este **_FIN_**.
 
## Máquina de estado de Protocolo de Control de Transmisión 

 ![./recursos/tcp-state-machine.png](https://github.com/Adrian-REH/Adrian-REH-TrabajoPractico-Informatica2_TCP/blob/main/recursos/tcp-state-machine.png)

### Aperturas y Cierre de Puerto
__ACTIVE OPEN__

- __SYN_SENT__: La aplicación local ha emitido una llamada abierta de socket en un determinado puerto. Esto da como resultado un paquete **_SYN_** que fluye hacia la pila remota.
  La pila local luego espera un paquete **_ACK SYN_**. La conexión permanece en estado **_SYN_SENT_** cuando se recibe este paquete.
- __STABLISHED__: Sigue del estado **_SYN_SENT_** cuando la pila local envía un reconocimiento por el paquete **_ACKSYN_** recibido, completando el protocolo de enlace de tres vías. Ambos lados ahora pueden enviar y recibir datos.

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


__CABECERA__
> __ACK__: Indica que el Número de Reconocimiento es válido.
> 
> __SYN__: Permite sincronizar los Números de Secuencia al iniciar una conexión o
después de una reinicialización.
> 
> __FIN__: Indica la finalización del envío de datos. Puede estar activo tanto en los
segmentos de origen a destino como en los pertenecientes al flujo contrario ya
que se trata de una comunicación full-duplex

## Código
