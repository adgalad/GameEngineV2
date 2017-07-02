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
    cout << "Client: Connecting to " << inet_str() << endl;
    long n;
    int i = 0;
    do {
      new_socket(PF_INET);
      n = Socket::Connect();
      ++i;
      if (i % 10 == 9){
        error("Client: Could not connect to " + inet_str() + ".");
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
    Send(fd(), (void*)&_signal.type, sizeof(SignalType));
    
    size_t n = Recive(fd(), (void*)&_id, sizeof(int));
    if (n == 0){
      printf("Client: Server went offline\n");
      return;
    }
    
    printf("Se recibio el entero: %d\n", _id);
    
    string s = Recive(fd());
    
    Scene *scene = new Scene();
    deserialize(s, *scene);
    Application.currentScene = shared_ptr<Scene> (scene);
    thread t (&Client::Update, this);
//
    Application.Run();
  }
  
  
  void Update(){
    while (true){
      _signal.type = UPDATE;
      Send(fd(), &_signal, sizeof(Signal));
      
      
      string s = Recive(fd());
      Scene *scene = new Scene();
      deserialize(s, *scene);
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
