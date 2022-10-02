#include "../Header/Mytypes.h"

int seleccionar(void){
	int opc;
	int siguiente=0,crack=4;
	printf("\n---------------------------------------------------------\n");
	printf("Hola Jefe!. Que quiere ser? 1.Servidor 2.Cliente 3.Salir\n: ");
	scanf("%d",&opc);
	switch(opc){
	case 1:
		printf("\n---------------------------------------------------------\n");
		printf("*SEGMENTO*:  ");

		do{

			siguiente=LISTEN(escribe_servicio("SYN/ACK"));

			if(siguiente==3 || siguiente==1){
				crack=1;
			}else if(siguiente==2){
				crack=0;
			}

		}while(crack!=1);

		break;
	case 2:
		printf("*SEGMENTO*:  ");
		do{

			siguiente=SYN_SENT(escribe_servicio("SYN"));

			if(siguiente==3 || siguiente==1){
				crack=1;
			}else if(siguiente==2){
				crack=0;
			}

		}while(crack!=1);


		break;
	case 3:
		return 0;
		break;
	}
	switch(siguiente){
	case 1:
		printf("\n---------------------------------------------------------\n");
		FIN_WAIT_1();

		//ACTIVO
		break;
	case 3:
		//CLOSING_WAIT(escribe_servicio("SYN"));
			//PASIVO
		printf("\n---------------------------------------------------------\n");
		CLOSING_WAIT();

		break;
	}



	return 0;
}

segmento_t escribe_servicio(char *CTRL){
	segmento_t segmentos;
	char aux[30];
	strcpy(aux,CTRL);


	strcpy(segmentos.ACK,"");
	printf("\n\tTexto a enviar: ");
	scanf("%s",segmentos.datos);
	printf("\n---------------------------------------------------------\n");
	if(strcmp(aux,"SYN/ACK")== 0){
		strcpy(segmentos.portip_origen,"255.255.255.255:4040");
		strcpy(segmentos.portip_destino,"");
		strcpy(segmentos.NS,"A");
		strcpy(segmentos.CTRL.ACK,"TRUE");
		strcpy(segmentos.CTRL.SYN,"TRUE");
		strcpy(segmentos.CTRL.FIN,"FALSE");
		printf("\n*SOCKET*\n\tIP:PORT(Origen):\t%s\n\tIP:PORT(Destino):\t%s\n",segmentos.portip_origen,segmentos.portip_destino);
		printf("\n---------------------------------------------------------\n");
	}else if(strcmp(aux,"SYN")== 0){

		strcpy(segmentos.portip_origen,"182.110.4.53:4040");
		strcpy(segmentos.portip_destino,"255.255.255.255:4040");
		strcpy(segmentos.NS,"B");
		strcpy(segmentos.CTRL.ACK,"FALSE");
		strcpy(segmentos.CTRL.SYN,"TRUE");
		strcpy(segmentos.CTRL.FIN,"FALSE");
		printf("\n*SOCKET*\n\tIP:PORT(Origen):\t%s\n\tIP:PORT(Destino):\t%s\n",segmentos.portip_origen,segmentos.portip_destino);
		printf("\n---------------------------------------------------------\n");
	}

	return segmentos;

}

//ACTIVE CLOSE
int SYN_SENT(segmento_t segmentos){
	segmento_t sgment,sgment_stb;
	int i = 0;
	char NS[30];
	datos=fopen("../../datos.dat","wb");
	printf("\n*CLIENTE*:\tSYN Enviado\n");
	printf("\n---------------------------------------------------------\n");
	fwrite(&segmentos,sizeof(segmento_t),1,datos);
	fclose(datos);
	Sleep(100);

	while(i<=60){

		datos=fopen("../../datos.dat","rb");
		fread(&sgment,sizeof(segmento_t),1,datos);

		while(!feof(datos)){

			strcpy(NS,ns_ack(sgment.ACK));

			if((strcmp(sgment.portip_destino,segmentos.portip_origen)== 0)&&(strcmp(segmentos.NS,NS)== 0)){

				if((strcmp(sgment.CTRL.SYN,"TRUE")== 0)&&strcmp(sgment.CTRL.ACK,"TRUE")== 0){
					printf("\n*CLIENTE*:\tSYN/ACK Recibido %dms\n",i);
					printf("\n\t*RECIBE*:\n\t\tIP:PORT(Origen):\t%s\n\t\tIP:PORT(Destino):\t%s\n\t\tNS:\t%s\n\t\tACK:\t%s\n\t\tCTRL.ACK:\t%s \n\t\tCTRL.SYN:\t%s\n\t\tCTRL.FIN:\t%s\n",sgment.portip_origen,sgment.portip_destino,sgment.NS,sgment.ACK,sgment.CTRL.ACK,sgment.CTRL.SYN,sgment.CTRL.FIN);
					printf("\n---------------------------------------------------------\n");
					strcpy(sgment_stb.portip_origen,segmentos.portip_origen);
					strcpy(sgment_stb.portip_destino,segmentos.portip_destino);
					strcpy(sgment_stb.ACK,segmentos.NS);
					strcat(sgment_stb.ACK,",");
					strcat(sgment_stb.ACK,sgment.NS);
					strcpy(sgment_stb.datos,segmentos.datos);
					strcpy(sgment_stb.NS,segmentos.NS);
					strcpy(sgment_stb.CTRL.ACK,"TRUE");
					strcpy(sgment_stb.CTRL.SYN,"FALSE");
					strcpy(sgment_stb.CTRL.FIN,"FALSE");
					return STABLISHED(sgment_stb,sgment.datos);

				}

			}
			fread(&sgment,sizeof(segmento_t),1,datos);

		}


		Sleep(1000);
		i++;
	}	//10 INTENTOS DE BUSCAR EN EL ARCHIVO CADA 10 SEGUNDOS SI EXISTE ALGUNA RESPUESTA

	printf("No se encontro comunicacion de parte del servidor");
	fclose(datos);

	return 0;
}

//PASSIVE CLOSE
int LISTEN(segmento_t segmentos){
	segmento_t sgment,sgment_rcvd;

	int i = 0;
	while(i<=60){
		datos=fopen("../../datos.dat","rb");
		fread(&sgment,sizeof(segmento_t),1,datos);
		while(!feof(datos)){
				if(strcmp(sgment.portip_destino,segmentos.portip_origen)==0){

					if(strcmp(sgment.CTRL.SYN,"TRUE")== 0){

						printf("\n*SERVIDOR*:\tSYN Recibido %dms\n",i);
						printf("\n\t*RECIBE*:\n\t\tIP:PORT(Origen):\t%s\n\t\tIP:PORT(Destino):\t%s\n\t\tNS:\t%s\n\t\tACK:\t%s\n\t\tCTRL.ACK:\t%s \n\t\tCTRL.SYN:\t%s\n\t\tCTRL.FIN:\t%s\n",sgment.portip_origen,sgment.portip_destino,sgment.NS,sgment.ACK,sgment.CTRL.ACK,sgment.CTRL.SYN,sgment.CTRL.FIN);
						printf("\n---------------------------------------------------------\n");
						strcpy(sgment_rcvd.portip_origen,segmentos.portip_origen);
						strcpy(sgment_rcvd.portip_destino,sgment.portip_origen);
						strcpy(sgment_rcvd.ACK,segmentos.NS);
						strcat(sgment_rcvd.ACK,",");
						strcat(sgment_rcvd.ACK,sgment.NS);
						strcpy(sgment_rcvd.datos,segmentos.datos);
						strcpy(sgment_rcvd.NS,segmentos.NS);
						strcpy(sgment_rcvd.CTRL.ACK,"TRUE");
						strcpy(sgment_rcvd.CTRL.SYN,"TRUE");
						strcpy(sgment_rcvd.CTRL.FIN,"FALSE");
						return SYN_RCVD(sgment_rcvd);

					}else if(strcmp(sgment.CTRL.FIN,"TRUE")){
						//return CLOSE();
					}

				}

				fread(&sgment,sizeof(segmento_t),1,datos);

		}



		Sleep(1000);
		i++;
	}	//10 INTENTOS DE BUSCAR EN EL ARCHIVO CADA 10 SEGUNDOS SI EXISTE ALGUNA RESPUESTA
	fclose(datos);
	printf("No se encontro comunicacion de parte del cliente");

	return 0;

}
int SYN_RCVD(segmento_t segmentos){
	segmento_t sgment;
	int i = 0;
	char NS[30];
	fclose(datos);
	datos=fopen("../../datos.dat","wb");

	printf("\n*SERVIDOR*:\tSYN/ACK Enviado\n");
	printf("\n---------------------------------------------------------\n");
	fwrite(&segmentos,sizeof(segmento_t),1,datos);
	fclose(datos);

	while(i<=60){
			datos=fopen("../../datos.dat","rb");
			fread(&sgment,sizeof(segmento_t),1,datos);

			while(!feof(datos)){
				strcpy(NS,ns_ack(sgment.ACK));

				if((strcmp(sgment.portip_destino,segmentos.portip_origen)== 0)&&(strcmp(segmentos.NS,NS)== 0)){
					if(strcmp(sgment.CTRL.ACK,"TRUE")== 0){

						printf("\n*SERVIDOR*:\tACK Recibido %dms\n",i);
						printf("\n\t*RECIBE*:\n\t\tIP:PORT(Origen):\t%s\n\t\tIP:PORT(Destino):\t%s\n\t\tNS:\t%s\n\t\tACK:\t%s\n\t\tCTRL.ACK:\t%s \n\t\tCTRL.SYN:\t%s\n\t\tCTRL.FIN:\t%s\n",sgment.portip_origen,sgment.portip_destino,sgment.NS,sgment.ACK,sgment.CTRL.ACK,sgment.CTRL.SYN,sgment.CTRL.FIN);
						printf("\n---------------------------------------------------------\n");
						return STABLISHED(segmentos,sgment.datos);
					}else if(strcmp(sgment.CTRL.FIN,"TRUE")){
						//return CLOSE();
					}

				}

				fread(&sgment,sizeof(segmento_t),1,datos);


			}





			Sleep(1000);
			i++;
		}	//10 INTENTOS DE BUSCAR EN EL ARCHIVO CADA 10 SEGUNDOS SI EXISTE ALGUNA RESPUESTA
	printf("No recivi un ACK en 6 segundos de espera\n");

	fclose(datos);
	return 0;
}

//ESPERO SEGMENTO O FIN
int STABLISHED(segmento_t segmentos,char*s){

	int opc;
	segmento_t sgment;
	servicio=fopen("servicios.dat","wb");

	printf("\n*SEGMENTO RESPALDADO*\n");
	printf("\n---------------------------------------------------------\n");
	fwrite(&segmentos,sizeof(segmento_t),1,servicio);
	fclose(servicio);

	datos=fopen("../../datos.dat","wb");

	printf("\n*CONEXION ESTABLECIDA*:\n");
	printf("\n---------------------------------------------------------\n");
	fwrite(&segmentos,sizeof(segmento_t),1,datos);
	fclose(datos);


	printf("*TEXTO RECIBIDO*:\t%s \nDesea enviar mas datos?\t1.No\t2.Si: ",s);
	scanf("%d",&opc);

		datos=fopen("../../datos.dat","rb");
		fread(&sgment,sizeof(segmento_t),1,datos);
		while(!feof(datos)){

			if(strcmp(sgment.CTRL.FIN,"TRUE")== 0){
				printf("\n---------------------------------------------------------\n");
				printf("\n*LA CONTRAPARTE ENVIO UN FIN DESCONECTARSE*\n");
				opc=3;
				return 3;//ES PASIVO
			}else if(strcmp(sgment.CTRL.FIN,"FALSE")== 0){

				return opc;//ES ACTIVO
			}

			fread(&sgment,sizeof(segmento_t),1,datos);
		}


	fclose(datos);
	return 2;

}

char * ns_ack(char *s){
	char *p,aux[30];
	strcpy(aux,s);
	p=aux;
	while(*p!=','){
		p++;
	}
	*p=0;
	p++;

	return p;
}

//ACTIVE CLOSE
int FIN_WAIT_1(void){
	segmento_t segmentos,finsegment;


	//LEO EL RESPALDO PARA ADQUIRIR DATOS
	servicio=fopen("servicios.dat","rb");
	fread(&segmentos,sizeof(segmento_t),1,servicio);

	fclose(servicio);

	strcpy(finsegment.ACK,"");
	strcpy(finsegment.datos,"");
	strcpy(finsegment.portip_origen,segmentos.portip_origen);
	strcpy(finsegment.portip_destino,segmentos.portip_destino);
	strcpy(finsegment.NS,"C");
	strcpy(finsegment.CTRL.ACK,"FALSE");
	strcpy(finsegment.CTRL.SYN,"FALSE");
	strcpy(finsegment.CTRL.FIN,"TRUE");

	datos=fopen("../../datos.dat","wb");

	printf("\n*FIN*:\tEnviado\n");
	printf("\n---------------------------------------------------------\n");
	fwrite(&finsegment,sizeof(segmento_t),1,datos);
	fclose(datos);


	return FIN_WAIT_2(finsegment);
}
int FIN_WAIT_2(segmento_t segmentos){
	segmento_t finsegment;
	int i = 0;
	char NS[30];
	while(i<=60){
		datos=fopen("../../datos.dat","rb");
		fread(&finsegment,sizeof(segmento_t),1,datos);
		while(!feof(datos)){
			strcpy(NS,ns_ack(finsegment.ACK));

			if((strcmp(finsegment.portip_destino,segmentos.portip_origen)== 0)&&(strcmp(segmentos.NS,NS)== 0)){

				printf("\n*ACK*:\tRecibido %dms\n",i);
				printf("\n\t*RECIBE*:\n\t\tIP:PORT(Origen):\t%s\n\t\tIP:PORT(Destino):\t%s\n\t\tNS:\t%s\n\t\tACK:\t%s\n\t\tCTRL.ACK:\t%s \n\t\tCTRL.SYN:\t%s\n\t\tCTRL.FIN:\t%s\n",finsegment.portip_origen,finsegment.portip_destino,finsegment.NS,finsegment.ACK,finsegment.CTRL.ACK,finsegment.CTRL.SYN,finsegment.CTRL.FIN);
				printf("\n---------------------------------------------------------\n");
				return TIME_WAIT(segmentos);

			}
			fread(&finsegment,sizeof(segmento_t),1,datos);
		}

		Sleep(1000);
		i++;
	}
	fclose(datos);
	return 0;
}
int TIME_WAIT(segmento_t segmentos){
	segmento_t finsegment,rcvsegment;
	int i = 0;
	while(i<=60){
		datos=fopen("../../datos.dat","rb");
		fread(&rcvsegment,sizeof(segmento_t),1,datos);
		while(!feof(datos)){
			if((strcmp(rcvsegment.portip_destino,segmentos.portip_origen)== 0)&&(strcmp(rcvsegment.CTRL.FIN,"TRUE")== 0)){

					printf("\n*FIN*:\tRecibido %dms\n",i);
					printf("\n\t*RECIBE*:\n\t\tIP:PORT(Origen):\t%s\n\t\tIP:PORT(Destino):\t%s\n\t\tNS:\t%s\n\t\tACK:\t%s\n\t\tCTRL.ACK:\t%s \n\t\tCTRL.SYN:\t%s\n\t\tCTRL.FIN:\t%s\n",rcvsegment.portip_origen,rcvsegment.portip_destino,rcvsegment.NS,rcvsegment.ACK,rcvsegment.CTRL.ACK,rcvsegment.CTRL.SYN,rcvsegment.CTRL.FIN);
					printf("\n---------------------------------------------------------\n");
					strcpy(finsegment.ACK,"C");
					strcat(finsegment.ACK,",");
					strcat(finsegment.ACK,rcvsegment.NS);
					strcpy(finsegment.datos,"");
					strcpy(finsegment.portip_origen,segmentos.portip_origen);
					strcpy(finsegment.portip_destino,segmentos.portip_destino);
					strcpy(finsegment.NS,"C");
					strcpy(finsegment.CTRL.ACK,"TRUE");
					strcpy(finsegment.CTRL.SYN,"FALSE");
					strcpy(finsegment.CTRL.FIN,"FALSE");

					i=61;
				}

			fread(&rcvsegment,sizeof(segmento_t),1,datos);
		}
		Sleep(1000);
		i++;
	}

	fclose(datos);

	datos=fopen("../../datos.dat","wb");

	printf("\n*ACK*:\tEnviado\n");
	printf("\n---------------------------------------------------------\n");
	fwrite(&finsegment,sizeof(segmento_t),1,datos);
	fclose(datos);
	printf("\nEspere 10s\n");
	Sleep(10000);
	printf("\n---------------------------------------------------------\n");

	return CLOSED();
}


//PASSIVE CLOSE
int CLOSING_WAIT(void){

	segmento_t finsegment,rcvsegment,segmentos;
	int i = 0;
	servicio=fopen("servicios.dat","rb");
	fread(&segmentos,sizeof(segmento_t),1,servicio);

	fclose(servicio);
	while(i<=60){
		datos=fopen("../../datos.dat","rb");
		fread(&rcvsegment,sizeof(segmento_t),1,datos);
		while(!feof(datos)){
				if(strcmp(rcvsegment.CTRL.FIN,"TRUE")== 0){

					printf("\n*FIN*:\tRecibido %dms\n",i);
					printf("\n\t*RECIBE*:\n\t\tIP:PORT(Origen):\t%s\n\t\tIP:PORT(Destino):\t%s\n\t\tNS:\t%s\n\t\tACK:\t%s\n\t\tCTRL.ACK:\t%s \n\t\tCTRL.SYN:\t%s\n\t\tCTRL.FIN:\t%s\n",rcvsegment.portip_origen,rcvsegment.portip_destino,rcvsegment.NS,rcvsegment.ACK,rcvsegment.CTRL.ACK,rcvsegment.CTRL.SYN,rcvsegment.CTRL.FIN);
					printf("\n---------------------------------------------------------\n");
					strcpy(finsegment.ACK,"D");
					strcat(finsegment.ACK,",");
					strcat(finsegment.ACK,rcvsegment.NS);
					strcpy(finsegment.datos,"");
					strcpy(finsegment.portip_origen,segmentos.portip_origen);
					strcpy(finsegment.portip_destino,segmentos.portip_destino);
					strcpy(finsegment.NS,"D");
					strcpy(finsegment.CTRL.ACK,"TRUE");
					strcpy(finsegment.CTRL.SYN,"FALSE");
					strcpy(finsegment.CTRL.FIN,"FALSE");
					return LAST_ACK(finsegment);
				}

			fread(&rcvsegment,sizeof(segmento_t),1,datos);
		}
		Sleep(1000);
		i++;
	}
	fclose(datos);



	return 0;

}
int LAST_ACK(segmento_t segmentos){
	segmento_t finsegment;
	int i = 0;
	char NS[30];

	datos=fopen("../../datos.dat","wb");

	printf("\n*ACK*:\tEnviado\n");
	printf("\n---------------------------------------------------------\n");
	fwrite(&segmentos,sizeof(segmento_t),1,datos);
	fclose(datos);
	Sleep(2000);

	strcpy(segmentos.CTRL.ACK,"FALSE");
	strcpy(segmentos.CTRL.FIN,"TRUE");
	datos=fopen("../../datos.dat","wb");

	printf("\n*FIN*:\tEnviado\n");
	printf("\n---------------------------------------------------------\n");
	fwrite(&segmentos,sizeof(segmento_t),1,datos);
	fclose(datos);



	while(i<=60){
		datos=fopen("../../datos.dat","rb");
		fread(&finsegment,sizeof(segmento_t),1,datos);
		while(!feof(datos)){
			strcpy(NS,ns_ack(finsegment.ACK));
			if((strcmp(finsegment.portip_destino,segmentos.portip_origen)== 0)&&(strcmp(segmentos.NS,NS)== 0)){

				printf("\n*ACK*:\tRecibido %dms\n",i);
				printf("\n\t*RECIBE*:\n\t\tIP:PORT(Origen):\t%s\n\t\tIP:PORT(Destino):\t%s\n\t\tNS:\t%s\n\t\tACK:\t%s\n\t\tCTRL.ACK:\t%s \n\t\tCTRL.SYN:\t%s\n\t\tCTRL.FIN:\t%s\n",finsegment.portip_origen,finsegment.portip_destino,finsegment.NS,finsegment.ACK,finsegment.CTRL.ACK,finsegment.CTRL.SYN,finsegment.CTRL.FIN);
				printf("\n---------------------------------------------------------\n");
					return CLOSED();

			}
			fread(&finsegment,sizeof(segmento_t),1,datos);
		}

		Sleep(1000);
		i++;
	}
	fclose(datos);
	return CLOSED();
}


//FIN TOTAL
int CLOSED(void){

	printf("\n*FIN DE LA COMUNICACION*\n");
	printf("\n---------------------------------------------------------\n");
	return 0;
}
