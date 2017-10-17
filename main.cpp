#include <windows.h>
#include <tlhelp32.h>
#include <iostream>

using namespace std;
typedef LONG(NTAPI *NtSuspendProcess)(IN HANDLE ProcessHandle);
typedef LONG(NTAPI *NtResumeProcess)(IN HANDLE ProcessHandle);

void showTitle() {

	cout << "   _____ _______       _" << endl;
	cout << "  / ____|__   __|/\\   | |" << endl;
	cout << " | |  __   | |  /  \\  | | ___  _ __   ___" << endl;
	cout << " | | |_ |  | | / /\\ \\ | |/ _ \\| '_ \\ / _ \\" << endl;
	cout << " | |__| |  | |/ ____ \\| | (_) | | | |  __/" << endl;
	cout << "  \\_____|  |_/_/    \\_\\_|\\___/|_| |_|\\___|" << endl;
	cout << "\tMade by Arkaitz Vizuete | github.com/arkaitzvizuete" << endl << endl << endl;
}

void showCoolWait() {

	cout << "|It won't take long :D|" << endl;
	Sleep(7000);
	cout << "|Patience please :)|" << endl;
	Sleep(4000);
	cout << "|Just a couple of seconds more :)|" << endl;
	Sleep(2000);
	cout << "|Almost finished";
	Sleep(1000);
	cout << ".";
	Sleep(1000);
	cout << ".";
	Sleep(1000);
	cout << ".|" << endl << endl;
}

int getGtaProcessId() {
	
	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(PROCESSENTRY32);

	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	if (Process32First(snapshot, &entry)) {
		do {
            		if (strcmp(entry.szExeFile, "GTA5.exe") == 0) {
				
				CloseHandle(snapshot);
				return entry.th32ProcessID;
			}
		} while (Process32Next(snapshot, &entry));
	}

	CloseHandle(snapshot);
  	return -1;
}

void suspendGtaProcess(int gtaProcessId) {

	HANDLE processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, gtaProcessId);
	NtSuspendProcess pfnNtSuspendProcess = (NtSuspendProcess)GetProcAddress(GetModuleHandle("ntdll"), "NtSuspendProcess");

	pfnNtSuspendProcess(processHandle);
	CloseHandle(processHandle);
}

void resumeGtaProcess(int gtaProcessId) {

	HANDLE processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, gtaProcessId);
	NtResumeProcess pfnNtResumeProcess = (NtResumeProcess)GetProcAddress(GetModuleHandle("ntdll"), "NtResumeProcess");

	pfnNtResumeProcess(processHandle);
	CloseHandle(processHandle);
}

int main() {

	showTitle();

  	int gtaProcessId = getGtaProcessId();

	if (gtaProcessId != -1) {
		
		cout << "|GTA5 Detected. PID: " << gtaProcessId << "|" << endl;
		cout << "|PLEASE STAND BY|" << endl << endl;
		suspendGtaProcess(gtaProcessId);
		showCoolWait();
		resumeGtaProcess(gtaProcessId);
		cout << "|DONE! Enjoy your loneliness :D|";
		Sleep(2000);
	}
	else {
		
		cout << "|ERROR: GTA5 not detected.|" << endl << endl << "|Open GTA5 Online please.|";
		Sleep(3000);
	}
}
