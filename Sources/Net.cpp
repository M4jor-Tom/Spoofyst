#include "../Headers/Net.h"
#include "../Stringyst/Headers/Stringyst.h"
#include "../Menu/unicommand/Headers/unicommand.h"

#include <bitset>

Net::Net(const string& name, const usi& connectionType, const Ipv4 &userIp, const Ipv4 &gateIp, const usi &mask):
	_name(name),
	_userIp(Ipv4(userIp)),
	_gateIp(Ipv4(gateIp)),
	_mask(mask),
	_connectionType(connectionType)
{
	//Scan network when creating
	//nmap();
}

void Net::nmap()
{
	//Clearing ips before scanning again
	_ips.clear();

	//writing nmap command
	stringstream nmapCommand;
	nmapCommand << "nmap -sP " << _userIp.toString() << "/" << _mask;

	//Scanning network
	//cout << nmapCommand.str();
	system(clearCommand.c_str());
	cout << "[" << _name << "] Scanning network..." << endl;
	string stringyMap = _system(nmapCommand.str().c_str());
	system(clearCommand.c_str());

	//Extracting Ips from nmap commandline echoes
	

	//TESTING
	_ips.push_back(Ipv4(192, 168, 0, 1));
	_ips.push_back(Ipv4(192, 168, 0, 3));
	_ips.push_back(Ipv4(192, 168, 0, 4));
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

	for(const Ipv4 &ip : _ips)
		//{cout << ip.toString(); _getch();}
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

usi Net::maskToUsi(const string &stringyMask)
{
	vector<usi> explodedMask = Ipv4::readIp(stringyMask);

	return maskToUsi(
		explodedMask[0],
		explodedMask[1],
		explodedMask[2],
		explodedMask[3]
	);
}

usi Net::maskToUsi(const usi &word1, const usi &word2, const usi &word3, const usi &word4)
{
	//Mask's bits consist in 4 bytes
	vector<bitset<8>> words =
	{
		bitset<8>(word1),
		bitset<8>(word2),
		bitset<8>(word3),
		bitset<8>(word4)
	};
	
	//Counting bits
	usi sIndex, bIndex, ret = 0;
	for(sIndex = 0; sIndex < 4; sIndex++)
		//For each byte
		for(bIndex = 7; bIndex > 0; bIndex--)
			//For each bit
			if(words[sIndex].test(bIndex) == true)
				//Sum
				ret++;
			else
				//Return
				//I don't know why, but an offset of -3 has to be compensated
				return ret + 3;

	return 64;
}