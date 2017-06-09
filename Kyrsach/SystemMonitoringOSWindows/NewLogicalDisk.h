#pragma once
#include "stdafx.h"
#include "..\GetInfoWithWMI\FILE.h"

using namespace std;

namespace AllHardware {
	class LogicalDisk
	{
		char mask[9];
		double blockSize;//
		string driveType;//
		string deviceID;//
		string fileSystem;//
		unsigned long long freeSpace;//
		unsigned long long availableFreeSpace;//
		double maxComponentLenght;//
		double numberOfBlocks;//
		unsigned long long size;//

		std::string CreatMask()
		{
			if (this->blockSize >= 0) this->mask[0] = '1';
			if (this->driveType.size() > 0) this->mask[1] = '1';
			if (this->deviceID.size() > 0) this->mask[2] = '1';
			if (this->fileSystem.size() > 0) this->mask[3] = '1';
			if (this->freeSpace >= 0) this->mask[4] = '1';
			if (this->availableFreeSpace >= 0) this->mask[5] = '1';
			if (this->maxComponentLenght >= 0) this->mask[6] = '1';
			if (this->numberOfBlocks >= 0) this->mask[7] = '1';
			if (this->size >= 0) this->mask[8] = '1';
			return std::string(this->mask);
		}

		void ReadMask(const char *base)
		{
			for (int i = 0; i < 9; this->mask[i] = *(base + i), i++);
		}

	public:
		LogicalDisk() {
			this->blockSize = 0;
			this->freeSpace = 0;
			this->availableFreeSpace = 0;
			this->maxComponentLenght = 0;
			this->numberOfBlocks = 0;
			this->size = 0;
			for (int i = 0; i < 9; this->mask[i] = '0', i++);
		}

		LogicalDisk(const LogicalDisk &ob)
		{
			this->availableFreeSpace = ob.availableFreeSpace;
			this->blockSize = ob.blockSize;
			this->deviceID = ob.deviceID;
			this->driveType = ob.driveType;
			this->fileSystem = ob.fileSystem;
			this->freeSpace = ob.freeSpace;
			this->maxComponentLenght = ob.maxComponentLenght;
			this->numberOfBlocks = ob.numberOfBlocks;
			this->size = ob.size;
			for (int i = 0; i < 9; this->mask[i] = ob.mask[i], i++);
		}

		void getBlockSize(long long bl)
		{
			this->blockSize = bl / 1.0;
		}

		void getDriveType(int drt)
		{
			switch (drt)
			{
			case 0:
				this->driveType = "Unknown";
				break;
			case 1:
				this->driveType = "No root directory";
				break;
			case 2:
				this->driveType = "Removable disk";
				break;
			case 3:
				this->driveType = "Local Disk";
				break;
			case 4:
				this->driveType = "Network Drive";
				break;
			case 5:
				this->driveType = "Compact Disc";
				break;
			case 6:
				this->driveType = "RAM Disk";
				break;
			}
		}

		void getFileSystem(string flsys)
		{
			this->fileSystem = flsys;
		}

		void getFreeSpace(unsigned long long frsp)
		{
			this->freeSpace = frsp;
		}

		void getAvailableFreeSpace(unsigned long long frsp)
		{
			this->availableFreeSpace = frsp;
		}

		void getMaxComponentLenght(double mcl)
		{
			this->maxComponentLenght = mcl;
		}

		void getNumberOfBlocks(double num)
		{
			this->numberOfBlocks = num;
		}

		void getSize(unsigned long long s)
		{
			this->size = s;
		}

		void getDeviceID(string did)
		{
			this->deviceID = did;
		}

		double setBlockSize() const
		{
			return this->blockSize;
		}

		const char *setDriveType() const
		{
			return this->driveType.c_str();
		}

		const char *setFileSystem() const
		{
			return this->fileSystem.c_str();
		}

		unsigned long long setFreeSpace() const
		{
			return this->freeSpace;
		}

		unsigned long long setFreeSpaceAvailable() const
		{
			return this->availableFreeSpace;
		}

		double setMaxComponentLenght() const
		{
			return this->maxComponentLenght;
		}

		double setNumberOfBlocks() const
		{
			return this->numberOfBlocks;
		}

		unsigned long long setSize() const
		{
			return this->size;
		}

		const char *setDeviceID() const
		{
			return this->deviceID.c_str();
		}

		LogicalDisk& operator=(const LogicalDisk &ob)
		{
			if (this == &ob)
			{
				return *this;
			}
			else {
				this->availableFreeSpace = ob.availableFreeSpace;
				this->blockSize = ob.blockSize;
				this->deviceID = ob.deviceID;
				this->driveType = ob.driveType;
				this->fileSystem = ob.fileSystem;
				this->freeSpace = ob.freeSpace;
				this->maxComponentLenght = ob.maxComponentLenght;
				this->numberOfBlocks = ob.numberOfBlocks;
				this->size = ob.size;
				for (int i = 0; i < 9; this->mask[i] = ob.mask[i], i++);
			}
			return *this;
		}

		void ToFile(BINARFILE *bFile)
		{
			bFile->ToFile(this->CreatMask(), 1);
			if (this->mask[0] == '1') bFile->ToFile(std::to_string(this->blockSize), 1);
			if (this->mask[1] == '1') bFile->ToFile(this->driveType, 1);
			if (this->mask[2] == '1') bFile->ToFile(this->deviceID, 1);
			if (this->mask[3] == '1') bFile->ToFile(this->fileSystem, 1);
			if (this->mask[4] == '1') bFile->ToFile(std::to_string(this->freeSpace), 1);
			if (this->mask[5] == '1') bFile->ToFile(std::to_string(this->availableFreeSpace), 1);
			if (this->mask[6] == '1') bFile->ToFile(std::to_string(this->maxComponentLenght), 1);
			if (this->mask[7] == '1') bFile->ToFile(std::to_string(this->numberOfBlocks), 1);
			if (this->mask[8] == '1') bFile->ToFile(std::to_string(this->size), 1);
		}

		void FromFile(BINARFILE *bFile)
		{
			this->ReadMask(bFile->FromFile().c_str());
			if (this->mask[0] == '1') this->blockSize = std::stod(bFile->FromFile());
			if (this->mask[1] == '1') this->driveType = bFile->FromFile();
			if (this->mask[2] == '1') this->deviceID = bFile->FromFile();
			if (this->mask[3] == '1') this->fileSystem = bFile->FromFile();
			if (this->mask[4] == '1') this->freeSpace = std::stoull(bFile->FromFile());
			if (this->mask[5] == '1') this->availableFreeSpace = std::stoull(bFile->FromFile());
			if (this->mask[6] == '1') this->maxComponentLenght = std::stod(bFile->FromFile());
			if (this->mask[7] == '1') this->numberOfBlocks = std::stod(bFile->FromFile());
			if (this->mask[8] == '1') this->size = std::stoull(bFile->FromFile());
		}
	};
}