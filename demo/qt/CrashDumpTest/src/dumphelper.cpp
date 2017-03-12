#include "dumphelper.h"

#ifndef __unix__
#  include <Windows.h>
#else
#  include <execinfo.h>
#endif

#include <DbgHelp.h>
#include <stdlib.h>

DumpHelper::DumpHelper()
{

}

DumpHelper &DumpHelper::getInst()
{
    static DumpHelper obj;
    return obj;
}

inline BOOL IsDataSectionNeeded(const WCHAR* pModuleName)
{
    if (pModuleName == 0)
    {
        return FALSE;
    }

    WCHAR szFileName[_MAX_FNAME] = L"";
    _wsplitpath(pModuleName, NULL, NULL, szFileName, NULL);

    if (_wcsicmp(szFileName, L"ntdll") == 0)
        return TRUE;

    return FALSE;
}

inline BOOL CALLBACK MiniDumpCallback(PVOID                            pParam,
                                      const PMINIDUMP_CALLBACK_INPUT   pInput,
                                      PMINIDUMP_CALLBACK_OUTPUT        pOutput)
{
    if (pInput == 0 || pOutput == 0)
        return FALSE;

    switch (pInput->CallbackType)
    {
        case ModuleCallback:
            if (pOutput->ModuleWriteFlags & ModuleWriteDataSeg)
                if (!IsDataSectionNeeded(pInput->Module.FullPath))
                    pOutput->ModuleWriteFlags &= (~ModuleWriteDataSeg);
        case IncludeModuleCallback:
        case IncludeThreadCallback:
        case ThreadCallback:
        case ThreadExCallback:
            return TRUE;
        default:;
    }

    return FALSE;
}

inline void CreateMiniDump(PEXCEPTION_POINTERS pep, LPCTSTR strFileName)
{
    HANDLE hFile = CreateFile(strFileName, GENERIC_READ | GENERIC_WRITE,
                              FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    if ((hFile != NULL) && (hFile != INVALID_HANDLE_VALUE))
    {
        MINIDUMP_EXCEPTION_INFORMATION mdei;
        mdei.ThreadId = GetCurrentThreadId();
        mdei.ExceptionPointers = pep;
        mdei.ClientPointers = NULL;

        MINIDUMP_CALLBACK_INFORMATION mci;
        mci.CallbackRoutine = (MINIDUMP_CALLBACK_ROUTINE)MiniDumpCallback;
        mci.CallbackParam = 0;

        ::MiniDumpWriteDump(::GetCurrentProcess(), ::GetCurrentProcessId(), hFile, MiniDumpNormal, (pep != 0) ? &mdei : 0, NULL, &mci);

        CloseHandle(hFile);
    }
}

LONG __stdcall MyUnhandledExceptionFilter(PEXCEPTION_POINTERS pExceptionInfo)
{
    CreateMiniDump(pExceptionInfo, L"core.dmp");
    /*printf("Error   address   %x/n", pExceptionInfo->ExceptionRecord->ExceptionAddress);
    printf("CPU   register:/n");
    printf("eax   %x   ebx   %x   ecx   %x   edx   %x/n", pExceptionInfo->ContextRecord->Eax,
        pExceptionInfo->ContextRecord->Ebx, pExceptionInfo->ContextRecord->Ecx,
        pExceptionInfo->ContextRecord->Edx);*/
    return EXCEPTION_EXECUTE_HANDLER;
}

// 此函数一旦成功调用，之后对 SetUnhandledExceptionFilter 的调用将无效
//void DisableSetUnhandledExceptionFilter()
//{
//    void* addr = (void*)GetProcAddress(LoadLibrary(L"kernel32.dll"),
//        "SetUnhandledExceptionFilter");
//
//    if (addr)
//    {
//        unsigned char code[16];
//        int size = 0;
//
//        code[size++] = 0x33;
//        code[size++] = 0xC0;
//        code[size++] = 0xC2;
//        code[size++] = 0x04;
//        code[size++] = 0x00;
//
//        DWORD dwOldFlag, dwTempFlag;
//        VirtualProtect(addr, size, PAGE_READWRITE, &dwOldFlag);
//        WriteProcessMemory(GetCurrentProcess(), addr, code, size, NULL);
//        VirtualProtect(addr, size, dwOldFlag, &dwTempFlag);
//    }
//}

void DumpHelper::init()
{
#ifndef __unix__
    SetUnhandledExceptionFilter(MyUnhandledExceptionFilter);
#else
    int backtrace(void **buffer, int size);
    char **backtrace_symbols(void *const *buffer, int size);
    void backtrace_symbols_fd(void *const *buffer, int size, int fd);
#endif
}
