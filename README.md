# Máquina de Estado
### Memoria descriptiva

### Máquina de estado de Protocolo de Control de Transmisión y Descripcion de estados de conexion

 ![./recursos/tcp-state-machine.png](https://github.com/Adrian-REH/Adrian-REH-TrabajoPractico-Informatica2_TCP/blob/main/recursos/tcp-state-machine.png)

- __ACTIVE OPEN__
 ```
SYN_SENT: 
STABLISHED: 
 ```
- __PASSIVE OPEN__
```
 - __LISTEN__: 
 - __SYN_RCVD__: 
 - __STABLISHED__: 
 ```
 - __ACTIVE CLOSE__
 ```
 - __FIN_WAIT_1__: 
 - __FIN_WAIT_2__: 
 - __CLOSING__: 
 - __TIME_WAIT__:
 - __CLOSED__: 
 ```
 - __PASSIVE CLOSE__
 ```
 - __CLOSING_WAIT__: 
 - __LAST_ACK__: 
 - __CLOSED__: 
```

 __CABECERA__

 - __ACK__:Indica que el Número de Reconocimiento es válido.
 - __SYN__:Permite sincronizar los Números de Secuencia al iniciar una conexión o
después de una reinicialización.
 - __FIN__:Indica la finalización del envío de datos. Puede estar activo tanto en los
segmentos de origen a destino como en los pertenecientes al flujo contrario ya
que se trata de una comunicación full-duplex

### Código
