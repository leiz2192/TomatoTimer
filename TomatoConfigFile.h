#ifndef __TOMATOCONFIGFILE_H__
#define __TOMATOCONFIGFILE_H__

#include <QString>

const QString Tomato_Config_File("tomato_config.ini");

class TomatoConfigFile
{
public:
    TomatoConfigFile() {}
    virtual ~TomatoConfigFile() {}

    static void setConfigFile(unsigned int working_time, unsigned int resting_time);
    static bool readConfigFile(unsigned int & working_time, unsigned int & resting_time);
};

#endif  //__TOMATOCONFIGFILE_H__


