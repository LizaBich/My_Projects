#pragma once
#include "stdafx.h"
#include "..\GetInfoWithWMI\FILE.h"

using namespace std;

namespace AllHardware {
	class MotherBoard
	{
		char mask[11];
		string Caption;//
		string Manufacturer;//
		string Model;//
		string Name;//
		bool Removable;//
		bool Replaceable;
		string RequirementsDescription;//
		bool SpecialRequirements;//
		string SerialNumber;//
		string SlotLayout;//
		string Version;//

		std::string CreatMask()
		{
			if (this->Caption.size() > 0) this->mask[0] = '1';
			if (this->Manufacturer.size() > 0) this->mask[1] = '1';
			if (this->Model.size() > 0) this->mask[2] = '1';
			if (this->Name.size() > 0) this->mask[3] = '1';
			if (this->Removable == true) this->mask[4] = '1';
			if (this->Replaceable == true) this->mask[5] = '1';
			if (this->SpecialRequirements == true) this->mask[6] = '1';
			if (this->RequirementsDescription.size() > 0) this->mask[7] = '1';
			if (this->SerialNumber.size() > 0) this->mask[8] = '1';
			if (this->SlotLayout.size() > 0) this->mask[9] = '1';
			if (this->Version.size() > 0) this->mask[10] = '1';
			return std::string(this->mask);
		}

		void ReadMask(const char *base)
		{
			for (int i = 0; i < 11; this->mask[i] = *(base + i), i++);
		}

		int boolToInt(bool a) const
		{
			if (a == true) return 1; else return 0;
		}

		bool intToBool(int b) const
		{
			if (b == 1) return true; else return false;
		}

	public:
		MotherBoard() {
			this->Removable = false;
			this->Replaceable = false;
			this->SpecialRequirements = false;
			for (int i = 0; i < 11; this->mask[i] = '0', i++);
		}
		MotherBoard(const MotherBoard &ob)
		{
			this->Caption = ob.Caption;
			this->Manufacturer = ob.Manufacturer;
			this->Model = ob.Model;
			this->Name = ob.Name;
			this->Removable = ob.Removable;
			this->Replaceable = ob.Replaceable;
			this->RequirementsDescription = ob.RequirementsDescription;
			this->SerialNumber = ob.SerialNumber;
			this->SlotLayout = ob.SlotLayout;
			this->SpecialRequirements = ob.SpecialRequirements;
			this->Version = ob.Version;
			for (int i = 0; i < 11; this->mask[i] = ob.mask[i], i++);
		}

		void getCaption(string c)
		{
			this->Caption = c;
		}

		void getManufacturer(string m)
		{
			this->Manufacturer = m;
		}

		void getModel(string m)
		{
			this->Model = m;
		}

		void getName(string n)
		{
			this->Name = n;
		}

		void getRemovable(bool rem)
		{
			this->Removable = rem;
		}

		void getReplaceable(bool rep)
		{
			this->Replaceable = rep;
		}

		void getRequirementsDescription(string n)
		{
			this->RequirementsDescription = n;
		}

		void getSpecialRequirements(bool sr)
		{
			this->SpecialRequirements = sr;
		}

		void getSerialNumber(string sn)
		{
			this->SerialNumber = sn;
		}

		void getSlotLayout(string sl)
		{
			this->SlotLayout = sl;
		}

		void getVersion(string ver)
		{
			this->Version = ver;
		}

		const char *setCaption() const
		{
			return this->Caption.c_str();
		}

		const char *setManufacturer() const
		{
			return this->Manufacturer.c_str();
		}

		const char *setModel() const
		{
			return this->Model.c_str();
		}

		const char *setName() const
		{
			return this->Name.c_str();
		}

		const char *setSerialNumber() const
		{
			return this->SerialNumber.c_str();
		}

		const char *setSlotLayout() const
		{
			return this->SlotLayout.c_str();
		}

		const char *setVersion() const
		{
			return this->Version.c_str();
		}

		const char *setRemovable() const
		{
			if (this->Removable == true) return "true";
			else return "false";
		}

		const char *setReplaceable() const
		{
			if (this->Replaceable == true) return "true";
			else return "false";
		}

		bool setSpecialRequirements() const
		{
			return this->SpecialRequirements;
		}

		const char *setRequirementsDescription() const
		{
			return this->RequirementsDescription.c_str();
		}

		MotherBoard& operator=(const MotherBoard &ob)
		{
			if (this == &ob)
			{
				return *this;
			}
			else {
				this->Caption = ob.Caption;
				this->Manufacturer = ob.Manufacturer;
				this->Model = ob.Model;
				this->Name = ob.Name;
				this->Removable = ob.Removable;
				this->Replaceable = ob.Replaceable;
				this->RequirementsDescription = ob.RequirementsDescription;
				this->SerialNumber = ob.SerialNumber;
				this->SlotLayout = ob.SlotLayout;
				this->SpecialRequirements = ob.SpecialRequirements;
				this->Version = ob.Version;
				for (int i = 0; i < 11; this->mask[i] = ob.mask[i], i++);
			}
			return *this;
		}

		void ToFile(BINARFILE *bFile)
		{
			bFile->ToFile(this->CreatMask(), 1);
			if (this->mask[0] == '1') bFile->ToFile(this->Caption, 1);
			if (this->mask[1] == '1') bFile->ToFile(this->Manufacturer, 1);
			if (this->mask[2] == '1') bFile->ToFile(this->Model, 1);
			if (this->mask[3] == '1') bFile->ToFile(this->Name, 1);
			if (this->mask[4] == '1') bFile->ToFile(std::to_string(this->boolToInt(this->Removable)), 1);
			if (this->mask[5] == '1') bFile->ToFile(std::to_string(this->boolToInt(this->Replaceable)), 1);
			if (this->mask[6] == '1') bFile->ToFile(std::to_string(this->boolToInt(this->SpecialRequirements)), 1);
			if (this->SpecialRequirements && this->mask[7] == '1') 
			{
				bFile->ToFile(this->RequirementsDescription, 1);
			}
			if (this->mask[8] == '1') bFile->ToFile(this->SerialNumber, 1);
			if (this->mask[9] == '1') bFile->ToFile(this->SlotLayout, 1);
			if (this->mask[10] == '1') bFile->ToFile(this->Version, 1);
		}

		void FromFile(BINARFILE *bFile)
		{
			this->ReadMask(bFile->FromFile().c_str());
			if (this->mask[0] == '1') this->Caption = bFile->FromFile();
			if (this->mask[1] == '1') this->Manufacturer = bFile->FromFile();
			if (this->mask[2] == '1') this->Model = bFile->FromFile();
			if (this->mask[3] == '1') this->Name = bFile->FromFile();
			if (this->mask[4] == '1') this->Removable = this->intToBool(std::stoi(bFile->FromFile()));
			if (this->mask[5] == '1') this->Replaceable = this->intToBool(std::stoi(bFile->FromFile()));
			if (this->mask[6] == '1') this->SpecialRequirements = this->intToBool(std::stoi(bFile->FromFile()));
			if (this->SpecialRequirements && this->mask[7] == '1')
			{
				this->RequirementsDescription = bFile->FromFile();
			}
			if (this->mask[8] == '1') this->SerialNumber = bFile->FromFile();
			if (this->mask[9] == '1') this->SlotLayout = bFile->FromFile();
			if (this->mask[10] == '1') this->Version = bFile->FromFile();
		}
	};
}