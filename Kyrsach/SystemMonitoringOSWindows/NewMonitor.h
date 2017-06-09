#pragma once
#include "stdafx.h"
#include "..\GetInfoWithWMI\FILE.h"

using namespace std;

namespace AllHardware {
	class Monitor
	{
		char mask[5];
		string Caption;
		string DisplayType;
		string MonitorManufacturer;
		string MonitorType;
		string Name;

		string CreatMask()
		{
			if (this->Caption.size() > 0) this->mask[0] = '1';
			if (this->DisplayType.size() > 0) this->mask[1] = '1';
			if (this->MonitorManufacturer.size() > 0) this->mask[2] = '1';
			if (this->MonitorType.size() > 0) this->mask[3] = '1';
			if (this->Name.size() > 0) this->mask[4] = '1';
			return std::string(this->mask);
		}

		void ReadMask(const char *base)
		{
			for (int i = 0; i < 5; this->mask[i] = *(base + i), i++);
		}

	public:
		Monitor()
		{
			for (int i = 0; i < 5; this->mask[i] = '0', i++);
		}

		Monitor(const Monitor &ob)
		{
			for (int i = 0; i < 5; this->mask[i] = ob.mask[i], i++);
			this->Caption = ob.Caption;
			this->DisplayType = ob.DisplayType;
			this->MonitorManufacturer = ob.MonitorManufacturer;
			this->MonitorType = ob.MonitorType;
			this->Name = ob.Name;
		}

		Monitor& operator=(const Monitor &ob)
		{
			if (this == &ob) return *this;
			else {
				for (int i = 0; i < 5; this->mask[i] = ob.mask[i], i++);
				this->Caption = ob.Caption;
				this->DisplayType = ob.DisplayType;
				this->MonitorManufacturer = ob.MonitorManufacturer;
				this->MonitorType = ob.MonitorType;
				this->Name = ob.Name;
				return *this;
			}
		}

		void getCaption(string str)
		{
			this->Caption = str;
		}

		void getDisplayType(int a)
		{
			switch (a)
			{
			case 0: this->DisplayType = "Unknown";
			case 1: this->DisplayType = "Other";
			case 2: this->DisplayType = "Multiscan Color";
			case 3: this->DisplayType = "Multiscan Monochrome";
			case 4: this->DisplayType = "Fixed Frequency Color";
			case 5: this->DisplayType = "Fixed Frequency Monochrome";
			}
		}

		void getMonitorManufacturer(string str)
		{
			this->MonitorManufacturer = str;
		}

		void getMonitorType(string str)
		{
			this->MonitorType = str;
		}

		void getName(string str)
		{
			this->Name = str;
		}

		const char *setCaption()
		{
			return this->Caption.c_str();
		}

		const char *setDisplayType()
		{
			return this->DisplayType.c_str();
		}

		const char *setMonitorManufacturer()
		{
			return this->MonitorManufacturer.c_str();
		}

		const char *setMonitorType()
		{
			return this->MonitorType.c_str();
		}

		const char *setName()
		{
			return this->Name.c_str();
		}

		void ToFile(BINARFILE *bFile)
		{
			bFile->ToFile(this->CreatMask(), 1);
			if (this->mask[0] == '1') bFile->ToFile(this->Caption, 1);
			if (this->mask[1] == '1') bFile->ToFile(this->DisplayType, 1);
			if (this->mask[2] == '1') bFile->ToFile(this->MonitorManufacturer, 1);
			if (this->mask[3] == '1') bFile->ToFile(this->MonitorType, 1);
			if (this->mask[4] == '1') bFile->ToFile(this->Name, 1);
		}

		void FromFile(BINARFILE *bFile)
		{
			this->ReadMask(bFile->FromFile().c_str());
			if (this->mask[0] == '1') this->Caption = bFile->FromFile();
			if (this->mask[1] == '1') this->DisplayType = bFile->FromFile();
			if (this->mask[2] == '1') this->MonitorManufacturer = bFile->FromFile();
			if (this->mask[3] == '1') this->MonitorType = bFile->FromFile();
			if (this->mask[4] == '1') this->Name = bFile->FromFile();
		}
	};
}