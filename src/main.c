#include "../defines.h"

static int sfd;
static int cfd;

int main(int argc, char **argv)
{
  if((sfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0);
  
}
