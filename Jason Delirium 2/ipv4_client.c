#include "ipv4_client.h"
#define USER_INPUT 200
#define DEFAULT_PAYLOAD_LENGTH 1500

ipv4_route_table_t * ipv4_route_table_aux;
ipv4_route_t * ipv4_route_aux;

void empty_buffer (char * buffer, int size){
  
  int l;
  
  for (l=0; l<size; l++){
    buffer [l] = 0;
  }
  
  
}



int main (int argc, char * argv[]){

printf ("\n--------------X ROUTING CONFIG--------------\n\n");

printf ("COMMAND LIST: command_list\n");
printf ("MANUAL: man <command>\n");
printf ("EXIT: exit\n");
printf ("\n");

char user_input [USER_INPUT], *result;;

char user_command [40]; 
char arg1 [30];
char arg2 [30];
char arg3 [30];
char arg4 [30];
char arg5 [30];

char aux_buffer[200];

int p = 0;

while (p == 0){

printf ("> ");

result = fgets (user_input, USER_INPUT, stdin);

int j;

for (j=0; j<200; j++){
  
  if (user_input [j] == ' '){ aux_buffer[j] = '|'; ++j;}
  else{ if(user_input [j] == '\n'){aux_buffer[j] ='\0'; break;}}
  
  aux_buffer[j] = user_input [j];
   
}

int i;
int stream_index;
int end_of_stream = 0;
int arg_num = 0;


for (i=0; i<40; i++){

  if (aux_buffer[i] == '|' || aux_buffer[i] == '\0'){
    if (aux_buffer[i] == '|'){ stream_index = i+1; arg_num++; user_command [i] = '\0';} 
    else {aux_buffer[i] = '\0'; end_of_stream = 1; arg_num++; user_command [i] = '\0';}
    break;
  }
  
  user_command [i] = aux_buffer[i];
  
}

int command_number = 0;

if (strcmp (user_command, "") == 0) command_number = 69;

/*if (command_number != 69){
printf ("\n> USER COMMAND: >%s<\n", user_command);}*/

if (strcmp (user_command, "route_create") == 0) command_number = 1;
if (strcmp (user_command, "route_print") == 0) command_number = 3;
if (strcmp (user_command, "route_table_remove") == 0) command_number = 4;
if (strcmp (user_command, "route_table_find") == 0) command_number = 5;
if (strcmp (user_command, "route_table_lookup") == 0) command_number = 6;
if (strcmp (user_command, "route_table_read") == 0) command_number = 7;
if (strcmp (user_command, "route_table_write") == 0) command_number = 8;
if (strcmp (user_command, "route_table_print") == 0) command_number = 9;
if (strcmp (user_command, "man") == 0) command_number = 10;
if (strcmp (user_command, "command_list") == 0) command_number = 11;
if (strcmp (user_command, "exit") == 0) command_number = 12;
if (strcmp (user_command, "clear") == 0) command_number = 13;
if (strcmp (user_command, "send_segment") == 0) command_number = 14;

if (command_number != 69)//{
if (command_number == 0) printf ("> COMMAND NOT FOUND\n");
//else printf ("> COMMAND NUMBER: >%d<\n\n", command_number);}

int end_loop = 0;
int k = 0;

if (end_of_stream == 0){

  arg_num = 2;
  
  for (i=stream_index; i<170; i++){
    
    switch (arg_num){
      
      case 2: 
	arg1 [k] = aux_buffer[i];
	++k;
	if (aux_buffer[i+1] == '|'){++arg_num; ++i; arg1 [k] ='\0'; k=0;}
	else{if (aux_buffer[i+1] == '\0'){end_loop = 1; arg1 [k] ='\0';}}
	break;
      case 3: 
	arg2 [k] = aux_buffer[i];
	++k;
	if (aux_buffer[i+1] == '|'){++arg_num; ++i; arg2 [k] ='\0'; k=0;}
	else{if (aux_buffer[i+1] == '\0'){end_loop = 1; arg2 [k] ='\0';}}
	break;
      case 4: 
	arg3 [k] = aux_buffer[i];
	++k;
	if (aux_buffer[i+1] == '|'){++arg_num; ++i; arg3 [k] ='\0'; k=0;}
	else{if (aux_buffer[i+1] == '\0'){end_loop = 1; arg3 [k] ='\0';}}
	break;
      case 5: 
	arg4 [k] = aux_buffer[i];
	++k;
	if (aux_buffer[i+1] == '|'){++arg_num; ++i; arg4 [k] ='\0'; k=0;}
	else{if (aux_buffer[i+1] == '\0'){end_loop = 1; arg4 [k] ='\0';}}
	break;
      case 6: 
	arg5 [k] = aux_buffer[i];
	++k;
	if (aux_buffer[i+1] == '|'){++arg_num; ++i; arg5 [k] ='\0'; k=0;}
	else{if (aux_buffer[i+1] == '\0'){end_loop = 1; arg5 [k] ='\0';}}
	break;
      
    }
    
    if (end_loop == 1) break;
    
  }
  
}


int arg_num_required;
int exit_flag = 0;

ipv4_addr_t ip_addr;
ipv4_addr_t ip_mask;
ipv4_addr_t ip_gw;

int index;
unsigned int adist;

if (ipv4_route_table_aux == NULL) ipv4_route_table_aux = ipv4_route_table_create ();

switch (command_number){
  
      case 1:
      
      arg_num_required = 6;
      if (arg_num != arg_num_required){ printf ("> usage: route_create <ip_addr> <ip_mask> <iface> <gw> <adist>\n"); break;}
  
      ipv4_str_addr (arg1, ip_addr);
      ipv4_str_addr (arg2, ip_mask);
      ipv4_str_addr (arg4, ip_gw);
      
      adist = (unsigned int) atoi (arg5);
      
      ipv4_route_t * ipv4_route_new;
      
      ipv4_route_new = ipv4_route_create (ip_addr, ip_mask, arg3, ip_gw, adist);
      
      ipv4_route_table_add (ipv4_route_table_aux, ipv4_route_new);
      
      break;
      
      case 2:
      
      break;
      
      case 3:
	
	arg_num_required = 3;
	if (arg_num != arg_num_required){ printf ("> usage: route_print <ip_addr> <ip_mask>\n"); break;}
	ipv4_str_addr (arg1, ip_addr);
        ipv4_str_addr (arg2, ip_mask);
	index = ipv4_route_table_find (ipv4_route_table_aux, ip_addr, ip_mask);
	ipv4_route_aux = ipv4_route_table_get (ipv4_route_table_aux, index);
	ipv4_route_print (ipv4_route_aux);
	printf ("\n\n");     
      
      break;
        
      case 4:
        arg_num_required = 3;
	if (arg_num != arg_num_required){ printf ("> usage: route_table_remove <ip_addr> <ip_mask>\n"); break;}
	index = ipv4_route_table_find (ipv4_route_table_aux, ip_addr, ip_mask);
	ipv4_route_aux = ipv4_route_table_remove (ipv4_route_table_aux, index);
	ipv4_route_free (ipv4_route_aux);
      break;
      
      case 5:
        arg_num_required = 3;
	if (arg_num != arg_num_required){ printf ("> usage: route_table_find <ip_addr> <ip_mask>\n"); break;}
	ipv4_str_addr (arg1, ip_addr);
        ipv4_str_addr (arg2, ip_mask);
	index = ipv4_route_table_find (ipv4_route_table_aux, ip_addr, ip_mask);
	printf ("INDEX FOR SUBNET %s WITH MASK %s: %d\n\n", arg1, arg2, index);
      break;
     
      case 6:
      
      ipv4_route_aux = NULL;
      arg_num_required = 2;
      if (arg_num != arg_num_required){ printf ("> usage: route_table_lookup <ip_addr>\n"); break;}
      ipv4_str_addr (arg1, ip_addr);
      ipv4_route_aux = ipv4_route_table_lookup (ipv4_route_table_aux, ip_addr);
      if (ipv4_route_aux != NULL){
      ipv4_route_print (ipv4_route_aux); printf ("\n");}
      else printf ("No route available\n");
  
      break;
      
      case 7:
	
	arg_num_required = 2;
	if (arg_num != arg_num_required){ printf ("> usage: route_table_read <filename>\n"); break;}
	ipv4_route_table_read (arg1, ipv4_route_table_aux);

	
      break;    
      
      
      case 8:
	
	arg_num_required = 2;
	if (arg_num != arg_num_required){ printf ("> usage: route_table_write <filename>\n"); break;}
	ipv4_route_table_write (ipv4_route_table_aux, arg1);
	
	
      break;
      
      case 9:
      
	arg_num_required = 1;
	if (arg_num != arg_num_required){ printf ("> usage: route_table_print\n"); break;}
	printf ("\n");
	ipv4_route_table_print (ipv4_route_table_aux);
	printf ("\n");
	
      break;
      
      case 10:
	
	arg_num_required = 2;
	if (arg_num != arg_num_required){ printf ("> usage: man <command>\n"); break;}
	
	int man_number;
	
	if (strcmp (arg1, "route_create") == 0) man_number = 1;
	if (strcmp (arg1, "route_print") == 0) man_number = 3;
	if (strcmp (arg1, "route_table_remove") == 0) man_number = 4;
	if (strcmp (arg1, "route_table_find") == 0) man_number = 5;
	if (strcmp (arg1, "route_table_lookup") == 0) man_number = 6;
	if (strcmp (arg1, "route_table_read") == 0) man_number = 7;
	if (strcmp (arg1, "route_table_write") == 0) man_number = 8;
	if (strcmp (arg1, "route_table_print") == 0) man_number = 9;
	if (strcmp (arg1, "send_segment") == 0) man_number = 14;
	if (strcmp (arg1, "man") == 0) man_number = 10;
	if (strcmp (arg1, "command_list") == 0) man_number = 11;
	if (strcmp (arg1, "exit") == 0) man_number = 12;
	if (strcmp (arg1, "clear") == 0) man_number = 13;
	
	printf ("\n");
	
	switch (man_number){
	  
	  
	  case 1: printf ("route_create <ip_addr> <ip_mask> <iface> <gw> <adist>\n\n");
	  printf ("This command creates an IPv4 route\n\n");
	  printf ("<ip_addr>\t\tIPv4 subnet destination address\n");
	  printf ("<ip_mask>\t\tDestination subnet mask\n");
	  printf ("<iface>\t\t\tInterface name\n");
	  printf ("<gw>\t\t\tGateway\n");
	  printf ("<adist>\t\t\tAdministrative distance\n\n");
	  break;
	  
	  case 3: 
	  printf ("route_print <ip_addr> <ip_mask>\n\n");
	  printf ("This command prints the specified route\n\n");
	  printf ("<ip_addr>		IPv4 subnet destination address\n");
	  printf ("<ip_mask>		Destination subnet mask\n\n");
	  break;
	  
	  case 4: 
	  printf ("route_table_remove <ip_addr> <ip_mask>\n\n");
	  printf ("This command removes one of the routes from the routing table\n\n");
	  printf ("<ip_addr>		IPv4 subnet destination address\n");
	  printf ("<ip_mask>		Destination subnet mask\n\n");
	  break;
	  
	  case 5:
	  printf ("route_table_find <ip_addr> <ip_mask>\n\n");
	  printf ("This command prints the index assigned to the corresponding subnet IPv4 address\n\n");
	  printf ("<ip_addr>		IPv4 subnet destination address\n");
	  printf ("<ip_mask>		Destination subnet mask\n\n");
	  break;
	  
	  case 6: 
	  printf ("route_table_lookup <ip_addr>\n\n");
	  printf ("This command prints the best route to reach the specified destination subnet IPv4 address\n\n");
	  printf ("<ip_addr>		IPv4 subnet destination address\n\n");
	  break;
	  
	  case 7:  
	  printf ("route_table_read <filename>\n\n");
	  printf ("This command reads the specified file and adds the content to the actual table\n\n");
	  printf ("<filename>		Name of the file\n\n");
	  break;
	  
	  case 8: 
	  printf ("route_table_read <write>\n\n");
	  printf ("This command writes the contents of the actual table in a file\n\n");
	  printf ("<filename>		Name of the file\n\n");
	  break;
	  
	  case 9: 
	  printf ("route_table_print\n\n");
	  printf ("This command prints the contents of the actual table\n\n");
	  break;
	  
	  case 10: break;
	  case 11: break;
	  case 12: break;
	  
	  case 14: 
	  printf ("send_segment <ip_addr> <iface> <type> <length>\n\n"); 
	  printf ("<ip_addr>\t\tIPv4 subnet destination address\n");
	  printf ("<iface>\t\t\tInterface name\n");
	  printf ("<type>\t\t\tEthernet segment Type field\n");
	  printf ("<length>\t\t\tLength of data to send\n");
	  break;
	  
	  default: printf ("No manual entry for %s\n\n", arg1);
	  
	  
	  
	  
	  
	  
	}
	  
	  
      break;
      
      case 11:
      printf ("route_create\n");
      printf ("route_print\n");
      printf ("route_table_remove\n");
      printf ("route_table_find\n");
      printf ("route_table_lookup\n");
      printf ("route_table_read\n");
      printf ("route_table_write\n");
      printf ("route_table_print\n");
      printf ("send_segment\n");
      printf ("man\n");
      printf ("command_list\n");
      printf ("exit\n");
      printf ("clear\n");
      printf ("\n");
      
      break;
      
      case 12:
       exit_flag = 1;
      break;
      
      case 13:
      system ("clear");
      break;
      
      
      case 14:
      {
	
       arg_num_required = 5;
       if (arg_num != arg_num_required){ printf ("> usage: send_segment <ip_addr> <iface> <type> <length>\n"); break;}
      //Opens the interface enabling us to send and receive 
      eth_iface_t * iface1;
      
      iface1 = eth_open (arg2);
      //ipv4_addr_t is an unsigned char array to store ip address in a particular format
      ipv4_addr_t ip_addr1;
      ipv4_str_addr(arg1, ip_addr1);
      int arp_resolve_no_response_flag;
      mac_addr_t mac_addr; 
      arp_resolve_no_response_flag = arp_resolve (iface1, ip_addr1, mac_addr);
      char mac_recv [MAC_STR_LENGTH];
      mac_addr_str (mac_addr, mac_recv);
      char ip_recv [IPv4_STR_MAX_LENGTH ];
      ipv4_addr_str (ip_addr1, ip_recv);
      if (arp_resolve_no_response_flag == 1)  printf ("> %s -> NO RESPONSE\n",ip_recv);
      else  printf ("> %s -> %s\n",ip_recv, mac_recv);
      
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

  int payload_len = DEFAULT_PAYLOAD_LENGTH;
       /* Generar payload */
  unsigned char payload[payload_len];
  int i;
  for (i=0; i<payload_len; i++) {
    payload[i] = (unsigned char) i;
  }

  int len;
  mac_addr_t src_addr;
  unsigned char buffer[ETH_MTU];

  /* Enviar trama Ethernet al Servidor */
  print_pkt(payload, payload_len, 0);
  
  
  /* Recibir trama Ethernet del Servidor y procesar errores */
  long int timeout = 2000;
  len = eth_recv(iface1, mac_addr, 0, buffer, timeout);

  if (len > 0) {
    char src_addr_str[MAC_STR_LENGTH];
    mac_addr_str(src_addr, src_addr_str);    

    printf("Recibidos %d bytes del Servidor Ethernet (%s)\n", 
           len, src_addr_str);
    print_pkt(buffer, len, 0);
  }

  
  ////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////
  
      eth_close (iface1);
      
      break;
      }

}

empty_buffer (arg1, sizeof (arg1));
empty_buffer (arg2, sizeof (arg2));
empty_buffer (arg3, sizeof (arg3));
empty_buffer (arg4, sizeof (arg4));
empty_buffer (arg5, sizeof (arg5));
empty_buffer (user_command, sizeof (user_command));
empty_buffer (user_input, sizeof (user_input));
empty_buffer (aux_buffer, sizeof (aux_buffer));

if (exit_flag == 1) break;

}

ipv4_route_table_free (ipv4_route_table_aux);

return 1;

}
