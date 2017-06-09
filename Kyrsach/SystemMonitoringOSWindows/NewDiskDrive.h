#pragma once
#include "stdafx.h"
#include "..\GetInfoWithWMI\FILE.h"

using namespace std;

namespace AllHardware {
	class DiskDrive
	{
		char mask[12];
		int BytesPerSector;//
		string Description;//
		string DeviceID;//
		string FirmwareRevision;//
		string InterfaceType;//
		string Manufacturer;//
		string MediaType;//
		string Model;//
		string Name;//
		string SerialNumber;//
		unsigned long long Size;//
		unsigned long long FreeSpace;

		std::string CreatMask()
		{
			if (this->BytesPerSector >= 0) this->mask[0] = '1';
			if (this->Description.size() != 0) this->mask[1] = '1';
			if (this->DeviceID.size() != 0) this->mask[2] = '1';
			if (this->FirmwareRevision.size() != 0) this->mask[3] = '1';
			if (this->InterfaceType.size() != 0) this->mask[4] = '1';
			if (this->Manufacturer.size() != 0) this->mask[5] = '1';
			if (this->MediaType.size() != 0) this->mask[6] = '1';
			if (this->Model.size() != 0) this->mask[7] = '1';
			if (this->Name.size() != 0) this->mask[8] = '1';
			if (this->SerialNumber.size() != 0) this->mask[9] = '1';
			if (this->Size >= 0) this->mask[10] = '1';
			if (this->FreeSpace >= 0) this->mask[11] = '1';
			return std::string(this->mask);
		}

		void ReadMask(const char *base)
		{
			for (int i = 0; i < 12; this->mask[i] = *(base + i), i++);
		}

	public:
		DiskDrive()
		{
			this->BytesPerSector = 0;
			this->Size = 0;
			this->FreeSpace = 0;
			for (int i = 0; i < 12; this->mask[i] = '0', i++);
		}
		DiskDrive(const DiskDrive &ob)
		{
			this->BytesPerSector = ob.BytesPerSector;
			this->Description = ob.Description;
			this->DeviceID = ob.DeviceID;
			this->FirmwareRevision = ob.FirmwareRevision;
			this->InterfaceType = ob.InterfaceType;
			this->Manufacturer = ob.Manufacturer;
			this->MediaType = ob.MediaType;
			this->Model = ob.Model;
			this->Name = ob.Name;
			this->SerialNumber = ob.SerialNumber;
			this->Size = ob.Size;
			this->FreeSpace = ob.FreeSpace;
			for (int i = 0; i < 12; this->mask[i] = ob.mask[i], i++);
		}

		void getBytesPerSector(int bytes)
		{
			this->BytesPerSector = bytes;
		}

		void getDescription(string description)
		{
			this->Description = description;
		}

		void getDeviceID(string id)
		{
			this->DeviceID = id;
		}

		void getFirmwareRevision(string revision)
		{
			this->FirmwareRevision = revision;
		}

		void getInterfaceType(string inttype)
		{
			this->InterfaceType = inttype;
		}

		void getManufacturer(string manufacturer)
		{
			this->Manufacturer = manufacturer;
		}

		void getMediaType(string mediaType)
		{
			this->MediaType = mediaType;
		}

		void getModel(string model)
		{
			this->Model = model;
		}

		void getName(string name)
		{
			this->Name = name;
		}

		void getSerialNumber(string snumber)
		{
			this->SerialNumber = snumber;
		}

		void getSize(unsigned long long size)
		{
			this->Size = size;
		}

		int setBytesPerSector() const
		{
			return this->BytesPerSector;
		}

		const char *setDescription() const
		{
			return this->Description.c_str();
		}

		const char *setDeviceID() const
		{
			return this->DeviceID.c_str();
		}

		const char *setFirmwareRevision() const
		{
			return this->FirmwareRevision.c_str();
		}

		const char *setInterfaceType() const
		{
			return this->InterfaceType.c_str();
		}

		const char *setManufacturer() const
		{
			return this->Manufacturer.c_str();
		}

		const char *setMediaType() const
		{
			return this->MediaType.c_str();
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

		unsigned long long setSize() const
		{
			return this->Size;
		}

		DiskDrive& operator=(const DiskDrive &ob)
		{
			if (this == &ob)
			{
				return *this;
			}
			else {
				this->BytesPerSector = ob.BytesPerSector;
				this->Description = ob.Description;
				this->DeviceID = ob.DeviceID;
				this->FirmwareRevision = ob.FirmwareRevision;
				this->InterfaceType = ob.InterfaceType;
				this->Manufacturer = ob.Manufacturer;
				this->MediaType = ob.MediaType;
				this->Model = ob.Model;
				this->Name = ob.Name;
				this->SerialNumber = ob.SerialNumber;
				this->Size = ob.Size;
				this->FreeSpace = ob.FreeSpace;
				for (int i = 0; i < 12; this->mask[i] = ob.mask[i], i++);
			}
			return *this;
		}

		void ToFile(BINARFILE *bFile)
		{
			bFile->ToFile(this->CreatMask(), 1);
			if (this->mask[0] == '1') bFile->ToFile(std::to_string(this->BytesPerSector), 1);
			if (this->mask[1] == '1') bFile->ToFile(this->Description, 1);
			if (this->mask[2] == '1') bFile->ToFile(this->DeviceID, 1);
			if (this->mask[3] == '1') bFile->ToFile(this->FirmwareRevision, 1);
			if (this->mask[4] == '1') bFile->ToFile(this->InterfaceType, 1);
			if (this->mask[5] == '1') bFile->ToFile(this->Manufacturer, 1);
			if (this->mask[6] == '1') bFile->ToFile(this->MediaType, 1);
			if (this->mask[7] == '1') bFile->ToFile(this->Model, 1);
			if (this->mask[8] == '1') bFile->ToFile(this->Name, 1);
			if (this->mask[9] == '1') bFile->ToFile(this->SerialNumber, 1);
			if (this->mask[10] == '1') bFile->ToFile(std::to_string(this->Size), 1);
			if (this->mask[11] == '1') bFile->ToFile(std::to_string(this->FreeSpace), 1);
		}

		void FromFile(BINARFILE *bFile)
		{
			this->ReadMask(bFile->FromFile().c_str());
			if (this->mask[0] == '1') this->BytesPerSector = std::stoi(bFile->FromFile());
			if (this->mask[1] == '1') this->Description = bFile->FromFile();
			if (this->mask[2] == '1') this->DeviceID = bFile->FromFile();
			if (this->mask[3] == '1') this->FirmwareRevision = bFile->FromFile();
			if (this->mask[4] == '1') this->InterfaceType = bFile->FromFile();
			if (this->mask[5] == '1') this->Manufacturer = bFile->FromFile();
			if (this->mask[6] == '1') this->MediaType = bFile->FromFile();
			if (this->mask[7] == '1') this->Model = bFile->FromFile();
			if (this->mask[8] == '1') this->Name = bFile->FromFile();
			if (this->mask[9] == '1') this->SerialNumber = bFile->FromFile();
			if (this->mask[10] == '1') this->Size = std::stoull(bFile->FromFile());
			if (this->mask[11] == '1') this->FreeSpace = std::stoull(bFile->FromFile());
		}

		void getFreeSpace(string name)
		{
			DWORD FreeBytesAvailable, TotalNumberOfBytes, TotalNumberOfFreeBytes;
			bool rez = GetDiskFreeSpaceEx((LPCWSTR)name.c_str(), (PULARGE_INTEGER)&FreeBytesAvailable, (PULARGE_INTEGER)&TotalNumberOfBytes, (PULARGE_INTEGER)&TotalNumberOfFreeBytes);
			if (rez == false) this->FreeSpace = 0;
			else {
				this->FreeSpace = TotalNumberOfFreeBytes;
			}
		}

		unsigned long long setFreeSpace() const
		{
			return this->FreeSpace;
		}
	};
}