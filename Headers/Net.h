#pragma once
#include "Ipv4.h"
#include "../process/Headers/process.h"

class Net
{
private:
	const string _name;
	list<Ipv4> _ips;
	Ipv4 _userIp, _gateIp;
	const usi _mask, _connectionType;
public:
	//Constructors
	Net(const string &name, const usi &connectionType, const Ipv4& userIp, const Ipv4& gateIp, const usi &mask);

	//Setters
	void nmap();

	//Getters
	string toString() const;
	size_t getIpCount() const;

	//Displayers
	void displayIpv4s();
	void attackMenu(list<Ipv4> routers, const Ipv4 &ip);

	//Attackers
	void spoof(const Ipv4& router, const Ipv4& target) const;
	void shutdown(const Ipv4& target) const;

	//Constants
	static const usi
		INET = 1,
		ETHER = 2;
};
