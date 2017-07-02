//
//  Sockets.hpp
//
//  Created by Carlos Spaggiari Roa on 2/2/17.
//  Copyright © 2017 ARSC. All rights reserved.
//

#ifndef sockets_h
#define sockets_h

#include <errno.h>
#include <unistd.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/socket.h>
#include <netinet/in.h> // struct sockaddr_in
#include <sys/un.h>     // struct sockaddr_un
#include <arpa/inet.h>


#include <sys/types.h>
#include <sys/time.h>

#include <signal.h>
#include <string>


#define MAX_BUFFER_SIZE 4096

/*
 struct	sockaddr_un {
 unsigned char sun_len;       // Permite saber el tamaño y por ende, que tipo de direccion es
 sa_family_t   sun_family;	  // siempre es AF_UNIX (AF_FILE)
 char		       sun_path[104]; // String con el path
 };
 
 
 struct sockaddr_in {
 __uint8_t	     sin_len;    // Permite saber el tamaño y que tipo de direccion es
 sa_family_t	   sin_family; // siempre es AF_INET
 in_port_t	     sin_port;   // numero de puerto
 struct	 in_addr sin_addr;   // direccion de Internet
 char		         sin_zero[8];
 };
 
 
 De la maquina a la Red
 • unsigned short int htons (unsigned short int n2_intern);
 • unsigned long  int htonl (unsigned long  int n4_intern);
 
 De la Red a la Maquina
 • unsigned short int ntohs (unsigned short int n2_red);
 • unsigned long  int ntohl (unsigned long  int n4_red);
 
 */


/* Constantes:
 
 Para el IP:
 • INADDR_LOOPBACK
 • INADDR_BROADCAST
 • INADDR_ANY
 
 Para los numero de puerto:
 • IPPORT_RESERVED: 1024
 • IPPORT_USERRESERVED: generalmente 5000
 -- los puertos asignados automaticamente estan
 -- entre IPPORT_RESERVED y (IPPORT_USERRESERVED - 1)
 
 */

using namespace std;


typedef enum  {
  ACCEPTED   = 0,
  RECEIVED   = 1,
  SENDING    = 2,
  REFUSED    = 3,
  DISCONNECT = 4,
  CONNECT    = 5,
  RECONNECT  = 6,
  EXIT       = 7,
  UPDATE     = 8
} SignalType;

struct Signal {
  SignalType type;
  /* ... */
};


typedef struct {
  int  acpacket;
  int  npacket;
  int  bufferSize;
  char buffer[MAX_BUFFER_SIZE];
} GameInfo;


/* Sirve para llenar una direccionde Internet */
void fill_sockaddr_in ( struct sockaddr_in *adr
                       , in_addr_t adr_host
                       , in_port_t n_port);



int create_TCP_socket(int space);

int create_UDP_socket(int space);

int pairsocket_TCP(int space, int vs[2]);

int pairsocket_UDP(int space, int vs[2]);


class Socket {
private:
  
  struct sockaddr_in _addr;
  uint32_t _fd;
  string   _inet;
  
public:
  
  Socket(const char* ip, in_port_t port){
    _fd = create_TCP_socket(PF_INET);
    fill_sockaddr_in(&_addr, inet_addr(ip), port);
    printf(">> %s\n", inet_ntoa(_addr.sin_addr));
    _inet = string(ip) + ":" + to_string(port);
  }

  ~Socket() {
    close(_fd);
  }
  
  inline string inet_str(){
    return _inet;
  }
  
  inline uint32_t ip() {
    return _addr.sin_addr.s_addr;
  }
  
  inline uint32_t port(){
    return _addr.sin_port;
  }
  
  inline uint32_t fd(){
    return _fd;
  }
  

  void new_socket(int space){
    int _fd = socket(space, SOCK_STREAM, 0);
    if (_fd == -1) {
      fprintf(stderr,"Could not create Socket\nerrno: %s\n",strerror(errno));
      exit(EXIT_FAILURE);
    }
  }
  
  /* Asignarle al fd de un socket una direccion, path para files, ip y puerto 
     para internet. En los clientes, no hace falta realizar bind, ya que el 
     OS se encarga de asignarle un puerto. En caso de que se quiera que el cliente
     use un puerto predeterminado (ej. problemas con firewalls) se usa bind.
   */
  
//  int bind_file_addr(const char *name);
  int bind_internet_addr ();
  
  
  /* Enviar
   Se puede usar las funciones:
   write  (<unistd.h>)
   send   (<sys/socket.h>, cuando es con conexion o tenga destino por defecto)
   sentto (<sys/socket.h>, se puede especificar el destino, aunque si hay conexion trabaja igual que send)
   
   Estas funciones colocan en errno distintos errores que pueden ocurrir
   durante el envio de los datos y se envian señales en caso de error.
   En caso de no tener señales ignoradas, se tiene (errno == EINTR).
   
   • EINTR: no se ha completado la operación porque ha llegado una señal no ignorada.
   
   Mientras (errno == EINTR) se puede seguir enviando los datos
   */
  
  int Send(uint32_t fd, void *data, size_t n);
  
  /* Recibir
   read     (<unistd.h>)
   recv     (<sys/socket.h>, cuando es con conexion o tenga destino por defecto)
   recvfrom (<sys/socket.h>, se obtiene de donde viene, aunque si hay conexion trabaja igual que recv)
   
   */
  
  string Recive(uint32_t fd);
  
  int Recive(uint32_t fd, void* data, size_t size);

  int Connect();
  
  
};


/*
void sendFD(int socket, int fd); // send fd through a socket to another process

int recvFD(int socket);  // receive fd from another process
*/

#endif /* sockets_h */
