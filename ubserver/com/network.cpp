#include "network.h"

//net
bool NET_CLOSE(SOCKET_T fd)
{
    return ::close(fd) == 0;
}

size_t NET_RECV(SOCKET_T fd, void* bytes, size_t len)
{
    return ::recv(fd, bytes, len, 0);
}

int NET_SEND(SOCKET_T fd, const void* bytes, size_t len)
{
    return (int)::send(fd, bytes, len, 0);
}

int NET_SEND_PACKET(SOCKET_T fd, PacketBuffer* packet)
{
    return NET_SEND(fd, &packet->get(0), packet->wpos());
}
