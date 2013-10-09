#ifndef

#include "arp.h"
#include "ipv4_route_table.h"
#include "ipv4.h"
#define FILENAME "default.txt"
#define IPV4_OVER_ETH_TYPE 0

/*
Esta funcion iniciaiza la interfaz Ethernet asi como las tablas de rutas y 
provee el contexto necesario para el envio y la recepcion de los paquetes
*/
ipv4_iface_t * ipv4_open( ); 

/*
Envia un paquete ip
*/
int ipv4_send( ipv4_address_t dst, uint8_t type, unsigned char * payload, int payload_len );

/*
Recibe un paquete ip
*/
int ipv4_recv( ipv4_address_t src, uint8_t prot, unsigned char buffer[], long int timeout );

/*
Cierra el contexto ip
*/

int ipv4_close(); 


