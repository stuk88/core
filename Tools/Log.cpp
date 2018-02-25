#include "Log.h"
#include "../FS/FS.h"

std::mutex Log::logLock;

Log::Log(uint8_t level) {

    char cPath[1024];

    std::chrono::seconds us = std::chrono::duration_cast< std::chrono::seconds >(
            std::chrono::system_clock::now().time_since_epoch()
    );

    this->logLevel = level;
    switch (this->logLevel) {
        case LOG_LEVEL_ERROR: {

            FS::charPathFromVectorPath(cPath, FS::concatPaths(FS::getLogPath(), "ERROR.txt"));

            fb.open(cPath, std::ios_base::app);
            std::ostream newStream(&fb);
            currentStream = new std::ostream(&fb);

            *currentStream << "[" << "ERROR " << (uint64_t)us.count() <<  "] ";
            *currentStream << "(" << std::hash<std::thread::id>()(std::this_thread::get_id()) % 100000 << ") ";
            std::cout << "[" << "ERROR " << (uint64_t)us.count() <<  "] ";
            std::cout << "(" << std::hash<std::thread::id>()(std::this_thread::get_id()) % 100000 << ") ";
            break;
        }
        case LOG_LEVEL_INFO: {

            FS::charPathFromVectorPath(cPath, FS::concatPaths(FS::getLogPath(), "INFO.txt"));

            fb.open(cPath, std::ios_base::app);
            std::ostream newStream(&fb);
            currentStream = new std::ostream(&fb);

            *currentStream << "[" << "INFO " << (uint64_t)us.count() << "]    ";
            *currentStream << "(" << std::hash<std::thread::id>()(std::this_thread::get_id()) % 100000 << ") ";
            std::cout << "[" << "INFO " << (uint64_t)us.count() <<  "] ";
            std::cout << "(" << std::hash<std::thread::id>()(std::this_thread::get_id()) % 100000 << ") ";
            break;
        }
        case LOG_LEVEL_CRITICAL_ERROR: {

            FS::charPathFromVectorPath(cPath, FS::concatPaths(FS::getLogPath(), "CRITICAL.txt"));

            fb.open(cPath, std::ios_base::app);
            std::ostream newStream(&fb);
            currentStream = new std::ostream(&fb);

            *currentStream << "[" << "CRITICAL " << (uint64_t)us.count() <<  "] ";
            *currentStream << "(" << std::hash<std::thread::id>()(std::this_thread::get_id()) % 100000 << ") ";
            std::cout << "[" << "CRITICAL " << (uint64_t)us.count() <<  "] ";
            std::cout << "(" << std::hash<std::thread::id>()(std::this_thread::get_id()) % 100000 << ") ";
            break;
        }
        case LOG_LEVEL_NOTICE: {

            FS::charPathFromVectorPath(cPath, FS::concatPaths(FS::getLogPath(), "NOTICE.txt"));

            fb.open(cPath, std::ios_base::app);
            std::ostream newStream(&fb);
            currentStream = new std::ostream(&fb);

            *currentStream << "[" << "NOTICE " << (uint64_t)us.count() <<  "] ";
            *currentStream << "(" << std::hash<std::thread::id>()(std::this_thread::get_id()) % 100000 << ") ";
            std::cout << "[" << "NOTICE " << (uint64_t)us.count() <<  "] ";
            std::cout << "(" << std::hash<std::thread::id>()(std::this_thread::get_id()) % 100000 << ") ";
            break;
        }
        case LOG_LEVEL_WARNING: {

            FS::charPathFromVectorPath(cPath, FS::concatPaths(FS::getLogPath(), "WARNING.txt"));

            fb.open(cPath, std::ios_base::app);
            std::ostream newStream(&fb);
            currentStream = new std::ostream(&fb);

            *currentStream << "[" << "WARNING " << (uint64_t)us.count() <<  "] ";
            *currentStream << "(" << std::hash<std::thread::id>()(std::this_thread::get_id()) % 100000 << ") ";
            std::cout << "[" << "WARNING " << (uint64_t)us.count() <<  "] ";
            std::cout << "(" << std::hash<std::thread::id>()(std::this_thread::get_id()) % 100000 << ") ";
            break;
        }
    }
}

Log& Log::operator<<(CDataStream obj)
{
    std::cout << Hexdump::vectorToHexString(std::vector<unsigned char>(obj.data(), obj.data() + obj.size()));
    *currentStream << Hexdump::vectorToHexString(std::vector<unsigned char>(obj.data(), obj.data() + obj.size()));
    return *this;
}

Log& Log::operator<<(std::vector<unsigned char> obj)
{
    std::cout << Hexdump::vectorToHexString(obj);
    *currentStream << Hexdump::vectorToHexString(obj);
    return *this;
}

Log& Log::operator<<(const char* obj)
{
    std::cout << obj;
    *currentStream << obj;
    return *this;
}

Log& Log::operator<<(const unsigned char* obj)
{
    std::cout << obj;
    *currentStream << obj;
    return *this;
}


Log& Log::operator<<(std::string obj)
{
    std::cout << obj;
    *currentStream << obj;
    return *this;
}

Log& Log::operator<<(uint32_t obj)
{
    std::cout << obj;
    *currentStream << obj;
    return *this;
}

#if defined(_WIN32) || defined(__APPLE__)
Log& Log::operator<<(uint64_t obj)
{
    std::cout << obj;
    *currentStream << obj;
    return *this;
}
#endif

Log& Log::operator<<(float obj)
{
    std::cout << obj;
    *currentStream << obj;
    return *this;
}

#if defined(__linux__)
Log& Log::operator<<(size_t obj)
{
    std::cout << obj;
    *currentStream << obj;
    return *this;
}
#endif

Log& Log::operator<<(int obj)
{
    std::cout << obj;
    *currentStream << obj;
    return *this;
}

Log& Log::operator<<(bool obj)
{
    if(obj) {
        std::cout << "true";
        *currentStream << "true";
    } else {
        std::cout << "false";
        *currentStream << "false";
    }
    return *this;
}

Log& Log::operator<<(UAmount obj)
{
    for (std::map<uint8_t, CAmount>::const_iterator it(obj.map.begin()); it != obj.map.end(); ++it) {
        std::cout << "[" << (int)it->first << ":" << it->second << "]";
        *currentStream << "[" << (int)it->first << ":" << it->second << "]";
    }
    return *this;
}

Log& Log::operator<<(UAmount32 obj)
{
    for (std::map<uint8_t, CAmount32>::const_iterator it(obj.map.begin()); it != obj.map.end(); ++it) {
        std::cout << "[" << (int)it->first << ":" << it->second << "]";
        *currentStream << "[" << (int)it->first << ":" << it->second << "]";
    }
    return *this;
}

Log::~Log()
{
    logLock.lock();
    std::cout << std::endl;
    *currentStream << std::endl;
    fb.close();

    logLock.unlock();
}
