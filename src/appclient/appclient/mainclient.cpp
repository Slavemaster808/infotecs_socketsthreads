#include <libclient/client.hpp>

#include <iostream>
#include <thread>

int main() {
  inftcs::Buffer buffer;
  inftcs::Handler handler(buffer);
  inftcs::Sender sender(buffer);

  std::cout << "Enter digits only (no longer than 64 digits)/q to quit."
            << '\n';

  // Создаем потоки с использованием std::thread
  std::thread handlerThread(&inftcs::Handler::input, &handler);
  std::thread senderThread(&inftcs::Sender::sendData, &sender);

  // Ожидаем завершения потоков
  handlerThread.join();
  senderThread.join();

  return 0;
}