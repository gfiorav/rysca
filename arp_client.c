#include "arp.h"

// int arp_resolve(eth_iface_t * iface, ipv4_addr_t ip_addr, mac_addr_t mac_addr);

int main(int argc, char *argv[]) {

	if(argc != 3) {

		printf("Usage: arp_client <eth_iface> <ip_address>\n");
		return 0;
	}

	else {

		eth_iface_t* iface 	= eth_open( argv[1] );

	 	/* Abrimos interfaz de 								ethernet para poder 
			enviar/recibir*/

		ipv4_addr_t ip_addr;		
		ipv4_str_addr(argv[2], ip_addr);		//dir ip deseada

		printf("\nBuscando %s por la interfaz %s\n", argv[2], argv[1]);
	/* 1o hacer flooding para informar a la red de que buscas una mac*/
	
	arp_msg flood_arp = init_flood_req( iface, ip_addr);

	
	/* enviarlo por ethernet */

	eth_send ( iface, 
		flood_arp.mac_dst, 
		ETH_ARP_TYPE, 
		(unsigned char *) &flood_arp,
		sizeof(flood_arp));

// 	// int eth_recv 
// ( eth_iface_t * iface, 
//   mac_addr_t src, uint16_t type, unsigned char buffer[], long int timeout );

	arp_msg recv_buffer = default_arp_msg();

	int rcv_flag;

	rcv_flag = eth_recv( iface,
		flood_arp.mac_dst, 
		ETH_ARP_TYPE,
		(unsigned char*) &recv_buffer,
		(long int) 2000);
	
	char mac_recv[MAC_ADDR_SIZE];

	mac_addr_str(recv_buffer.mac_src, mac_recv);

	// Si no se ha recibido se vuelve a enviar la peticion ARP
	if( rcv_flag != -2)  
	{
		printf("%s ~> %s\n", argv[2], mac_recv);
	}
	else 
	{
		eth_send ( iface, 
		flood_arp.mac_dst, 
		ETH_ARP_TYPE, 
		(unsigned char *) &flood_arp,
		sizeof(flood_arp));

		rcv_flag = eth_recv( iface,
		flood_arp.mac_dst, 
		ETH_ARP_TYPE,
		(unsigned char*) &recv_buffer,
		(long int) 2000);
	}
		
	eth_close(iface);

	}

	return 0;	
}
