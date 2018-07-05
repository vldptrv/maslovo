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
static char buf[1024];

static init(uint32_t ip, uint16_t port);
static work(void);

int main(int argc, char **argv)
{
  init(htonl(argc > 1 ? atoi(argv[1]) : 0), htons(argc > 2 ? atoi(argv[2]) : 8090));
  
  while(1)
  {
    cfd = MAS_ACCEPT(sfd, ssa);
    MAS_READ(cfd, buf, sizeof(buf));
    MAS_SEND(cfd, buf, sizeof(buf));
  }
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
}

static work(void) {
    MAS_READ(cfd, buf, sizeof(buf));
    MAS_SEND(cfd, buf, sizeof(buf));
}
