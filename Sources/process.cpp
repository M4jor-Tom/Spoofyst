#include "../Headers/process.h"

//Check if _popen / _pclose or popen/pclose shall be used
//Is windows the compiling os ?
#if __has_include(<unistd.h>)
#else
FILE* __cdecl popen(const char *_Command, const char *_Mode)
{
    return _popen(_Command, _Mode);
}

int __cdecl pclose(FILE* _Stream)
{
    return _pclose(_Stream);
}
#endif

string _system(const char* cmd)
{
    //Buffer, return and pipe initialization
    array<char, 128> buffer;
    string result;
    unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);

    //Pipe status checkings
    if(!pipe)
        throw runtime_error("Error while trying to reading system command data.");

    //Reading command data
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
        result += buffer.data();

    //Returning
    return result;
}