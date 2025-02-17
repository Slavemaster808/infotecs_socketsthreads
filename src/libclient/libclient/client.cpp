#include <libclient/client.hpp>

#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>

namespace inftcs {
void Buffer::set(const std::string& data) {
  std::unique_lock<std::mutex> lock(mtx);
  buffer = data;
  isReady = true;
  cv.notify_one();
}

std::string Buffer::get() {
  std::unique_lock<std::mutex> lock(mtx);
  cv.wait(lock, [this] { return isReady; });
  isReady = false;
  return buffer;
}

void Handler::input() {
  while (true) {
    std::string in;
    std::getline(std::cin, in);

    if (in == "q") {
      break;
    }

    if (in.size() > 64 ||
        in.find_first_not_of("0123456789") != std::string::npos) {
      std::cerr << "Invalid input." << '\n';
      continue;
    }

    std::sort(in.begin(), in.end(), std::greater<char>());

    for (size_t i = 0; i < in.size();) {
      unsigned int d = in[i] - '0';
      if (d % 2 == 0) {
        in.replace(i, 1, "KV");
        i += 2;
      } else {
        i++;
      }
    }

    buff.set(in);
  }
  exit(0);
}

void Sender::sendToServer(unsigned int sum) {
  int sock = 0;
  struct sockaddr_in servaddr;

  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock == -1) {
    std::cerr << "Failed to create socket." << '\n';
    return;
  }

  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(8080);
  servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

  if (connect(sock, reinterpret_cast<sockaddr*>(&servaddr), sizeof(servaddr)) !=
      0) {
    std::cerr << "Connection failed. Please restart the server." << '\n';
    close(sock);
    return;
  }

  send(sock, &sum, sizeof(sum), 0);
  close(sock);
}

void Sender::sendData() {
  while (true) {
    std::string data = buff.get();
    std::cout << "Result string: " << data << '\n';

    unsigned int sum = 0;
    for (const auto& c : data) {
      if (std::isdigit(c)) {
        sum += c - '0';
      }
    }

    std::cout << "Sum of all digits: " << sum << '\n';
    sendToServer(sum);
  }
}
}  // namespace inftcs