#pragma once
#include "stdafx.h"
#include "..\GetInfoWithWMI\FILE.h"

using namespace std;

namespace AllHardware {
	class Network
	{
		char mask[12];
		string adapterType;//
		string caption;//
		string DeviceID;//
		string GUID;//
		string MACAddress;//
		string Manufacturer;//
		string name;//
		string netConnectionID;//
		string netConnectionStatus;//
		string PNPDeviceID;//
		string ServiceName;//
		long long CurSpeed;//					// bits per second

		std::string CreatMask()
		{
			if (this->adapterType.size() > 0) this->mask[0] = '1';
			if (this->caption.size() > 0) this->mask[1] = '1';
			if (this->DeviceID.size() > 0) this->mask[2] = '1';
			if (this->GUID.size() > 0) this->mask[3] = '1';
			if (this->MACAddress.size() > 0) this->mask[4] = '1';
			if (this->Manufacturer.size() > 0) this->mask[5] = '1';
			if (this->name.size() > 0) this->mask[6] = '1';
			if (this->netConnectionID.size() > 0) this->mask[7] = '1';
			if (this->netConnectionStatus.size() > 0) this->mask[8] = '1';
			if (this->PNPDeviceID.size() > 0) this->mask[9] = '1';
			if (this->ServiceName.size() > 0) this->mask[10] = '1';
			if (this->CurSpeed >= 0) this->mask[11] = '1';
			return std::string(this->mask);
		}

		void ReadMask(const char *base)
		{
			for (int i = 0; i < 12; this->mask[i] = *(base + i), i++);
		}

	public:
		Network()
		{
			this->CurSpeed = 0;
			for (int i = 0; i < 12; this->mask[i] = '0', i++);
		}
		Network(const Network &ob)
		{
			this->adapterType = ob.adapterType;
			this->caption = ob.caption;
			this->CurSpeed = ob.CurSpeed;
			this->DeviceID = ob.DeviceID;
			this->GUID = ob.GUID;
			this->MACAddress = ob.MACAddress;
			this->Manufacturer = ob.Manufacturer;
			this->name = ob.name;
			this->netConnectionID = ob.netConnectionID;
			this->netConnectionStatus = ob.netConnectionStatus;
			this->PNPDeviceID = ob.PNPDeviceID;
			this->ServiceName = ob.ServiceName;
			for (int i = 0; i < 12; this->mask[i] = ob.mask[i], i++);
		}

		void getAdapterType(string atype)
		{
			this->adapterType = atype;
		}

		void getCaption(string capt)
		{
			this->caption = capt;
		}

		void getDeviceID(string id)
		{
			this->DeviceID = id;
		}

		void getGUID(string guid)
		{
			this->GUID = guid;
		}

		void getMACAddress(string macaddress)
		{
			this->MACAddress = macaddress;
		}

		void getManufacturer(string manufacturer)
		{
			this->Manufacturer = manufacturer;
		}

		void getName(string name)
		{
			this->name = name;
		}

		void getNetConnectionID(string netID)
		{
			this->netConnectionID = netID;
		}

		void getNetConnectionStatus(int sw)
		{
			switch (sw)
			{
			case 0: this->netConnectionStatus = "Disconnected";
				break;
			case 1: this->netConnectionStatus = "Connecting";
				break;
			case 2: this->netConnectionStatus = "Connected";
				break;
			case 3: this->netConnectionStatus = "Disconnecting";
				break;
			case 4: this->netConnectionStatus = "Hardware Not Present";
				break;
			case 5: this->netConnectionStatus = "Hardware Disabled";
				break;
			case 6: this->netConnectionStatus = "Hardware Malfunction";
				break;
			case 7: this->netConnectionStatus = "Media Disconnected";
				break;
			case 8: this->netConnectionStatus = "Authenticating";
				break;
			case 9: this->netConnectionStatus = "Authentication Succeeded";
				break;
			case 10: this->netConnectionStatus = "Authentication Failed";
				break;
			case 11: this->netConnectionStatus = "Invalid Address";
				break;
			case 12: this->netConnectionStatus = "Credentials Required";
				break;
			default: this->netConnectionStatus = "Other";
				break;
			}
		}

		void getPNPDeviceID(string pnp)
		{
			this->PNPDeviceID = pnp;
		}

		void getServiceName(string servicename)
		{
			this->ServiceName = servicename;
		}

		void getSpeed(long long speed)
		{
			this->CurSpeed = speed;
		}

		const char *setAdapterType() const
		{
			return this->adapterType.c_str();
		}

		const char *setCaption() const
		{
			return this->caption.c_str();
		}

		const char *setDeviceID() const
		{
			return this->DeviceID.c_str();
		}

		const char *setGUID() const
		{
			return this->GUID.c_str();
		}

		const char *setMACAddress() const
		{
			return this->MACAddress.c_str();
		}

		const char *setManufacturer() const
		{
			return this->Manufacturer.c_str();
		}

		const char *setName() const
		{
			return this->name.c_str();
		}

		const char *setNetConnectionID() const
		{
			return this->netConnectionID.c_str();
		}

		const char *setNetConnectionStatus() const
		{
			return this->netConnectionStatus.c_str();
		}

		const char *setPNPDeviceID() const
		{
			return this->PNPDeviceID.c_str();
		}

		const char *setServiceName() const
		{
			return this->ServiceName.c_str();
		}

		long long setSpeed() const
		{
			return this->CurSpeed;
		}

		Network& operator=(const Network &ob)
		{
			if (this == &ob)
			{
				return *this;
			}
			else {
				this->adapterType = ob.adapterType;
				this->caption = ob.caption;
				this->CurSpeed = ob.CurSpeed;
				this->DeviceID = ob.DeviceID;
				this->GUID = ob.GUID;
				this->MACAddress = ob.MACAddress;
				this->Manufacturer = ob.Manufacturer;
				this->name = ob.name;
				this->netConnectionID = ob.netConnectionID;
				this->netConnectionStatus = ob.netConnectionStatus;
				this->PNPDeviceID = ob.PNPDeviceID;
				this->ServiceName = ob.ServiceName;
				for (int i = 0; i < 12; this->mask[i] = ob.mask[i], i++);
			}
			return *this;
		}

		void ToFile(BINARFILE *bFile)
		{
			bFile->ToFile(this->CreatMask(), 1);
			if (this->mask[0] == '1') bFile->ToFile(this->adapterType, 1);
			if (this->mask[1] == '1') bFile->ToFile(this->caption, 1);
			if (this->mask[2] == '1') bFile->ToFile(this->DeviceID, 1);
			if (this->mask[3] == '1') bFile->ToFile(this->GUID, 1);
			if (this->mask[4] == '1') bFile->ToFile(this->MACAddress, 1);
			if (this->mask[5] == '1') bFile->ToFile(this->Manufacturer, 1);
			if (this->mask[6] == '1') bFile->ToFile(this->name, 1);
			if (this->mask[7] == '1') bFile->ToFile(this->netConnectionID, 1);
			if (this->mask[8] == '1') bFile->ToFile(this->netConnectionStatus, 1);
			if (this->mask[9] == '1') bFile->ToFile(this->PNPDeviceID, 1);
			if (this->mask[10] == '1') bFile->ToFile(this->ServiceName, 1);
			if (this->mask[11] == '1') bFile->ToFile(std::to_string(this->CurSpeed), 1);
		}

		void FromFile(BINARFILE *bFile)
		{
			this->ReadMask(bFile->FromFile().c_str());
			if (this->mask[0] == '1') this->adapterType = bFile->FromFile();
			if (this->mask[1] == '1') this->caption = bFile->FromFile();
			if (this->mask[2] == '1') this->DeviceID = bFile->FromFile();
			if (this->mask[3] == '1') this->GUID = bFile->FromFile();
			if (this->mask[4] == '1') this->MACAddress = bFile->FromFile();
			if (this->mask[5] == '1') this->Manufacturer = bFile->FromFile();
			if (this->mask[6] == '1') this->name = bFile->FromFile();
			if (this->mask[7] == '1') this->netConnectionID = bFile->FromFile();
			if (this->mask[8] == '1') this->netConnectionStatus = bFile->FromFile();
			if (this->mask[9] == '1') this->PNPDeviceID = bFile->FromFile();
			if (this->mask[10] == '1') this->ServiceName = bFile->FromFile();
			if (this->mask[11] == '1') this->CurSpeed = std::stoll(bFile->FromFile());
		}
	};
}