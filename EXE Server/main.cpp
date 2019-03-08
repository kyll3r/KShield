#include <iostream>
#include <winsock2.h>
#include <windows.h>
#include <tlhelp32.h>
#include <stdio.h>
#include <conio.h>
#include <ctime>
#include <cstdlib> 
#include <string>
#include <shellapi.h>
#include "chronistic.h"


using namespace std;

/* Coded by KyLL3R */

BYTE newdata[4]; 
DWORD newdatasize = sizeof(newdata);

LPVOID PD_addr =    (void*) 0x00496750;        // memory address of the PDVersion value in the GunBound process
LPVOID PD_addr2 =    (void*) 0x004969CC;        // memory address of the PDVersion value in the GunBound process



int player = 0;
int ip = 0;

DWORD WINAPI receive_cmds(LPVOID);  

int socket()
{

DWORD thread;
  
WSADATA data;
SOCKET winsock;
SOCKADDR_IN sock;

printf("Server Mult-threaded connected\n\n");

if((WSAStartup(0x101, &data)) == SOCKET_ERROR)
{
  printf("\nerro ao iniciar socket");
  getch();
  exit(1);
}


sock.sin_family = AF_INET;
sock.sin_addr.s_addr = INADDR_ANY;
sock.sin_port=htons(8888);
  
if((winsock = socket(AF_INET, SOCK_STREAM, 0)) == SOCKET_ERROR)
{
     printf("\nerro ao criar socket");
     getch();
     exit(1);
}
  
if(bind(winsock,(SOCKADDR*)&sock,sizeof(sock)) == SOCKET_ERROR)
{
     printf("\nerro ao acessar rede");
     getch();
     exit(1);
}
  
if(listen(winsock, 5) != 0)
{
    printf("\nerro ao criar lista de socket");
    getch();
    exit(1);
}

SOCKET client;

SOCKADDR_IN from;
int fromlen = sizeof(from);
  
while(true)
{
  client = accept(winsock,(struct sockaddr*)&from, &fromlen);
  
  ip = (int)inet_ntoa(from.sin_addr);
  printf("ip: %s\n", ip);
  
  CreateThread(NULL, 0, receive_cmds, (LPVOID)client, 0, &thread);  
}

closesocket(winsock);
WSACleanup();

return 0;
}

DWORD WINAPI receive_cmds(LPVOID lpParam)
{
      ;
  SOCKET current_client = (SOCKET)lpParam;

  char recebe[1024];
  char KeyOpen[]="XaSaAsODPA";
  char enviarPD[4];
  
  for(int i=0;i<sizeof(newdata);i++){
          
          enviarPD[i]=newdata[i];
          
          printf(" %d", newdata[i]);}
          
          
  
  int byte;
  
  player++;
  printf("\nclient connectado\r\n");
  printf("%d player online\n\n", player);
  
  
  
  
  while(true)
  {
   memset(recebe, 0, 1024);
   byte = recv(current_client, recebe, 1024, 0);
   
   if(recebe!=KeyOpen){
   send(current_client,enviarPD,strlen(enviarPD),0);
}else{byte = -1;}

  printf(recebe);
  
   if(byte == -1)
   {
    player--;
    printf("\nplayer %s desconectado\n", ip);
    printf("%d player online\n\n", player);
    
    break;
   }
  }

  closesocket(current_client);
}




BOOL SetPrivilege(LPSTR type) // more flexible
{
HANDLE Htoken;
TOKEN_PRIVILEGES tokprivls;
if(!OpenProcessToken( GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &Htoken)){
                      return 0;
                      }
tokprivls.PrivilegeCount = 1;
LookupPrivilegeValue(NULL, type, &tokprivls.Privileges[0].Luid);
tokprivls.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
BOOL Success =AdjustTokenPrivileges( Htoken, FALSE, &tokprivls, sizeof(tokprivls), NULL, NULL);
CloseHandle(Htoken);
return Success;

}// end 

struct MyChronFunction : Chronistic
{
MyChronFunction(int seconds) : Chronistic(seconds) {}
virtual bool operator()()
{
if (!trigger()) return false;
cout<<"Time to do something"<<endl;
return true;
}
};// end 

int rarray() 
{ 
 
 srand((unsigned)time(0)); 
     
    for(int i=0; i<sizeof(newdata); i++){ 
         
        newdata[i]=(rand()%100)+1; 

 } 
 
}// end 


int program(char process_name[32])
{    

    HANDLE hProcessSnap;    // will store a snapshot of all processes
    HANDLE hProcess = NULL;    // we will use this one for the gb process
    PROCESSENTRY32 pe32;    // stores basic info of a process, using this one to read the ProcessID from
    
    hProcessSnap = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );    // make process snapshot

    pe32.dwSize = sizeof( PROCESSENTRY32 );        // correct size

    Process32First(hProcessSnap, &pe32);    // read info about the first process into pe32
    
    

    do    // loop to find the gb process
    {        
        if(strcmp(pe32.szExeFile, process_name) == 0)    // if gb was found
        {
               SetPrivilege(SE_DEBUG_NAME); // set privileges
                                                         
            hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID);    // open it, assigning to the hProcess handle
           
            break;    // break the loop
        }
    }
    while(Process32Next(hProcessSnap, &pe32));    // loop continued until Process32Next deliver NULL or its interrupted with the "break" above

    CloseHandle( hProcessSnap );    // close the handle (just fuckin do it)

if(hProcess == NULL) 
    {
        printf("\n\nError ocurred in %s!",process_name);

    }
    else
    {

    printf("\n\nChange in memory of %s successfully!",process_name);
    WriteProcessMemory(hProcess,PD_addr, &newdata, newdatasize, NULL);
    WriteProcessMemory(hProcess,PD_addr2, &newdata, newdatasize, NULL);

    }

    return 0;    // THE END 
       
}// end 



int main(int argc, char* argv[]){

    SetConsoleTitle("GunBound Server Monitor"); // title console
    printf("                      .::Program Created By KyLL3R::.");
    
    int sec=1000; //seconds execute in Sleep (1000 = 1 second)
    
MyChronFunction cronologic(60); // setup to execute every 60 seconds
while (true)
{
 rarray(); // function random array   
 program("GunBoundServ1.exe"); //fuction for change PD in memory files 
 program("GunBoundServ2.exe"); //fuction for change PD in memory files 
 program("GunBoundServ3.exe"); //fuction for change PD in memory files 
 
 //limpar console
 //system("cls");
 
 //tempo de execução
 Sleep(sec*30); // 1 minute
 
}//end while
socket();
  

return EXIT_SUCCESS;

    system("pause");
}//end




