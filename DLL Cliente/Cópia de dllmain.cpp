#include <windows.h>
#include <tlhelp32.h>


/* 
Coded By: KyLL3R;
Date: 1/10/2011;
Function: Change ProductVersion on GunBound;
 */

BYTE newdata[]={0x35, 0x45, 0x55, 0x65}; 
DWORD newdatasize = sizeof(newdata);

LPVOID PD_addr =    (void*) 0x004F277F;        // memory address of the PDVersion value in the GunBound process

int main(int argc, char* argv[])
{    
    HANDLE hProcessSnap;    // will store a snapshot of all processes
    HANDLE hProcess = GetCurrentProcess();    // we will use this one for the gb process
    PROCESSENTRY32 pe32;    // stores basic info of a process, using this one to read the ProcessID from
    
    hProcessSnap = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );    // make process snapshot

    pe32.dwSize = sizeof( PROCESSENTRY32 );        // correct size

    Process32First(hProcessSnap, &pe32);    // read info about the first process into pe32

    do    // loop to find the gb process
    {        
        if(strcmp(pe32.szExeFile, "GunBound.exe") == 0)    // if gb was found
        {
            hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID);    // open it, assigning to the hProcess handle
            break;    // break the loop
        }
    }
    while(Process32Next(hProcessSnap, &pe32));    // loop continued until Process32Next deliver NULL or its interrupted with the "break" above

    CloseHandle( hProcessSnap );    // close the handle (just fuckin do it)


    WriteProcessMemory(hProcess,PD_addr, &newdata, newdatasize, NULL);


    return 0;    // THE END
}

extern "C"
{
    __declspec(dllexport) BOOL __stdcall WINAPI DllMain (HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
    {
        switch (dwReason)
        {
        case DLL_PROCESS_ATTACH:
            DisableThreadLibraryCalls (hModule);
            CreateThread (0,0, (LPTHREAD_START_ROUTINE)main, 0, 0, 0);
            break;
        case DLL_PROCESS_DETACH:
            //Module is being detached now.
            break;
        }
        return TRUE;
    }
}

