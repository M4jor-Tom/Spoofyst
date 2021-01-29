#include "../Headers/WebNode.h"
#include "../Menu/unicommand/Headers/unicommand.h"
#include "../Stringyst/Headers/Stringyst.h"

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

	//May use netstat instead of ifconfig
	string
		stringyNetworks = _system("ifconfig -a"),
		stringyGate = _system("ip route | grep default");
	vector<string> vectyGate = vExplode(" ", stringyGate);
	string
		stringyGateIpv4 = vectyGate[2],
		mainNetName = vectyGate[4];

	system(clearCommand.c_str());

	/*cout
		<< "main: " << mainNetName << endl
		<< "stringyGateIpv4: " << stringyGateIpv4 << endl;*/

	//Converting string return to:
	//-A list of networks and for each:
	//--User Ip
	//--Router Ip
	size_t startCursor = 0, endCursor = 0, infoEndCursor = 0;
	while(infoEndCursor != string::npos)
	{
		//First we check where are the last informations to look for, to avoid messingly looking further
		//"collisions" is a word appearing at the end of each network display
		infoEndCursor = stringyNetworks.find("collisions ", startCursor + 1);

		//Then we look for the length of the network name
		//Getting name
		endCursor = stringyNetworks.find(":", startCursor);
		string netName = stringyNetworks.substr(startCursor, endCursor - startCursor);
		startCursor = endCursor;

		string inetString = "inet ", maskString = "netmask ";
		if((startCursor = stringyNetworks.find(inetString, startCursor)) < infoEndCursor)
		{
			//If there's an inet, there's an Ipv4 to hack (maybe)
			//Getting Ipv4
			endCursor = stringyNetworks.find(maskString, startCursor);
			string stringyUserIpv4 = stringyNetworks.substr(
				startCursor + inetString.size(),
				endCursor - startCursor - inetString.size()
			);
			startCursor = endCursor;

			//Getting netmask
			endCursor = stringyNetworks.find(" ", startCursor);
			string stringyMask = stringyNetworks.substr(
				startCursor + maskString.size(),
				endCursor - startCursor + maskString.size()
			);
			startCursor = endCursor;

			//Printing info
			/*cout
				<< "netName: " << netName << endl
				<< "netMask: " << stringyMask << endl
				<< "userIpv4: " << stringyUserIpv4 << endl
				<< "gateIpv4: " << stringyGateIpv4 << endl;*/
			
			//Storing them into a network list if router ip is found
			if(mainNetName == netName)
				_networks.push_back(
					Net(
						netName,
						Net::INET,
						Ipv4(stringyUserIpv4),
						Ipv4(stringyGateIpv4),
						Net::maskToUsi(stringyMask)
					)
				);
		}
		else if(infoEndCursor != string::npos)
		{
			//Ending loop
			endCursor = infoEndCursor;

			//Skipping "collisions" word
			while(isalpha(stringyNetworks[endCursor]))
				endCursor++;
			
			//Skipping whitespace between "collisions" and collisions count
			endCursor++;

			//Skipping collisions count
			while(isdigit(stringyNetworks[endCursor]))
				endCursor++;
			
			//Skipping carriage returns
			endCursor += 2;

			startCursor = endCursor;
		}

		/*cout
			<< "loop end: " << endl
			<< "startCursor: " << startCursor << endl
			<< "endCursor: " << endCursor << endl
			<< "infoEndCursor: " << infoEndCursor << endl;*/
	}


	//TESTING
	/*_networks.push_back(Net("eno1", Net::ETHER, Ipv4(192, 168, 1, 2), Ipv4(192, 168, 0, 0), 24));
	_networks.push_back(Net("usb0", Net::ETHER, Ipv4(192, 168, 1, 2), Ipv4(192, 168, 0, 0), 24));
	_networks.push_back(Net("lo", Net::ETHER, Ipv4(192, 168, 1, 2), Ipv4(192, 168, 0, 0), 24));*/
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
