#include "arp.h"

// int arp_resolve(eth_iface_t * iface, ipv4_addr_t ip_addr, mac_addr_t mac_addr);

int main(int argc, char *argv[]) {

	if(argc != 3) {

		printf("Usage: arp_client <eth_iface> <ip_address>\n");
		return -1;
	}

	unsigned char * mac_received = (unsigned char*) malloc(MAC_ADDR_SIZE);
	eth_iface_t * iface = eth_open( argv[1]);
	ipv4_addr_t addr;
	ipv4_str_addr ( argv[2], addr );
	printf("Llamamos a arp_resolve... \n");
	int result = arp_resolve( iface, addr, mac_received  );
	
	if (result == -1 ) {

		printf("No se ha podido traducir la ip\n");
	
	} else {

		char mac_str[MAC_STR_SIZE];
		mac_addr_str( mac_received, mac_str );
		printf("El cliente verifica que la mac es %s\n", mac_str );
	}

	free(mac_received);
	eth_close(iface);

	return 0;	
}
