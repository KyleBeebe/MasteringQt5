#ifndef SYSINFOLINUX_H
#define SYSINFOLINUX_H

#include <QtGlobal>

#include "SysInfo.h"

class SysInfoLinux : public SysInfo
{
public:
    SysInfoLinux();

    void init() override;
    double cpuLoadAverage() override;
    double memoryUsed() override;

private:
    QVector<qulonglong> cpuRawData();
    QVector<qulonglong> mCpuLoadLastValues;
};

#endif // SYSINFOLINUX_H
