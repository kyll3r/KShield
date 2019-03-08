#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <stdio.h>
#include "config.h"
#include "systemdir.h"

#define SERVICENAME "EXEHIDE" // The display name of the driver.


//function for Instalation driver
int InstallDriver(char* SYSFILE)
{
	SC_HANDLE SCManager = 0; 
	SC_HANDLE SERVICE = 0;

	SCManager = OpenSCManager(NULL, NULL, SC_MANAGER_CREATE_SERVICE);

	if(SCManager){
	SERVICE = CreateService(SCManager, SERVICENAME, "Driver Description", SERVICE_ALL_ACCESS, SERVICE_KERNEL_DRIVER, SERVICE_BOOT_START, SERVICE_ERROR_IGNORE, SYSFILE, NULL, NULL, NULL, NULL, NULL);
	
	if(!SERVICE){
	//printf("Error Initializing Driver!");
	return 0; 
	}

	if(SERVICE){
	StartService(SERVICE, 0, NULL);
	//printf("The driver has been installed!");
	}
	}
	else 
	{
	return 0; 
	}
	return 0;
}//end


//Function for check version the current windows
bool Checkwinver() {
    DWORD version = GetVersion();
    DWORD maior = (DWORD) (LOBYTE(LOWORD(version)));
    DWORD menor = (DWORD) (HIBYTE(LOWORD(version)));
    
    
    if((maior > 6) || ((maior == 6) && (menor >= 1))){
              AlterDir(1);
            InstallDriver(final);
            } 
            
            else if((maior > 5) || ((maior == 5) && (menor >= 1))){
                 AlterDir(2);
            InstallDriver(final);
            
            } 
            else{
                 AlterDir(2);
                 InstallDriver(final);
                 }
                 
    return 0;
    
}//end


//Function for checking status Driving
int CheckDriver()
{
    
    
    SC_HANDLE SCManager = 0; 
	SC_HANDLE SERVICE = 0;
	SERVICE_STATUS SS; 

	SCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	SERVICE = OpenService(SCManager, SERVICENAME, SERVICE_ALL_ACCESS);


        if ( !QueryServiceStatus( SERVICE, &SS) )
        {

             MessageBox(NULL, "Um Drive do jogo foi alterado. \nEfetue a re-instalação do mesmo.", "KyLL3R Game Shield!", MB_OK | MB_ICONEXCLAMATION);
             ExitProcess(1);


        }

        else if ( SS.dwCurrentState == SERVICE_STOPPED ){
             MessageBox(NULL, "Um Drive do jogo foi alterado(2). \nEfetue a re-instalação do mesmo.", "KyLL3R Game Shield!", MB_OK | MB_ICONEXCLAMATION);
             ExitProcess(1);
            
            }
            
            else {
                 //printf("Started");
                 }
       
	return 0;
}//end


//function for detect Virtual Machine

char* sProduct[] = { "*VMWARE*", "*VBOX*", "*VIRTUAL*", "*QEMU*"};    

bool DetectVM() 
{ 
    HKEY hKey; 
    char szBuffer[64];  
    unsigned long hSize = sizeof(szBuffer) - 1; 
	
    if (RegOpenKeyEx( HKEY_LOCAL_MACHINE, "SYSTEM\\ControlSet001\\Services\\Disk\\Enum", 0, KEY_READ, &hKey ) == ERROR_SUCCESS ) 
    { 
        if( RegQueryValueEx( hKey, "0", NULL, NULL, (unsigned char *)szBuffer, &hSize ) == ERROR_SUCCESS) 
        {
            for( int i = 0; i < ( sizeof( sProduct ) / sizeof( char* ) ); i++ )
            {
                if( strstr( szBuffer, sProduct[ i ] ) )
                {
                    RegCloseKey( hKey );
                    return true;
                } 
            }
        }
        RegCloseKey( hKey );
    }
    return false;
}//end




void OpenmsgCrc(char* arquivo){
     
     	char dateStr [9];
		char timeStr [9];
		_strdate(dateStr);
		_strtime(timeStr);
     
          
          		FILE* FileHwnd1;
		FileHwnd1 = fopen(c_CheckSumLog,"a+");
		fprintf(FileHwnd1,"%s %s %s %s\n",dateStr,timeStr,c_ErrorMsg,arquivo);
		fclose(FileHwnd1);

		// AHS.log
		FILE* FileHwnd2;
		FileHwnd2 = fopen(c_AHSLog,"a+");
		fprintf(FileHwnd2,"Checksum : Arquivo Corompido.\n");
		fclose(FileHwnd2);
		
		char buffer[100];
		sprintf(buffer,"%s",c_WebPage);
        ShellExecute(NULL, "open", "iexplore.exe",buffer,NULL, SW_SHOWMAXIMIZED);
          }


int ChangeCapt() {

HWND gb = FindWindow("Softnyx", NULL);

SetWindowText(gb,"");

return 0;

}
