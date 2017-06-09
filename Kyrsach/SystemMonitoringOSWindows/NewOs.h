#pragma once
#include "stdafx.h"
#include "..\GetInfoWithWMI\FILE.h"

using namespace std;

namespace AllHardware {
	class Os
	{
		char mask[11];
		string buildNumber;//					// при желании, зная этот параметр можно получить больше информации об ОС
		string caption;//
		string CSName;//						// name of the scoping computer system
		string manufacturer;//
		int currentNumberOfProcesses;//
		string operationSystemSKU;//
		string OSArchitecture;//
		string serialNumber;//
		string systemDevice;//				// physical disk on which the operation system is installed
		string systemDirectory;//
		string version;//

		std::string CreatMask()
		{
			if (this->buildNumber.size() > 0) this->mask[0] = '1';
			if (this->caption.size() > 0) this->mask[1] = '1';
			if (this->CSName.size() > 0) this->mask[2] = '1';
			if (this->manufacturer.size() > 0) this->mask[3] = '1';
			if (this->currentNumberOfProcesses >= 0) this->mask[4] = '1';
			if (this->operationSystemSKU.size() > 0) this->mask[5] = '1';
			if (this->OSArchitecture.size() > 0) this->mask[6] = '1';
			if (this->serialNumber.size() > 0) this->mask[7] = '1';
			if (this->systemDevice.size() > 0) this->mask[8] = '1';
			if (this->systemDirectory.size() > 0) this->mask[9] = '1';
			if (this->version.size() > 0) this->mask[10] = '1';
			return std::string(this->mask);
		}

		void ReadMask(const char *base)
		{
			for (int i = 0; i < 11; this->mask[i] = *(base + i), i++);
		}

	public:
		Os()
		{
			this->currentNumberOfProcesses = 0;
			for (int i = 0; i < 11; this->mask[i] = '0', i++);
		}
		Os(const Os &ob)
		{
			this->buildNumber = ob.buildNumber;
			this->caption = ob.caption;
			this->CSName = ob.CSName;
			this->currentNumberOfProcesses = ob.currentNumberOfProcesses;
			this->manufacturer = ob.manufacturer;
			this->operationSystemSKU = ob.operationSystemSKU;
			this->OSArchitecture = ob.OSArchitecture;
			this->serialNumber = ob.serialNumber;
			this->systemDevice = ob.systemDevice;
			this->systemDirectory = ob.systemDirectory;
			this->version = ob.version;
			for (int i = 0; i < 11; this->mask[i] = ob.mask[i], i++);
		}

		void getBuildNumber(string bnum)
		{
			this->buildNumber = bnum;
		}

		void getCaption(string caption)
		{
			this->caption = caption;
		}

		void getCSName(string csname)
		{
			this->CSName = csname;
		}

		void getManufacturer(string manuf)
		{
			this->manufacturer = manuf;
		}

		void getNumberOfProcesses(int nop)
		{
			this->currentNumberOfProcesses = nop;
		}

		void getOperatingSystemSKU(int sw)
		{
			switch (sw)
			{
			case 0: this->operationSystemSKU = "Undefined";
				break;
			case 1: this->operationSystemSKU = "Ultimate Edition";
				break;
			case 2: this->operationSystemSKU = "Home Basic Edition";
				break;
			case 3: this->operationSystemSKU = "Home Premium Edition";
				break;
			case 4: this->operationSystemSKU = "Enterprise Edition";
				break;
			case 6: this->operationSystemSKU = "Business Edition";
				break;
			case 7: this->operationSystemSKU = "Windows Server Standard Edition (Desktop Experience installation)";
				break;
			case 8: this->operationSystemSKU = "Windows Server Datacenter Edition (Desktop Experience installation)";
				break;
			case 9: this->operationSystemSKU = "Small Business Server Edition";
				break;
			case 10: this->operationSystemSKU = "Enterprise Server Edition";
				break;
			case 11: this->operationSystemSKU = "Starter Edition";
				break;
			case 12: this->operationSystemSKU = "Datacenter Server Core Edition";
				break;
			case 13: this->operationSystemSKU = "Standard Server Core Edition";
				break;
			case 14: this->operationSystemSKU = "Enterprise Server Core Edition";
				break;
			case 17: this->operationSystemSKU = "Web Server Edition";
				break;
			case 19: this->operationSystemSKU = "Home Server Edition";
				break;
			case 20: this->operationSystemSKU = "Storage Express Server Edition";
				break;
			case 21: this->operationSystemSKU = "Windows Storage Server Standard Edition (Desktop Experience installation)";
				break;
			case 22: this->operationSystemSKU = "Windows Storage Server Workgroup Edition (Desktop Experience installation)";
				break;
			case 23: this->operationSystemSKU = "Storage Enterprise Server Edition";
				break;
			case 24: this->operationSystemSKU = "Server For Small Business Edition";
				break;
			case 25: this->operationSystemSKU = "Small Business Server Premium Edition";
				break;
			case 27: this->operationSystemSKU = "Windows Enterprise Edition";
				break;
			case 28: this->operationSystemSKU = "Windows Ultimate Edition";
				break;
			case 29: this->operationSystemSKU = "Windows Server Web Server Edition (Server Core installation)";
				break;
			case 36: this->operationSystemSKU = "Windows Server Standard Edition without Hyper-V";
				break;
			case 37: this->operationSystemSKU = "Windows Server Datacenter Edition without Hyper-V (full installation)";
				break;
			case 38: this->operationSystemSKU = "Windows Server Enterprise Edition without Hyper-V (full installation)";
				break;
			case 39: this->operationSystemSKU = "Windows Server Datacenter Edition without Hyper-V (Server Core installation)";
				break;
			case 40: this->operationSystemSKU = "Windows Server Standard Edition without Hyper-V (Server Core installation)";
				break;
			case 41: this->operationSystemSKU = "Windows Server Enterprise Edition without Hyper-V (Server Core installation)";
				break;
			case 42: this->operationSystemSKU = "Microsoft Hyper-V Server";
				break;
			case 43: this->operationSystemSKU = "Storage Server Express Edition (Server Core installation)";
				break;
			case 44: this->operationSystemSKU = "Storage Server Standard Edition (Server Core installation)";
				break;
			case 45: this->operationSystemSKU = "Storage Server Workgroup Edition (Server Core installation)";
				break;
			case 46: this->operationSystemSKU = "Storage Server Enterprise Edition (Server Core installation)";
				break;
			case 50: this->operationSystemSKU = "Windows Server Essentials (Desktop Experience installation)";
				break;
			case 63: this->operationSystemSKU = "Small Business Server Premium (Server Core installation)";
				break;
			case 64: this->operationSystemSKU = "Windows Compute Cluster Server without Hyper-V";
				break;
			case 97: this->operationSystemSKU = "Windows RT";
				break;
			case 101: this->operationSystemSKU = "Windows Home";
				break;
			case 103: this->operationSystemSKU = "Windows Professional with Media Center";
				break;
			case 104: this->operationSystemSKU = "Windows Mobile";
				break;
			case 121: this->operationSystemSKU = "Windows Education Edition";
				break;
			case 123: this->operationSystemSKU = "Windows IoT (Internet of Things) Core";
				break;
			case 143: this->operationSystemSKU = "Windows Server Datacenter Edition (Nano Server installation)";
				break;
			case 144: this->operationSystemSKU = "Windows Server Standard Edition (Nano Server installation)";
				break;
			case 147: this->operationSystemSKU = "Windows Server Datacenter Edition (Server Core installation)";
				break;
			case 148: this->operationSystemSKU = "Windows Server Standard Edition (Server Core installation)";
				break;
			default: this->operationSystemSKU = "Unknown";
				break;
			}
		}

		void getOSArchitecture(string arch)
		{
			this->OSArchitecture = arch;
		}

		void getSerialNumber(string sn)
		{
			this->serialNumber = sn;
		}

		void getSystemDevice(string sysd)
		{
			this->systemDevice = sysd;
		}

		void getSystemDirectory(string sysd)
		{
			this->systemDirectory = sysd;
		}

		void getVersion(string v)
		{
			this->version = v;
		}

		const char *setBuildNumber() const
		{
			return this->buildNumber.c_str();
		}

		const char *setCaption() const
		{
			return this->caption.c_str();
		}

		const char *setCSName() const
		{
			return this->CSName.c_str();
		}

		const char *setManufacturer() const
		{
			return this->manufacturer.c_str();
		}

		int setNumberOfProcesses() const
		{
			return this->currentNumberOfProcesses;
		}

		const char *setOperatingSystemSKU() const
		{
			return this->operationSystemSKU.c_str();

		}

		const char *setOSArchitecture() const
		{
			return this->OSArchitecture.c_str();
		}

		const char *setSerialNumber() const
		{
			return this->serialNumber.c_str();
		}

		const char *setSystemDevice() const
		{
			return this->systemDevice.c_str();
		}

		const char *setSystemDirectory() const
		{
			return this->systemDirectory.c_str();
		}

		const char *setVersion() const
		{
			return this->version.c_str();
		}

		Os& operator=(const Os &ob)
		{
			if (this == &ob)
			{
				return *this;
			}
			this->buildNumber = ob.buildNumber;
			this->caption = ob.caption;
			this->CSName = ob.CSName;
			this->currentNumberOfProcesses = ob.currentNumberOfProcesses;
			this->manufacturer = ob.manufacturer;
			this->operationSystemSKU = ob.operationSystemSKU;
			this->OSArchitecture = ob.OSArchitecture;
			this->serialNumber = ob.serialNumber;
			this->systemDevice = ob.systemDevice;
			this->systemDirectory = ob.systemDirectory;
			this->version = ob.version;
			for (int i = 0; i < 11; this->mask[i] = ob.mask[i], i++);
			return *this;
		}

		void ToFile(BINARFILE *bFile) 
		{
			bFile->ToFile(this->CreatMask(), 1);
			if (this->mask[0] == '1') bFile->ToFile(this->buildNumber, 1);
			if (this->mask[1] == '1') bFile->ToFile(this->caption, 1);
			if (this->mask[2] == '1') bFile->ToFile(this->CSName, 1);
			if (this->mask[3] == '1') bFile->ToFile(this->manufacturer, 1);
			if (this->mask[4] == '1') bFile->ToFile(std::to_string(this->currentNumberOfProcesses), 1);
			if (this->mask[5] == '1') bFile->ToFile(this->operationSystemSKU, 1);
			if (this->mask[6] == '1') bFile->ToFile(this->OSArchitecture, 1);
			if (this->mask[7] == '1') bFile->ToFile(this->serialNumber, 1);
			if (this->mask[8] == '1') bFile->ToFile(this->systemDevice, 1);
			if (this->mask[9] == '1') bFile->ToFile(this->systemDirectory, 1);
			if (this->mask[10] == '1') bFile->ToFile(this->version, 1);
		}

		void FromFile(BINARFILE *bFile)
		{
			this->ReadMask(bFile->FromFile().c_str());
			if (this->mask[0] == '1') this->buildNumber = bFile->FromFile();
			if (this->mask[1] == '1') this->caption = bFile->FromFile();
			if (this->mask[2] == '1') this->CSName = bFile->FromFile();
			if (this->mask[3] == '1') this->manufacturer = bFile->FromFile();
			if (this->mask[4] == '1') this->currentNumberOfProcesses = std::stoi(bFile->FromFile());
			if (this->mask[5] == '1') this->operationSystemSKU = bFile->FromFile();
			if (this->mask[6] == '1') this->OSArchitecture = bFile->FromFile();
			if (this->mask[7] == '1') this->serialNumber = bFile->FromFile();
			if (this->mask[8] == '1') this->systemDevice = bFile->FromFile();
			if (this->mask[9] == '1') this->systemDirectory = bFile->FromFile();
			if (this->mask[10] == '1') this->version = bFile->FromFile();
		}
	};
}