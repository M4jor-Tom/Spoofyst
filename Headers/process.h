#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>

using namespace std;

//Is windows the compiling os ?
#if __has_include(<unistd.h>)
#else
FILE* __cdecl popen(const char* _Command, const char* _Mode);
int __cdecl pclose(FILE* _Stream);
#endif

string _system(const char* cmd);