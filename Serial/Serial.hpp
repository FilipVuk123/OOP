#pragma once

#include <fcntl.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <iostream>

class Serial {
 public:
  Serial(const std::string& device, speed_t baudRate);
  ~Serial();

  /*
   * opens serial port
   */
  bool openSerial();

  /*
   * closes serial port
   */
  void closeSerial();

  /*
   * writes data to serial port
   */
  bool writeData(const std::string& data);

  /*
   * reads data to buffer
   */
  int readData(char *buffer, const int bufferSize);

  /*
   * reads char to ch
   */
  int readChar(char *ch);

  /*
   * returns file descriptor
   */
  int getFD();

  /*
   * returns device name
   */
  std::string getDevicePath();

 private:
  std::string device_{};
  speed_t baudRate_{};
  int fd_{-1};
};
