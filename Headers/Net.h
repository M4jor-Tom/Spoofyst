#pragma once
#include "Ipv4.h"

class Net
{
private:
	list<Ipv4> _ips;
	const usi _connectionType, _mask;
	const string _name;
public:
	//Constructors
	Net(const string &name, const usi &connectionType, const usi &mask);

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