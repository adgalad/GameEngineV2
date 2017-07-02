//
//  Sockets.cpp
//
//  Created by Carlos Spaggiari Roa on 2/2/17.
//  Copyright © 2017 ARSC. All rights reserved.
//

#include "Sockets.hpp"


/* int socket (int espacio, int estilo, int protocolo)
 
 Espacio:
 • PF_FILE: familia de protocolos del espacio de nombres de ficheros. (Not defined macOS)
 • PF_UNIX: es un sinónimo de PF_FILE definido por compatibilidad con versiones
 antiguas de la librería de sockets.
 • PF_INET: familia de protocolos Internet.
 
 Estilo:
 • SOCK_STREAM: representa el estilo de comunicación secuencia de bytes.
 • SOCK_DGRAM:representa el estilo de comunicación datagrama.
 • SOCK_RAW: representa un estilo con acceso directo al nivel de red que
 permite enviar datagramas arbitrarios (una aplicación que utilice
 este estilo puede definir, por ejemplo, su formato de cabeceras
 de los paquetes).
 • SOCK_SEQPACKET(datagramas transferidos demanera fiable)
 ,SOCK_RDM (reliably delivered message, también basado en datagramas)
 ,etc., represen- tan estilos de comunicación que tampoco estudiaremos aquí.
 
 Protocolo:
 Para TCP y UDP, es cero.
 
 */

int create_TCP_socket(int space){
  int fd = socket(space, SOCK_STREAM, 0);
  if ( fd == -1) {
    fprintf(stderr,"Could not create Socket\nerrno: %s\n",strerror(errno));
    exit(EXIT_FAILURE);
  }
  
  return fd;
}

/* int socketpair(int espacio, int estilo, int protocolo, int vs[2]);
 
 Espacio, estilo y protocolo son analogos.
 Los campos fd y vs[1] contienen los fd de dos socket ya conectados.
 
 Debido a que se hacen amobs socket en la misma llamada, estos perteneceran
 al mismo proceso (o derivados), por lo que solo son utiles para comunicacion
 entre procesos padres e hijos.
 
 */

int create_UDP_socket(int space){
  int fd = socket(space, SOCK_DGRAM, 0);
  if ( fd == -1) {
    fprintf(stderr,"Could not create Socket\nerrno: %s\n",strerror(errno));
    exit(EXIT_FAILURE);
  }
  return fd;
}




int pairsocket_TCP(int space, int vs[2]){
  int output = socketpair(space, SOCK_STREAM, 0, vs);
  if (output == -1) {
    fprintf(stderr,"Could not create Socket\nerrno: %s\n",strerror(errno));
    exit(EXIT_FAILURE);
  }
  return output;
}

int pairsocket_UDP(int space, int vs[2]){
  int output = socketpair(space, SOCK_DGRAM, 0, vs);
  if (output == -1) {
    fprintf(stderr,"Could not create Socket\nerrno: %s\n",strerror(errno));
    exit(EXIT_FAILURE);
  }
  return output;
}

void fill_sockaddr_in ( struct sockaddr_in *adr
                       , in_addr_t adr_host
                       , in_port_t n_port)
{
  adr->sin_family      = AF_INET;
  adr->sin_addr.s_addr = (in_addr_t)adr_host;
  adr->sin_port        = n_port;
}



int Socket::bind_internet_addr ()
{
  int output = bind(_fd, (struct sockaddr *)&_addr, sizeof _addr);
  if (output == -1) {
    fprintf(stderr,"Could not bind address to socket no. %d\nerrno: %s\n", _fd, strerror(errno));
    exit(EXIT_FAILURE);
  }
  return output;
}


int Socket::Send(uint32_t fd, void *data, size_t n)
{
  int ret;
  while ((ret = (int)send(fd, data, n, 0)) < 0 && errno == EINTR){
    printf("Sending ...\n");
  };
  return ret;
}


string Socket::Recive(uint32_t fd) {
  long n = 0;
  char buffer[1025];
  string msg = "";
  buffer[1024] = 0;
  do {
    n = recv(fd, buffer, 1024, 0);
    if (n <= 0) break;
    string newMsgPart (buffer, n);
    msg += newMsgPart;
  } while (n == 1024);
  return msg;
}


int Socket::Recive(uint32_t fd, void* buffer, size_t size){
  int readed = 0, pos = 0;
  
  while (pos < size)
  {
    readed = (int)recv(fd, (char*)buffer + pos, size - pos, 0);
    if (readed  < 0) {
      fprintf(stderr, "Warning: Comunication was terminate.\n");
      return - 1;
    }
    if (readed == 0) break;
    pos += readed;
  }
  return readed;
  
}

int Socket::Connect(){
  return connect(_fd, (const struct sockaddr*)&_addr, sizeof(struct sockaddr));
}






//void sendFD(int socket, int fd)  // send fd by socket
//{
//  struct msghdr msg = { 0 };
//  char buf[CMSG_SPACE(sizeof(fd))];
//  memset(buf, '\0', sizeof(buf));
//  struct iovec io = { .iov_base = (void*)"ABC", .iov_len = 3 };
//  
//  msg.msg_iov = &io;
//  msg.msg_iovlen = 1;
//  msg.msg_control = buf;
//  msg.msg_controllen = sizeof(buf);
//  
//  struct cmsghdr * cmsg = CMSG_FIRSTHDR(&msg);
//  cmsg->cmsg_level = SOL_SOCKET;
//  cmsg->cmsg_type = SCM_RIGHTS;
//  cmsg->cmsg_len = CMSG_LEN(sizeof(fd));
//  
//  *((int *) CMSG_DATA(cmsg)) = fd;
//  
//  msg.msg_controllen = cmsg->cmsg_len;
//  
//  if (sendmsg(socket, &msg, 0) < 0)
//    perror("Failed to send message");
//}
//
//int recvFD(int socket)  // receive fd from socket
//{
//  struct msghdr msg = {0};
//  
//  char m_buffer[256];
//  struct iovec io = { .iov_base = m_buffer, .iov_len = sizeof(m_buffer) };
//  msg.msg_iov = &io;
//  msg.msg_iovlen = 1;
//  
//  char c_buffer[256];
//  msg.msg_control = c_buffer;
//  msg.msg_controllen = sizeof(c_buffer);
//  
//  if (recvmsg(socket, &msg, 0) < 0)
//    perror("Failed to receive message\n");
//  
//  struct cmsghdr * cmsg = CMSG_FIRSTHDR(&msg);
//  
//  unsigned char * data = CMSG_DATA(cmsg);
//  
//  int fd = *((int*) data);
//  
//  return fd;
//}


//int Socket::bind_file_addr(const char *name)
//{
//  struct sockaddr_un addr;
//  memset(&addr, 0, sizeof(struct sockaddr_un));
//  addr.sun_family = AF_UNIX;
//  strcpy(addr.sun_path, name);
//
//  socklen_t size = (socklen_t)(sizeof addr.sun_family + strlen(name) + 1);
//  int output = bind(_fd, (struct sockaddr *)&addr, size);
//
//
//  if (output == -1) {
//    fprintf(stderr,"Could not bind address to socket no. %d\nerrno: %s\n", _fd, strerror(errno));
//    exit(EXIT_FAILURE);
//  }
//
//  return output;
//}
