#include <rawnet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include "eth.h"
#include "ipv4.h"
#include <unistd.h>
#include <libgen.h>

#define MAC_ANY_ADDR "0:0:0:0:0:0"
#define IP_ANY_ADDR "0.0.0.0"
#define ETH_ARP_TYPE 0x0806

#define LVL2_TYPE 1  	  	//para arp mac
#define LVL3_TYPE 0x0800 	//para arp ip
#define OP_CODE_ARP_REQ 1 
#define OP_CODE_ARP_RPLY 2

// void ipv4_addr_str (ipv4_addr_t, char str [])
// int ipv4_str_addr (char* str, ipv4_addr_t addr);

int arp_resolve (eth_iface_t * iface, ipv4_addr_t dest, mac_addr_t mac);
