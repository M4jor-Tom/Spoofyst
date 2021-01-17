#include "../Headers/Ipv4.h"
#include <sstream>
#include <string>

using namespace std;

Ipv4::Ipv4(const usi& word1, const usi& word2, const usi& word3, const usi& word4, const usi &who):
	_who(who)
{
	_words[0] = word1;
	_words[1] = word2;
	_words[2] = word3;
	_words[3] = word4;
}

Ipv4::Ipv4(const Ipv4 &toCopy):
	_who(toCopy._who)
{
	_words[0] = toCopy._words[0];
	_words[1] = toCopy._words[1];
	_words[2] = toCopy._words[2];
	_words[3] = toCopy._words[3];
}

string Ipv4::toString() const
{
	return toSstream().str();
}

stringstream Ipv4::toSstream() const
{
	stringstream _toSstream;
	usi i = 0;
	for (usi word : _words)
	{
		_toSstream << word;
		if (++i != sizeof(_words) / sizeof(usi))
			_toSstream << ".";
	}

	/*if (_who == Ipv4::ROUTER)
		_toSstream << "[ROUTER]";
	else if (_who == Ipv4::USER)
		_toSstream << "[YOU]";
	else
		_toSstream << "[SOMEONE]";*/

	return _toSstream;
}

/*
usi Ipv4::getIdentity() const
{
	return _who;
}*/