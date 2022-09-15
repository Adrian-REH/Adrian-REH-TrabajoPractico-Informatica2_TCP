# Máquina de Estado
### Memoria descriptiva

### Máquina de estado de Protocolo de Control de Transmisión y Descripcion de estados de conexion

 ![./recursos/tcp-state-machine.png](https://github.com/Adrian-REH/Adrian-REH-TrabajoPractico-Informatica2_TCP/blob/main/recursos/tcp-state-machine.png)

- __ACTIVE OPEN__
 ```
SYN_SENT: La aplicación local ha emitido una llamada abierta de socket. 
 Esto da como resultado un paquete SYN que fluye hacia la pila remota.
 La pila local luego espera un paquete ACKSYN. La conexión permanece en estado SYN_SENT cuando se recibe este paquete.
STABLISHED: 
 ```
- __PASSIVE OPEN__
```
LISTEN: 
SYN_RCVD: 
STABLISHED: 
 ```
 - __ACTIVE CLOSE__
 ```
FIN_WAIT_1: 
FIN_WAIT_2: 
CLOSING: 
TIME_WAIT:
CLOSED: 
 ```
 - __PASSIVE CLOSE__
 ```
CLOSING_WAIT: 
LAST_ACK: 
CLOSED: 
```

CABECERA
> __ACK__: Indica que el Número de Reconocimiento es válido.
> 
> __SYN__: Permite sincronizar los Números de Secuencia al iniciar una conexión o
después de una reinicialización.
> 
> __FIN__: Indica la finalización del envío de datos. Puede estar activo tanto en los
segmentos de origen a destino como en los pertenecientes al flujo contrario ya
que se trata de una comunicación full-duplex

### Código
