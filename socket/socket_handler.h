#pragma once

#include <map>
#include "socket/server_socket.h"
#include "socket/selector.h"

#include "thread/mutex.h"
using namespace melon::thread;

namespace melon
{
  namespace socket
  {
    class SocketHandler
    {
      SINGLETON(SocketHandler);
    public:

      void listen(const std::string& ip, int port);

      void attach(int socket_fd); 
      void detach(int socket_fd);

      void handle(int timeout);

    private:
      Socket* m_server = nullptr;
      Selector m_selector;
      Mutex m_mutex;
    };
  }
}
