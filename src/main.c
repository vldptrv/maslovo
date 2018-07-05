#include "../defines.h"

#include <stdint.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

const static int on = 1;

static int sfd;
static int cfd;
static int pid;
static struct sockaddr_in ssa;

static init(uint32_t ip, uint16_t port);

int main(int argc, char **argv)
{
  
  
}

static init(uint32_t ip, uint16_t port) {
  if((sfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
    error(1, errno, "socket()");
  }
  
  bzero(&ssa, sizeof(ssa));
  
  ssa.sin_family = AF_INET;
  ssa.sin_port = htons(port);
  ssa.sin_addr.s_addr = htonl(ip);
  
  if(setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
  
  if(bind(sfd, (struct sockaddr *)&ssa, sizeof(ssa)) {
    error(1, errno, "bind()");
  }
     
  if(listen(sfd, SOMAXCONN)) {
    error(1, errno, "listen()"); 
  }
     
  while(1) {
     
  }
     
}
