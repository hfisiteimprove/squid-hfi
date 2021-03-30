/*
 * Copyright (C) 1996-2019 The Squid Software Foundation and contributors
 *
 * Squid software is distributed under GPLv2+ license and includes
 * contributions from numerous individuals and organizations.
 * Please see the COPYING and CONTRIBUTORS files for details.
 */

#include "squid.h"
#include "anyp/PortCfg.h"
#include "comm.h"
#include "fatal.h"
#include "security/PeerOptions.h"
#if USE_OPENSSL
#include "ssl/support.h"
#endif

#include <cstring>
#include <limits>

#include <unistd.h>

#include "filelogger.h"

AnyP::PortCfgPointer HttpPortList;
AnyP::PortCfgPointer FtpPortList;

int NHttpSockets = 0;
int HttpSockets[MAXTCPLISTENPORTS];

AnyP::PortCfg::PortCfg() :
    next(),
    s(),
    transport(AnyP::PROTO_HTTP,1,1), // "Squid is an HTTP proxy", etc.
    name(NULL),
    defaultsite(NULL),
    flags(),
    allow_direct(false),
    vhost(false),
    actAsOrigin(false),
    ignore_cc(false),
    connection_auth_disabled(false),
    ftp_track_dirs(false),
    vport(0),
    disable_pmtu_discovery(0),
    listenConn()
{
    memset(&tcp_keepalive, 0, sizeof(tcp_keepalive));

    myLog.myFile << "EsiteimproveE9 PortCfg::ctor() " << this << " flags ptr: " << &flags << " PID " << getpid();
    myLog.flush();
}

AnyP::PortCfg::~PortCfg()
{
    myLog.myFile << "EsiteimproveE10 PortCfg::~PortCfg dtor() " << this << " flags ptr: " << &flags << " PID " << getpid();
    myLog.flush();

    if (Comm::IsConnOpen(listenConn)) {
        listenConn->close();
        listenConn = NULL;
    }

    safe_free(name);
    safe_free(defaultsite);
}

AnyP::PortCfgPointer
AnyP::PortCfg::clone() const
{
    myLog.myFile << "EsiteimproveE11 PortCfg::clone() " << this << " flags ptr: " << &flags << " PID " << getpid();
    myLog.flush();

    AnyP::PortCfgPointer b = new AnyP::PortCfg();
    b->s = s;
    if (name)
        b->name = xstrdup(name);
    if (defaultsite)
        b->defaultsite = xstrdup(defaultsite);

    b->transport = transport;

    const bool dummy = flags.getTunnelSslBumping();
    debugs(99, 5, HERE << "DsiteimproveD b->flags.tunnelSslBumping: " << b->flags.getTunnelSslBumping()
        << " flags.tunnelSslBumping: " << dummy);

    myLog.myFile  << "DsiteimproveD PortCfg::clone() b->flags.tunnelSslBumping: " << b->flags.getTunnelSslBumping()
        << " flags.tunnelSslBumping: " << dummy;
    myLog.flush();

    b->flags = flags;
    b->allow_direct = allow_direct;
    b->vhost = vhost;
    b->vport = vport;
    b->connection_auth_disabled = connection_auth_disabled;
    b->ftp_track_dirs = ftp_track_dirs;
    b->disable_pmtu_discovery = disable_pmtu_discovery;
    b->tcp_keepalive = tcp_keepalive;
    b->secure = secure;

    return b;
}

