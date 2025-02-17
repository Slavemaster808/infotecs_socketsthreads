#include <libfuncs/funcs.hpp>
#include <libserver/server.hpp>

#include <unistd.h>
#include <iostream>

#define MAXCREQ 5

namespace inftcs {
void Server::start() {
  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock == -1) {
    std::cerr << "Socket creation failed." << '\n';
    return;
  }

  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = INADDR_ANY;
  servaddr.sin_port = htons(port);

  if (bind(sock, reinterpret_cast<sockaddr*>(&servaddr), sizeof(servaddr)) !=
      0) {
    std::cerr << "Socket bind failed." << '\n';
    close(sock);
    return;
  }

  if (listen(sock, MAXCREQ) != 0) {
    std::cerr << "Listen failed." << '\n';
    close(sock);
    return;
  }

  while (true) {
    socklen_t len = sizeof(clientaddr);
    int conn = accept(sock, reinterpret_cast<sockaddr*>(&clientaddr), &len);
    if (conn < 0) {
      std::cerr << "Server accept failed." << '\n';
      continue;
    }

    std::thread clientThread(&Server::handleClient, this, conn);
    clientThread.detach();
  }

  close(sock);
}

void Server::handleClient(int conn) {
  unsigned int sum = 0;
  while (recv(conn, &sum, sizeof(sum), 0) > 0) {
    if (helper::checkDigit(sum)) {
      std::cout << "Received data: " << sum << '\n';
    } else {
      std::cerr << "Error: Invalid data received." << '\n';
    }
  }

  close(conn);
}
}  // namespace inftcs