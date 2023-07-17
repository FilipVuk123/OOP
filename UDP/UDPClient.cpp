#include "UDPClient.hpp"

namespace UDP {

UdpClient::UdpClient(std::string ip, const int port) {
  std::cout << "[UDP Client] Initializing UDP client!" << std::endl;
  initUdpClient(ip, port);
}

void UdpClient::initUdpClient(std::string ip, const int port) {
  ip_ = ip;
  port_ = port;

  sock_ = socket(AF_INET, SOCK_DGRAM, 0);
  if (sock_ < 0) {
    std::cerr << "[UDP Client] failed to create socket" << std::endl;
    return;
  }
  int opt = 1;
  if (setsockopt(sock_, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) < 0) {
    std::cerr << "[UDP Client] Failed to set socket options: " << strerror(errno) << std::endl;
  }

  memset(&serverAddr_, 0, sizeof(serverAddr_));
  serverAddr_.sin_family = AF_INET;
  serverAddr_.sin_port = htons(port);
  serverAddr_.sin_addr.s_addr = inet_addr(ip.c_str());

  recvBuffer_ = static_cast<char *>(calloc(1, mtu_));
}

UdpClient::~UdpClient() {
  std::cout << "[UDP Client] Destroying UDP client!" << std::endl;
  destroyUdpClient();
}

void UdpClient::destroyUdpClient() {
  free(recvBuffer_);
  close(sock_);
}

void UdpClient::setMtu(int value) {
  mtu_ = value;
  recvBuffer_ = static_cast<char *>(realloc(recvBuffer_, mtu_));
}

int UdpClient::enableNonBlocking(bool enable) {
  int flags;

  flags = fcntl(sock_, F_GETFL, 0);

  if (flags < 0) {
    std::cerr << "[UDP Client] Failed to get socket flags: " << strerror(errno) << std::endl;

    return -1;
  }

  if (enable) {
    std::cout << "[UDP Client] [fd: " << sock_ << "] Enabling non-blocking mode" << std::endl;

    flags |= O_NONBLOCK;
  } else {
    std::cout << "[UDP Client] [fd: " << sock_ << "] Disabling non-blocking mode" << std::endl;

    flags &= ~O_NONBLOCK;
  }

  if (fcntl(sock_, F_SETFL, flags) < 0) {
    std::cerr << "[UDP Client] Failed to enable non-blocking mode for a socket: " << strerror(errno) << std::endl;

    return -1;
  }

  return 0;
}

int UdpClient::connectSocket() {
  if (connect(sock_, reinterpret_cast<sockaddr *>(&serverAddr_), sizeof(serverAddr_)) < 0) {
    std::cerr << "[UDP Client] Error connecting to socket: " << strerror(errno) << std::endl;
    return -1;
  } else {
    std::cout << "[UDP Client] Connected to server: " << inet_ntoa(serverAddr_.sin_addr) << ":"
              << port_ << std::endl;
    return 0;
  }
}

size_t UdpClient::receive(buffer_t *buffer) {
  int len = sizeof(serverAddr_);
  int recv_bytes = recvfrom(sock_, recvBuffer_, mtu_, 0, (struct sockaddr *)&serverAddr_, (socklen_t *)&len);
  if (recv_bytes >= 0) {
    buffer->ptr = recvBuffer_;
    buffer->size = recv_bytes;
    return recv_bytes;
  } else {
    if ((errno == EAGAIN) || (errno == EWOULDBLOCK)) {
      return 0;
      buffer->size = 0;
      buffer->ptr = nullptr;
    } else {
      std::cout << "[UDP Client] Error while receiving: " << strerror(errno) << std::endl;
      return recv_bytes;
    }
  }
}

int UdpClient::getMtu() {
  return mtu_;
}

size_t UdpClient::send(buffer_t *buffer) {
  int bytes = sendto(sock_, buffer->ptr, buffer->size, 0, (sockaddr *)&serverAddr_, sizeof(serverAddr_));
  if (bytes >= 0) {
    return bytes;
  } else {
    if ((errno == EAGAIN) || (errno == EWOULDBLOCK)) {
      return 0;
    } else {
      std::cerr << "[UDP Client] Error while sending: " << strerror(errno) << std::endl;
      return bytes;
    }
  }
}

}