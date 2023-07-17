#pragma once

#include <arpa/inet.h>
#include <fcntl.h>
#include <linux/if_ether.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <sys/wait.h>
#include <unistd.h>

#include <iostream>

namespace UDP {

#ifndef __BUFFER_T__
#define __BUFFER_T__
typedef struct buffer_t {
  void *ptr;
  size_t size;
} buffer_t;
#endif

class UdpServer {
 public:
  int port_{};
  std::string ip_{};
  std::string interface_{};

  UdpServer(std::string ip, const int port);
  ~UdpServer();

  /*
   * sets MTU to mtuValue
   */
  void setMtu(const int mtuValue);
  
  /*
   * enables non blocking receive
   */
  int enableNonBlocking(bool enable);
  
  /*
   * binds socket
   */
  int bindSocket();
  
  /*
   * receives data to buffer_t struct
   */
  size_t receive(buffer_t *buffer);
  
  /*
   * sends data stored in buffer_t struct
   */
  size_t send(buffer_t *buffer);
  
  
  /*
   * returns MTU value
   */
  int getMtu();

 private:
  char *recvBuffer_;
  int sock_{-1};
  int mtu_{ETH_FRAME_LEN};
  struct sockaddr_in serverAddr_ {};
  struct sockaddr_in clientAddr_ {};

  /*
   * closes socket
   */
  void destroyUdpServer();
  
  /*
   * opens and configures socket
   */
  void initUdpServer(std::string ip, const int port);
};

}  // namespace UDP
