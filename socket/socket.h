#pragma once

#include <string>
#include <cstring>
#include <sys/socket.h> // socket.h
#include <netinet/in.h> // IPPROTO_TCP
#include <arpa/inet.h>  // inet_addr()
#include <unistd.h>    
#include <fcntl.h>

#include "utility/log_system.h"

using namespace melon::utility;

namespace melon
{
  namespace socket
  {
    class Socket
    {
    public:
      Socket();
      Socket(int socket_fd);
      virtual ~Socket();

      int fd() const;
      bool bind(const std::string& ip, int port);
      bool listen(int backlog);
      bool connect(const std::string& ip, int port);
      int accept();
      int send(const char* buf, int len);
      int recv(char* buf, int len);
      void close();

      bool setNonBlocking();
      bool setSendBuffer(int size);
      bool setRecvBuffer(int size);
      bool setLinger(bool active, int seconds);
      bool setKeepAlive();
      bool setReuseAddr();

    protected:
      std::string m_ip;
      int m_port;
      int m_socket_fd;
    };
  }
}
