#ifndef KyLL3R_KyLL3R_H
#define KyLL3R_KyLL3R_H

#include <tlhelp32.h>
#include <windows.h>
#include <list>

#define MAX_DUMP_SIZE 32
#define MAX_PROCESS_DUMP 107

#define INVALID_PROCESSID -1
#define SYSTEMSHELL_NAME "GunBound.exe"

typedef struct ANITHACK_PROCDUMP {
	unsigned int m_aOffset;
	unsigned char m_aMemDump[MAX_DUMP_SIZE];
} *PANITHACK_PROCDUMP;

extern ANITHACK_PROCDUMP g_ProcessesDumps[MAX_PROCESS_DUMP];

class KShield {
public:
	void Startup();
	void SystemProcessesScan();
	void CheckProcessOwner();
	void Cleanup();


private:
	void GetSystemProcessesList();
	bool ScanProcessMemory(DWORD dwProcessId);
	void GetExplorerProcessId();
	int CheckProcessName(char *sProcessName, char *sSrcProcessName);
	bool CheckExplorerProcessDirectory(DWORD dwProcessId);

	int m_dwExplorerProcessId;
	std::list<PROCESSENTRY32> m_lProcessesList;

	//std::vector<PPROCESSENTRY32> m_vProcessesList;
};

#endif //KyLL3R_KyLL3R_H
