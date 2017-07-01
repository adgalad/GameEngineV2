//
//  Server.hpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 6/29/17.
//  Copyright © 2017 ARSC. All rights reserved.
//

#ifndef Server_hpp
#define Server_hpp

#include "Sockets.hpp"
#include "Game.hpp"
#include <thread>
#include <map>


using namespace std;
  

class ClientHandler {
public:
  thread   t;
  uint32_t fd;
  struct sockaddr_in addr;
  
  ClientHandler(){}
};


class Server : public Socket {

  
  uint32_t _maxNumberOfClients;
  uint32_t _currentNumberOfClients = 0;
  bool     _run = true;

  socklen_t _len;
  fd_set _active_fds, _ready_fds;
  Signal _signal;
  int j = 0;
  map<int,ClientHandler*> clients;
  
public:
  
  Server();
  
  ~Server();
  
  Server(uint32_t maxClients, const char *inet, uint32_t port);
  
  void Start();
  
  void Stop();
  
  void catchClient();
  
  void serveClient (ClientHandler *client);
  

    
};

#endif /* Server_hpp */
