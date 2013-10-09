#ifndef _IP_H
#define _IP_H

//variables globales para la gestion de rutas
ipv4_route_table_t * ipv4_route_table_aux = NULL;
eth_iface_t eth_iface_aux = NULL;

ipv4_iface_t * ipv4_open( ) {

	eth_iface = eth_open( "eth0" );
	ipv4_route_table_read ( FILENAME , ipv4_route_table_aux );
	
}


ipv4_iface_t * ipv4_open( ) {

	//suponemos que solo hay una interfaz
	eth_close( eth_iface_aux );
	ipv4_route_table_free (ipv4_route_table_aux);
}

/* devuelve lo mismo que eth_send (bytes enviados) o -1 si ha habido error*/
int ipv4_send( ipv4_address_t dst, uint8_t type, unsigned char * payload, int payload_len  ) {

	int bytes_sent = 0;
	int arp_flag = 0;   

        mac_addr_t mac_addr; //mac destino 
   
   	arp_flag = arp_resolve (iface, dst , mac_addr_t ); //resolvemos ip

	if( arp_flag == -1 ) {

	//si error salimos
		printf("Cannot resolve ip addr into mac addr");
		return arp_flag; //-1
	}    

	bytes_sent eth_send ( eth_iface_aux, 
	 			 dst,
				 IPV4_OVER_ETH_TYPE,
				 payload,
 				 payload_len );
	

	return bytes_sent;
}


int ipv4_recv( ipv4_address_t src, uint8_t prot, unsigned char buffer[], long int timeout ) {

 /* PROGRAMAR ESTO JODER HIJOS DE PUTA Y HACED PRUEBAS */
}


#endif
