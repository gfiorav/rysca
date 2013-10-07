#include "arp.h"


//We define the structure containing the ARP fields
  struct arp_message{
  
	  uint16_t l2_type; 	/* Tipo de protocolo de nv2*/
	  uint16_t l3_type; 	/* Tipo de protocolo de red*/

	  uint8_t mac_addr_len;	/* Longitud mac adress en bits*/
	  uint8_t ip_addr_len; 	/* Longitud ip address en bits*/

	  uint16_t op_code;	/* Codigo opcional */ 
	  
	  mac_addr_t mac_src;	/* Dirección MAC origen */
	  ipv4_addr_t ip_src;	/* Dirección IP origen*/
	  
	  mac_addr_t mac_dst;	/* Dirección MAC destino*/
	  ipv4_addr_t ip_dst;	/* Dirección IP destino*/
	  
  };
  
  typedef struct arp_message arp_msg;
  typedef struct arp_message * arp_msg_ptr;
  
  arp_msg arp_request;
  arp_msg_ptr arp_request_ptr = &arp_request;
  
  arp_msg arp_reply;
  arp_msg_ptr arp_reply_ptr = &arp_reply;
  

//We construct the arp request message
 void arp_request_construct (eth_iface_t * iface, ipv4_addr_t ip_addr){
  
    arp_request_ptr->l2_type = htons (LVL2_TYPE);
    arp_request_ptr->l3_type = htons (LVL3_TYPE);
    arp_request_ptr->ip_addr_len = IPv4_ADDR_SIZE;
    arp_request_ptr->mac_addr_len = MAC_ADDR_SIZE;
    arp_request_ptr->op_code = htons (OP_CODE_ARP_REQ);
    ipv4_str_addr (IP_ANY_ADDR, arp_request_ptr->ip_src); //IP LOCAL
    eth_getaddr (iface, arp_request_ptr->mac_src); //MAC LOCAL
    mac_str_addr (MAC_ANY_ADDR, arp_request_ptr->mac_dst);
    memcpy (arp_request_ptr->ip_dst, ip_addr, sizeof(ip_addr));
   
}

int arp_resolve (eth_iface_t * iface, ipv4_addr_t ip_addr, mac_addr_t mac_addr) {

      arp_request_construct (iface, ip_addr);
  
      int eth_send_flag;
    
      eth_send_flag = eth_send (iface, MAC_BCAST_ADDR, ETH_ARP_TYPE,(unsigned char *) arp_request_ptr, sizeof (arp_request));

      int eth_recv_flag;
     
      arp_reply_ptr = (arp_msg_ptr) malloc (ETH_MTU);
      
      eth_recv_flag = eth_recv (iface, mac_addr, ETH_ARP_TYPE, (unsigned char*) arp_reply_ptr, (long int) 2000);
      
      printf ("-------------------------------------------------------------\n");
      
      //ERROR CHECKING
      if (eth_recv_flag == -1) printf ("> RECIEVE ERROR!!!! ALERT!!!!\n");
      else printf ("> BYTES RECEIVED: %d\n", eth_recv_flag);
      
      printf ("-------------------------------------------------------------\n");
      
      int no_response_flag;
      
      if (eth_recv_flag == 0) no_response_flag = 1; 
  
      memcpy (mac_addr, arp_reply_ptr->mac_src, sizeof(arp_reply_ptr->mac_src));
      
      free (arp_reply_ptr);
      
      return no_response_flag;
}


