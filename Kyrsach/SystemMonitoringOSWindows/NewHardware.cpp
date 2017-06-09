#include "NewHardware.h"

using namespace std;

AllHardware::Hardware::Hardware(const Hardware &hardware)
{
	this->hard.disk = hardware.hard.disk;
	this->hard.gpu = hardware.hard.gpu;
	this->hard.ldisk = hardware.hard.ldisk;
	this->hard.mb = hardware.hard.mb;
	this->hard.mem = hardware.hard.mem;
	this->hard.net = hardware.hard.net;
	this->hard.opsys = hardware.hard.opsys;
	this->hard.proc = hardware.hard.proc;
	this->hard.procv = hardware.hard.procv;
	this->hard.monitor = hardware.hard.monitor;
}

AllHardware::Hardware & AllHardware::Hardware::operator=(const Hardware &hardware)
{
	if (this == &hardware)
	{
		return *this;
	}
	this->hard.disk = hardware.hard.disk;
	this->hard.gpu = hardware.hard.gpu;
	this->hard.ldisk = hardware.hard.ldisk;
	this->hard.mb = hardware.hard.mb;
	this->hard.mem = hardware.hard.mem;
	this->hard.net = hardware.hard.net;
	this->hard.opsys = hardware.hard.opsys;
	this->hard.proc = hardware.hard.proc;
	this->hard.procv = hardware.hard.procv;
	this->hard.monitor = hardware.hard.monitor;
	return *this;
}

void AllHardware::Hardware::ReadFromFile(int flag)
{
	try {
		BINARFILE *bFile = new BINARFILE(FILENAME);
		int count;
		if (flag == 0) {
			count = std::stoi(bFile->FromFile());
			AllHardware::DiskDrive d;
			for (int i = 0; i < count; i++)
			{
				d.FromFile(bFile);
				this->hard.disk.push_back(d);
			}

			this->hard.gpu.FromFile(bFile);

			count = std::stoi(bFile->FromFile());
			AllHardware::LogicalDisk ld;
			for (int i = 0; i < count; i++)
			{
				ld.FromFile(bFile);
				this->hard.ldisk.push_back(ld);
			}

			this->hard.mb.FromFile(bFile);

			count = std::stoi(bFile->FromFile());
			AllHardware::Network netw;
			for (int i = 0; i < count; i++)
			{
				netw.FromFile(bFile);
				this->hard.net.push_back(netw);
			}

			count = std::stoi(bFile->FromFile());
			AllHardware::Os op;
			for (int i = 0; i < count; i++)
			{
				op.FromFile(bFile);
				this->hard.opsys.push_back(op);
			}

			this->hard.proc.ReadFromFile(bFile);

			count = std::stoi(bFile->FromFile());
			AllHardware::Process pr;
			for (int i = 0; i < count; i++)
			{
				pr.FromFile(bFile);
				this->hard.procv.push_back(pr);
			}

			this->hard.monitor.FromFile(bFile);
		}
		else {
			count = std::stoi(bFile->FromFile());
			AllHardware::LogicalDisk ld;
			for (int i = 0; i < count; i++)
			{
				ld.FromFile(bFile);
				this->hard.ldisk.push_back(ld);
			}

			count = std::stoi(bFile->FromFile());
			AllHardware::Network netw;
			for (int i = 0; i < count; i++)
			{
				netw.FromFile(bFile);
				this->hard.net.push_back(netw);
			}

			count = std::stoi(bFile->FromFile());
			AllHardware::Os op;
			for (int i = 0; i < count; i++)
			{
				op.FromFile(bFile);
				this->hard.opsys.push_back(op);
			}

			this->hard.proc.ReadFromFile(bFile);

			count = std::stoi(bFile->FromFile());
			AllHardware::Process pr;
			for (int i = 0; i < count; i++)
			{
				pr.FromFile(bFile);
				this->hard.procv.push_back(pr);
			}
		}
		delete bFile;
	}
	catch (...)
	{
		return;
	}
	return;
}
