#ifndef _LWIPOPTS_H
#define _LWIPOPTS_H

// Generally you would define your own explicit list of lwIP options
// (see https://www.nongnu.org/lwip/2_1_x/group__lwip__opts.html)
//
// This example uses a common include to avoid repetition

#define NO_SYS 0
#define	LWIP_SOCKET 1
#define	LWIP_COMPAT_SOCKETS 1
#define	LWIP_POSIX_SOCKETS_IO_NAMES 1
#define	LWIP_SOCKET_OFFSET 0
#define	LWIP_TCP_KEEPALIVE 0
#define	LWIP_SO_SNDTIMEO 0
#define	LWIP_SO_RCVTIMEO 0
#define	LWIP_SO_SNDRCVTIMEO_NONSTANDARD 0
#define	LWIP_SO_RCVBUF 0
#define	LWIP_SO_LINGER 0
#define	RECV_BUFSIZE_DEFAULT INT_MAX
#define	LWIP_TCP_CLOSE_TIMEOUT_MS_DEFAULT 20000
#define	SO_REUSE 0
#define	SO_REUSE_RXTOALL 0
#define	LWIP_FIONREAD_LINUXMODE 0
#define	LWIP_SOCKET_SELECT 1
#define	LWIP_SOCKET_POLL 1

#endif
