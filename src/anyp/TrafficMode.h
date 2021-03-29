/*
 * Copyright (C) 1996-2019 The Squid Software Foundation and contributors
 *
 * Squid software is distributed under GPLv2+ license and includes
 * contributions from numerous individuals and organizations.
 * Please see the COPYING and CONTRIBUTORS files for details.
 */

#ifndef SQUID_ANYP_TRAFFIC_MODE_H
#define SQUID_ANYP_TRAFFIC_MODE_H

#include "Debug.h"

namespace AnyP
{

/**
 * Set of 'mode' flags defining types of trafic which can be received.
 *
 * Use to determine the processing steps which need to be applied
 * to this traffic under any special circumstances which may apply.
 */
class TrafficMode
{
    /** marks intercept and decryption of CONNECT (tunnel) SSL traffic
     *
     * Indicating the following are required:
     *  - decryption of CONNECT request
     *  - URL translation from relative to absolute form
     *  - authentication prohibited on unwrapped requests (only on the CONNECT tunnel)
     *  - encrypted outbound server connections
     *  - peer relay prohibited. TODO: re-encrypt and re-wrap with CONNECT
     */
    bool _tunnelSslBumping = false;


public:
    TrafficMode() :
        _tunnelSslBumping(false),
        accelSurrogate(false),
        proxySurrogate(false),
        natIntercept(false),
        tproxyIntercept(false) {
        debugs(99, 5, HERE << "EsiteimproveE1 ctor() " << this << " _tunnelSslBumping: " << _tunnelSslBumping);
    }

    TrafficMode(const TrafficMode &value)
    {
        _tunnelSslBumping = value._tunnelSslBumping;
        accelSurrogate = value.accelSurrogate;
        proxySurrogate = value.proxySurrogate;
        natIntercept = value.natIntercept;
        tproxyIntercept = value.tproxyIntercept;

        debugs(99, 5, HERE << "EsiteimproveE2 cpy_ctor() " << this << " _tunnelSslBumping: " << _tunnelSslBumping);
    }

    TrafficMode& operator=(const TrafficMode& value)
    {
        _tunnelSslBumping = value._tunnelSslBumping;
        accelSurrogate = value.accelSurrogate;
        proxySurrogate = value.proxySurrogate;
        natIntercept = value.natIntercept;
        tproxyIntercept = value.tproxyIntercept;


        debugs(99, 5, HERE << "EsiteimproveE3 operator=() " << this << " _tunnelSslBumping: " << _tunnelSslBumping);

        return *this;
    }

    bool getTunnelSslBumping() const {
        debugs(99, 5, HERE << "EsiteimproveE4 getTunnelSslBumping() " << this << " _tunnelSslBumping: " << _tunnelSslBumping);
        return _tunnelSslBumping;
    }

    void setTunnelSslBumping(bool value) {
        _tunnelSslBumping = value;
        debugs(99, 5, HERE << "EsiteimproveE5 setTunnelSslBumping() " << this << " _tunnelSslBumping: " << _tunnelSslBumping);
    }

    /** marks HTTP accelerator (reverse/surrogate proxy) traffic
     *
     * Indicating the following are required:
     *  - URL translation from relative to absolute form
     *  - restriction to origin peer relay recommended
     */
    bool accelSurrogate = false;

    /** marks ports receiving PROXY protocol traffic
     *
     * Indicating the following are required:
     *  - PROXY protocol magic header
     *  - src/dst IP retrieved from magic PROXY header
     *  - indirect client IP trust verification is mandatory
     *  - TLS is not supported
     */
    bool proxySurrogate = false;

    /** marks NAT intercepted traffic
     *
     * Indicating the following are required:
     *  - NAT lookups
     *  - URL translation from relative to absolute form
     *  - Same-Origin verification is mandatory
     *  - destination pinning is recommended
     *  - authentication prohibited
     */
    bool natIntercept = false;

    /** marks TPROXY intercepted traffic
     *
     * Indicating the following are required:
     *  - src/dst IP inversion must be performed
     *  - client IP should be spoofed if possible
     *  - URL translation from relative to absolute form
     *  - Same-Origin verification is mandatory
     *  - destination pinning is recommended
     *  - authentication prohibited
     */
    bool tproxyIntercept = false;

    /** true if the traffic is in any way intercepted
     *
     */
    bool isIntercepted() { return natIntercept||tproxyIntercept ;}
};

} // namespace AnyP

#endif

