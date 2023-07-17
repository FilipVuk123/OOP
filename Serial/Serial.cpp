#include "Serial.hpp"

Serial::Serial(const std::string& device, speed_t baudRate) : device_(device), baudRate_(baudRate), fd_(-1) {}

Serial::~Serial() {
  closeSerial();
}

bool Serial::openSerial() {
  fd_ = open(device_.c_str(), O_RDWR | O_CLOEXEC);
  if (fd_ == -1) {
    std::cerr << "[Serial] Failed to open serial port on " << device_ << ": " << strerror(errno) << std::endl;
    std::cerr << "[Serial] Closing serial for: " << device_ << std::endl;
    return false;
  }else{
    std::cout << "[Serial] Opened serial fd: " << fd_ << " for device: " << device_ << std::endl; 
  }

  fcntl(fd_, F_SETFL, 0);

  struct termios options;
  if (tcgetattr(fd_, &options) != 0) {
    std::cerr << "[Serial] Error from tcgetattr: " << strerror(errno) << ". For device: " << device_ << std::endl;
    return false;
  }

  cfsetispeed(&options, baudRate_);
  cfsetospeed(&options, baudRate_);

  options.c_cflag &= ~PARENB;         // Clear parity bit, disabling parity (most common)
  options.c_cflag &= ~CSTOPB;         // Clear stop field, only one stop bit used in communication (most common)
  options.c_cflag &= ~CSIZE;          // Clear all bits that set the data size
  options.c_cflag |= CS8;             // 8 bits per byte (most common)
  options.c_cflag &= ~CRTSCTS;        // Disable RTS/CTS hardware flow control (most common)
  options.c_cflag |= CREAD | CLOCAL;  // Turn on READ & ignore ctrl lines (CLOCAL = 1)
  options.c_lflag &= ~ICANON;
  options.c_lflag &= ~ECHO;                                                         // Disable echo
  options.c_lflag &= ~ECHOE;                                                        // Disable erasure
  options.c_lflag &= ~ECHONL;                                                       // Disable new-line echo
  options.c_lflag &= ~ISIG;                                                         // Disable interpretation of INTR, QUIT and SUSP
  options.c_iflag &= ~(IXON | IXOFF | IXANY);                                       // Turn off s/w flow ctrl
  options.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL);  // Disable any special handling of received bytes
  options.c_oflag &= ~OPOST;                                                        // Prevent special interpretation of output bytes (e.g. newline chars)
  options.c_oflag &= ~ONLCR;

  options.c_cc[VTIME] = 1;
  options.c_cc[VMIN] = 0;
  // Non-blocking

  if (tcsetattr(fd_, TCSANOW, &options) != 0) {
    std::cerr << "[Serial] Error from tcsetattr: " << strerror(errno) << ". For device: " << device_ << std::endl;
    return false;
  }

  return true;
}

void Serial::closeSerial() {
  if (fd_ != -1) {
    std::cout << "[Serial] Closing serial fd: " << fd_ << ", for device: " << device_ << std::endl;
    close(fd_);
  }
  fd_ = -1;
}

bool Serial::writeData(const std::string& data) {
  ssize_t numBytes = write(fd_, data.c_str(), data.length());
  if (numBytes == -1) {
    std::cerr << device_ << " [Serial] Failed to write data to serial port. Error: " << strerror(errno) << std::endl;
    return false;
  }
  return true;
}

int Serial::readData(char *buffer, const int bufferSize) {
  ssize_t numBytes = read(fd_, buffer, bufferSize);
  if (numBytes == -1) {
    std::cerr << device_ << " [Serial] Failed to read data from serial port. Error: " << strerror(errno) << std::endl;
    closeSerial();
    return -1;
  }
  return numBytes;
}

int Serial::readChar(char *ch) {
  ssize_t numBytes = read(fd_, ch, 1);
  if (numBytes == -1) {
    std::cerr << device_ << " [Serial] Failed to read char from serial port. Error: " << strerror(errno) << std::endl;
    closeSerial();
    return -1;
  }
  return numBytes;
}

int Serial::getFD(){
  return fd_;
}


std::string Serial::getDevicePath(){
  return device_;
}