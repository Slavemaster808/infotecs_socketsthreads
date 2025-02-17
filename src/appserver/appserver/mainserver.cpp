#include <libserver/server.hpp>

#include <iostream>

int main() {
  std::cout << "Server response:" << '\n';
  inftcs::Server server(8080);
  server.start();
}