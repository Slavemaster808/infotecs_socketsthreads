#include <libserver/server.hpp>

int main() {
  inftcs::Server server(8080);
  server.start();
}