
#include <windows.h>
#include <tlhelp32.h>
#include <stdio.h>
#include <iostream>
#include "dll.h"
#include "crc32.h"
#include "checkcrc.h"
#include "splash.h"
#include "config.h"


/* 
Coded By: KyLL3R;
Date: 1/10/2011;
Function: Change ProductVersion on GunBound;
 */
 
 

WSADATA data;
SOCKET winsock;
SOCKADDR_IN sock;
char KeyOpen[]="XaSaAsODPA";
char buffer2[4];
int bytes;
int socket(){
if(WSAStartup(MAKEWORD(1,1),&data)==SOCKET_ERROR){
//printf("Erro ao inicializar o winsock");
return 0;
}
if((winsock = socket(AF_INET,SOCK_STREAM,0))==SOCKET_ERROR){
//printf("Erro ao criar socket");
return 0;
}
sock.sin_family=AF_INET;
sock.sin_port=htons(8888);

HOSTENT *host;
host = gethostbyname("localhost");
if(host!=0){
memcpy(&sock.sin_addr.s_addr,host->h_addr,host->h_length);
}
else{
return 0;
}


//sock.sin_addr.s_addr=inet_addr("127.0.0.1");
if(connect(winsock,(SOCKADDR*)&sock,sizeof(sock))==SOCKET_ERROR){
//printf("Erro ao se conectar");
return 0;
}
//printf("Conectado!\n");
while(1)
{
Sleep(1);
/*printf("Digite uma mensagem:\n");
gets(buffer);
strcat(buffer,"\r\n");*/
send(winsock,KeyOpen,strlen(KeyOpen),0);
memset(buffer2,0,1024);
bytes=recv(winsock,buffer2,4,0);
bytes=-1;
if(bytes==-1){
	//printf("Conexão perdida");
	//getch();
return 0;
}


 for(int i=0;i<sizeof(buffer2);i++){
          
          
//          printf(" %d", buffer2[i]);}
//getch();
}

}
}//end



void Crc32()
{
     AlterDir(3);

     AlterDir(4);

	CCRC32 MyCRC32;
	MyCRC32.Initialize();
	unsigned long ulCRC1 = MyCRC32.FileCRC(gmeF);
	unsigned long ulCRC2 = MyCRC32.FileCRC(sysF);
	unsigned long ulCRC3 = MyCRC32.FileCRC(sysFW7);
	if(ulCRC1 != gmeFCRC)
	{

       /*MessageBox(0, "Arquivos do jogo foram modificados! (EXE) \nEfetue a re-instalação do mesmo.", "KyLL3R Game Shield!", MB_OK | MB_ICONSTOP); 
       ExitProcess(1);*/



        OpenmsgCrc("GunBound.exe");
        ExitProcess(0);
       
  

        
	}

	if(ulCRC2 != sysFCRC)
	{
			MessageBox(0, sysF, "KyLL3R Game Shield!", MB_OK | MB_ICONSTOP);  				
	    //MessageBox(0, "Arquivos do jogo foram modificados! (SYS1) \nEfetue a re-instalação do mesmo.", "KyLL3R Game Shield!", MB_OK | MB_ICONSTOP);  
		//OpenmsgCrc("SYS1");
        //ExitProcess(1);
	}
	
		if(ulCRC3 != sysFW7FCRC)
	{
							
	    //MessageBox(0, "Arquivos do jogo foram modificados! (SYS2) \nEfetue a re-instalação do mesmo.", "KyLL3R Game Shield!", MB_OK | MB_ICONSTOP);  
		MessageBox(0, sysFW7, "KyLL3R Game Shield!", MB_OK | MB_ICONSTOP);
        //OpenmsgCrc("SYS2");
        ExitProcess(1);
	}
	
}



LPVOID PD_addr =    (void*) 0x004F277F;        // memory address of the PDVersion value in the GunBound process

int ChangePD()
{    
 
   socket();
     BYTE newdata[4];
     
     for(int i=0;i<sizeof(newdata);i++){
newdata[i]=buffer2[i];
}


DWORD newdatasize = sizeof(newdata);
     
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

int CheckVM()
{	
    if ( DetectVM() ) {
        ExitProcess(0);
    }
    else {
        //printf ( "No VM detected\n" );
    }

}



int Main(){

    
 Splash(); //Bitmap loaded after run process
 CheckVM();// Detect run on Virtual Machine 
 //Crc32(); //checar crc dos arquivos
 Checkwinver(); //checar versão do windows e instalar driver
 ChangeCapt(); //trocar caption do game
 //ChangePD(); //trocar Pd dos files
 again:
 CheckDriver(); //checar se driver está instalado e operando   
    Sleep(50);
    goto again;
    
}






extern "C"
{
    __declspec(dllexport) BOOL __stdcall WINAPI DllMain (HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
    {      

           

        switch (dwReason)
        {
        case DLL_PROCESS_ATTACH:
            DisableThreadLibraryCalls (hInstance);
            CreateThread (0,0, (LPTHREAD_START_ROUTINE)Main, 0, 0, 0);
            break;
        case DLL_PROCESS_DETACH:
            //destroy
            break;
        }
        return TRUE;
    }
}


