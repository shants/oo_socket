#include<iostream>
#include "INET_Addr.h"

int main()
{
INET_Addr addr(8080, "127.0.0.1");
SOCK_Acceptor acceptor(addr);
SOCK_Stream stream;
acceptor.accept(stream);
return 0;
}
