//
// Created by Chuilian Kong on 2/2/2018.
//

#include <sys/socket>
#include <stdlib>
#include <thread>
#include <exception>
#include <string>
#include <iostream>

#define BUFFER_SIZE 1024

/**
 * Simple Http server that supports some types of HTTP requests.
 */
class HttpServer{
public:
    /**
     * default ctor
     */
    HttpServer() : _port(80) {};
    /**
     * ctor
     */
    HttpServer(const int port) : _port(port) {};

    /**
     * copy ctor
     */
    HttpServer(HttpServer other) = delete;

    /**
     * assignment optr
     */
    operator=(HttpServer other) = delete;

    /**
     * dtor
     */
    ~HttpServer(){

    }


    /////////////////////////////////////////////////////////////

    /**
     * start the server in another thread, return the thread handle in which the server runs
     */
    void start(){

    }





private:
    int _port;
    int _socket_id;
    struct sockaddr_in _socket_addr;
    std::thread _server_thread;


    /**
     * initialize the socket and keep receiving connection requests
     */
    void task(){
        // create TCP socket: IPv4, TCP, 0
        _socket_id = socket(AF_INET, SOCKET_STREAM, 0);
        if(_socket_id == 0) throw std::runtime_error("socket creation failed");
        _socket_addr.sin_family = AF_INET;
        _socket_addr.s_addr = INADDR_ANY;
        _socket_addr.port = htons(_port);

        // bind this socket to the specified port
        if(bind(_socket_id, (struct sockaddr *)&_socket_addr, sizeof(_socket_addr)) < 0){
            throw std::runtime_error("socket cannot bind to the port: " + _port);
        }

        // start to listen to the port: req queue length 10
        if(listen(_socket_id, 10) < 0){
            throw std::runtime_error("socket cannot listen to the port: " + _port);
        }

        // socket addr length (needed only for accept call)
        int addrlen = sizeof(_socket_addr);
        // request buffer
        char req_buffer[BUFFER_SIZE] = {0};

        // keep receiving connection requests
        while(true){
            int new_socket_in = accept(_socket_id, (struct sockaddr *)&_socket_addr, (struct socklen_t *)&addrlen);
            if(new_socket_in < 0) throw std::runtime_error("socket accept failed");

            // read request
            int valread = read(new_socket_in, req_buffer, BUFFER_SIZE);
            cout << "request received: " << req_buffer;
            // parse request

            // process request

        }

    }



};