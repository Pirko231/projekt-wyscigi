#include "raport.h"

void perf::Report::logMessage(std::string _message)
{
    if (this->file.is_open())
        this->file << "!-- " << _message << " --!" << "\n";
}

void perf::Report::addEntry(std::string _entry, bool _status)
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
}

perf::Report::~Report()
{
    if(this->file.is_open())
        this->file.close();
}
