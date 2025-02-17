#pragma once

#include <condition_variable>
#include <mutex>
#include <string>
#include <thread>

namespace inftcs {
class Buffer {
 private:
  std::string buffer;
  bool isReady = false;
  std::mutex mtx;
  std::condition_variable cv;

 public:
  void set(const std::string& data);

  std::string get(void);
};

class Handler {
 private:
  Buffer& buff;

 public:
  Handler(Buffer& b) : buff(b) {};

  void input(void);
};

class Sender {
 private:
  Buffer& buff;
  void sendToServer(unsigned int sum);

 public:
  Sender(Buffer& b) : buff(b) {};

  void sendData(void);
};
}  // namespace inftcs