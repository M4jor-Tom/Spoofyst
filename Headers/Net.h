#pragma once
#include "Ipv4.h"
#include "../process/Headers/process.h"

class Net
{
private:
	Menu _ipv4sMenu;
	const string _name;
	list<Ipv4> _ips;
	Ipv4 _userIp, _gateIp;
	const usi _mask, _connectionType;
	
public:
	//Constructors
	Net(const string &name, const usi &connectionType, const Ipv4& userIp, const Ipv4& gateIp, const usi &mask);

	//Destructors
	~Net();

	//Setters
	bool nmap();

	//Getters
	string toString() const;
	size_t getIpCount() const;

	//Displayers
	void displayIpv4s();
	void attackMenu(Ipv4 &ip);

	//Attackers
	void arpSpoof(bool forward, Ipv4& target);
	void shutdown(const Ipv4& target) const;

	//Process managers
	void killChilds();
	void stopAttacks(Ipv4& target);

	//Static functions
	static usi maskToUsi(const string &stringyMask);
	static usi maskToUsi(const usi &word1, const usi &word2, const usi &word3, const usi &word4);

	//Constants
	static const usi
		INET = 1,
		ETHER = 2;
};
