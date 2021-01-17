#include "../Headers/WebNode.h"

WebNode::WebNode()
{
	setNetworks();
}

void WebNode::setNetworks()
{
	//Linux command


	//TESTING
	_networks.push_back(Net("eno1", Net::ETHER, Ipv4(192, 168, 1, 2, Ipv4::USER), Ipv4(192, 168, 0, 0, Ipv4::ROUTER), 24));
	_networks.push_back(Net("usb0", Net::ETHER, Ipv4(192, 168, 1, 2, Ipv4::USER), Ipv4(192, 168, 0, 0, Ipv4::ROUTER), 24));
	_networks.push_back(Net("lo", Net::ETHER, Ipv4(192, 168, 1, 2, Ipv4::USER), Ipv4(192, 168, 0, 0, Ipv4::ROUTER), 24));
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