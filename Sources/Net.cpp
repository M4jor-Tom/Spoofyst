#include "../Headers/Net.h"

Net::Net(const string& name, const usi& connectionType, const usi &mask):
	_name(name),
	_connectionType(connectionType),
	_mask(mask)
{
	nmap();
}

void Net::nmap()
{
	//TESTING
	_ips.clear();
	_ips.push_back(Ipv4(192, 168, 0, 0, Ipv4::ROUTER));
	_ips.push_back(Ipv4(192, 168, 0, 1, Ipv4::OTHER));
	_ips.push_back(Ipv4(192, 168, 0, 2, Ipv4::USER));
	_ips.push_back(Ipv4(192, 168, 0, 3, Ipv4::OTHER));
	_ips.push_back(Ipv4(192, 168, 0, 4, Ipv4::OTHER));
}

string Net::toString() const
{
	return _name;
}

size_t Net::getIpCount() const
{
	return _ips.size();
}

void Net::displayIpv4s()
{
	Menu ipv4sMenu;
	list<Ipv4> routers;

	for (const Ipv4& ip : _ips)
		if (ip.getIdentity() == Ipv4::OTHER)
			ipv4sMenu.addChoice(ip.toString());
		else if(ip.getIdentity() == Ipv4::ROUTER)
			routers.push_back(ip);
	
	ipv4sMenu.addExit();

	do
	{
		unsigned int
			chosenIpv4 = ipv4sMenu.display(),
			increment = 0;

		for (Ipv4& ip : _ips)
			if (increment++ == chosenIpv4)
				attackMenu(routers, ip);
	} while (!ipv4sMenu.leaving());
}

void Net::attackMenu(list<Ipv4> routers, const Ipv4 &ip)
{
	Menu optionsMenu;

	optionsMenu.addChoice("Spoof");
	optionsMenu.addChoice("Shutdown");
	optionsMenu.addExit();

	do
	{
		switch (optionsMenu.display())
		{
		case 0:
			//Spoof
			for(const Ipv4 &router: routers)
				spoof(router, ip);
			break;

		case 1:
			//Shutdown
			shutdown(ip);
			break;
		}
	} while (!optionsMenu.leaving());
}

void Net::spoof(const Ipv4& router, const Ipv4& target) const
{
	//Linux command

}

void Net::shutdown(const Ipv4& target) const
{
	//Linux command

	//Windows command

}