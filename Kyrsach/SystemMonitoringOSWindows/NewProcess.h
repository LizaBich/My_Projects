#pragma once
#include "stdafx.h"
#include "..\GetInfoWithWMI\FILE.h"

using namespace std;

namespace AllHardware {
	class Process
	{
		char mask[8];
		string executablePath;//          // путь к процессу
		string handle;//					// идентификатор процесса
		int handleCount;//				// кол-во запущенных процессов
		string name;//
		int parentProcessID;//
		int processID;//
		int threadCount;//				// кол-во потоков
		long long workingSetSize;//

		std::string CreatMask()
		{
			if (this->executablePath.size() > 0) this->mask[0] = '1';
			if (this->handle.size() > 0) this->mask[1] = '1';
			if (this->handleCount >= 0) this->mask[2] = '1';
			if (this->name.size() > 0) this->mask[3] = '1';
			if (this->parentProcessID >= 0) this->mask[4] = '1';
			if (this->processID >= 0) this->mask[5] = '1';
			if (this->threadCount >= 0) this->mask[6] = '1';
			if (this->workingSetSize >= 0) this->mask[7] = '1';
			return std::string(this->mask);
		}

		void ReadMask(const char *base)
		{
			for (int i = 0; i < 8; this->mask[i] = *(base + i), i++);
		}
	public:

		Process()
		{
			this->handleCount = 0;
			this->parentProcessID = 0;
			this->processID = 0;
			this->threadCount = 0;
			this->workingSetSize = 0;
			for (int i = 0; i < 8; this->mask[i] = '0', i++);
		}
		Process(const Process &ob)
		{
			this->executablePath = ob.executablePath;
			this->handle = ob.handle;
			this->handleCount = ob.handleCount;
			this->name = ob.name;
			this->parentProcessID = ob.parentProcessID;
			this->processID = ob.processID;
			this->threadCount = ob.threadCount;
			this->workingSetSize = ob.workingSetSize;
			for (int i = 0; i < 8; this->mask[i] = ob.mask[i], i++);
		}

		void getExecutablePath(string path)
		{
			this->executablePath = path;
		}

		void getHandle(string hand)
		{
			this->handle = hand;
		}

		void getHandleCount(int count)
		{
			this->handleCount = count;
		}

		void getName(string name)
		{
			this->name = name;
		}

		void getParentProcessID(int pID)
		{
			this->parentProcessID = pID;
		}

		void getProcessID(int pID)
		{
			this->processID = pID;
		}

		void getThreadCount(int tcount)
		{
			this->threadCount = tcount;
		}

		void getWorkingSetSize(long long wssize)
		{
			this->workingSetSize = wssize;
		}

		const char *setExecutablePath() const
		{
			return this->executablePath.c_str();
		}

		const char *setHandle() const
		{
			return this->executablePath.c_str();
		}

		int setHandleCount() const
		{
			return this->handleCount;
		}

		const char *setName() const
		{
			return this->name.c_str();
		}

		int setParentProccessID() const
		{
			return this->parentProcessID;
		}

		int setProccessID() const
		{
			return this->processID;
		}

		int setThreadCount() const
		{
			return this->threadCount;
		}

		long long setWorkingSetSize() const
		{
			return this->workingSetSize;
		}

		Process& operator=(const Process &ob)
		{
			if (this == &ob)
			{
				return *this;
			}
			this->executablePath = ob.executablePath;
			this->handle = ob.handle;
			this->handleCount = ob.handleCount;
			this->name = ob.name;
			this->parentProcessID = ob.parentProcessID;
			this->processID = ob.processID;
			this->threadCount = ob.threadCount;
			this->workingSetSize = ob.workingSetSize;
			for (int i = 0; i < 8; this->mask[i] = ob.mask[i], i++);
			return *this;
		}

		void ToFile(BINARFILE *bFile)
		{
			bFile->ToFile(this->CreatMask(), 1);
			if (this->mask[0] == '1') bFile->ToFile(this->executablePath, 1);
			if (this->mask[1] == '1') bFile->ToFile(this->handle, 1);
			if (this->mask[2] == '1') bFile->ToFile(std::to_string(this->handleCount), 1);
			if (this->mask[3] == '1') bFile->ToFile(this->name, 1);
			if (this->mask[4] == '1') bFile->ToFile(std::to_string(this->parentProcessID), 1);
			if (this->mask[5] == '1') bFile->ToFile(std::to_string(this->processID), 1);
			if (this->mask[6] == '1') bFile->ToFile(std::to_string(this->threadCount), 1);
			if (this->mask[7] == '1') bFile->ToFile(std::to_string(this->workingSetSize), 1);
		}

		void FromFile(BINARFILE *bFile)
		{
			this->ReadMask(bFile->FromFile().c_str());
			if (this->mask[0] == '1') this->executablePath = bFile->FromFile();
			if (this->mask[1] == '1') this->handle = bFile->FromFile();
			if (this->mask[2] == '1') this->handleCount = std::stoi(bFile->FromFile());
			if (this->mask[3] == '1') this->name = bFile->FromFile();
			if (this->mask[4] == '1') this->parentProcessID = std::stoi(bFile->FromFile());
			if (this->mask[5] == '1') this->processID = std::stoi(bFile->FromFile());
			if (this->mask[6] == '1') this->threadCount = std::stoi(bFile->FromFile());
			if (this->mask[7] == '1') this->workingSetSize = std::stoll(bFile->FromFile());
		}
	};
}