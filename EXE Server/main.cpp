#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <iostream>

/**

Arquivo codado por KyLL3R. (BETA)



int Memory(char Caption[], int long Address, int Value, bool _w)
{
    DWORD PROC_ID;
    HANDLE PROC_HANDLE;

    GetWindowThreadProcessId(FindWindow(NULL, (LPCTSTR)Caption), &PROC_ID);
    PROC_HANDLE = OpenProcess(PROCESS_ALL_ACCESS, false, PROC_ID);
    if(_w)
        WriteProcessMemory(PROC_HANDLE, (LPVOID)Address, &Value, sizeof(long int), NULL);
    else
        ReadProcessMemory(PROC_HANDLE, (LPVOID)Address, &Value, sizeof(long int), NULL);
    CloseHandle(PROC_HANDLE);
    return Value;
}

*/

extern "C" __declspec(dllexport) void DLLE(){
    
    HWND hWnd = FindWindow(0, "GBGMGAME"); 
    DWORD proc_id; 

         		GetWindowThreadProcessId(hWnd, &proc_id); 

         		HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, proc_id); 
      
      
      BYTE newdata[]={0x35, 0x45, 0x55, 0x65}; 
             			DWORD newdatasize = sizeof(newdata); 

      
    
    WriteProcessMemory(hProcess, (LPVOID)0x004F277F, &newdata, newdatasize, NULL);
    

}
