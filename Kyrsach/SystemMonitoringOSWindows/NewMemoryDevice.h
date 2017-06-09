#pragma once
#include "stdafx.h"

using namespace std;

namespace AllHardware {
	class MemoryDevice
	{
		MEMORYSTATUSEX memInf;

	public:
		MemoryDevice()
		{
			this->memInf.dwLength = sizeof(MEMORYSTATUSEX);
		}

		MemoryDevice(const MemoryDevice &ob)
		{
			this->memInf.dwLength = ob.memInf.dwLength;
			this->memInf.dwMemoryLoad = ob.memInf.dwMemoryLoad;
			this->memInf.ullAvailExtendedVirtual = ob.memInf.ullAvailExtendedVirtual;
			this->memInf.ullAvailPageFile = ob.memInf.ullAvailPageFile;
			this->memInf.ullAvailPhys = ob.memInf.ullAvailPhys;
			this->memInf.ullAvailVirtual = ob.memInf.ullAvailVirtual;
			this->memInf.ullTotalPageFile = ob.memInf.ullTotalPageFile;
			this->memInf.ullTotalPhys = ob.memInf.ullTotalPhys;
			this->memInf.ullTotalVirtual = ob.memInf.ullTotalVirtual;
		}

		unsigned long long setTotalMemory()
		{
			GlobalMemoryStatusEx(&this->memInf);
			return this->memInf.ullTotalPhys;
		}

		unsigned long long setTotalVirtualMemory()
		{
			GlobalMemoryStatusEx(&this->memInf);
			return this->memInf.ullTotalPageFile;
		}

		unsigned long long setFreeMemory()
		{
			GlobalMemoryStatusEx(&this->memInf);
			return this->memInf.ullAvailPhys;
		}

		unsigned long long setFreeVirtualMemory()
		{
			GlobalMemoryStatusEx(&this->memInf);
			return this->memInf.ullAvailPageFile;
		}

		MemoryDevice& operator=(const MemoryDevice &ob)
		{
			if (this == &ob)
			{
				return *this;
			}
			else {
				this->memInf.dwLength = ob.memInf.dwLength;
				this->memInf.dwMemoryLoad = ob.memInf.dwMemoryLoad;
				this->memInf.ullAvailExtendedVirtual = ob.memInf.ullAvailExtendedVirtual;
				this->memInf.ullAvailPageFile = ob.memInf.ullAvailPageFile;
				this->memInf.ullAvailPhys = ob.memInf.ullAvailPhys;
				this->memInf.ullAvailVirtual = ob.memInf.ullAvailVirtual;
				this->memInf.ullTotalPageFile = ob.memInf.ullTotalPageFile;
				this->memInf.ullTotalPhys = ob.memInf.ullTotalPhys;
				this->memInf.ullTotalVirtual = ob.memInf.ullTotalVirtual;
			}
			return *this;
		}
	};
}