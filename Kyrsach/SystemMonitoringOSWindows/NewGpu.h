#pragma once
#include "stdafx.h"
#include "..\GetInfoWithWMI\FILE.h"

using namespace std;

namespace AllHardware {
	class Gpu
	{
		char mask[14];
		string adapterCompatibility;//			// чипсет, обеспечивающий совместимость с системой
		long long adapterRAM;//						// размер памяти адаптера
		double currentBitsPerPixel;//
		int currentHorizontalResolution;//
		int currentVerticalResolution;//
		double currentNumberOfColor;//
		double currentRefreshRate;//				// частота обновления кадров
		double maxRefreshRate;//
		double minRefreshRate;//
		string name;//
		string protocolSupported;//
		string videoArchitecture;//
		string videoMemoryType;//
		string videoProcessor;//

		std::string CreatMask()
		{
			if (this->adapterCompatibility.size() != 0) this->mask[0] = '1';
			if (this->adapterRAM >= 0) this->mask[1] = '1';
			if (this->currentBitsPerPixel >= 0) this->mask[2] = '1';
			if (this->currentHorizontalResolution >= 0) this->mask[3] = '1';
			if (this->currentVerticalResolution >= 0) this->mask[4] = '1';
			if (this->currentNumberOfColor >= 0) this->mask[5] = '1';
			if (this->currentRefreshRate >= 0) this->mask[6] = '1';
			if (this->maxRefreshRate >= 0) this->mask[7] = '1';
			if (this->minRefreshRate >= 0) this->mask[8] = '1';
			if (this->name.size() != 0) this->mask[9] = '1';
			if (this->protocolSupported.size() != 0) this->mask[10] = '1';
			if (this->videoArchitecture.size() != 0) this->mask[11] = '1';
			if (this->videoMemoryType.size() != 0) this->mask[12] = '1';
			if (this->videoProcessor.size() != 0) this->mask[13] = '1';
			return std::string(this->mask);
		}

		void ReadMask(const char *base)
		{
			for (int i = 0; i < 14; this->mask[i] = *(base + i), i++);
		}

	public:

		Gpu()
		{
			this->adapterRAM = 0;
			this->currentBitsPerPixel = 0;
			this->currentHorizontalResolution = 0;
			this->currentNumberOfColor = 0;
			this->currentVerticalResolution = 0;
			this->currentRefreshRate = 0;
			this->maxRefreshRate = 0;
			this->minRefreshRate = 0;
			for (int i = 0; i < 14; this->mask[i] = '0', i++);
		}

		Gpu(const Gpu &object)
		{
			this->adapterCompatibility = object.adapterCompatibility;
			this->adapterRAM = object.adapterRAM;
			this->currentBitsPerPixel = object.currentBitsPerPixel;
			this->currentHorizontalResolution = object.currentHorizontalResolution;
			this->currentNumberOfColor = object.currentNumberOfColor;
			this->currentRefreshRate = object.currentRefreshRate;
			this->currentVerticalResolution = object.currentVerticalResolution;
			this->maxRefreshRate = object.maxRefreshRate;
			this->minRefreshRate = object.minRefreshRate;
			this->name = object.name;
			this->protocolSupported = object.protocolSupported;
			this->videoArchitecture = object.videoArchitecture;
			this->videoMemoryType = object.videoMemoryType;
			this->videoProcessor = object.videoProcessor;
			for (int i = 0; i < 14; this->mask[i] = object.mask[i], i++);
		}

		void getAdapterCompatibility(string adc)
		{
			this->adapterCompatibility = adc;
		}

		void getAdapterRAM(long long vram)
		{
			this->adapterRAM = vram;
		}

		void getCurrentBitsPerPixel(double cbp)
		{
			this->currentBitsPerPixel = cbp;
		}

		void getCurrentHorizontalResolution(int hresol)
		{
			this->currentHorizontalResolution = hresol;
		}

		void getCurrentVerticalResolution(int vresol)
		{
			this->currentVerticalResolution = vresol;
		}

		void getCurrentNumberOfColor(double numofcolor)
		{
			this->currentNumberOfColor = numofcolor;
		}

		void getCurrentRefreshRate(double currefspeed)
		{
			this->currentRefreshRate = currefspeed;
		}

		void getMaxRefreshRate(double mrefspeed)
		{
			this->maxRefreshRate = mrefspeed;
		}

		void getMinRefreshRate(double mrefspeed)
		{
			this->minRefreshRate = mrefspeed;
		}

		void getName(string n)
		{
			this->name = n;
		}

		void getProtocolSupported(int sw)
		{
			switch (sw)
			{
			case 1: this->protocolSupported = "Other";
				break;
			case 2: this->protocolSupported = "Unknown";
				break;
			case 3: this->protocolSupported = "EISA";
				break;
			case 4: this->protocolSupported = "ISA";
				break;
			case 5: this->protocolSupported = "PCI";
				break;
			case 6: this->protocolSupported = "ATA/ATAPI";
				break;
			case 7: this->protocolSupported = "Flexible Diskette";
				break;
			case 8: this->protocolSupported = "1496";
				break;
			case 9: this->protocolSupported = "SCSI Parallel Interface";
				break;
			case 10: this->protocolSupported = "SCSI Fibre Channel Protocol";
				break;
			case 11: this->protocolSupported = "SCSI Serial Bus Protocol";
				break;
			case 12: this->protocolSupported = "SCSI Serial Bus Protocol-2 (1394)";
				break;
			case 13: this->protocolSupported = "SCSI Serial Storage Architecture";
				break;
			case 14: this->protocolSupported = "VESA";
				break;
			case 15: this->protocolSupported = "PCMCIA";
				break;
			case 16: this->protocolSupported = "Universal Serial Bus";
				break;
			case 17: this->protocolSupported = "Parallel Protocol";
				break;
			case 18: this->protocolSupported = "ESCON";
				break;
			case 19: this->protocolSupported = "Diagnostic";
				break;
			case 20: this->protocolSupported = "I2C";
				break;
			case 21: this->protocolSupported = "Power";
				break;
			case 22: this->protocolSupported = "HIPPI";
				break;
			case 23: this->protocolSupported = "MultiBus";
				break;
			case 24: this->protocolSupported = "VME";
				break;
			case 25: this->protocolSupported = "IPI";
				break;
			case 26: this->protocolSupported = "IEEE-488";
				break;
			case 27: this->protocolSupported = "RS232";
				break;
			case 28: this->protocolSupported = "IEEE 802.3 10BASE5";
				break;
			case 29: this->protocolSupported = "IEEE 802.3 10BASE2";
				break;
			case 30: this->protocolSupported = "IEEE 802.3 1BASE5";
				break;
			case 31: this->protocolSupported = "IEEE 802.3 10BROAD36";
				break;
			case 32: this->protocolSupported = "IEEE 802.3 100BASEVG";
				break;
			case 33: this->protocolSupported = "IEEE 802.5 Token-Ring";
				break;
			case 34: this->protocolSupported = "ANSI X3T9.5 FDDI";
				break;
			case 35: this->protocolSupported = "MCA";
				break;
			case 36: this->protocolSupported = "ESDI";
				break;
			case 37: this->protocolSupported = "IDE";
				break;
			case 38: this->protocolSupported = "CMD";
				break;
			case 39: this->protocolSupported = "ST506";
				break;
			case 40: this->protocolSupported = "DSSI";
				break;
			case 41: this->protocolSupported = "QIC2";
				break;
			case 42: this->protocolSupported = "Enhanced ATA/IDE";
				break;
			case 43: this->protocolSupported = "AGP";
				break;
			case 44: this->protocolSupported = "TWIRP (two-way infrared)";
				break;
			case 45: this->protocolSupported = "FIR (fast infrared)";
				break;
			case 46: this->protocolSupported = "SIR (serial infrared)";
				break;
			case 47: this->protocolSupported = "IrBus";
				break;
			default: this->protocolSupported = sw + '0';
				break;
			}
		}

		void getVideoArchitecture(int sw)
		{
			switch (sw)
			{
			case 1: this->videoArchitecture = "Other";
				break;
			case 2: this->videoArchitecture = "Unknown";
				break;
			case 3: this->videoArchitecture = "CGA";
				break;
			case 4: this->videoArchitecture = "EGA";
				break;
			case 5: this->videoArchitecture = "VGA";
				break;
			case 6: this->videoArchitecture = "SVGA";
				break;
			case 7: this->videoArchitecture = "MDA";
				break;
			case 8: this->videoArchitecture = "HGC";
				break;
			case 9: this->videoArchitecture = "MCGA";
				break;
			case 10: this->videoArchitecture = "8514A";
				break;
			case 11: this->videoArchitecture = "XGA";
				break;
			case 12: this->videoArchitecture = "Linear Frame Buffer";
				break;
			case 160: this->videoArchitecture = "PC-98";
				break;
			}
		}

		void getVideoMemoryType(int sw)
		{
			switch (sw)
			{
			case 1: this->videoMemoryType = "Other";
				break;
			case 2: this->videoMemoryType = "Unknown";
				break;
			case 3: this->videoMemoryType = "VRAM";
				break;
			case 4: this->videoMemoryType = "DRAM";
				break;
			case 5: this->videoMemoryType = "SRAM";
				break;
			case 6: this->videoMemoryType = "WRAM";
				break;
			case 7: this->videoMemoryType = "EDO RAM";
				break;
			case 8: this->videoMemoryType = "Burst Synchronous DRAM";
				break;
			case 9: this->videoMemoryType = "Pipelined Burst SRAM";
				break;
			case 10: this->videoMemoryType = "CDRAM";
				break;
			case 11: this->videoMemoryType = "3DRAM";
				break;
			case 12: this->videoMemoryType = "SDRAM";
				break;
			case 13: this->videoMemoryType = "SGRAM";
				break;
			}
		}

		void getVideoProcessor(string proc)
		{
			this->videoProcessor = proc;
		}

		const char *setAdapterCompatibility() const
		{
			return this->adapterCompatibility.c_str();
		}

		long long setAdapterRAM() const
		{
			return this->adapterRAM;
		}

		double setCurrentBitsPerPixel() const
		{
			return this->currentBitsPerPixel;
		}

		int setCurrentHorizontalResolution() const
		{
			return this->currentHorizontalResolution;
		}

		int setCurrentVerticalResolution() const
		{
			return this->currentVerticalResolution;
		}

		double setCurrentNumberOfColor() const
		{
			return this->currentNumberOfColor;
		}

		double setCurrentRefreshRate() const
		{
			return this->currentRefreshRate;
		}

		double setMaxRefreshRate() const
		{
			return this->maxRefreshRate;
		}

		double setMinRefreshRate() const
		{
			return this->minRefreshRate;
		}

		const char *setName() const
		{
			return this->name.c_str();
		}

		const char *setProtocolSupported() const
		{
			return this->protocolSupported.c_str();
		}

		const char *setVideoArchitecture() const
		{
			return this->videoArchitecture.c_str();
		}

		const char *setVideoMemoryType() const
		{
			return this->videoMemoryType.c_str();
		}

		const char *setVideoProcessor() const
		{
			return this->videoProcessor.c_str();
		}

		Gpu& operator=(const Gpu &object)
		{
			if (this == &object)
			{
				return *this;
			}
			else {
				this->adapterCompatibility = object.adapterCompatibility;
				this->adapterRAM = object.adapterRAM;
				this->currentBitsPerPixel = object.currentBitsPerPixel;
				this->currentHorizontalResolution = object.currentHorizontalResolution;
				this->currentNumberOfColor = object.currentNumberOfColor;
				this->currentRefreshRate = object.currentRefreshRate;
				this->currentVerticalResolution = object.currentVerticalResolution;
				this->maxRefreshRate = object.maxRefreshRate;
				this->minRefreshRate = object.minRefreshRate;
				this->name = object.name;
				this->protocolSupported = object.protocolSupported;
				this->videoArchitecture = object.videoArchitecture;
				this->videoMemoryType = object.videoMemoryType;
				this->videoProcessor = object.videoProcessor;
				for (int i = 0; i < 14; this->mask[i] = object.mask[i], i++);
			}
			return *this;
		}

		void ToFile(BINARFILE *bFile)
		{
			bFile->ToFile(this->CreatMask(), 1);
			if (this->mask[0] == '1') bFile->ToFile(this->adapterCompatibility, 1);
			if (this->mask[1] == '1') bFile->ToFile(std::to_string(this->adapterRAM), 1);
			if (this->mask[2] == '1') bFile->ToFile(std::to_string(this->currentBitsPerPixel), 1);
			if (this->mask[3] == '1') bFile->ToFile(std::to_string(this->currentHorizontalResolution), 1);
			if (this->mask[4] == '1') bFile->ToFile(std::to_string(this->currentVerticalResolution), 1);
			if (this->mask[5] == '1') bFile->ToFile(std::to_string(this->currentNumberOfColor), 1);
			if (this->mask[6] == '1') bFile->ToFile(std::to_string(this->currentRefreshRate), 1);
			if (this->mask[7] == '1') bFile->ToFile(std::to_string(this->maxRefreshRate), 1);
			if (this->mask[8] == '1') bFile->ToFile(std::to_string(this->minRefreshRate), 1);
			if (this->mask[9] == '1') bFile->ToFile(this->name, 1);
			if (this->mask[10] == '1') bFile->ToFile(this->protocolSupported, 1);
			if (this->mask[11] == '1') bFile->ToFile(this->videoArchitecture, 1);
			if (this->mask[12] == '1') bFile->ToFile(this->videoMemoryType, 1);
			if (this->mask[13] == '1') bFile->ToFile(this->videoProcessor, 1);
		}

		void FromFile(BINARFILE *bFile)
		{
			this->ReadMask(bFile->FromFile().c_str());
			if (this->mask[0] == '1') this->adapterCompatibility = bFile->FromFile();
			if (this->mask[1] == '1') this->adapterRAM = std::stoll(bFile->FromFile());
			if (this->mask[2] == '1') this->currentBitsPerPixel = std::stod(bFile->FromFile());
			if (this->mask[3] == '1') this->currentHorizontalResolution = std::stoi(bFile->FromFile());
			if (this->mask[4] == '1') this->currentVerticalResolution = std::stoi(bFile->FromFile());
			if (this->mask[5] == '1') this->currentNumberOfColor = std::stod(bFile->FromFile());
			if (this->mask[6] == '1') this->currentRefreshRate = std::stod(bFile->FromFile());
			if (this->mask[7] == '1') this->maxRefreshRate = std::stod(bFile->FromFile());
			if (this->mask[8] == '1') this->minRefreshRate = std::stod(bFile->FromFile());
			if (this->mask[9] == '1') this->name = bFile->FromFile();
			if (this->mask[10] == '1') this->protocolSupported = bFile->FromFile();
			if (this->mask[11] == '1') this->videoArchitecture = bFile->FromFile();
			if (this->mask[12] == '1') this->videoMemoryType = bFile->FromFile();
			if (this->mask[13] == '1') this->videoProcessor = bFile->FromFile();
		}
	};
}