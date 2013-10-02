#include "arp.h"
#define LVL2_TYPE 1  	  	//para arp mac
#define LVL3_TYPE 0x0800 	//para arp ip
#define OP_CODE_ARP_REQ 1 
#define OP_CODE_ARP_RPLY 2

/* recibe iface abierta con eth_open y ip dst y devuelve estructura para flood*/

arp_msg default_arp_msg() {

	arp_msg std;			//standart
	std.l2_type = htons(LVL2_TYPE);
	std.l3_type = htons(LVL3_TYPE);
	std.ip_addr_len = IPv4_ADDR_SIZE;
	std.mac_addr_len = MAC_ADDR_SIZE;
	/*segmentation fault muy probable, malloc en ese caso*/
	return std;
}
 	
arp_msg init_flood_req( eth_iface_t * iface, ipv4_addr_t ip_dst ) {

	arp_msg flood;
	flood = default_arp_msg();
	flood.op_code = htons( OP_CODE_ARP_REQ ); //tipo request

	eth_getaddr ( iface, flood.mac_src ); //mac local
	ipv4_str_addr( IP_ANY_ADDR , flood.ip_src ); //ip local

	mac_str_addr ( MAC_ANY_ADDR, flood.mac_dst );
	memcpy( flood.ip_dst, ip_dst, sizeof(ip_dst) );

	return flood;
}

int arp_resolve(eth_iface_t * iface, ipv4_addr_t ip_addr, mac_addr_t mac_addr) {

	
 	return 0;
}
