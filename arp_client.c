#include "arp.h"

// int arp_resolve(eth_iface_t * iface, ipv4_addr_t ip_addr, mac_addr_t mac_addr);

int main(int argc, char *argv[]) {

	if(argc != 3) {

		printf("Usage: arp_client <eth_iface> <ip_address>\n");
		return -1;
	}

	unsigned char mac_received[MAC_ADDR_SIZE];
	eth_iface_t * iface = eth_open( argv[1]);
	ipv4_addr_t addr;
	ipv4_str_addr ( argv[2], addr );
	arp_resolve( iface, addr, mac_received  );

	printf("Hemos recibido %s\n", mac_received );
	eth_close(iface);

	return 0;	
}
