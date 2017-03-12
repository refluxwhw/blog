#ifndef DUMPHELPER_H
#define DUMPHELPER_H

class DumpHelper
{
    DumpHelper();
    DumpHelper(const DumpHelper&){}
    DumpHelper& operator=(const DumpHelper&){}
public:
    static DumpHelper &getInst();
    void init();
};

#endif // DUMPHELPER_H
