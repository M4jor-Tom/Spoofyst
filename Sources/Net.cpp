#include "../Headers/Net.h"

Net::Net(const string& name, const usi& connectionType, const Ipv4 &userIp, const Ipv4 &gateIp, const usi &mask):
	_name(name),
	_connectionType(connectionType),
	_userIp(Ipv4(userIp)),
	_gateIp(Ipv4(gateIp)),
	_mask(mask)
{
	nmap();
}

void Net::nmap()
{
	//Clearing ips before scanning again
	_ips.clear();

	//Scanning
	stringstream nmapCommand;
	nmapCommand << "nmap -sP " << _userIp.toString();

	string stringyMap = _system(nmapCommand.str().c_str());

	//Linux command [nmap]
	//Getting Ips of the whole network,
	//*It is required to ommit ips of the user and the router
	//*figuring in the class' attributes


	//TESTING
	_ips.push_back(Ipv4(192, 168, 0, 1));// , Ipv4::OTHER));
	_ips.push_back(Ipv4(192, 168, 0, 3));// , Ipv4::OTHER));
	_ips.push_back(Ipv4(192, 168, 0, 4));// , Ipv4::OTHER));
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


	for (const Ipv4 &ip : _ips)
		ipv4sMenu.addChoice(ip.toString());
	
	ipv4sMenu.addExit();

	while (!ipv4sMenu.leaving())
	{
		unsigned int
			chosenIpv4 = ipv4sMenu.display("Choose the Ipv4 of a machine you wish to interact with:"),
			increment = 0;

		for (const Ipv4 &ip : _ips)
			if (increment++ == chosenIpv4)
				attackMenu(routers, ip);
	}
}

void Net::attackMenu(list<Ipv4> routers, const Ipv4 &ip)
{
	Menu optionsMenu;

	optionsMenu.addChoice("Spoof");
	optionsMenu.addChoice("Shutdown");
	optionsMenu.addExit();

	while (!optionsMenu.leaving())
	{
		switch (optionsMenu.display("Choose the interaction you want to have with it:"))
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
	}
}

void Net::spoof(const Ipv4& router, const Ipv4& target) const
{
	//Linux command [arpspoof]

}

void Net::shutdown(const Ipv4& target) const
{
	//Linux command [shutdown]

}