#include "UDPServer.hpp"

namespace UDP {

UdpServer::UdpServer(std::string ip, const int port) {
  std::cout << "[UDP Server] Initializing UDP server!" << std::endl;
  initUdpServer(ip, port); 
}

void UdpServer::initUdpServer(std::string ip, const int port) {
  ip_ = ip;
  port_ = port;

  sock_ = socket(AF_INET, SOCK_DGRAM, 0);
  if (sock_ < 0) {
    std::cerr << "[UDP Server] failed to create socket" << std::endl;
    return;
  }
  int opt = 1;
  if (setsockopt(sock_, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) < 0) {
    std::cerr << "[UDP Server] Failed to set socket options: " << strerror(errno) << std::endl;
  }

  memset(&clientAddr_, 0, sizeof(clientAddr_));
  memset(&serverAddr_, 0, sizeof(serverAddr_));
  serverAddr_.sin_family = AF_INET;
  serverAddr_.sin_port = htons(port_);
  serverAddr_.sin_addr.s_addr = ntohl(INADDR_ANY);

  recvBuffer_ = static_cast<char *>(calloc(1, mtu_));
}

UdpServer::~UdpServer() {
  std::cout << "[UDP Server] Destroying UDP server!" << std::endl;
  destroyUdpServer();
}

void UdpServer::destroyUdpServer() {
  free(recvBuffer_);
  close(sock_);
}

void UdpServer::setMtu(int value) {
  mtu_ = value;
  recvBuffer_ = static_cast<char *>(realloc(recvBuffer_, mtu_));
}

int UdpServer::getMtu() {
  return mtu_;
}

int UdpServer::enableNonBlocking(bool enable) {
  int flags;

  flags = fcntl(sock_, F_GETFL, 0);

  if (flags < 0) {
    std::cerr << "[UDP Server] Failed to get socket flags: " << strerror(errno) << std::endl;

    return -1;
  }

  if (enable) {
    std::cout << "[UDP Server] [fd: " << sock_ << "] Enabling non-blocking mode" << std::endl;

    flags |= O_NONBLOCK;
  } else {
    std::cout << "[UDP Server] [fd: " << sock_ << "] Disabling non-blocking mode" << std::endl;

    flags &= ~O_NONBLOCK;
  }

  if (fcntl(sock_, F_SETFL, flags) < 0) {
    std::cerr << "[UDP Server] Failed to enable non-blocking mode for a socket: " << strerror(errno) << std::endl;

    return -1;
  }

  return 0;
}

int UdpServer::bindSocket() {
  if (bind(static_cast<int>(sock_), reinterpret_cast<sockaddr *>(&serverAddr_), sizeof(serverAddr_)) < 0) {
    std::cerr << "[UDP Server] Error binding to socket: " << strerror(errno) << std::endl;
    return -1;
  } else {
    std::cout << "[UDP Server] Bound to socket: " << inet_ntoa(serverAddr_.sin_addr) << ":" << port_ << std::endl;
    return 0;
  }
}

size_t UdpServer::receive(buffer_t *buffer) {
  int len = sizeof(clientAddr_);

  int recv_bytes = recvfrom(sock_, recvBuffer_, mtu_, 0, (struct sockaddr *)&clientAddr_, (socklen_t *)&len);
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
      std::cerr << "[UDP Server] Error while receiving: " << strerror(errno) << std::endl;
      return recv_bytes;
    }
  }
}

size_t UdpServer::send(buffer_t *buffer) {
  int bytes = sendto(sock_, buffer->ptr, buffer->size, 0, (struct sockaddr *)&clientAddr_, sizeof(clientAddr_));
  if (bytes >= 0) {
    return bytes;
  } else {
    if ((errno == EAGAIN) || (errno == EWOULDBLOCK)) {
      return 0;
    } else {
      std::cerr << "[UDP Server] Error while sending: " << strerror(errno) << std::endl;
      return bytes;
    }
  }
}

}