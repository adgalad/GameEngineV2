//
//  Server.cpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 6/29/17.
//  Copyright © 2017 ARSC. All rights reserved.
//

#include "Server.hpp"


Server::Server() : Server(100, "127.0.0.1", 8080){
  
}
typedef pair<int, ClientHandler> p;
Server::~Server(){
  
  FD_ZERO(&_active_fds);
  FD_ZERO(&_ready_fds);
  
  auto i = clients.begin();
  
  foreach(i, clients){
    close(i->second->fd);
  }
}

Server::Server(uint32_t maxClients, const char* inet, uint32_t port):Socket(inet, port){
  _maxNumberOfClients = maxClients;
  bind_internet_addr();
  int yes = 1;
#ifdef __APPLE__
  if ( setsockopt(fd(), SOL_SOCKET, SO_REUSEPORT, &yes, sizeof(int)) == -1 )
#elif __linux__                          //  ^^--vv
    if ( setsockopt(fd(), SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1 )
#endif
    {
      perror("Server: Failed setting socket option `SO_REUSEPORT`");
    }
  
  FD_ZERO(&_active_fds);
  FD_SET(fd(), &_active_fds);
}

void Server::Start() {
  printf("Server: Listening ...\n");
  if (listen(fd(), 1) < 0) {
    perror ("No Listen: ");
    exit(1);
  }
  
  
  while (_run) {
    catchClient();
  }
}

void Server::Stop(){
  _run = false;
  uint32_t sock = create_TCP_socket(PF_INET);
  struct sockaddr_in addr;
  fill_sockaddr_in(&addr, ip(), port());
  
  if (connect( sock,
              (struct sockaddr*)&addr,
              sizeof(addr)) < 0)
  {
    printf("Server: Could not terminete or it's terminated already\n");
  } else {
    perror("Server: Terminating\n");
  }
  
}

void Server::catchClient(){
  _ready_fds = _active_fds;
  if (select(FD_SETSIZE, &this->_ready_fds, NULL, NULL,NULL) < 0) {
    printf("Debug: select() failed\n");
    return;
  }
  
  if (not _run) return;
  
  if (FD_ISSET(fd(), &_ready_fds)){
    
    printf("Server: Accepting ...\n");
    ClientHandler *client = new ClientHandler();
    socklen_t len = sizeof (struct sockaddr);
    int conn = accept(fd(), (struct sockaddr *)&client->addr, &len);
    
  
    if (conn < 0){
      return;
    }
    client->fd = (uint32_t) conn;
    
    FD_SET(client->fd, &_active_fds);
    
    
    if (FD_ISSET(client->fd, &_active_fds)){
      
      if (true /* num of thread < max num of thread */) {
        Debug::Log("Server: Connected with " + inet_str() + ".\n");
        int n = (int) Recive(client->fd, (void*)&_signal, sizeof(Signal));
        
        if (n < 0){
          printf("ERROR: Can not receive messages\n");
        }
        
        if (_signal.type == CONNECT){
          thread newThread (&Server::serveClient,this, client);
          newThread.detach();
          clients[conn] = client;
          
        }
        //          else if (_signal.type == RECONNECT){
        //            int ID = -1;
        //            for (int j = 0 ; j < FD_SETSIZE ; ++j){
        ////              if (child[j].pid == .CID) {
        ////                ID = j;
        ////                break;
        ////              }
        //              printf("Not 1\n");
        //            }
        //            if (ID == -1){
        //              thread newThread (&Server::serveClient, this, client_socket);
        //            } else {
        ////              sendFD(child[ID].unixSocket[0], i); // send the new FD
        //              printf("Not 2\n");
        //            }
        //          }
        //
      } else {
        Debug::Log("Server: Refusing " + inet_str());
        Debug::Log("Clearing FD " + to_string(client->fd));
        _signal.type = REFUSED;
        
        Send(client->fd, (void*)&_signal, sizeof(Signal));
        FD_CLR(client->fd, &_active_fds);
        
      }
    }
  }
}

void Server::serveClient (ClientHandler *client){
  
  Send(client->fd,&client->fd, sizeof(int));
  printf("Se envio un entero al cliente: %d\n", client->fd);
  
  do {
    ostringstream oss = serialize(*Application.currentScene);
    size_t size = oss.str().size() * sizeof(char);
    Send(client->fd, (char*)&oss.str()[0], size);
    printf("Se envio la Escena.\n");
    
    if (Recive(client->fd, &_signal, sizeof (Signal)) < 0) return;
    cout << "Se recibio la senal: " << _signal.type << endl;
    
    
  } while (_signal.type != EXIT);
}
