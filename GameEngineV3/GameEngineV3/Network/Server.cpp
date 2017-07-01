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

Server::~Server(){
  
  FD_ZERO(&_active_fds);
  FD_ZERO(&_ready_fds);
}

Server::Server(uint32_t maxClients, const char* inet, uint32_t port):Socket(inet, port){
  _maxNumberOfClients = maxClients;
  _fd = create_TCP_socket(PF_INET);
  
  int yes = 1;
#ifdef __APPLE__
  if ( setsockopt(_fd, SOL_SOCKET, SO_REUSEPORT, &yes, sizeof(int)) == -1 )
#elif __linux__                          //  ^^--vv
    if ( setsockopt(_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1 )
#endif
    {
      perror("Server: Failed setting socket option `SO_REUSEPORT`");
    }
  bind_internet_addr(_fd, ip(), Server::port());
  
  FD_ZERO(&_active_fds);
  FD_SET(_fd, &_active_fds);
}

void Server::Start() {
  printf("Server: Listening ...\n");
  if (listen(_fd, 1) < 0) {
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
  
  if (FD_ISSET(_fd, &_ready_fds)){
    
    printf("Server: Accepting ...\n");
    ClientHandler *client = new ClientHandler();
    socklen_t len = sizeof _addr;
    int conn = accept(_fd, (struct sockaddr *)&client->addr, &len);
    
  
    if (conn < 0){
      return;
    }
    client->fd = (uint32_t) conn;
    
    FD_SET(client->fd, &_active_fds);
    
    
    if (FD_ISSET(client->fd, &_active_fds)){
      
      if (true /* num of thread < max num of thread */) {
        Debug::Log("Server: Connected with " + _inet + ".\n");
        int n = (int) recv(client->fd, (void*)&_signal, sizeof(Signal), 0);
        
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
        printf("Server (%d): Refusing `%s`\n",getpid(), inet_str());
        printf("Debug: Clearing FD %d\n", client->fd);
        _signal.type = REFUSED;
        
        send_data(client->fd, (void*)&_signal, sizeof(Signal));
        FD_CLR(client->fd, &_active_fds);
        
      }
    }
  }
}

void Server::serveClient (ClientHandler *client){
  
  send_data(client->fd,&client->fd, sizeof(int));
  printf("Se envio un entero al cliente: %d\n", client->fd);
  
  do {
    ostringstream oss = sceneToStream(*Application.currentScene);
    send_data(client->fd, (char*)&oss.str()[0], oss.str().size() * sizeof(char));
    printf("Se envio la Escena.\n");
    
    if (recv(client->fd, &_signal, sizeof (Signal), 0) < 0) return;
    cout << "Se recibio la senal: " << _signal.type << endl;
  } while (_signal.type == UPDATE);
  
  
}
