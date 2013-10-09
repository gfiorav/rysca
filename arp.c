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


//devuelve 1 si todo ha ido bien, -1 si no ha recibido nada

int arp_resolve (eth_iface_t * iface, ipv4_addr_t ip_addr, mac_addr_t mac_addr) {


  /* VARIABLES */
    /* FLOOD REQUEST */
    arp_request_ptr->l2_type = htons (LVL2_TYPE);
    arp_request_ptr->l3_type = htons (LVL3_TYPE);
    arp_request_ptr->ip_addr_len = IPv4_ADDR_SIZE;
    arp_request_ptr->mac_addr_len = MAC_ADDR_SIZE;
    arp_request_ptr->op_code = htons (OP_CODE_ARP_REQ);
    ipv4_str_addr (IP_ANY_ADDR, arp_request_ptr->ip_src); //IP LOCAL
    eth_getaddr (iface, arp_request_ptr->mac_src); //MAC LOCAL
    mac_str_addr (MAC_ANY_ADDR, arp_request_ptr->mac_dst);
    memcpy (arp_request_ptr->ip_dst, ip_addr, sizeof(ip_addr));

    /* resto de variables */
    arp_reply_ptr = (arp_msg_ptr) malloc (ETH_MTU); //buffer de datos
    int bytes_sent = 0;
    int bytes_recv = 0;
    int result = 1; //suponemos exito
    char * ip_str_sent = (char *) malloc(IPv4_STR_SIZE);
    ipv4_addr_str ( ip_addr , ip_str_sent ); //ip a mandar

    printf("Vamos a buscar %s\n", ip_str_sent);

    char * ip_str_recv = (char *) malloc(IPv4_STR_SIZE); //ip a recibir
    char * mac_str_recv = (char *) malloc(MAC_STR_SIZE); //cadena de la mac recibida

    printf("Vamos a buscar %s\n", ip_str_sent);
    
    bytes_sent = eth_send (iface, 
      MAC_BCAST_ADDR,
      ETH_ARP_TYPE,
      (unsigned char *) arp_request_ptr,
      sizeof (arp_request));

    if( bytes_sent < 0 ) {

      printf ("Ha ocurrido un error durante el envio \n");
      return -1;
      
    } else if ( bytes_sent == 0 ) {

      printf ("No se ha enviado nada \n");
      return -1;

    }

      /* Temporizador y guardian de intentos */

      int not_received = 1 ;          //bandera de si se ha recibido
      int n = 0;                      //numero de intentos
      timerms_t timer;                //cronometro 
      long int timeout = 2000;        //2 segundos
      timerms_reset(&timer, timeout); //empezamos el contador

      while ( not_received && timerms_left(&timer) && n < 2) {
        //mientras no se haya recibido una MAC con la ip deseada
        //mientras quede tiempo 
        //3 intentos

        bytes_recv = eth_recv (iface,
          mac_addr, 
          ETH_ARP_TYPE,
          (unsigned char*) arp_reply_ptr,
          timeout );

        //comparamos los resultados recibidos con los deseados

        ipv4_addr_str ( arp_reply_ptr->ip_src, ip_str_recv );
        mac_addr_str ( arp_reply_ptr->mac_src, mac_str_recv );

        printf(" Queremos %s, Hemos recibido %s con mac %s\n", 
          ip_str_sent, ip_str_recv, mac_str_recv );

        if ( !strcmp(ip_str_sent, ip_str_recv) ) {
            //si son iguales
          memcpy (mac_addr, arp_reply_ptr->mac_src, sizeof(arp_reply_ptr->mac_src));
          not_received = 0;
          result = 1;
        }

        if( bytes_recv < 0 && not_received ) {

          printf ("Ha ocurrido un error durante la recepcion. \n");
          result = -1;

        } else if ( bytes_recv == 0 && not_received ) {

          printf ("No se ha recibido nada. \n");

        } else if ( bytes_recv > 0  && not_received ) {
              //si se han recibido bytes pero la direccion ip no coincide con 
              //la deseada
          printf (" ... " );
              //se imprime para saber q se ha recibido una mac de forma incorrecta
        }

        timerms_reset(&timer, timeout); 
          if( n == 0 ) printf(" \n Reintentando... \n"); //solo se intenta 2 veces
          n++;
        }

        free(ip_str_sent);
        free(ip_str_recv);
        free(mac_str_recv);
        free (arp_reply_ptr);
        return result;
      }


