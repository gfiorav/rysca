#include <rawnet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include "eth.h"
#include "ipv4.h"
#include <timerms.h>
#include <string.h>

#define MAC_ANY_ADDR "0:0:0:0:0:0"
#define IP_ANY_ADDR "0.0.0.0"
#define ETH_ARP_TYPE 0x0806
#define IPv4_STR_SIZE 24
#define MAC_STR_SIZE  32

#define LVL2_TYPE 1  	  	//para arp mac
#define LVL3_TYPE 0x0800 	//para arp ip
#define OP_CODE_ARP_REQ 1 
#define OP_CODE_ARP_RPLY 2

int arp_resolve (eth_iface_t * iface, ipv4_addr_t dest, mac_addr_t mac);
