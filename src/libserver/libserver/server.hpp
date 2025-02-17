#pragma once

#include <arpa/inet.h>
#include <thread>

namespace inftcs {
class Server {
 private:
  int sock = 0;
  int port;
  struct sockaddr_in servaddr, clientaddr;

 public:
  Server(const int port) : port(port) {};

  void handleClient(int conn);

  void start(void);
};
}  // namespace inftcs