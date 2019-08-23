#ifndef SYSINFOLINUX_H
#define SYSINFOLINUX_H

#include <QtGlobal>
#include <QVector>

#include "SysInfo.h"

class SysInfoLinux : public SysInfo
{
public:
    SysInfoLinux();

    void init() override;
    double cpuLoadAverage() override;
    double memoryUsed() override;
    double rawMemoryUsed() override;
    double rawMemoryHave() override;

private:
    QVector<qulonglong> cpuRawData();
    QVector<qulonglong> mCpuLoadLastValues;
};

#endif // SYSINFOLINUX_H
