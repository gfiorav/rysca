#ifndef _ARP_H
#define _ARP_H

#define MAC_BROADCAST_ADDR "FF:FF:FF:FF:FF:FF"
#define IP_ANY_ADRESS "0.0.0.0"
#define ETH_ARP_TYPE 0x0806

#include <rawnet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include "ipv4.h"
#include "eth.h"

typedef struct arp_message {

	uint16_t l2_type; 	/* Tipo de protocolo de nv2*/
	uint16_t l3_type; 	/* Tipo de protocolo de red*/

	uint8_t mac_addr_len;	/* Longitud mac adress en bits*/
	uint8_t ip_addr_len; 	/* Longitud ip address en bits*/

	uint16_t op_code;	/* Codigo opcional */ 
  	
  	mac_addr_t mac_src;	/* Dirección MAC origen */
  	ipv4_addr_t ip_src;	/* Dirección IP destino*/
  	
	mac_addr_t mac_dst;	/* Dirección MAC destino*/
  	ipv4_addr_t ip_dst;	/* Dirección IP destino*/
  } arp_msg;

/* recibe iface abierta con eth_open y ip dst y devuelve estructura para flood*/
arp_msg init_flood_req(eth_iface_t * iface, ipv4_addr_t ip_dst);

/* devuelve arp msg default*/
arp_msg default_arp_msg();

#endif
