#include "../Headers/WebNode.h"

WebNode::WebNode()
{
	setNetworks();
}

void WebNode::setNetworks()
{
	//TESTING
	_networks.push_back(Net("eno1", Net::ETHER, 24));
	_networks.push_back(Net("usb0", Net::ETHER, 24));
	_networks.push_back(Net("lo", Net::ETHER, 24));
}

void WebNode::displayNetworks()
{
	Menu networkMenu;

	for(const Net& network : _networks)
		networkMenu.addChoice(network.toString());

	networkMenu.addExit();

	do
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
	} while (!networkMenu.leaving());
}