#pragma once

#include "Types.h"
#include "Ethernet.h"
#include "IPV4.h"

class ICMP;
class ARP;
class UDP;
class Ethernet;
//Internet Protocol Version 4
class IPV4 :public NetworkProtocol
{
public:
	//IP-address
	typedef u32 Address;
	//Protocol types
	enum Protocol
	{
		ICMP=1,
		IGMP=2,
		UDP=17,
		TCP=6
	};

	//IP network packet header.
	typedef struct Header
	{
		u8 versionIHL;//Version and header length(IHL)
		u8 typeOfService;
		u16 length;
		u16 identification;
		u16 fragmentOffset;
		u8 timeToLive;
		u8 Protocol;
		u16 checksum;
		Address source;
		Address destination;
	}
	PACKED Header;


	//Pseudo Header.
	typedef struct PseudoHeader
	{
		Address source;
		Address destination;
		u8	reserved;
		u8  prootocol;
		u16	length;
	}
	PseudoHeader;

	//Ctr
	IPV4(NetworkServer *server, NetworkDevice *device);

	//Dtr
	virtual ~IPV4();

	//Perform initialization.
	virtual Error initialize();

	//Set ICMP instance.
	void setICMP(::ICMP *icmp);

	void setARP(::ARP *arp);

	void setUDP(::UDP *udp);

	void setEthernet(::Ethernet *ether);

	/**
	* Get current IP address
	*
	* @param address IPV4 address buffer
	* @return Error code
	*/
	virtual Error getAddress(Address *address);

	/**
	* Set current IP address
	*
	* @param address IPV4 address buffer
	* @return Error code
	*/
	virtual Error setAddress(Address *address);

	/**
	* Convert address to string
	*
	* @param address Input IP address
	* @return Text value of the IP
	*/
	static const String toString(Address address);

	/**
	* Convert string to IPV4 address.
	*
	* @param address Input textual IP address in dot notation (xxx.xxx.xxx.xxx)
	* @return IPV4::Address or ZERO if not valid
	*/
	static const Address toAddress(const char *address);


	//Get a new packet for transmission
	Error getTransmitPacket(NetworkQueue::Packet **pkt, 
						    Address destination,
							Protocol type,
							Size size);

	//Process incoming network packet.
	virtual Error process(NetworkQueue::Packet *pkt, Size offset);

	//Calculate IP checksum
	static const u16 checksum(const void *buffer, Size length);

	private:
		//Current IP address
		Address m_address;
		//ICMP instance
		::ICMP *m_icmp;
		//ARP instance
		::ARP *m_arp;

		//UDP instance
		::UDP *m_udp;

		//Ethernet instance
		::Ethernet *m_enter;

		//Packet ID for IPV4
		u16 m_id;
};

