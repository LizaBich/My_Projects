#include "NewWmiClass.h"


bool AllHardware::WMIClass::getInfo(string WIN32Class, LPCWSTR parameter)
{
	string str = "SELECT * FROM ";
	str += WIN32Class;
	this->hres = this->pSvc->ExecQuery(
		bstr_t("WQL"),
		bstr_t(str.c_str()),
		WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
		NULL,
		&pEnumerator);

	if (FAILED(this->hres))
	{
		cout << "Query for processes failed. "
			<< "Error code = 0x"
			<< hex << hres << endl;
		this->pSvc->Release();
		this->pLoc->Release();
		CoUninitialize();
		return false;               // Program has failed.
	}

	while (this->pEnumerator)
	{
		this->hres = this->pEnumerator->Next(WBEM_INFINITE, 1,
			&pclsObj, &uReturn);

		if (0 == this->uReturn)
		{
			break;
		}

		VARIANT vtProp;

		// Get the value of the Name property
		this->hres = this->pclsObj->Get(parameter, 0, &vtProp, 0, 0);
		if (FALSE(this->hres)) cout << "\nInvalid getting of value!" << endl;
		this->inf->bstrVal = vtProp.bstrVal;
		this->inf->uintVal = vtProp.uintVal;
		this->inf->dblVal = vtProp.dblVal;
		this->inf->llVal = vtProp.llVal;
		VariantClear(&vtProp);
	}
	return true;
}

unsigned long long AllHardware::WMIClass::getDiskSize(const char *drive)
{
	DISK_GEOMETRY pdn = { 0 };
	HANDLE hDevice;
	BOOL bResult;
	DWORD junk;

	hDevice = CreateFileA((LPCSTR)drive, 0, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);

	if (hDevice == INVALID_HANDLE_VALUE)
		return 0;

	bResult = DeviceIoControl(hDevice, IOCTL_DISK_GET_DRIVE_GEOMETRY, NULL, 0, &pdn, sizeof(pdn), &junk, (LPOVERLAPPED)NULL);
	if (!bResult) return 0;
	CloseHandle(hDevice);

	//ULONGLONG DiskSize = pdn.Cylinders.QuadPart * (ULONG)pdn.TracksPerCylinder * (ULONG)pdn.SectorsPerTrack * (ULONG)pdn.BytesPerSector;

	return pdn.Cylinders.QuadPart * (ULONG)pdn.TracksPerCylinder * (ULONG)pdn.SectorsPerTrack * (ULONG)pdn.BytesPerSector;
}

void AllHardware::WMIClass::getLogicalDiskFreeSpace(const char *drive, LogicalDiskSpace *space)
{
	string dr = drive;
	dr += "\\";

	GetDiskFreeSpaceExA((LPCSTR)dr.c_str(), (PULARGE_INTEGER)&space->FreeSpaceAvailable, (PULARGE_INTEGER)&space->TotalNumberOfBytes, (PULARGE_INTEGER)&space->TotalNumberOfFreeBytes);
	return;
}

bool AllHardware::WMIClass::getInfoAboutLogicalDisks(vector<LogicalDisk> *vect)
{
	string str = "SELECT * FROM Win32_LogicalDisk";
	this->hres = this->pSvc->ExecQuery(
		bstr_t("WQL"),
		bstr_t(str.c_str()),
		WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
		NULL,
		&pEnumerator);

	if (FAILED(this->hres))
	{
		cout << "Query for processes failed. "
			<< "Error code = 0x"
			<< hex << hres << endl;
		this->pSvc->Release();
		this->pLoc->Release();
		CoUninitialize();
		return false;               // Program has failed.
	}

	LogicalDiskSpace space;
	LogicalDisk *logd = new LogicalDisk();

	while (this->pEnumerator)
	{


		this->hres = this->pEnumerator->Next(WBEM_INFINITE, 1,
			&pclsObj, &uReturn);

		if (0 == this->uReturn)
		{
			break;
		}

		VARIANT vtProp;

		// Get the value of the Name property
		this->hres = this->pclsObj->Get(L"DeviceID", 0, &vtProp, 0, 0);
		if (FALSE(this->hres)) cout << "\nInvalid getting of value!" << endl;
		logd->getDeviceID(this->BstrToStdString(vtProp.bstrVal));
		VariantClear(&vtProp);

		this->hres = this->pclsObj->Get(L"BlockSize", 0, &vtProp, 0, 0);
		if (FALSE(this->hres)) cout << "\nInvalid getting of value!" << endl;
		logd->getBlockSize(vtProp.uintVal);
		VariantClear(&vtProp);

		this->hres = this->pclsObj->Get(L"DriveType", 0, &vtProp, 0, 0);
		if (FALSE(this->hres)) cout << "\nInvalid getting of value!" << endl;
		logd->getDriveType(vtProp.uintVal);
		VariantClear(&vtProp);

		this->hres = this->pclsObj->Get(L"FileSystem", 0, &vtProp, 0, 0);
		if (FALSE(this->hres)) cout << "\nInvalid getting of value!" << endl;
		logd->getFileSystem(this->BstrToStdString(vtProp.bstrVal));
		VariantClear(&vtProp);

		this->hres = this->pclsObj->Get(L"MaximumComponentLength", 0, &vtProp, 0, 0);
		if (FALSE(this->hres)) cout << "\nInvalid getting of value!" << endl;
		logd->getMaxComponentLenght(vtProp.uintVal);
		VariantClear(&vtProp);

		this->hres = this->pclsObj->Get(L"NumberOfBlocks", 0, &vtProp, 0, 0);
		if (FALSE(this->hres)) cout << "\nInvalid getting of value!" << endl;
		logd->getNumberOfBlocks(vtProp.uintVal);
		VariantClear(&vtProp);

		this->getLogicalDiskFreeSpace(logd->setDeviceID(), &space);
		logd->getSize(space.TotalNumberOfBytes);
		logd->getFreeSpace(space.FreeSpaceAvailable);
		logd->getAvailableFreeSpace(space.FreeSpaceAvailable);

		vect->push_back(*logd);
	}
	delete logd;
	return true;
}

bool AllHardware::WMIClass::getInfoAboutProccess(vector<Process> *prvec)
{
	string str = "SELECT * FROM Win32_Process";
	this->hres = this->pSvc->ExecQuery(
		bstr_t("WQL"),
		bstr_t(str.c_str()),
		WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
		NULL,
		&pEnumerator);



	if (FAILED(this->hres))
	{
		cout << "Query for processes failed. "
			<< "Error code = 0x"
			<< hex << hres << endl;
		this->pSvc->Release();
		this->pLoc->Release();
		CoUninitialize();
		return false;               // Program has failed.
	}

	while (this->pEnumerator)
	{
		Process *proc = new Process();

		this->hres = this->pEnumerator->Next(WBEM_INFINITE, 1,
			&pclsObj, &uReturn);

		if (0 == this->uReturn)
		{
			break;
		}

		VARIANT vtProp;

		this->hres = this->pclsObj->Get(L"ExecutablePath", 0, &vtProp, 0, 0);
		proc->getExecutablePath(this->BstrToStdString(vtProp.bstrVal));
		VariantClear(&vtProp);

		this->hres = this->pclsObj->Get(L"Handle", 0, &vtProp, 0, 0);
		proc->getHandle(this->BstrToStdString(vtProp.bstrVal));
		VariantClear(&vtProp);

		this->hres = this->pclsObj->Get(L"HandleCount", 0, &vtProp, 0, 0);
		proc->getHandleCount(vtProp.uintVal);
		VariantClear(&vtProp);

		this->hres = this->pclsObj->Get(L"Name", 0, &vtProp, 0, 0);
		proc->getName(this->BstrToStdString(vtProp.bstrVal));
		VariantClear(&vtProp);

		this->hres = this->pclsObj->Get(L"ParentProcessID", 0, &vtProp, 0, 0);
		proc->getParentProcessID(vtProp.uintVal);
		VariantClear(&vtProp);

		this->hres = this->pclsObj->Get(L"ProcessID", 0, &vtProp, 0, 0);
		proc->getProcessID(vtProp.uintVal);
		VariantClear(&vtProp);

		this->hres = this->pclsObj->Get(L"ThreadCount", 0, &vtProp, 0, 0);
		proc->getThreadCount(vtProp.uintVal);
		VariantClear(&vtProp);

		this->hres = this->pclsObj->Get(L"WorkingSetSize", 0, &vtProp, 0, 0);
		proc->getWorkingSetSize(vtProp.uintVal);
		VariantClear(&vtProp);

		prvec->push_back(*proc);
		delete proc;
	}
	return true;
}

bool AllHardware::WMIClass::getInfoAbooutGpu(Gpu * gpu)
{
	cout << "Connect to WIN32_VideoController class" << endl;
	this->hres = this->pSvc->ExecQuery(
		bstr_t("WQL"),
		bstr_t("SELECT * FROM Win32_VideoController"),
		WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
		NULL,
		&pEnumerator);

	if (FAILED(this->hres))
	{
		cout << "Query for processes failed. "
			<< "Error code = 0x"
			<< hex << hres << endl;
		this->pSvc->Release();
		this->pLoc->Release();
		CoUninitialize();
		return false;               // Program has failed.
	}

	while (this->pEnumerator)
	{
		this->hres = this->pEnumerator->Next(WBEM_INFINITE, 1,
			&pclsObj, &uReturn);

		if (0 == this->uReturn)
		{
			break;
		}

		VARIANT vtProp;

		// Get the value of the Name property
		//cout << "Load Adapter Compatibility" << endl;
		this->hres = this->pclsObj->Get(L"AdapterCompatibility", 0, &vtProp, 0, 0);
		if (FALSE(this->hres)) cout << "\nInvalid getting of value!" << endl;
		//cout << "Try to write this value to the Gpu class" << endl;
		gpu->getAdapterCompatibility(this->BstrToStdString(vtProp.bstrVal));
		VariantClear(&vtProp);

		this->hres = this->pclsObj->Get(L"AdapterRAM", 0, &vtProp, 0, 0);
		if (FALSE(this->hres)) cout << "\nInvalid getting of value!" << endl;
		gpu->getAdapterRAM(vtProp.llVal);
		VariantClear(&vtProp);

		this->hres = this->pclsObj->Get(L"CurrentBitsPerPixel", 0, &vtProp, 0, 0);
		if (FALSE(this->hres)) cout << "\nInvalid getting of value!" << endl;
		gpu->getCurrentBitsPerPixel(vtProp.uintVal);
		VariantClear(&vtProp);

		this->hres = this->pclsObj->Get(L"CurrentHorizontalResolution", 0, &vtProp, 0, 0);
		if (FALSE(this->hres)) cout << "\nInvalid getting of value!" << endl;
		gpu->getCurrentHorizontalResolution(vtProp.uintVal);
		VariantClear(&vtProp);

		this->hres = this->pclsObj->Get(L"CurrentVerticalResolution", 0, &vtProp, 0, 0);
		if (FALSE(this->hres)) cout << "\nInvalid getting of value!" << endl;
		gpu->getCurrentVerticalResolution(vtProp.uintVal);
		VariantClear(&vtProp);

		this->hres = this->pclsObj->Get(L"CurrentNumberOfColor", 0, &vtProp, 0, 0);
		if (FALSE(this->hres)) cout << "\nInvalid getting of value!" << endl;
		gpu->getCurrentNumberOfColor(vtProp.llVal / 1000000000.0);
		VariantClear(&vtProp);

		this->hres = this->pclsObj->Get(L"CurrentRefreshRate", 0, &vtProp, 0, 0);
		if (FALSE(this->hres)) cout << "\nInvalid getting of value!" << endl;
		gpu->getCurrentRefreshRate(vtProp.uintVal);
		VariantClear(&vtProp);

		this->hres = this->pclsObj->Get(L"MaxRefreshRate", 0, &vtProp, 0, 0);
		if (FALSE(this->hres)) cout << "\nInvalid getting of value!" << endl;
		gpu->getMaxRefreshRate(vtProp.uintVal);
		VariantClear(&vtProp);

		this->hres = this->pclsObj->Get(L"MinRefreshRate", 0, &vtProp, 0, 0);
		if (FALSE(this->hres)) cout << "\nInvalid getting of value!" << endl;
		gpu->getMinRefreshRate(vtProp.uintVal);
		VariantClear(&vtProp);

		this->hres = this->pclsObj->Get(L"Name", 0, &vtProp, 0, 0);
		if (FALSE(this->hres)) cout << "\nInvalid getting of value!" << endl;
		gpu->getName(this->BstrToStdString(vtProp.bstrVal));
		VariantClear(&vtProp);

		this->hres = this->pclsObj->Get(L"ProtocolSupported", 0, &vtProp, 0, 0);
		if (FALSE(this->hres)) cout << "\nInvalid getting of value!" << endl;
		gpu->getProtocolSupported(vtProp.uintVal);
		VariantClear(&vtProp);

		this->hres = this->pclsObj->Get(L"VideoArchitecture", 0, &vtProp, 0, 0);
		if (FALSE(this->hres)) cout << "\nInvalid getting of value!" << endl;
		gpu->getVideoArchitecture(vtProp.uintVal);
		VariantClear(&vtProp);

		this->hres = this->pclsObj->Get(L"VideoMemoryType", 0, &vtProp, 0, 0);
		if (FALSE(this->hres)) cout << "\nInvalid getting of value!" << endl;
		gpu->getVideoMemoryType(vtProp.uintVal);
		VariantClear(&vtProp);

		this->hres = this->pclsObj->Get(L"VideoProcessor", 0, &vtProp, 0, 0);
		if (FALSE(this->hres)) cout << "\nInvalid getting of value!" << endl;
		gpu->getVideoProcessor(this->BstrToStdString(vtProp.bstrVal));
		VariantClear(&vtProp);
	}

	return false;
}

bool AllHardware::WMIClass::getCPUAndCurSpeedUsage(Processor * proc)
{
	string Win32Class = "Win32_Processor";
	if (!this->getInfo(Win32Class, L"LoadPercentage")) return false;
	proc->getLoadPercentage(this->inf->uintVal);

	if (!this->getInfo(Win32Class, L"CurrentClockSpeed")) return false;
	proc->getCurrentSpeed(this->inf->uintVal / 1000.0);
	return true;
}



bool AllHardware::WMIClass::getInfoAboutOperationSystem(vector<Os> *opsys)
{
	string str = "SELECT * FROM Win32_OperatingSystem";
	this->hres = this->pSvc->ExecQuery(
		bstr_t("WQL"),
		bstr_t(str.c_str()),
		WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
		NULL,
		&pEnumerator);



	if (FAILED(this->hres))
	{
		cout << "Query for processes failed. "
			<< "Error code = 0x"
			<< hex << hres << endl;
		this->pSvc->Release();
		this->pLoc->Release();
		CoUninitialize();
		return false;               // Program has failed.
	}
	Os *os = new Os();
	while (this->pEnumerator)
	{
		this->hres = this->pEnumerator->Next(WBEM_INFINITE, 1,
			&pclsObj, &uReturn);

		if (0 == this->uReturn)
		{
			break;
		}

		VARIANT vtProp;

		// Get the value of the Name property
		this->hres = this->pclsObj->Get(L"BuildNumber", 0, &vtProp, 0, 0);
		if (FALSE(this->hres)) cout << "\nInvalid getting of value!" << endl;
		os->getBuildNumber(this->BstrToStdString(vtProp.bstrVal));
		VariantClear(&vtProp);

		this->hres = this->pclsObj->Get(L"Caption", 0, &vtProp, 0, 0);
		if (FALSE(this->hres)) cout << "\nInvalid getting of value!" << endl;
		os->getCaption(this->BstrToStdString(vtProp.bstrVal));
		VariantClear(&vtProp);

		this->hres = this->pclsObj->Get(L"CSName", 0, &vtProp, 0, 0);
		if (FALSE(this->hres)) cout << "\nInvalid getting of value!" << endl;
		os->getCSName(this->BstrToStdString(vtProp.bstrVal));
		VariantClear(&vtProp);

		this->hres = this->pclsObj->Get(L"Manufacturer", 0, &vtProp, 0, 0);
		if (FALSE(this->hres)) cout << "\nInvalid getting of value!" << endl;
		os->getManufacturer(this->BstrToStdString(vtProp.bstrVal));
		VariantClear(&vtProp);

		this->hres = this->pclsObj->Get(L"NumberOfProcesses", 0, &vtProp, 0, 0);
		if (FALSE(this->hres)) cout << "\nInvalid getting of value!" << endl;
		os->getNumberOfProcesses(vtProp.uintVal);
		VariantClear(&vtProp);

		this->hres = this->pclsObj->Get(L"OperatingSystemSKU", 0, &vtProp, 0, 0);
		if (FALSE(this->hres)) cout << "\nInvalid getting of value!" << endl;
		os->getOperatingSystemSKU(vtProp.uintVal);
		VariantClear(&vtProp);

		this->hres = this->pclsObj->Get(L"OSArchitecture", 0, &vtProp, 0, 0);
		if (FALSE(this->hres)) cout << "\nInvalid getting of value!" << endl;
		os->getOSArchitecture(this->BstrToStdString(vtProp.bstrVal));
		VariantClear(&vtProp);

		this->hres = this->pclsObj->Get(L"SerialNumber", 0, &vtProp, 0, 0);
		if (FALSE(this->hres)) cout << "\nInvalid getting of value!" << endl;
		os->getSerialNumber(this->BstrToStdString(vtProp.bstrVal));
		VariantClear(&vtProp);

		this->hres = this->pclsObj->Get(L"SystemDevice", 0, &vtProp, 0, 0);
		if (FALSE(this->hres)) cout << "\nInvalid getting of value!" << endl;
		os->getSystemDevice(this->BstrToStdString(vtProp.bstrVal));
		VariantClear(&vtProp);

		this->hres = this->pclsObj->Get(L"SystemDirectory", 0, &vtProp, 0, 0);
		if (FALSE(this->hres)) cout << "\nInvalid getting of value!" << endl;
		os->getSystemDirectory(this->BstrToStdString(vtProp.bstrVal));
		VariantClear(&vtProp);

		this->hres = this->pclsObj->Get(L"Version", 0, &vtProp, 0, 0);
		if (FALSE(this->hres)) cout << "\nInvalid getting of value!" << endl;
		os->getVersion(this->BstrToStdString(vtProp.bstrVal));
		VariantClear(&vtProp);

		opsys->push_back(*os);
	}
	delete os;
	return true;
}

bool AllHardware::WMIClass::getInfoAboutNetworkAdapters(vector<Network>* net)
{
	string str = "SELECT * FROM Win32_NetworkAdapter";
	this->hres = this->pSvc->ExecQuery(
		bstr_t("WQL"),
		bstr_t(str.c_str()),
		WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
		NULL,
		&pEnumerator);



	if (FAILED(this->hres))
	{
		cout << "Query for processes failed. "
			<< "Error code = 0x"
			<< hex << hres << endl;
		this->pSvc->Release();
		this->pLoc->Release();
		CoUninitialize();
		return false;               // Program has failed.
	}
	Network *netw = new Network();
	while (this->pEnumerator)
	{
		this->hres = this->pEnumerator->Next(WBEM_INFINITE, 1,
			&pclsObj, &uReturn);

		if (0 == this->uReturn)
		{
			break;
		}

		VARIANT vtProp;
		int pos;
		if (net->size() > 0) pos = net->size() - 1;

		// Get the value of the Name property
		this->hres = this->pclsObj->Get(L"AdapterType", 0, &vtProp, 0, 0);
		if (FALSE(this->hres)) cout << "\nInvalid getting of value!" << endl;
		netw->getAdapterType(this->BstrToStdString(vtProp.bstrVal));
		VariantClear(&vtProp);

		this->hres = this->pclsObj->Get(L"Caption", 0, &vtProp, 0, 0);
		if (FALSE(this->hres)) cout << "\nInvalid getting of value!" << endl;
		netw->getCaption(this->BstrToStdString(vtProp.bstrVal));
		VariantClear(&vtProp);

		this->hres = this->pclsObj->Get(L"DeviceID", 0, &vtProp, 0, 0);
		if (FALSE(this->hres)) cout << "\nInvalid getting of value!" << endl;
		netw->getDeviceID(this->BstrToStdString(vtProp.bstrVal));
		VariantClear(&vtProp);

		this->hres = this->pclsObj->Get(L"GUID", 0, &vtProp, 0, 0);
		if (FALSE(this->hres)) cout << "\nInvalid getting of value!" << endl;
		netw->getGUID(this->BstrToStdString(vtProp.bstrVal));
		VariantClear(&vtProp);

		this->hres = this->pclsObj->Get(L"MACAddress", 0, &vtProp, 0, 0);
		if (FALSE(this->hres)) cout << "\nInvalid getting of value!" << endl;
		netw->getMACAddress(this->BstrToStdString(vtProp.bstrVal));
		VariantClear(&vtProp);

		this->hres = this->pclsObj->Get(L"Manufacturer", 0, &vtProp, 0, 0);
		if (FALSE(this->hres)) cout << "\nInvalid getting of value!" << endl;
		netw->getManufacturer(this->BstrToStdString(vtProp.bstrVal));
		VariantClear(&vtProp);

		this->hres = this->pclsObj->Get(L"Name", 0, &vtProp, 0, 0);
		if (FALSE(this->hres)) cout << "\nInvalid getting of value!" << endl;
		netw->getName(this->BstrToStdString(vtProp.bstrVal));
		VariantClear(&vtProp);

		this->hres = this->pclsObj->Get(L"NetConnectionID", 0, &vtProp, 0, 0);
		if (FALSE(this->hres)) cout << "\nInvalid getting of value!" << endl;
		netw->getNetConnectionID(this->BstrToStdString(vtProp.bstrVal));
		VariantClear(&vtProp);

		this->hres = this->pclsObj->Get(L"NetConnectionStatus", 0, &vtProp, 0, 0);
		if (FALSE(this->hres)) cout << "\nInvalid getting of value!" << endl;
		netw->getNetConnectionStatus(vtProp.uintVal);
		VariantClear(&vtProp);

		this->hres = this->pclsObj->Get(L"PNPDeviceID", 0, &vtProp, 0, 0);
		if (FALSE(this->hres)) cout << "\nInvalid getting of value!" << endl;
		netw->getPNPDeviceID(this->BstrToStdString(vtProp.bstrVal));
		VariantClear(&vtProp);

		this->hres = this->pclsObj->Get(L"ServiceName", 0, &vtProp, 0, 0);
		if (FALSE(this->hres)) cout << "\nInvalid getting of value!" << endl;
		netw->getServiceName(this->BstrToStdString(vtProp.bstrVal));
		VariantClear(&vtProp);

		this->hres = this->pclsObj->Get(L"Speed", 0, &vtProp, 0, 0);
		if (FALSE(this->hres)) cout << "\nInvalid getting of value!" << endl;
		netw->getSpeed(vtProp.llVal);
		VariantClear(&vtProp);

		if (net->size() > 1) {
			if ((*net)[pos].setSpeed() == netw->setSpeed()) netw->getSpeed(0);
			if (std::string((*net)[pos].setMACAddress()) == std::string(netw->setMACAddress())) netw->getMACAddress(" ");
			if (std::string((*net)[pos].setGUID()) == std::string(netw->setGUID())) netw->getGUID(" ");
		}

		net->push_back(*netw);
	}
	delete netw;
	return true;
}

bool AllHardware::WMIClass::getInformationAboutDiskDrive(vector<DiskDrive>* disk)
{
	string str = "SELECT * FROM Win32_DiskDrive";
	this->hres = this->pSvc->ExecQuery(
		bstr_t("WQL"),
		bstr_t(str.c_str()),
		WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
		NULL,
		&pEnumerator);



	if (FAILED(this->hres))
	{
		cout << "Query for processes failed. "
			<< "Error code = 0x"
			<< hex << hres << endl;
		this->pSvc->Release();
		this->pLoc->Release();
		CoUninitialize();
		return false;               // Program has failed.
	}
	DiskDrive *odisk = new DiskDrive();
	while (this->pEnumerator)
	{
		this->hres = this->pEnumerator->Next(WBEM_INFINITE, 1,
			&pclsObj, &uReturn);

		if (0 == this->uReturn)
		{
			break;
		}

		VARIANT vtProp;

		// Get the value of the Name property
		this->hres = this->pclsObj->Get(L"BytesPerSector", 0, &vtProp, 0, 0);
		if (FALSE(this->hres)) cout << "\nInvalid getting of value!" << endl;
		odisk->getBytesPerSector(vtProp.uintVal);
		VariantClear(&vtProp);

		this->hres = this->pclsObj->Get(L"DeviceID", 0, &vtProp, 0, 0);
		if (FALSE(this->hres)) cout << "\nInvalid getting of value!" << endl;
		odisk->getDeviceID(this->BstrToStdString(vtProp.bstrVal));
		VariantClear(&vtProp);

		this->hres = this->pclsObj->Get(L"Description", 0, &vtProp, 0, 0);
		if (FALSE(this->hres)) cout << "\nInvalid getting of value!" << endl;
		odisk->getDescription(this->BstrToStdString(vtProp.bstrVal));
		VariantClear(&vtProp);

		this->hres = this->pclsObj->Get(L"FirmwareRevision", 0, &vtProp, 0, 0);
		if (FALSE(this->hres)) cout << "\nInvalid getting of value!" << endl;
		odisk->getFirmwareRevision(this->BstrToStdString(vtProp.bstrVal));
		VariantClear(&vtProp);

		this->hres = this->pclsObj->Get(L"Manufacturer", 0, &vtProp, 0, 0);
		if (FALSE(this->hres)) cout << "\nInvalid getting of value!" << endl;
		odisk->getManufacturer(this->BstrToStdString(vtProp.bstrVal));
		VariantClear(&vtProp);

		this->hres = this->pclsObj->Get(L"Name", 0, &vtProp, 0, 0);
		if (FALSE(this->hres)) cout << "\nInvalid getting of value!" << endl;
		odisk->getName(this->BstrToStdString(vtProp.bstrVal));
		VariantClear(&vtProp);

		this->hres = this->pclsObj->Get(L"MediaType", 0, &vtProp, 0, 0);
		if (FALSE(this->hres)) cout << "\nInvalid getting of value!" << endl;
		odisk->getMediaType(this->BstrToStdString(vtProp.bstrVal));
		VariantClear(&vtProp);

		this->hres = this->pclsObj->Get(L"InterfaceType", 0, &vtProp, 0, 0);
		if (FALSE(this->hres)) cout << "\nInvalid getting of value!" << endl;
		odisk->getInterfaceType(this->BstrToStdString(vtProp.bstrVal));
		VariantClear(&vtProp);

		this->hres = this->pclsObj->Get(L"Model", 0, &vtProp, 0, 0);
		if (FALSE(this->hres)) cout << "\nInvalid getting of value!" << endl;
		odisk->getModel(this->BstrToStdString(vtProp.bstrVal));
		VariantClear(&vtProp);

		this->hres = this->pclsObj->Get(L"SerialNumber", 0, &vtProp, 0, 0);
		if (FALSE(this->hres)) cout << "\nInvalid getting of value!" << endl;
		odisk->getSerialNumber(this->BstrToStdString(vtProp.bstrVal));
		VariantClear(&vtProp);

		odisk->getSize(this->getDiskSize(odisk->setDeviceID()));
		odisk->getFreeSpace(odisk->setDeviceID());

		disk->push_back(*odisk);
	}
	delete odisk;
	return true;
}

bool AllHardware::WMIClass::getInformationAboutMotherBoard(MotherBoard * mb)
{
	string str = "SELECT * FROM Win32_BaseBoard";
	this->hres = this->pSvc->ExecQuery(
		bstr_t("WQL"),
		bstr_t(str.c_str()),
		WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
		NULL,
		&pEnumerator);

	if (FAILED(this->hres))
	{
		cout << "Query for processes failed. "
			<< "Error code = 0x"
			<< hex << hres << endl;
		this->pSvc->Release();
		this->pLoc->Release();
		CoUninitialize();
		return false;               // Program has failed.
	}
	while (this->pEnumerator)
	{
		this->hres = this->pEnumerator->Next(WBEM_INFINITE, 1,
			&pclsObj, &uReturn);

		if (0 == this->uReturn)
		{
			break;
		}

		VARIANT vtProp;

		// Get the value of the Name property
		//cout << "Load caption" << endl;
		this->hres = this->pclsObj->Get(L"Caption", 0, &vtProp, 0, 0);
		if (FALSE(this->hres)) cout << "\nInvalid getting of value!" << endl;
		//cout << "Try to write caption to the class" << endl;
		mb->getCaption(this->BstrToStdString(vtProp.bstrVal));
		//cout << "Caption succsesfully write" << endl;
		VariantClear(&vtProp);

		this->hres = this->pclsObj->Get(L"Model", 0, &vtProp, 0, 0);
		if (FALSE(this->hres)) cout << "\nInvalid getting of value!" << endl;
		mb->getModel(this->BstrToStdString(vtProp.bstrVal));
		VariantClear(&vtProp);

		this->hres = this->pclsObj->Get(L"Removable", 0, &vtProp, 0, 0);
		if (FALSE(this->hres)) cout << "\nInvalid getting of value!" << endl;
		mb->getRemovable(vtProp.boolVal);
		VariantClear(&vtProp);

		this->hres = this->pclsObj->Get(L"Replaceable", 0, &vtProp, 0, 0);
		if (FALSE(this->hres)) cout << "\nInvalid getting of value!" << endl;
		mb->getReplaceable(vtProp.boolVal);
		VariantClear(&vtProp);

		this->hres = this->pclsObj->Get(L"SpecialRequirements", 0, &vtProp, 0, 0);
		if (FALSE(this->hres)) cout << "\nInvalid getting of value!" << endl;
		mb->getSpecialRequirements(vtProp.boolVal);
		VariantClear(&vtProp);

		if (mb->setSpecialRequirements())
		{
			this->hres = this->pclsObj->Get(L"RequirementsDescription", 0, &vtProp, 0, 0);
			if (FALSE(this->hres)) cout << "\nInvalid getting of value!" << endl;
			mb->getRequirementsDescription(this->BstrToStdString(vtProp.bstrVal));
			VariantClear(&vtProp);
		}

		this->hres = this->pclsObj->Get(L"Manufacturer", 0, &vtProp, 0, 0);
		if (FALSE(this->hres)) cout << "\nInvalid getting of value!" << endl;
		mb->getManufacturer(this->BstrToStdString(vtProp.bstrVal));
		VariantClear(&vtProp);

		this->hres = this->pclsObj->Get(L"Name", 0, &vtProp, 0, 0);
		if (FALSE(this->hres)) cout << "\nInvalid getting of value!" << endl;
		mb->getName(this->BstrToStdString(vtProp.bstrVal));
		VariantClear(&vtProp);

		this->hres = this->pclsObj->Get(L"Version", 0, &vtProp, 0, 0);
		if (FALSE(this->hres)) cout << "\nInvalid getting of value!" << endl;
		mb->getVersion(this->BstrToStdString(vtProp.bstrVal));
		VariantClear(&vtProp);

		this->hres = this->pclsObj->Get(L"SlotLayout", 0, &vtProp, 0, 0);
		if (FALSE(this->hres)) cout << "\nInvalid getting of value!" << endl;
		mb->getSlotLayout(this->BstrToStdString(vtProp.bstrVal));
		VariantClear(&vtProp);

		this->hres = this->pclsObj->Get(L"SerialNumber", 0, &vtProp, 0, 0);
		if (FALSE(this->hres)) cout << "\nInvalid getting of value!" << endl;
		mb->getSerialNumber(this->BstrToStdString(vtProp.bstrVal));
		VariantClear(&vtProp);
	}
	return true;
}

bool AllHardware::WMIClass::getAllInfo(Hardware *hard)
{
	cout << "Load Information about Video Adapter" << endl;
	this->getInfoAbooutGpu(&hard->hard.gpu);
	cout << "Load information about Logical diskd" << endl;
	this->getInfoAboutLogicalDisks(&hard->hard.ldisk);
	cout << "Load information about Network adapters" << endl;
	this->getInfoAboutNetworkAdapters(&hard->hard.net);
	cout << "Load information about Operation system" << endl;
	this->getInfoAboutOperationSystem(&hard->hard.opsys);
	cout << "Load information about Processor" << endl;
	this->getInfoAboutProc(&hard->hard.proc);
	this->getCPUAndCurSpeedUsage(&hard->hard.proc);
	cout << "Load information about Process" << endl;
	this->getInfoAboutProccess(&hard->hard.procv);
	cout << "Load information about Disk Drive" << endl;
	this->getInformationAboutDiskDrive(&hard->hard.disk);
	cout << "Load information about Motherboard" << endl;
	this->getInformationAboutMotherBoard(&hard->hard.mb);
	cout << "Load information about Monitor" << endl;
	this->getInformationAboutMonitor(&hard->hard.monitor);
	return true;
}

bool AllHardware::WMIClass::getChangableInfo(Hardware * hard)
{
	this->getCPUAndCurSpeedUsage(&hard->hard.proc);
	this->getInfoAboutLogicalDisks(&hard->hard.ldisk);
	this->getInfoAboutNetworkAdapters(&hard->hard.net);
	this->getInfoAboutProccess(&hard->hard.procv);
	this->getInfo("FROM Win32_OperatingSystem", L"NumberOfProcesses");
	AllHardware::Os os;
	os.getNumberOfProcesses(this->inf->uintVal);
	hard->hard.opsys.push_back(os);
	return false;
}

bool AllHardware::WMIClass::getInformationAboutMonitor(Monitor *monitor)
{
	string str = "SELECT * FROM Win32_DesktopMonitor";
	this->hres = this->pSvc->ExecQuery(
		bstr_t("WQL"),
		bstr_t(str.c_str()),
		WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
		NULL,
		&pEnumerator);

	if (FAILED(this->hres))
	{
		cout << "Query for processes failed. "
			<< "Error code = 0x"
			<< hex << hres << endl;
		this->pSvc->Release();
		this->pLoc->Release();
		CoUninitialize();
		return false;               // Program has failed.
	}
	while (this->pEnumerator)
	{
		this->hres = this->pEnumerator->Next(WBEM_INFINITE, 1,
			&pclsObj, &uReturn);

		if (0 == this->uReturn)
		{
			break;
		}

		VARIANT vtProp;

		// Get the value of the Name property
		//cout << "Load caption" << endl;
		this->hres = this->pclsObj->Get(L"Caption", 0, &vtProp, 0, 0);
		if (FALSE(this->hres)) cout << "\nInvalid getting of value!" << endl;
		//cout << "Try to write caption to the class" << endl;
		monitor->getCaption(this->BstrToStdString(vtProp.bstrVal));
		//cout << "Caption succsesfully write" << endl;
		VariantClear(&vtProp);

		this->hres = this->pclsObj->Get(L"DisplayType", 0, &vtProp, 0, 0);
		if (FALSE(this->hres)) cout << "\nInvalid getting of value!" << endl;
		monitor->getDisplayType(vtProp.uintVal);
		VariantClear(&vtProp);

		this->hres = this->pclsObj->Get(L"MonitorManufacturer", 0, &vtProp, 0, 0);
		if (FALSE(this->hres)) cout << "\nInvalid getting of value!" << endl;
		monitor->getMonitorManufacturer(this->BstrToStdString(vtProp.bstrVal));
		VariantClear(&vtProp);

		this->hres = this->pclsObj->Get(L"MonitorType", 0, &vtProp, 0, 0);
		if (FALSE(this->hres)) cout << "\nInvalid getting of value!" << endl;
		monitor->getMonitorType(this->BstrToStdString(vtProp.bstrVal));
		VariantClear(&vtProp);

		this->hres = this->pclsObj->Get(L"Name", 0, &vtProp, 0, 0);
		if (FALSE(this->hres)) cout << "\nInvalid getting of value!" << endl;
		monitor->getName(this->BstrToStdString(vtProp.bstrVal));
		VariantClear(&vtProp);
	}

	return true;
}

AllHardware::WMIClass::~WMIClass()
{
	this->pSvc->Release();//
	this->pLoc->Release();
	this->pEnumerator->Release();
	this->pclsObj->Release();
	free(this->inf);
	CoUninitialize();
}

bool AllHardware::WMIClass::getInfoAboutProc(Processor *proc)
{
	this->hres = this->pSvc->ExecQuery(
		bstr_t("WQL"),
		bstr_t("SELECT * FROM Win32_Processor"),
		WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
		NULL,
		&pEnumerator);

	if (FAILED(this->hres))
	{
		cout << "Query for processes failed. "
			<< "Error code = 0x"
			<< hex << hres << endl;
		this->pSvc->Release();
		this->pLoc->Release();
		CoUninitialize();
		return false;               // Program has failed.
	}

	while (this->pEnumerator)
	{
		this->hres = this->pEnumerator->Next(WBEM_INFINITE, 1,
			&pclsObj, &uReturn);

		if (0 == this->uReturn)
		{
			break;
		}

		VARIANT vtProp;

		// Get the value of the Name property
		this->hres = this->pclsObj->Get(L"AddressWidth", 0, &vtProp, 0, 0);
		if (FALSE(this->hres)) cout << "\nInvalid getting of value!" << endl;
		proc->getAddressWidth(vtProp.uintVal);
		VariantClear(&vtProp);

		this->hres = this->pclsObj->Get(L"Architecture", 0, &vtProp, 0, 0);
		if (FALSE(this->hres)) cout << "\nInvalid getting of value!" << endl;
		proc->getArchitecture(vtProp.uintVal);
		VariantClear(&vtProp);

		this->hres = this->pclsObj->Get(L"Availability", 0, &vtProp, 0, 0);
		if (FALSE(this->hres)) cout << "\nInvalid getting of value!" << endl;
		proc->getAvailability(vtProp.uintVal);
		VariantClear(&vtProp);

		this->hres = this->pclsObj->Get(L"Caption", 0, &vtProp, 0, 0);
		if (FALSE(this->hres)) cout << "\nInvalid getting of value!" << endl;
		proc->getCaption(this->BstrToStdString(vtProp.bstrVal));
		VariantClear(&vtProp);

		this->hres = this->pclsObj->Get(L"ExtClock", 0, &vtProp, 0, 0);
		if (FALSE(this->hres)) cout << "\nInvalid getting of value!" << endl;
		proc->getExtClock(vtProp.uintVal / 1000.0);
		VariantClear(&vtProp);

		this->hres = this->pclsObj->Get(L"Family", 0, &vtProp, 0, 0);
		if (FALSE(this->hres)) cout << "\nInvalid getting of value!" << endl;
		proc->getFamily(vtProp.uintVal);
		VariantClear(&vtProp);

		this->hres = this->pclsObj->Get(L"L2CacheSize", 0, &vtProp, 0, 0);
		if (FALSE(this->hres)) cout << "\nInvalid getting of value!" << endl;
		proc->getL2Size(vtProp.uintVal);
		VariantClear(&vtProp);

		this->hres = this->pclsObj->Get(L"L3CacheSize", 0, &vtProp, 0, 0);
		if (FALSE(this->hres)) cout << "\nInvalid getting of value!" << endl;
		proc->getL3Size(vtProp.uintVal);
		VariantClear(&vtProp);

		this->hres = this->pclsObj->Get(L"Manufacturer", 0, &vtProp, 0, 0);
		if (FALSE(this->hres)) cout << "\nInvalid getting of value!" << endl;
		proc->getManufacturer(this->BstrToStdString(vtProp.bstrVal));
		VariantClear(&vtProp);

		this->hres = this->pclsObj->Get(L"MaxClockSpeed", 0, &vtProp, 0, 0);
		if (FALSE(this->hres)) cout << "\nInvalid getting of value!" << endl;
		proc->getMaxSpeed(vtProp.uintVal / 1000.0);
		VariantClear(&vtProp);

		this->hres = this->pclsObj->Get(L"Name", 0, &vtProp, 0, 0);
		if (FALSE(this->hres)) cout << "\nInvalid getting of value!" << endl;
		proc->getName(this->BstrToStdString(vtProp.bstrVal));
		VariantClear(&vtProp);

		this->hres = this->pclsObj->Get(L"NumberOfCores", 0, &vtProp, 0, 0);
		if (FALSE(this->hres)) cout << "\nInvalid getting of value!" << endl;
		proc->getNumberOfCores(vtProp.uintVal);
		VariantClear(&vtProp);

		this->hres = this->pclsObj->Get(L"NumberOfEnabledCore", 0, &vtProp, 0, 0);
		if (FALSE(this->hres)) cout << "\nInvalid getting of value!" << endl;
		proc->getNumberOfEnabledCores(vtProp.uintVal);
		VariantClear(&vtProp);

		this->hres = this->pclsObj->Get(L"NumberOfLogicalProcessors", 0, &vtProp, 0, 0);
		if (FALSE(this->hres)) cout << "\nInvalid getting of value!" << endl;
		proc->getNumberOfLogicalPrroc(vtProp.uintVal);
		VariantClear(&vtProp);

		this->hres = this->pclsObj->Get(L"ThreadCount", 0, &vtProp, 0, 0);
		if (FALSE(this->hres)) cout << "\nInvalid getting of value!" << endl;
		proc->getThreadsCount(vtProp.uintVal);
		VariantClear(&vtProp);
	}
	return true;
}

AllHardware::WMIClass::WMIClass()
{
		this->pLoc = NULL;
		this->pSvc = NULL;
		this->pEnumerator = NULL;
		this->pclsObj = NULL;
		this->uReturn = 0;
		this->inf = (struct Info*)malloc(sizeof(struct Info));
		if (!this->inf)
		{
			exit(1);
		}

		// Step 1: --------------------------------------------------
		// Initialize COM. ------------------------------------------

		this->hres = CoInitializeEx(0, COINIT_MULTITHREADED);
		if (FAILED(this->hres)) 
		{
			cout << "Failed to initialize COM library. Error code = 0x"
				<< hex << hres << endl;
			return;                  // Program has failed.
		}

		// Step 2: --------------------------------------------------
		// Set general COM security levels --------------------------

		this->hres = CoInitializeSecurity(
			NULL,
			-1,                          // COM authentication
			NULL,                        // Authentication services
			NULL,                        // Reserved
			RPC_C_AUTHN_LEVEL_DEFAULT,   // Default authentication 
			RPC_C_IMP_LEVEL_IMPERSONATE, // Default Impersonation  
			NULL,                        // Authentication info
			EOAC_NONE,                   // Additional capabilities 
			NULL                         // Reserved
		);


		if (FAILED(this->hres))
		{
			cout << "Failed to initialize security. Error code = 0x"
				<< hex << this->hres << endl;
			CoUninitialize();
			return;                    // Program has failed.
		}

		// Step 3: ---------------------------------------------------
		// Obtain the initial locator to WMI -------------------------

		this->hres = CoCreateInstance(
			CLSID_WbemLocator,
			0,
			CLSCTX_INPROC_SERVER,
			IID_IWbemLocator, (LPVOID *)&pLoc);

		if (FAILED(this->hres))
		{
			cout << "Failed to create IWbemLocator object."
				<< " Err code = 0x"
				<< hex << this->hres << endl;
			CoUninitialize();
			return;                 // Program has failed.
		}

		// Step 4: -----------------------------------------------------
		// Connect to WMI through the IWbemLocator::ConnectServer method
		// Connect to the root\cimv2 namespace with
		// the current user and obtain pointer pSvc
		// to make IWbemServices calls.
		this->hres = this->pLoc->ConnectServer(
			_bstr_t(L"ROOT\\CIMV2"), // Object path of WMI namespace
			NULL,                    // User name. NULL = current user
			NULL,                    // User password. NULL = current
			0,                       // Locale. NULL indicates current
			NULL,                    // Security flags.
			0,                       // Authority (for example, Kerberos)
			0,                       // Context object 
			&pSvc                    // pointer to IWbemServices proxy
		);

		if (FAILED(this->hres))
		{
			cout << "Could not connect. Error code = 0x"
				<< hex << this->hres << endl;
			this->pLoc->Release();
			CoUninitialize();
			return;                // Program has failed.
		}

		//cout << "Connected to ROOT\\CIMV2 WMI namespace" << endl;


		// Step 5: --------------------------------------------------
		// Set security levels on the proxy -------------------------

		this->hres = CoSetProxyBlanket(
			this->pSvc,                        // Indicates the proxy to set
			RPC_C_AUTHN_WINNT,           // RPC_C_AUTHN_xxx
			RPC_C_AUTHZ_NONE,            // RPC_C_AUTHZ_xxx
			NULL,                        // Server principal name 
			RPC_C_AUTHN_LEVEL_CALL,      // RPC_C_AUTHN_LEVEL_xxx 
			RPC_C_IMP_LEVEL_IMPERSONATE, // RPC_C_IMP_LEVEL_xxx
			NULL,                        // client identity
			EOAC_NONE                    // proxy capabilities 
		);

		if (FAILED(this->hres))
		{
			cout << "Could not set proxy blanket. Error code = 0x"
				<< hex << this->hres << endl;
			this->pSvc->Release();
			this->pLoc->Release();
			CoUninitialize();
			return;               // Program has failed.
		}
}

string& AllHardware::WMIClass::BstrToStdString(const BSTR bstr, string& dst, int cp)
{
	if (!bstr)
	{
		// define NULL functionality. I just clear the target.
		dst.clear();
		return dst;
	}

	// request content length in single-chars through a terminating
	//  nullchar in the BSTR. note: BSTR's support imbedded nullchars,
	//  so this will only convert through the first nullchar.
	int res = WideCharToMultiByte(cp, 0, bstr, -1, NULL, 0, NULL, NULL);
	if (res > 0)
	{
		dst.resize(res);
		WideCharToMultiByte(cp, 0, bstr, -1, &dst[0], res, NULL, NULL);
	}
	else
	{    // no content. clear target
		dst.clear();
	}
	return dst;
}

string AllHardware::WMIClass::BstrToStdString(BSTR bstr, int cp)
{
	string str;
	BstrToStdString(bstr, str, cp);
	return str;
}