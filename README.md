# SimpleHttpServer
* very simple http server
* default port: 8080
    * modify source [here](https://github.com/lmk/SimpleHttpServer/blob/master/src/HttpServer.cpp#L143)
* support: linux g++ 4.9.2

## How to use
* block server
```c++
HttpServer httpServer;

httpServer.Init(5, NULL);
httpServer.Run();
```

* non-block
```c++
NBHttpServer* httpServer = NBHttpServer::getInstance();
httpServer->Init(5);
httpServer->Start();
sleep(60);
httpServer->Stop();
```