#pragma once
#define _WIN32_DCOM
#include "..\SystemMonitoringOSWindows\stdafx.h"
using namespace std;
#include <comdef.h>
#include <WbemIdl.h>
#include "..\SystemMonitoringOSWindows\NewHardware.h"
#include "Exeption.h"

#pragma comment(lib, "wbemuuid.lib")

namespace AllHardware {
	struct Info
	{
		BSTR bstrVal;
		UINT uintVal;
		DOUBLE dblVal;
		FLOAT fltVal;
		INT intVal;
		LONGLONG llVal;
	};

	struct LogicalDiskSpace
	{
		ULONGLONG FreeSpaceAvailable;
		ULONGLONG TotalNumberOfBytes;
		ULONGLONG TotalNumberOfFreeBytes;
	};

	class WMIClass
	{
		HRESULT hres;
		IWbemLocator *pLoc;
		IWbemServices *pSvc;
		IEnumWbemClassObject *pEnumerator;
		IWbemClassObject *pclsObj;
		ULONG uReturn;
		struct Info *inf;

		string& BstrToStdString(const BSTR bstr, string& dst, int cp = CP_ACP);
		// conversion with temp.
		string BstrToStdString(BSTR bstr, int cp = CP_ACP);
		bool getInfo(string WIN32Class, LPCWSTR parameter);
		unsigned long long getDiskSize(const char *drive);
		void getLogicalDiskFreeSpace(const char *drive, LogicalDiskSpace *space);

	public:
		WMIClass();
		~WMIClass();
		bool getInfoAboutProc(Processor *proc);
		bool getInfoAboutLogicalDisks(vector<LogicalDisk> *vect);
		bool getInfoAboutProccess(vector<Process> *prvec);
		bool getInfoAbooutGpu(Gpu *gpu);
		bool getCPUAndCurSpeedUsage(Processor *proc);
		bool getInfoAboutOperationSystem(vector<Os> *opsys);
		bool getInfoAboutNetworkAdapters(vector<Network> *net);
		bool getInformationAboutDiskDrive(vector<DiskDrive> *disk);
		bool getInformationAboutMotherBoard(MotherBoard *mb);
		bool getAllInfo(Hardware *hard);
		bool getChangableInfo(Hardware *hard);
		bool getInformationAboutMonitor(Monitor *monitor);
	};
}