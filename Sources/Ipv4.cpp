#include "../Headers/Ipv4.h"
#include "../Stringyst/Headers/Stringyst.h"

#include <sstream>

using namespace std;

Ipv4::Ipv4()
{
	_words.reserve(4);
}

Ipv4::Ipv4(const string &stringyIp):
	Ipv4()
{
	_words = readIp(stringyIp);
}

Ipv4::Ipv4(const usi& word1, const usi& word2, const usi& word3, const usi& word4):
	Ipv4()
{
	_words[0] = word1;
	_words[1] = word2;
	_words[2] = word3;
	_words[3] = word4;
}

Ipv4::Ipv4(const Ipv4 &toCopy):
	Ipv4()
{
	_words[0] = toCopy._words[0];
	_words[1] = toCopy._words[1];
	_words[2] = toCopy._words[2];
	_words[3] = toCopy._words[3];
}

string Ipv4::toString() const
{
	//cout << "IP words:  " << _words[0] << "." << _words[1] << "." << _words[2] << "." << _words[3] << endl;
	//cout << "IP string: " << toSstream().str() << endl;
	return toSstream().str();
}

stringstream Ipv4::toSstream() const
{
	stringstream _toSstream;
	usi i = 0;
	for(; i < 4; i++)//(usi word : _words)
	{
		_toSstream << _words[i];
		if (i != 4 - 1)
			_toSstream << ".";
	}
	
	return _toSstream;
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