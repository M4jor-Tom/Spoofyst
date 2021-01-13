#include "../Headers/Ipv4.h"
#include <sstream>
#include <string>

using namespace std;

Ipv4::Ipv4(const usi& word1, const usi& word2, const usi& word3, const usi& word4, const usi& mask):
	_mask(mask)
{
	_words[0] = word1;
	_words[1] = word2;
	_words[2] = word3;
	_words[3] = word4;
}

string Ipv4::toString() const
{
	stringstream _toStream;
	usi i = 0;
	for(usi word: _words)
	{
		_toStream << word;
		if (++i == sizeof(_words) / sizeof(usi))
			_toStream << "/" << _mask;
		else
			_toStream << ".";
	}

	string _toString = _toStream.str();
	return _toString;
}