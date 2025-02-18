#include "socket/socket_handler.h"
using namespace melon::socket;

#include "task/task_factory.h"
using namespace melon::task;

#include "thread/task_dispatcher.h"
#include "thread/auto_lock.h"
using namespace melon::thread;

void SocketHandler::listen(const std::string& ip, int port)
{
  m_server = new ServerSocket(ip, port);
}

void SocketHandler::attach(int socket_fd)
{
  AutoLock lock(&m_mutex);
  m_selector.setFd(socket_fd);
}

void SocketHandler::detach(int socket_fd)
{
  AutoLock lock(&m_mutex);
  m_selector.delFd(socket_fd);
}

void SocketHandler::handle(int timeout)
{
  attach(m_server->fd());

  while (true)
  {
    int ret = m_selector.select(timeout);
    if (ret < 0)
    {
      log_error("select error: errno = %d, errmsg = %s.", errno, strerror(errno));
      break;
    }
    else if (ret == 0)
    {
      log_debug("select timeout.");
      continue;
    }
    log_debug("select ok: ret = %d.", ret);

    for (int fd = 0; fd < m_selector.maxFd() + 1; ++ fd)
    {
      if (!m_selector.isSet(fd))
        continue;
      if (fd == m_server->fd())
      {
        int conn_fd = m_server->accept();
        if (conn_fd < 0)
          continue;
        
        Socket socket(conn_fd);
        socket.setNonBlocking();
        attach(conn_fd);
      }
      else
      {
        detach(fd);

        auto task = TaskFactory::create(fd);
        Singleton<TaskDispatcher>::getInstance()->push(task);
      }
    }
  }
}
