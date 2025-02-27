#include "raport.h"

void Report::logMessage(std::string _message)
{
    if (this->file.is_open())
        this->file << "!-- " << _message << " --!" << "\n";
    else
        throw FileCouldNotOpen{this->fileName};
}

void Report::addEntry(std::string _entry, bool _status)
{
    if (!_status)
        this->status = false;
    if (this->file.is_open())
    {
        this->file << "-- " << _entry << " -- STATUS - ";
        if (_status)
            this->file << "SUCCESS";
        else
            this->file << "FAILURE";
        this->file << " --\n";
    }
    else
        throw FileCouldNotOpen{this->fileName};
}

Report::~Report()
{
    if(this->file.is_open())
        this->file.close();
}
