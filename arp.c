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
  /* Inicializamos flood request */
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
    /* Para el buffer de datos hay que esperar la longitud maxima */
  arp_reply_ptr = (arp_msg_ptr) malloc (ETH_MTU); //buffer de datos
  
  int bytes_sent = 0;
  int bytes_recv = 0;              
  int result = -1;                 //suponemos fracaso
  char ip_str_sent[IPv4_STR_SIZE]; //Ip que buscamos
  char ip_str_recv[IPv4_STR_SIZE]; //Ip que recibimos
  char mac_str_recv[MAC_STR_SIZE]; //cadena de la mac recibida

  //formateamos los campos de las cadenas
  //no es innecesario puesto que hay que comparar 
  //las ip, y al inicializar las cadenas, el compilador
  //las llena de basura
  memset( ip_str_sent, '\0', IPv4_STR_SIZE);
  memset( ip_str_recv, '\0', IPv4_STR_SIZE);
  memset( mac_str_recv, '\0', MAC_STR_SIZE);

  ipv4_addr_str ( ip_addr , ip_str_sent ); //ip que se busca 
  printf("Vamos a buscar %s\n", ip_str_sent); //en formato cadena

  /* Temporizador y guardian de intentos */

  int not_received = 1 ;          //bandera de si se ha recibido
  int n = 0;                      //numero de intentos
  timerms_t timer;                //cronometro 
  long int timeout = 2000;        //2 segundos
  timerms_reset(&timer, timeout); //empezamos el contador

  while ( not_received && timerms_left(&timer) && n < 2) {
        //mientras no se haya recibido una MAC con la ip deseada
        //mientras quede tiempo 
        //2 intentos

        /* ENVIO */

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

        /* RECEPCION */

    bytes_recv = eth_recv (iface,
      mac_addr, 
      ETH_ARP_TYPE,
      (unsigned char *) arp_reply_ptr,
      timeout );

    //comparamos los resultados recibidos con los deseados

    ipv4_addr_str ( arp_reply_ptr->ip_src, ip_str_recv );
    mac_addr_str ( arp_reply_ptr->mac_src, mac_str_recv );

    printf(" Queremos saber quien es %s, \n"
     " hemos recibido desde la ip %s con mac %s\n", 
     ip_str_sent, ip_str_recv, mac_str_recv );

    if ( !strcmp(ip_str_sent, ip_str_recv) && bytes_recv > 0) {
      //comprobamos si es la ip que buscamos

      memcpy (mac_addr, arp_reply_ptr->mac_src, sizeof(arp_reply_ptr->mac_src));
      result = 1;       //terminamos la ejecucion con exito
      not_received = 0; //terminamos la iteracion

    } else if( bytes_recv < 0 ) {

      printf ("Ha ocurrido un error durante la recepcion. \n");

    } else if ( bytes_recv == 0 ) {

      printf ("No se ha recibido nada. \n");

    }

    //si no se ha recibido reiniciamos el cronometro
    if(not_received) timerms_reset(&timer, timeout); 
    n++;
  }

  free (arp_reply_ptr);
  return result;
}


