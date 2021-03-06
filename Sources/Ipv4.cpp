#include "../Headers/Ipv4.h"
#include "../Stringyst/Headers/Stringyst.h"
#include "../Menu/unicommand/Headers/unicommand.h"

#include <sstream>

#include <unistd.h>
#include <limits.h>

#include <signal.h>
#include <sys/wait.h>

using namespace std;

Ipv4::Ipv4(const string &stringyIp, const string &label):
	_label(label), _attackerPid(0)
{
	_words.reserve(4);
	_words = readIp(stringyIp);
}

Ipv4::Ipv4(const usi& word1, const usi& word2, const usi& word3, const usi& word4, const string &label):
	_label(label), _attackerPid(0)
{
	_words.reserve(4);
	_words[0] = word1;
	_words[1] = word2;
	_words[2] = word3;
	_words[3] = word4;
}

Ipv4::Ipv4(const Ipv4 &toCopy):
	_label(toCopy._label), _attackerPid(toCopy._attackerPid)
{
	_words.reserve(4);
	_words[0] = toCopy._words[0];
	_words[1] = toCopy._words[1];
	_words[2] = toCopy._words[2];
	_words[3] = toCopy._words[3];
}

Ipv4::~Ipv4()
{
	if(getAttackerPid() != 0)
	{
		//In case an attack is still running, stopping it
		kill(_attackerPid, SIGINT);

		//Waiting for current attack to stop
		cout << Text::textEffect(Text::BLINK, "Stopping attack on " + toString(true));
		_getch();
		wait(NULL);

		//Clearing screen once finished
		system(clearCommand.c_str());
	}
}

bool Ipv4::setAttackerPid(const pid_t attackerPid)
{
	if(_attackerPid == 0)
		_attackerPid = attackerPid;
	else
		return false;
	
	return true;
}

string Ipv4::getLabel() const
{
	return _label;
}

string Ipv4::toString(bool label) const
{
	//cout << "IP words:  " << _words[0] << "." << _words[1] << "." << _words[2] << "." << _words[3] << endl;
	//cout << "IP string: " << toSstream().str() << endl;
	return toSstream(label).str();
}

stringstream Ipv4::toSstream(bool label) const
{
	stringstream _toSstream;
	
	usi i = 0;
	for(; i < 4; i++)//(usi word : _words)
	{
		_toSstream << _words[i];
		if (i != 4 - 1)
			_toSstream << ".";
	}

	if(label)
		_toSstream << "\t[" << _label << "]";
	
	return _toSstream;
}

pid_t Ipv4::getAttackerPid() const
{
	return _attackerPid;
}

vector<usi> Ipv4::readIp(const string &stringyIp)
{
	vector<string> stringyExplodedIp = vExplode(".", trim(stringyIp, " \n\r"));
	vector<usi> explodedIp;

	for(string word : stringyExplodedIp)
		if(str_isdigit(word))
			explodedIp.push_back(stoul(word));
		else
		{
			cout << "readIp: Invalid mask provided: " << stringyIp << endl;
			throw "non-numeric word";
		}
	
	return explodedIp;
}

string Ipv4::getHostName()
{
	char cHostName[HOST_NAME_MAX];
	gethostname(cHostName, HOST_NAME_MAX);
	
	return string(cHostName);
}