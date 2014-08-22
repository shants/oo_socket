#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include<string>

using namespace std;
#define INVALID_HANDLE_VALUE -1
typedef int SOCKET;

class INET_Addr
{
private:
    sockaddr_in _addr;
public:
    INET_Addr(int port,string addr); 
    ~INET_Addr(); 
    sockaddr* addr(void) ;    
    size_t size(void) const ;
};

INET_Addr::~INET_Addr()
{
}
 
INET_Addr::INET_Addr(int port, string addr) 
{
    memset(reinterpret_cast <void*>(&_addr), '\0', sizeof(_addr));
    _addr.sin_family = AF_INET;
    _addr.sin_port = htons(port);
    inet_pton(AF_INET, addr.c_str(), &(_addr.sin_addr));
}

sockaddr* INET_Addr::addr(void)  
{
    return (reinterpret_cast<sockaddr *>(&_addr));
}

size_t INET_Addr::size(void) const
{
    return sizeof(_addr);
}

////////////////////////////////


class SOCK_Stream
{
private:
    SOCKET _handle;

public:
    SOCK_Stream(void) : _handle(INVALID_HANDLE_VALUE) {}
    SOCK_Stream(SOCKET h) : _handle(h) {}
    ~SOCK_Stream() {
    close(_handle);
}

SOCKET get_handle() { return _handle; }
void set_handle(SOCKET h) { _handle = h; }

// add send and recv funcs
};


//////////////////////////////////////
class SOCK_Acceptor
{
public:
SOCK_Acceptor(INET_Addr &sock_addr) 
{
    _handle = socket(PF_INET, SOCK_STREAM, 0);
    bind(_handle, sock_addr.addr(), sock_addr.size());
    listen(_handle, 5);
}

int accept(SOCK_Stream &stream) 
{
    stream.set_handle( ::accept(_handle, 0, 0));
    cout << "\n client connected";
    if (stream.get_handle () == INVALID_HANDLE_VALUE)
	return -1;
    else 
	return 0;
}

private:
SOCKET _handle;
};

//////////////////////////////////////
class SOCK_Connector
{
public:
SOCK_Connector(INET_Addr &sock_addr) 
{
    _handle = socket(PF_INET, SOCK_STREAM, 0);
    bind(_handle, sock_addr.addr(), sock_addr.size());
}

int connect(SOCK_Stream &stream) 
{
    stream.set_handle( ::connect(_handle, 0, 0));
    if (stream.get_handle () == INVALID_HANDLE_VALUE)
	return -1;
    else 
	return 0;
}

private:
SOCKET _handle;
};
