
#include <windows.h>
#include <iostream>
#include <Winuser.h>

#pragma comment(lib, "Kshield.lib")//Lib directory
using namespace std;
typedef void (*HackCheck)();
BOOL CallDLL()
{
   HackCheck _HackCheck;
   HINSTANCE hInstLibrary = LoadLibrary("Kshield.dll");

   if (hInstLibrary)
   {
	  _HackCheck = (HackCheck)GetProcAddress(hInstLibrary,"DllMain");
      _HackCheck();
   }
   else
   {
      ExitProcess(0);
   }
   return true;
}
/*

int CallDLL(void) 
{ 
    
   HINSTANCE hGetProcIDDLL = LoadLibrary("Kshield.dll"); 

   
   FARPROC lpfnGetProcessID = GetProcAddress(HMODULE (hGetProcIDDLL),"DllMain"); 

   
   typedef int (__stdcall * pICFUNC)(char *, int); 

   pICFUNC MyFunction; 
   MyFunction = pICFUNC(lpfnGetProcessID); 

   
   int intMyReturnVal = MyFunction("ChangePD", 5); 

 
   FreeLibrary(hGetProcIDDLL); 


    return intMyReturnVal; 
}
*/
