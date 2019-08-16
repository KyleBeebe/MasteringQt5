#ifndef SYSINFO_H
#define SYSINFO_H


class SysInfo
{
public:
    static SysInfo& instance();
    virtual ~SysInfo();

    /**
        Perform OS specific intialization
    */
    virtual void init() = 0;

    /**
        Retrieves the average cpu load

        @return percentage value of average cpu load
    */
    virtual double cpuLoadAverage() = 0;

    /**
        Retrieves the total memory used

        @return percentage value of total memory used
    */
    virtual double memoryUsed() = 0;

    virtual double rawMemoryUsed() = 0;
    virtual double rawMemoryHave() = 0;

protected:
    explicit SysInfo();
    double memoryUsing;
    double memoryTotal;

private:
    SysInfo(const SysInfo& rhs);
    SysInfo& operator=(const SysInfo& rhs);

};

#endif // SYSINFO_H
