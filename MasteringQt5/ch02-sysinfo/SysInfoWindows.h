#ifndef SYSINFOWINDOWS_H
#define SYSINFOWINDOWS_H

#include "SysInfo.h"

#include <QtGlobal>
#include <QVector>

//forward declare FILETIME syntax
typedef struct _FILETIME FILETIME;

class SysInfoWindows : public SysInfo
{
public:
    SysInfoWindows();

    void init() override;
    double cpuLoadAverage() override;
    double memoryUsed() override;
    double rawMemoryUsed() override;
    double rawMemoryHave() override;


private:

    /**
        Get system-timing information

        @return three values (amount of time spent idle, in kernel, in user mode )
    */
    QVector<qulonglong> cpuRawData();

    /**
        Converts Windows FILETIME struct syntax to a qulonglong type

        @return qulonglong representation of Windows FILETIME struct
    */
    qulonglong convertFileTime(const FILETIME& filetime) const;

private:
    QVector<qulonglong> mCpuLoadLastValues;
};

#endif // SYSINFOWINDOWS_H
