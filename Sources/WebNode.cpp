#include "../Headers/WebNode.h"
#include "../Menu/unicommand/Headers/unicommand.h"

#include <regex>
#include <sstream>

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
	cout << "Scanning available networks..." << endl;
	string stringyNetworks = _system("ifconfig -a");// | grep -e '^.*: '
	system(clearCommand.c_str());

	//Converting string return to:
	//-A list of networks and for each:
	//--User Ip
	//--Router Ip
	//*Regexes*
	regex netNamesRegex("^(.+): ");
	smatch netNamesMatches;
	string delimiter = " ";

	/*stringstream results;
	regex wsaq_re("\\s+");
	copy(
		sregex_token_iterator(stringyNetworks.begin(), stringyNetworks.end(), wsaq_re, -1),
		sregex_token_iterator(),
		ostream_iterator<string>(results, delimiter)
	);

	string token = results.str().substr(0, results.str().find(delimiter));*/
	size_t pos = 0;
	string token;
	while ((pos = stringyNetworks.find(delimiter)) != string::npos)
	{
		token = stringyNetworks.substr(0, pos);
		if(regex_search(stringyNetworks, netNamesMatches, netNamesRegex))
			;//cout << token << endl;
		stringyNetworks.erase(0, pos + delimiter.length());
	}
	//auto stringyNetworksBegin = 
	//if(regex_search(stringyNetworks, netNamesMatches, netNamesRegex))
		/*for(
			auto it = cregex_iterator(stringyNetworks, stringyNetworks + stringyNetworks.size(), netNamesRegex);
            it != cregex_iterator();
           	++it
		)*/
		//cout << *it.str() << endl;
		//cout << netNamesMatches.str() << endl;
	//else
		//throw "Invalid result from from ifconfig";

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
