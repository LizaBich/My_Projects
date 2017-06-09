#pragma once
#include "stdafx.h"
#include "NewMemoryDevice.h"
#include "NewProcessor.h"
#include "NewLogicalDisk.h"
#include "NewGpu.h"
#include "NewProcess.h"
#include "NewOs.h"
#include "NewNetworkAdapter.h"
#include "NewDiskDrive.h"
#include "NewMotherBoard.h"
#include "NewMonitor.h"
#define BUFFER_SIZE sizeof(TransferData)
#define FILENAME "hardware.bin"

using namespace std;

namespace AllHardware {
	struct HardwareClasses
	{
		Processor proc;
		MemoryDevice mem;
		Gpu gpu;
		MotherBoard mb;
		vector<LogicalDisk> ldisk;
		vector<DiskDrive> disk;
		vector<Network> net;
		vector<Os> opsys;
		vector<Process> procv;
		Monitor monitor;
	};

	class Hardware
	{	
	public:
		struct HardwareClasses hard;

		Hardware() {}
		Hardware(const Hardware &);
		~Hardware() {}
		struct HardwareClasses setHardwareStruct() const
		{
			return this->hard;
		}
		Hardware &operator=(const Hardware &);


		void WriteToFile(int flag)
		{
			try {
				BINARFILE *bFile = new BINARFILE(FILENAME);
				if (flag == 0) {
					bFile->ToFile(std::to_string(this->hard.disk.size()), 0);
					for (int i = 0; i < this->hard.disk.size(); this->hard.disk[i].ToFile(bFile), i++);

					this->hard.gpu.ToFile(bFile);

					bFile->ToFile(std::to_string(this->hard.ldisk.size()), 1);
					for (int i = 0; i < this->hard.ldisk.size(); this->hard.ldisk[i].ToFile(bFile), i++);

					this->hard.mb.ToFile(bFile);

					bFile->ToFile(std::to_string(this->hard.net.size()), 1);
					for (int i = 0; i < this->hard.net.size(); this->hard.net[i].ToFile(bFile), i++);

					bFile->ToFile(std::to_string(this->hard.opsys.size()), 1);
					for (int i = 0; i < this->hard.opsys.size(); this->hard.opsys[i].ToFile(bFile), i++);

					this->hard.proc.WriteToFile(bFile);

					bFile->ToFile(std::to_string(this->hard.procv.size()), 1);
					for (int i = 0; i < this->hard.procv.size(); this->hard.procv[i].ToFile(bFile), i++);

					this->hard.monitor.ToFile(bFile);
				}
				else 
				{
					bFile->ToFile(std::to_string(this->hard.ldisk.size()), 0);
					for (int i = 0; i < this->hard.ldisk.size(); this->hard.ldisk[i].ToFile(bFile), i++);

					bFile->ToFile(std::to_string(this->hard.net.size()), 1);
					for (int i = 0; i < this->hard.net.size(); this->hard.net[i].ToFile(bFile), i++);

					bFile->ToFile(std::to_string(this->hard.opsys.size()), 1);
					for (int i = 0; i < this->hard.opsys.size(); this->hard.opsys[i].ToFile(bFile), i++);

					this->hard.proc.WriteToFile(bFile);

					bFile->ToFile(std::to_string(this->hard.procv.size()), 1);
					for (int i = 0; i < this->hard.procv.size(); this->hard.procv[i].ToFile(bFile), i++);
				}

				delete bFile;
			}
			catch (...) {
				cout << "\n\nERROR IN WRITE-FUN.\n\n";
				return;
			}
			return;
		}
		void ReadFromFile(int);
	};
}

struct TransferData
{
	AllHardware::Hardware *hardware;
	int flag;
};