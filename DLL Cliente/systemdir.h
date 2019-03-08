#include <iostream>
#include <windows.h>
#include "checkcrc.h"

#define STRLEN 200

using namespace std;

char* dir="\\system32\\drivers\\win7hg.sys";
char* dir2="\\system32\\drivers\\wxphg.sys";
char final[STRLEN];
char dirfinal[STRLEN];
char dirfinal2[STRLEN];

int AlterDir(int check)
{
char windir[MAX_PATH];



GetWindowsDirectory(windir, MAX_PATH);

if(check==1){

snprintf(final, STRLEN, "%s%s", windir, dir); 
}

if(check==2){

snprintf(final, STRLEN, "%s%s", windir, dir2); 
}


if(check==3){

snprintf(dirfinal, STRLEN, "%s%s", windir, dir);
sysFW7=dirfinal; 
}

if(check==4){

snprintf(dirfinal2, STRLEN, "%s%s", windir, dir2); 
sysF=dirfinal2
;
}


}
