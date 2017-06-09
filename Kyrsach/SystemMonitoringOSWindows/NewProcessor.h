#pragma once
#include "stdafx.h"
#include "..\GetInfoWithWMI\FILE.h"

using namespace std;

namespace AllHardware {
	class Processor
	{
		char mask[17];
		string name;//					//модель проца    0
		string manufacturer;//			//мануфактура проца    1
		string caption;//					//заголовок   2
		string addressWidth;//			//размер пам€ти    3
		string architecture;//			//архитектура проца   4
		string availability;//			//доступные функции   5
		double currentSpeed;			//текуща€ скорость работы   6
		double extClock;//				//внешн€€ частота проца    7
		string family;//					//семейство     8
		double L2Size;//					//размер кэша второго уровн€   9
		double L3Size;//					//размер кэша 3-го уровн€   10
		int loadPercentage;//										11
		double maxSpeed;//				//максимальна€ скорость    12
		int numberOfCores;//				//кол-во €дер     13
		int numberOfEnabledCores;//		//кол-во доступных €дер     14
		int numberOfLogicalProcessors;//	//кол-во логических процессоров   15
		int threadsCount;//				//кол-во процессов      16

		std::string CreatMask()
		{
			if (this->name.size() != 0) this->mask[0] = '1';
			if (this->manufacturer.size() != 0) this->mask[1] = '1';
			if (this->caption.size() != 0) this->mask[2] = '1';
			if (this->addressWidth.size() != 0) this->mask[3] = '1';
			if (this->architecture.size() != 0) this->mask[4] = '1';
			if (this->availability.size() != 0) this->mask[5] = '1';
			if (this->currentSpeed >= 0) this->mask[6] = '1';
			if (this->extClock >= 0) this->mask[7] = '1';
			if (this->family.size() != 0) this->mask[8] = '1';
			if (this->L2Size >= 0) this->mask[9] = '1';
			if (this->L3Size >= 0) this->mask[10] = '1';
			if (this->loadPercentage >= 0) this->mask[11] = '1';
			if (this->maxSpeed >= 0) this->mask[12] = '1';
			if (this->numberOfCores >= 0) this->mask[13] = '1';
			if (this->numberOfEnabledCores >= 0) this->mask[14] = '1';
			if (this->numberOfLogicalProcessors >= 0) this->mask[15] = '1';
			if (this->threadsCount >= 0) this->mask[16] = '1';
			return std::string(this->mask);
		}

		void ReadMask(const char *base)
		{
			for (int i = 0; i < 17; this->mask[i] = *(base + i), i++);
		}

	public:
		Processor()
		{
			this->currentSpeed = 0;
			this->extClock = 0;
			this->L2Size = 0;
			this->L3Size = 0;
			this->loadPercentage = 0;
			this->maxSpeed = 0;
			this->numberOfCores = 0;
			this->numberOfEnabledCores = 0;
			this->numberOfLogicalProcessors = 0;
			this->threadsCount = 0;
			for (int i = 0; i < 17; this->mask[i] = '0', i++);
		}
		Processor(const Processor &ob)
		{
			this->addressWidth = ob.addressWidth;
			this->architecture = ob.architecture;
			this->availability = ob.availability;
			this->caption = ob.caption;
			this->currentSpeed = ob.currentSpeed;
			this->extClock = ob.extClock;
			this->family = ob.family;
			this->L2Size = ob.L2Size;
			this->L3Size = ob.L3Size;
			this->loadPercentage = ob.loadPercentage;
			this->manufacturer = ob.manufacturer;
			this->maxSpeed = ob.maxSpeed;
			this->name = ob.name;
			this->numberOfCores = ob.numberOfCores;
			this->numberOfEnabledCores = ob.numberOfEnabledCores;
			this->numberOfLogicalProcessors = ob.numberOfLogicalProcessors;
			for (int i = 0; i < 17; this->mask[i] = ob.mask[i], i++);
		}

		void getName(string n)
		{
			this->name = n;
		}

		void getManufacturer(string man)
		{
			this->manufacturer = man;
		}

		void getCaption(string cap)
		{
			this->caption = cap;
		}

		void getAddressWidth(int aw)
		{
			switch (aw)
			{
			case 32:
				this->addressWidth = "32-bit";
				break;
			case 64:
				this->addressWidth = "64-bit";
				break;
			default:
				this->addressWidth = "Unknowm";
				break;
			}
		}

		void getArchitecture(int arch)
		{
			switch (arch)
			{
			case 0:
				this->architecture = "x86";
				break;
			case 1:
				this->architecture = "MIPS";
				break;
			case 2:
				this->architecture = "Alpha";
				break;
			case 3:
				this->architecture = "PowerPC";
				break;
			case 6:
				this->architecture = "ia64";
				break;
			case 9:
				this->architecture = "x64";
				break;
			default:
				this->architecture = "Unknown";
				break;
			}
		}

		void getAvailability(int aval)
		{
			switch (aval - 1)
			{
			case 0:
				this->availability = "Other";
				break;
			case 1:
				this->availability = "Unknown";
				break;
			case 2:
				this->availability = "Running/Full Power";
				break;
			case 3:
				this->availability = "Warning";
				break;
			case 4:
				this->availability = "In Test";
				break;
			case 5:
				this->availability = "Not Applicable";
				break;
			case 6:
				this->availability = "Power Off";
				break;
			case 7:
				this->availability = "Off Line";
				break;
			case 8:
				this->availability = "Off Duty";
				break;
			case 9:
				this->availability = "Degraded";
				break;
			case 10:
				this->availability = "Not Installed";
				break;
			case 11:
				this->availability = "Install Error";
				break;
			case 12:
				this->availability = "Power save (Unknown)";
				break;
			case 13:
				this->availability = "Power save (Low Power Mode)";
				break;
			case 14:
				this->availability = "Power save (Standby)";
				break;
			case 15:
				this->availability = "Power Cycle";
				break;
			case 16:
				this->availability = "Power save (Warning)";
				break;
			case 17:
				this->availability = "Paused";
				break;
			case 18:
				this->availability = "Not Ready";
				break;
			case 19:
				this->availability = "Not Configured";
				break;
			case 20:
				this->availability = "Quiescend";
				break;
			}
		}

		void getCurrentSpeed(double cs)
		{
			this->currentSpeed = cs;
		}

		void getExtClock(double ec)
		{
			this->extClock = ec;
		}

		void getFamily(int fam)
		{
			switch (fam)
			{
			case 1:
				this->family = "Other";
				break;
			case 2:
				this->family = "Unknown";
				break;
			case 3:
				this->family = "Intel86 Processor";
				break;
			case 4:
				this->family = "Intel286 Processor";
				break;
			case 5:
				this->family = "Intel386 Processor";
				break;
			case 6:
				this->family = "Intel486 Processor";
				break;
			case 7:
				this->family = "Intel87 Processor";
				break;
			case 8:
				this->family = "Intel287 Processor";
				break;
			case 9:
				this->family = "Intel387 Processor";
				break;
			case 10:
				this->family = "Intel487 Processor";
				break;
			case 11:
				this->family = "Pentium(R) brand";
				break;
			case 12:
				this->family = "Pentium(R) Pro";
				break;
			case 13:
				this->family = "Pentium(R) II";
				break;
			case 14:
				this->family = "Pentium(R) processor with MMX(TM) technology";
				break;
			case 15:
				this->family = "Celeron(TM)";
				break;
			case 16:
				this->family = "Pentium(R) II Xeon(TM)";
				break;
			case 17:
				this->family = "Pentium(R) III";
				break;
			case 18:
				this->family = "M1 Family";
				break;
			case 19:
				this->family = "M2 Family";
				break;
			case 24:
				this->family = "K5 Family";
				break;
			case 25:
				this->family = "K6 Family";
				break;
			case 26:
				this->family = "K6-2";
				break;
			case 27:
				this->family = "K6-3";
				break;
			case 28:
				this->family = "AMD Athlon(TM) Processor Family";
				break;
			case 29:
				this->family = "AMD(R) Duron(TM) Processor";
				break;
			case 30:
				this->family = "AMD29000 Family";
				break;
			case 31:
				this->family = "K6-2+";
				break;
			case 32:
				this->family = "Power PC Family";
				break;
			case 33:
				this->family = "Power PC 601";
				break;
			case 34:
				this->family = "Power PC 603";
				break;
			case 35:
				this->family = "Power PC 603+";
				break;
			case 36:
				this->family = "Power PC 604";
				break;
			case 37:
				this->family = "Power PC 620";
				break;
			case 38:
				this->family = "Power PC X704";
				break;
			case 39:
				this->family = "Power PC 750";
				break;
			case 48:
				this->family = "Alpha Family";
				break;
			case 49:
				this->family = "Alpha 21064";
				break;
			case 50:
				this->family = "Alpha 21066";
				break;
			case 51:
				this->family = "Alpha 21164";
				break;
			case 52:
				this->family = "Alpha 21164PC";
				break;
			case 53:
				this->family = "Alpha 21164a";
				break;
			case 54:
				this->family = "Alpha 21264";
				break;
			case 55:
				this->family = "Alpha 21364";
				break;
			case 64:
				this->family = "MIPS Family";
				break;
			case 65:
				this->family = "MIPS R4000";
				break;
			case 66:
				this->family = "MIPS R4200";
				break;
			case 67:
				this->family = "MIPS R4400";
				break;
			case 68:
				this->family = "MIPS R4600";
				break;
			case 69:
				this->family = "MIPS R10000";
				break;
			case 80:
				this->family = "SPARC Family";
				break;
			case 81:
				this->family = "SuperSPARC";
				break;
			case 82:
				this->family = "microSPARC II";
				break;
			case 83:
				this->family = "microSPARC IIep";
				break;
			case 84:
				this->family = "UltraSPARC";
				break;
			case 85:
				this->family = "UltraSPARC II";
				break;
			case 86:
				this->family = "UltraSPARC IIi";
				break;
			case 87:
				this->family = "UltraSPARC III";
				break;
			case 88:
				this->family = "UltraSPARC IIIi";
				break;
			case 96:
				this->family = "68040";
				break;
			case 97:
				this->family = "68xxx Family";
				break;
			case 98:
				this->family = "68000";
				break;
			case 99:
				this->family = "68010";
				break;
			case 100:
				this->family = "68020";
				break;
			case 101:
				this->family = "68030";
				break;
			case 112:
				this->family = "Hobbit Family";
				break;
			case 120:
				this->family = "Crusoe(TM) TM5000 Family";
				break;
			case 121:
				this->family = "Crusoe(TM) TM3000 Family";
				break;
			case 122:
				this->family = "Efficion(TM) TM8000 Family";
				break;
			case 128:
				this->family = "Weitek";
				break;
			case 130:
				this->family = "Itanium(TM) Processor";
				break;
			case 131:
				this->family = "AMD Athlon(TM) 64 Processor Family";
				break;
			case 132:
				this->family = "AMD Opteron(TM) Family";
				break;
			case 144:
				this->family = "PA-RISC Family";
				break;
			case 145:
				this->family = "PA-RISC 8500";
				break;
			case 146:
				this->family = "PA-RISK 8000";
				break;
			case 147:
				this->family = "PA-RISK 7300LC";
				break;
			case 148:
				this->family = "PA-RISK 7200";
				break;
			case 149:
				this->family = "PA-RISK 7100LC";
				break;
			case 150:
				this->family = "PA-RISK 7100";
				break;
			case 160:
				this->family = "V30 Family";
				break;
			case 176:
				this->family = "Pentium(R) III Xeon(TM)";
				break;
			case 177:
				this->family = "Pentium(R) III Processor with Intel(R) SpeedStep(TM) Technology";
				break;
			case 178:
				this->family = "Pentium(R) 4";
				break;
			case 179:
				this->family = "Intel(R) Xeon(TM)";
				break;
			case 180:
				this->family = "AS400 Family";
				break;
			case 181:
				this->family = "Intel(R) Xeon(TM) processor MP";
				break;
			case 182:
				this->family = "AMD AthlonXP(TM) Family";
				break;
			case 183:
				this->family = "AMD AthlonMP(TM) Family";
				break;
			case 184:
				this->family = "Intel(R) Itanium(R) 2";
				break;
			case 185:
				this->family = "Intel Pentium M Processor ";
				break;
			case 190:
				this->family = "K7";
				break;
			case 191:
				this->family = "Pentium(R) P6100";
				break;
			case 198:
				this->family = "Intel Core(TM)";
				break;
			case 200:
				this->family = "IBM390 Family";
				break;
			case 201:
				this->family = "G4";
				break;
			case 202:
				this->family = "G5";
				break;
			case 203:
				this->family = "G6";
				break;
			case 204:
				this->family = "z/Architecture base";
				break;
			case 250:
				this->family = "i860";
				break;
			case 251:
				this->family = "i960";
				break;
			case 260:
				this->family = "SH-3";
				break;
			case 261:
				this->family = "SH-4";
				break;
			case 280:
				this->family = "ARM";
				break;
			case 281:
				this->family = "StrongARM";
				break;
			case 300:
				this->family = "6x86";
				break;
			case 301:
				this->family = "MediaGX";
				break;
			case 302:
				this->family = "MII";
				break;
			case 320:
				this->family = "WinChip";
				break;
			case 350:
				this->family = "DSP";
				break;
			case 500:
				this->family = "Video Processor";
				break;
			}
		}

		void getL2Size(double l2s)
		{
			this->L2Size = l2s;
		}

		void getL3Size(double l3s)
		{
			this->L3Size = l3s;
		}

		void getLoadPercentage(int load)
		{
			this->loadPercentage = load;
		}

		void getMaxSpeed(double ms)
		{
			this->maxSpeed = ms;
		}

		void getNumberOfCores(int count)
		{
			this->numberOfCores = count;
		}

		void getNumberOfEnabledCores(int num)
		{
			this->numberOfEnabledCores = num;
		}

		void getNumberOfLogicalPrroc(int num)
		{
			this->numberOfLogicalProcessors = num;
		}

		void getThreadsCount(int count)
		{
			this->threadsCount = count;
		}

		const char *setName() const
		{
			return this->name.c_str();
		}

		const char *setManufacturer() const
		{
			return this->manufacturer.c_str();
		}

		const char *setCaption() const
		{
			return this->caption.c_str();
		}

		const char *setAddressWidth() const
		{
			return this->addressWidth.c_str();
		}

		const char *setArchitecture() const
		{
			return this->architecture.c_str();
		}

		const char *setAvailability() const
		{
			return this->availability.c_str();
		}

		double setCurrentSpeed() const
		{
			return this->currentSpeed;
		}

		double setExtClock() const
		{
			return this->extClock;
		}

		const char *setFamily() const
		{
			return this->family.c_str();
		}

		double setL2Size() const
		{
			return this->L2Size;
		}

		double setL3Size() const
		{
			return this->L3Size;
		}

		int setLoadPercentage() const
		{
			return this->loadPercentage;
		}

		double setMaxSpeed() const
		{
			return this->maxSpeed;
		}

		int setNumberOfCores() const
		{
			return this->numberOfCores;
		}

		int setNumberOfEnabledCores() const
		{
			return this->numberOfEnabledCores;
		}

		int setNumberOfLogicalPrroc() const
		{
			return this->numberOfLogicalProcessors;
		}

		int setThreadsCount() const
		{
			return this->threadsCount;
		}

		Processor& operator=(const Processor &ob)
		{
			if (this == &ob)
			{
				return *this;
			}
			this->addressWidth = ob.addressWidth;
			this->architecture = ob.architecture;
			this->availability = ob.availability;
			this->caption = ob.caption;
			this->currentSpeed = ob.currentSpeed;
			this->extClock = ob.extClock;
			this->family = ob.family;
			this->L2Size = ob.L2Size;
			this->L3Size = ob.L3Size;
			this->loadPercentage = ob.loadPercentage;
			this->manufacturer = ob.manufacturer;
			this->maxSpeed = ob.maxSpeed;
			this->name = ob.name;
			this->numberOfCores = ob.numberOfCores;
			this->numberOfEnabledCores = ob.numberOfEnabledCores;
			this->numberOfLogicalProcessors = ob.numberOfLogicalProcessors;
			for (int i = 0; i < 17; this->mask[i] = ob.mask[i], i++);
			return *this;
		}

		void WriteToFile(BINARFILE *bFile)
		{
			bFile->ToFile(this->CreatMask(), 1);
			if (this->mask[0] == '1') bFile->ToFile(this->name, 1);
			if (this->mask[1] == '1') bFile->ToFile(this->manufacturer, 1);
			if (this->mask[2] == '1') bFile->ToFile(this->caption, 1);
			if (this->mask[3] == '1') bFile->ToFile(this->addressWidth, 1);
			if (this->mask[4] == '1') bFile->ToFile(this->architecture, 1);
			if (this->mask[5] == '1') bFile->ToFile(this->availability, 1);
			if (this->mask[6] == '1') bFile->ToFile(std::to_string(this->currentSpeed), 1);
			if (this->mask[7] == '1') bFile->ToFile(std::to_string(this->extClock), 1);
			if (this->mask[8] == '1') bFile->ToFile(this->family, 1);
			if (this->mask[9] == '1') bFile->ToFile(std::to_string(this->L2Size), 1);
			if (this->mask[10] == '1') bFile->ToFile(std::to_string(this->L3Size), 1);
			if (this->mask[11] == '1') bFile->ToFile(std::to_string(this->loadPercentage), 1);
			if (this->mask[12] == '1') bFile->ToFile(std::to_string(this->maxSpeed), 1);
			if (this->mask[13] == '1') bFile->ToFile(std::to_string(this->numberOfCores), 1);
			if (this->mask[14] == '1') bFile->ToFile(std::to_string(this->numberOfEnabledCores), 1);
			if (this->mask[15] == '1') bFile->ToFile(std::to_string(this->numberOfLogicalProcessors), 1);
			if (this->mask[16] == '1') bFile->ToFile(std::to_string(this->threadsCount), 1);
		}

		void ReadFromFile(BINARFILE *bFile)
		{
			this->ReadMask(bFile->FromFile().c_str());
			if (this->mask[0] == '1') this->name = bFile->FromFile();
			if (this->mask[1] == '1') this->manufacturer = bFile->FromFile();
			if (this->mask[2] == '1') this->caption = bFile->FromFile();
			if (this->mask[3] == '1') this->addressWidth = bFile->FromFile();
			if (this->mask[4] == '1') this->architecture = bFile->FromFile();
			if (this->mask[5] == '1') this->availability = bFile->FromFile();
			if (this->mask[6] == '1') this->currentSpeed = std::stod(bFile->FromFile());
			if (this->mask[7] == '1') this->extClock = std::stod(bFile->FromFile());
			if (this->mask[8] == '1') this->family = bFile->FromFile();
			if (this->mask[9] == '1') this->L2Size = std::stod(bFile->FromFile());
			if (this->mask[10] == '1') this->L3Size = std::stod(bFile->FromFile());
			if (this->mask[11] == '1') this->loadPercentage = std::stoi(bFile->FromFile());
			if (this->mask[12] == '1') this->maxSpeed = std::stod(bFile->FromFile());
			if (this->mask[13] == '1') this->numberOfCores = std::stoi(bFile->FromFile());
			if (this->mask[14] == '1') this->numberOfEnabledCores = std::stoi(bFile->FromFile());
			if (this->mask[15] == '1') this->numberOfLogicalProcessors = std::stoi(bFile->FromFile());
			if (this->mask[16] == '1') this->threadsCount = std::stoi(bFile->FromFile());
		}
	};
}