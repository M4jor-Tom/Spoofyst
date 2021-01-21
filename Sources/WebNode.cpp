#include "../Headers/WebNode.h"

#include <regex>

const usi
	Net::INET,// = 1,
	Net::ETHER;// = 2;

WebNode::WebNode()
{
	setNetworks();
}

void WebNode::setNetworks()
{
	//Linux command [ifconfig]
	string stringyNetworks = _system("ifconfig -a");// | grep -e '^.*: '

	//Converting string return to:
	//-A list of networks and for each:
	//--User Ip
	//--Router Ip
	//*Regexes*
	regex netNamesRegex("^.+: ");
	string netNames;
	//regex_search(stringyNetworks, netNamesRegex);

	//Storing them into a network array
	//*_networks.push_back(Net(...));*


	//TESTING
	_networks.push_back(Net("eno1", Net::ETHER, Ipv4(192, 168, 1, 2), Ipv4(192, 168, 0, 0), 24));
	_networks.push_back(Net("usb0", Net::ETHER, Ipv4(192, 168, 1, 2), Ipv4(192, 168, 0, 0), 24));
	_networks.push_back(Net("lo", Net::ETHER, Ipv4(192, 168, 1, 2), Ipv4(192, 168, 0, 0), 24));
}

void WebNode::displayNetworks()
{
	Menu networkMenu;

	for(const Net& network : _networks)
		networkMenu.addChoice(network.toString());

	networkMenu.addExit();

	while (!networkMenu.leaving())
	{
		unsigned int
			chosenNetwork = networkMenu.display("Choose a network:"),
			increment = 0;

		for (Net &network : _networks)
			if (increment++ == chosenNetwork)
			{
				network.nmap();
				network.displayIpv4s();
			}
	}
}
