//
//  Client.hpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 6/29/17.
//  Copyright © 2017 ARSC. All rights reserved.
//

#ifndef Client_hpp
#define Client_hpp

#include "Game.hpp"
#include "Sockets.hpp"
#include <thread>

std::recursive_mutex update_mutex;

class Client : public Socket {
  
  uint32_t _id;
  Signal _signal;
  
public:
  
  Client() : Client("127.0.0.1", 8080){}
  
  
  Client(const char* inet, uint32_t port) : Socket(inet, port) {

  }
  
  
  /**  
    Start the client requesting a connection with the server and reciving the
    necessary parameters and the current scene
   **/
  
  void Connect() {
    errno = 0;
    cout << "Client: Connecting to " << _inet << endl;
    long n;
    int i = 0;
    do {
      _fd = create_TCP_socket(PF_INET);
      n = connect( _fd, (struct sockaddr*)&_addr, sizeof(_addr));
      ++i;
      if (i % 10 == 9){
        error("Client: Could not connect to " + _inet + ".");
        error("\terrno: " + string(strerror(errno)));
        error("\tAttempting to connect again (" + to_string(i/10+1) + "/10)...\n");
      }
      SDL_Delay(500);
    } while (n < 0 && i < 100);
    
    if (i == 100) {
      error("Client: Timeout.");
      exit(EXIT_FAILURE);
    }
  }
  
  void Start() {
    Connect();
    
    printf("Client: Connected\n");
  
    _signal.type = CONNECT;
    send_data(_fd, (void*)&_signal.type, sizeof(SignalType));
    
    size_t n = recv(_fd, (void*)&_id, sizeof(int), 0);
    if (n == 0){
      close(_fd);
      printf("Client: Server went offline\n");
      return;
    }
    
    printf("Se recibio el entero: %d\n", _id);
    
    string s = recvFromServer();
    istringstream iss (s, istringstream::binary);
    Scene *scene = new Scene();
    streamToScene(&iss, *scene);
    Application.currentScene = shared_ptr<Scene> (scene);
    thread t (&Client::Update, this);
//
    Application.Run();
  }
  
  string recvFromServer(){
    long n = 0;
    char buffer[1025];
    string msg;
    buffer[1024] = 0;
    do {
      n = recv(_fd, buffer, 1024, 0);
      if (n <= 0) break;
      string newMsgPart (buffer, n);
      msg += newMsgPart;
    } while (n == 1024);
    return msg;
  }
  
  
  
  void Update(){
    while (true){
      _signal.type = UPDATE;
      send_data(_fd, &_signal, sizeof(Signal));
      
      
      string s = recvFromServer();
      istringstream iss (s, istringstream::binary);
      Scene *scene = new Scene();
      streamToScene(&iss, *scene);
      update_mutex.lock();
      while (Application.currentScene.use_count() > 0){
        Application.currentScene.reset();
      }
      Application.currentScene = shared_ptr<Scene> (scene);
      Application.currentScene->Init();
      update_mutex.unlock();


    }
  }
  
  
};

#endif /* Client_hpp */
