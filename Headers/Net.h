#pragma once
#include "Ipv4.h"

#include <list>

class Net
{
private:
	list<Ipv4> _ips;
	const usi _connectionType;
public:
	const usi
		INET = 1,
		ETHER = 2;
};