#include "TrafficMode.h"


#include "squid.h"
#include "Debug.h"
#include "filelogger.h"

namespace AnyP
{
TrafficMode::TrafficMode() : _tunnelSslBumping(false),
                             accelSurrogate(false),
                             proxySurrogate(false),
                             natIntercept(false),
                             tproxyIntercept(false)
{
    debugs(99, 5, HERE << "EsiteimproveE1 ctor() " << this << " _tunnelSslBumping: " << _tunnelSslBumping);

	myLog.myFile << "EsiteimproveE1 ctor() " << this << " _tunnelSslBumping: " << _tunnelSslBumping;
	myLog.flush();
}

TrafficMode::TrafficMode(const TrafficMode &value)
{
    _tunnelSslBumping = value._tunnelSslBumping;
    accelSurrogate = value.accelSurrogate;
    proxySurrogate = value.proxySurrogate;
    natIntercept = value.natIntercept;
    tproxyIntercept = value.tproxyIntercept;

    debugs(99, 5, HERE << "EsiteimproveE2 cpy_ctor() " << this << " _tunnelSslBumping: " << _tunnelSslBumping);

	myLog.myFile << "EsiteimproveE2 cpy_ctor() " << this << " _tunnelSslBumping: " << _tunnelSslBumping;
	myLog.flush();
}

TrafficMode::~TrafficMode()
{
    debugs(99, 5, HERE << "EsiteimproveE7 ~TrafficMode() " << this << " _tunnelSslBumping: " << _tunnelSslBumping);
}

TrafficMode &TrafficMode::operator=(const TrafficMode &value)
{
    _tunnelSslBumping = value._tunnelSslBumping;
    accelSurrogate = value.accelSurrogate;
    proxySurrogate = value.proxySurrogate;
    natIntercept = value.natIntercept;
    tproxyIntercept = value.tproxyIntercept;

    debugs(99, 5, HERE << "EsiteimproveE3 operator=() " << this << " _tunnelSslBumping: " << _tunnelSslBumping);

    myLog.myFile << "EsiteimproveE3 operator=() " << this << " _tunnelSslBumping: " << _tunnelSslBumping;
	myLog.flush();

    return *this;
}

bool TrafficMode::getTunnelSslBumping() const
{
    debugs(99, 5, HERE << "EsiteimproveE4 getTunnelSslBumping() " << this << " _tunnelSslBumping: " << _tunnelSslBumping);
    return _tunnelSslBumping;
}

void TrafficMode::setTunnelSslBumping(bool value)
{
    _tunnelSslBumping = value;
    debugs(99, 5, HERE << "EsiteimproveE5 setTunnelSslBumping() " << this << " _tunnelSslBumping: " << _tunnelSslBumping);

    myLog.myFile << "EsiteimproveE5 setTunnelSslBumping() " << this << " _tunnelSslBumping: " << _tunnelSslBumping;
	myLog.flush();
}

}