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

class UdpClient {
 public:
  int port_{};
  std::string ip_{};
  std::string interface_{};

  UdpClient(std::string ip, const int port);
  ~UdpClient();

  /*
   * sets mtu size
   */
  void setMtu(const int mtu_value);
  
  /*
   * enables non blocking receive 
   */
  int enableNonBlocking(bool enable);
  
  /*
   * connects socket (not mandatory for udp sockets)
   */
  int connectSocket();
  
  /*
   * recieves data to buffer_t struct
   */
  size_t receive(buffer_t *buffer);
  
  /*
   * sends buffer_t struct data
   */
  size_t send(buffer_t *buffer);
  
  /*
   * returns MTU value
   */
  int getMtu();

 private:
  char *recvBuffer_{};
  int sock_{-1};
  int mtu_{ETH_FRAME_LEN};
  struct sockaddr_in serverAddr_ {};

  /*
   * closes socket
   */
  void destroyUdpClient();
  
  /*
   * opens and configures socket
   */
  void initUdpClient(std::string ip, const int port);
};

}  // namespace UDP
