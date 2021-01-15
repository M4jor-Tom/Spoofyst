#include "../Headers/Net.h"

Net::Net(const string& name, const usi& connectionType, const usi &mask, Ipv4 *userIpPtr):
	_name(name),
	_connectionType(connectionType),
	_mask(mask),
	_userIpPtr(userIpPtr)
{
	nmap();
}

void Net::nmap()
{
	//Deleting existing Ips for reload
	for (Ipv4* ipP : _ipsPtrs)
		delete ipP;
	_ipsPtrs.clear();

	//TESTING
	_ipsPtrs.push_back(new Ipv4(192, 168, 0, 0, Ipv4::ROUTER));
	_ipsPtrs.push_back(new Ipv4(192, 168, 0, 1, Ipv4::OTHER));
	_ipsPtrs.push_back(new Ipv4(192, 168, 0, 3, Ipv4::OTHER));
	_ipsPtrs.push_back(new Ipv4(192, 168, 0, 4, Ipv4::OTHER));

	//Linux command

}

string Net::toString() const
{
	return _name;
}

size_t Net::getIpCount() const
{
	return _ipsPtrs.size();
}

void Net::displayIpv4s()
{
	Menu ipv4sMenu;
	list<Ipv4 *> routers;

	for (Ipv4 *ipPtr : _ipsPtrs)
		if (ipPtr -> getIdentity() == Ipv4::OTHER)
			ipv4sMenu.addChoice(ipPtr -> toString());
		else if(ipPtr -> getIdentity() == Ipv4::ROUTER)
			routers.push_back(ipPtr);
	
	ipv4sMenu.addExit();

	do
	{
		unsigned int
			chosenIpv4 = ipv4sMenu.display("Choose the Ipv4 of a machine you wish to interact with:"),
			increment = 0;

		for (Ipv4 *ipPtr : _ipsPtrs)
			if (increment++ == chosenIpv4)
				attackMenu(routers, ipPtr);
	} while (!ipv4sMenu.leaving());
}

void Net::attackMenu(list<Ipv4 *> routers, const Ipv4 *ip)
{
	Menu optionsMenu;

	if (ip -> getIdentity() == Ipv4::IGNORED)
	{
		cout << "Error: you won't attack yourself" << endl;
		return;
	}

	optionsMenu.addChoice("Spoof");
	optionsMenu.addChoice("Shutdown");
	optionsMenu.addExit();

	do
	{
		switch (optionsMenu.display("Choose the interaction you want to have with it:"))
		{
		case 0:
			//Spoof
			for(const Ipv4 *router: routers)
				spoof(router, ip);
			break;

		case 1:
			//Shutdown
			shutdown(ip);
			break;
		}
	} while (!optionsMenu.leaving());
}

void Net::spoof(const Ipv4 *router, const Ipv4 *target) const
{
	//Linux command

}

void Net::shutdown(const Ipv4 *target) const
{
	//Linux command

}