#ifndef LOGFATAL_H
#define LOGFATAL_H

#include "LogType.h"
#include "LogStrategy.h"
#include "LogWriter.h"

class LogFatal : public LogStrategy
{
    public:
        void log(std::string message)
        {
            LogWriter* lw = LogWriter::getInstance();
            lw->write(LogType::FATAL, message);
        }
};

#endif