#include "MyForm.h"
#include "Server.h"
#include <string>

#define FILENAME "hardware.txt"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Threading;

Server *server;
struct TransferData *tdata;


SystemMonitoringOSWindows::MyForm::~MyForm()
{
	if (server)
	{
		delete server;
	}
	if (components)
	{
		delete components;
	}
}

void SystemMonitoringOSWindows::MyForm::InitializeClasses()
{
	server = new Server();
	tdata = (TransferData *)malloc(sizeof(TransferData));
	tdata->hardware = new AllHardware::Hardware();
	tdata->flag = 0;
	if (!server->CreatWMIProcess(0)) return;
	if (!server->CreatNamedPipe()) return;
	if (!server->CreatConnection(tdata)) return;
	server->CloseNamed();
	server->CloseWMIProcess();
	//
	//заполняются поля для процессора
	//
	this->CPU_NAME->Text =  gcnew String(tdata->hardware->hard.proc.setName());
	std::string str = tdata->hardware->hard.proc.setArchitecture();
	str = str + "/" + tdata->hardware->hard.proc.setAddressWidth();
	this->CPU_ARCH_ADDRESSWIDTH->Text = gcnew String(str.c_str());
	str = std::to_string(tdata->hardware->hard.proc.setNumberOfCores());
	str = str + "/" + std::to_string(tdata->hardware->hard.proc.setNumberOfEnabledCores());
	this->CPU_COUNT_OF_PROC_AVAILPROC->Text = gcnew String(str.c_str());
	this->CPU_FAMILY->Text = gcnew String(tdata->hardware->hard.proc.setFamily());
	this->CPU_MANUFACTURER->Text = gcnew String(tdata->hardware->hard.proc.setManufacturer());
	this->CPU_MAX_FREQUENCY->Text = gcnew String(std::to_string(tdata->hardware->hard.proc.setMaxSpeed()).c_str());
	this->CPU_L2CACHE->Text = gcnew String(std::to_string((long long)tdata->hardware->hard.proc.setL2Size()).c_str());
	this->CPU_L3CACHE->Text = gcnew String(std::to_string((long long)tdata->hardware->hard.proc.setL3Size() / 1000).c_str());
	this->CPU_LOG_PROC_COUNT->Text = gcnew String(std::to_string(tdata->hardware->hard.proc.setNumberOfLogicalPrroc()).c_str());
	this->CPU_CUR_FREQ->Text = gcnew String(std::to_string(tdata->hardware->hard.proc.setCurrentSpeed()).c_str());
	this->CPU_PERCANTAGE->Text = gcnew String(std::to_string(tdata->hardware->hard.proc.setLoadPercentage()).c_str());
	//
	//заполняются поля для видео адаптера
	//
	this->GPU_NAME->Text = gcnew String(tdata->hardware->hard.gpu.setName());
	this->GPU_CHIP->Text = gcnew String(tdata->hardware->hard.gpu.setAdapterCompatibility());
	this->GPU_PROC->Text = gcnew String(tdata->hardware->hard.gpu.setVideoProcessor());
	this->GPU_ARCHITECTURE->Text = gcnew String(tdata->hardware->hard.gpu.setVideoArchitecture());
	this->GPU_RAM->Text = gcnew String(std::to_string(tdata->hardware->hard.gpu.setAdapterRAM() / 1024 / 1024).c_str());
	this->GPU_BITS_PER_PIXEL->Text = gcnew String(std::to_string((long long)tdata->hardware->hard.gpu.setCurrentBitsPerPixel()).c_str());
	str = std::to_string(tdata->hardware->hard.gpu.setCurrentHorizontalResolution());
	str = str + "x" + std::to_string(tdata->hardware->hard.gpu.setCurrentVerticalResolution());
	this->GPU_RESOLUTION->Text = gcnew String(str.c_str());
	this->GPU_REFRESH_RATE->Text = gcnew String(std::to_string((long long)tdata->hardware->hard.gpu.setCurrentRefreshRate()).c_str());
	this->GPU_MEMORY_TYPE->Text = gcnew String(tdata->hardware->hard.gpu.setVideoMemoryType());
	//
	//монитор и дисплей
	//
	this->MONITOR_DISP_TYPE->Text = gcnew String(tdata->hardware->hard.monitor.setDisplayType());
	this->MONITOR_MANUFACTURER->Text = gcnew String(tdata->hardware->hard.monitor.setMonitorManufacturer());
	this->MONITOR_TYPE->Text = gcnew String(tdata->hardware->hard.monitor.setMonitorType());
	//
	//операционная система
	//
	this->OS_NAME->Text = gcnew String(tdata->hardware->hard.opsys[0].setCaption());
	this->OS_ARCHITECTURE->Text = gcnew String(tdata->hardware->hard.opsys[0].setOSArchitecture());
	this->OS_COMPUTER_NAME->Text = gcnew String(tdata->hardware->hard.opsys[0].setCSName());
	this->OS_DEVICE->Text = gcnew String(tdata->hardware->hard.opsys[0].setSystemDevice());
	this->OS_DIRECTORY->Text = gcnew String(tdata->hardware->hard.opsys[0].setSystemDirectory());
	this->OS_MANUFACTURER->Text = gcnew String(tdata->hardware->hard.opsys[0].setManufacturer());
	this->OS_SERIAL_NUMBER->Text = gcnew String(tdata->hardware->hard.opsys[0].setSerialNumber());
	this->OS_PROCESS_COUNT->Text = gcnew String(std::to_string(tdata->hardware->hard.opsys[0].setNumberOfProcesses()).c_str());
	this->OS_SKU->Text = gcnew String(tdata->hardware->hard.opsys[0].setOperatingSystemSKU());
	this->OS_VERSION->Text = gcnew String(tdata->hardware->hard.opsys[0].setVersion());
	this->TOTAL_COUNT_OF_PROCESSES->Text = gcnew String(std::to_string(tdata->hardware->hard.opsys[0].setNumberOfProcesses()).c_str());
	this->OS_BUILD_NUMBER->Text = gcnew String(tdata->hardware->hard.opsys[0].setBuildNumber());
	//
	//процессы
	//
	for (int i = 0; i < tdata->hardware->hard.procv.size(); i++)
	{
		this->listViewItem = gcnew System::Windows::Forms::ListViewItem(gcnew System::String(tdata->hardware->hard.procv[i].setName()));
		this->listViewItem->SubItems->Add(gcnew System::String(std::to_string(tdata->hardware->hard.procv[i].setProccessID()).c_str()));
		this->listViewItem->SubItems->Add(gcnew System::String(std::to_string(tdata->hardware->hard.procv[i].setParentProccessID()).c_str()));
		this->listViewItem->SubItems->Add(gcnew System::String(std::to_string(tdata->hardware->hard.procv[i].setWorkingSetSize()).c_str()));
		this->listViewItem->SubItems->Add(gcnew System::String(tdata->hardware->hard.procv[i].setExecutablePath()));
		this->listViewItem->SubItems->Add(gcnew System::String(std::to_string(tdata->hardware->hard.procv[i].setHandleCount()).c_str()));
		this->listViewItem->SubItems->Add(gcnew System::String(std::to_string(tdata->hardware->hard.procv[i].setThreadCount()).c_str()));
		this->PROCESSES->Items->Add(this->listViewItem);
	}
	//
	//материнская плата и ОЗУ
	//
	str = tdata->hardware->hard.mb.setCaption();
	str = str + " " + tdata->hardware->hard.mb.setManufacturer();
	this->BASEBOARD_DESCRIPTION->Text = gcnew System::String(str.c_str());
	this->BASEBOARD_SERIALNUMBER->Text = gcnew System::String(tdata->hardware->hard.mb.setSerialNumber());
	this->TOTAL_PHYS_MEM->Text = gcnew System::String(std::to_string((double)(tdata->hardware->hard.mem.setTotalMemory() / 1024.0 / 1024.0 / 1024.0)).c_str());
	this->AVAIL_PHYS_MEM->Text = gcnew System::String(std::to_string(tdata->hardware->hard.mem.setFreeMemory()).c_str());
	this->TOTAL_VIRTUAL_MEM->Text = gcnew System::String(std::to_string(tdata->hardware->hard.mem.setTotalVirtualMemory()).c_str());
	this->AVAIL_VIRTUAL_MEM->Text = gcnew System::String(std::to_string(tdata->hardware->hard.mem.setFreeVirtualMemory()).c_str());
	//
	//логические диски
	//
	for (int i = 0; i < tdata->hardware->hard.ldisk.size(); i++)
	{
		this->listViewItem = gcnew System::Windows::Forms::ListViewItem(gcnew System::String(tdata->hardware->hard.ldisk[i].setDeviceID()));
		this->listViewItem->SubItems->Add(gcnew System::String(tdata->hardware->hard.ldisk[i].setFileSystem()));
		this->listViewItem->SubItems->Add(gcnew System::String(tdata->hardware->hard.ldisk[i].setDriveType()));
		this->listViewItem->SubItems->Add(gcnew System::String(std::to_string(tdata->hardware->hard.ldisk[i].setSize() / 1000000000.0).c_str()));
		this->listViewItem->SubItems->Add(gcnew System::String(std::to_string(tdata->hardware->hard.ldisk[i].setFreeSpace() / 1000000000.0).c_str()));
		this->listViewItem->SubItems->Add(gcnew System::String(std::to_string((long long)tdata->hardware->hard.ldisk[i].setMaxComponentLenght()).c_str()));
		this->LOGICAL_DISKS->Items->Add(this->listViewItem);
	}
	//
	//физические диски
	//
	for (int i = 0; i < tdata->hardware->hard.disk.size(); i++)
	{
		this->listViewItem = gcnew System::Windows::Forms::ListViewItem(gcnew System::String(tdata->hardware->hard.disk[i].setModel()));
		this->listViewItem->SubItems->Add(gcnew System::String(tdata->hardware->hard.disk[i].setDescription()));
		this->listViewItem->SubItems->Add(gcnew System::String(std::to_string(tdata->hardware->hard.disk[i].setSize() / 1000 / 1000 / 1000).c_str()));
		this->listViewItem->SubItems->Add(gcnew System::String(tdata->hardware->hard.disk[i].setInterfaceType()));
		this->listViewItem->SubItems->Add(gcnew System::String(tdata->hardware->hard.disk[i].setDeviceID()));
		this->listViewItem->SubItems->Add(gcnew System::String(std::to_string(tdata->hardware->hard.disk[i].setBytesPerSector()).c_str()));
		this->listViewItem->SubItems->Add(gcnew System::String(tdata->hardware->hard.disk[i].setMediaType()));
		this->listViewItem->SubItems->Add(gcnew System::String(tdata->hardware->hard.disk[i].setSerialNumber()));
		this->listViewItem->SubItems->Add(gcnew System::String(tdata->hardware->hard.disk[i].setFirmwareRevision()));
		this->PD_LIST->Items->Add(this->listViewItem);
	}
	//
	//сетевые адаптеры
	//
	for (int i = 0; i < tdata->hardware->hard.net.size(); i++)
	{
		this->listViewItem = gcnew System::Windows::Forms::ListViewItem(gcnew System::String(tdata->hardware->hard.net[i].setName()));
		this->listViewItem->SubItems->Add(gcnew System::String(tdata->hardware->hard.net[i].setNetConnectionStatus()));
		this->listViewItem->SubItems->Add(gcnew System::String(tdata->hardware->hard.net[i].setNetConnectionID()));
		this->listViewItem->SubItems->Add(gcnew System::String(tdata->hardware->hard.net[i].setAdapterType()));
		this->listViewItem->SubItems->Add(gcnew System::String(tdata->hardware->hard.net[i].setDeviceID()));
		this->listViewItem->SubItems->Add(gcnew System::String(tdata->hardware->hard.net[i].setMACAddress()));
		this->listViewItem->SubItems->Add(gcnew System::String(tdata->hardware->hard.net[i].setGUID()));
		this->listViewItem->SubItems->Add(gcnew System::String(tdata->hardware->hard.net[i].setManufacturer()));
		this->listViewItem->SubItems->Add(gcnew System::String(std::to_string(tdata->hardware->hard.net[i].setSpeed() / 1000).c_str()));
		this->NET_LIST->Items->Add(this->listViewItem);
	}
	delete tdata->hardware;
	free(tdata);
	delete server;
	this->BACKGROUND_WORK->RunWorkerAsync(1);
}

void SystemMonitoringOSWindows::MyForm::InitializeComponent()
{
	System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
	System::Windows::Forms::ListViewItem^  listViewItem3 = (gcnew System::Windows::Forms::ListViewItem(L""));
	this->Hardware = (gcnew System::Windows::Forms::TabControl());
	this->CPU = (gcnew System::Windows::Forms::TabPage());
	this->CPU_PERCANTAGE = (gcnew System::Windows::Forms::Label());
	this->CPU_L3CACHE = (gcnew System::Windows::Forms::Label());
	this->CPU_L2CACHE = (gcnew System::Windows::Forms::Label());
	this->CPU_LOG_PROC_COUNT = (gcnew System::Windows::Forms::Label());
	this->CPU_THREADS = (gcnew System::Windows::Forms::Label());
	this->CPU_COUNT_OF_PROC_AVAILPROC = (gcnew System::Windows::Forms::Label());
	this->CPU_CUR_FREQ = (gcnew System::Windows::Forms::Label());
	this->CPU_MAX_FREQUENCY = (gcnew System::Windows::Forms::Label());
	this->CPU_ARCH_ADDRESSWIDTH = (gcnew System::Windows::Forms::Label());
	this->CPU_FAMILY = (gcnew System::Windows::Forms::Label());
	this->CPU_MANUFACTURER = (gcnew System::Windows::Forms::Label());
	this->label15 = (gcnew System::Windows::Forms::Label());
	this->label14 = (gcnew System::Windows::Forms::Label());
	this->label13 = (gcnew System::Windows::Forms::Label());
	this->label12 = (gcnew System::Windows::Forms::Label());
	this->label11 = (gcnew System::Windows::Forms::Label());
	this->label10 = (gcnew System::Windows::Forms::Label());
	this->label9 = (gcnew System::Windows::Forms::Label());
	this->label8 = (gcnew System::Windows::Forms::Label());
	this->label7 = (gcnew System::Windows::Forms::Label());
	this->label6 = (gcnew System::Windows::Forms::Label());
	this->label5 = (gcnew System::Windows::Forms::Label());
	this->CPU_NAME = (gcnew System::Windows::Forms::Label());
	this->label1 = (gcnew System::Windows::Forms::Label());
	this->GPU = (gcnew System::Windows::Forms::TabPage());
	this->MONITOR_DISP_TYPE = (gcnew System::Windows::Forms::Label());
	this->label36 = (gcnew System::Windows::Forms::Label());
	this->MONITOR_TYPE = (gcnew System::Windows::Forms::Label());
	this->label35 = (gcnew System::Windows::Forms::Label());
	this->MONITOR_MANUFACTURER = (gcnew System::Windows::Forms::Label());
	this->label34 = (gcnew System::Windows::Forms::Label());
	this->GPU_MEMORY_TYPE = (gcnew System::Windows::Forms::Label());
	this->GPU_REFRESH_RATE = (gcnew System::Windows::Forms::Label());
	this->GPU_RESOLUTION = (gcnew System::Windows::Forms::Label());
	this->GPU_BITS_PER_PIXEL = (gcnew System::Windows::Forms::Label());
	this->GPU_RAM = (gcnew System::Windows::Forms::Label());
	this->GPU_ARCHITECTURE = (gcnew System::Windows::Forms::Label());
	this->GPU_PROC = (gcnew System::Windows::Forms::Label());
	this->GPU_CHIP = (gcnew System::Windows::Forms::Label());
	this->label24 = (gcnew System::Windows::Forms::Label());
	this->label22 = (gcnew System::Windows::Forms::Label());
	this->label21 = (gcnew System::Windows::Forms::Label());
	this->label20 = (gcnew System::Windows::Forms::Label());
	this->label19 = (gcnew System::Windows::Forms::Label());
	this->label18 = (gcnew System::Windows::Forms::Label());
	this->label17 = (gcnew System::Windows::Forms::Label());
	this->label16 = (gcnew System::Windows::Forms::Label());
	this->GPU_NAME = (gcnew System::Windows::Forms::Label());
	this->label2 = (gcnew System::Windows::Forms::Label());
	this->LDISK = (gcnew System::Windows::Forms::TabPage());
	this->LOGICAL_DISKS = (gcnew System::Windows::Forms::ListView());
	this->columnHeader1 = (gcnew System::Windows::Forms::ColumnHeader());
	this->columnHeader2 = (gcnew System::Windows::Forms::ColumnHeader());
	this->columnHeader3 = (gcnew System::Windows::Forms::ColumnHeader());
	this->columnHeader4 = (gcnew System::Windows::Forms::ColumnHeader());
	this->columnHeader5 = (gcnew System::Windows::Forms::ColumnHeader());
	this->columnHeader6 = (gcnew System::Windows::Forms::ColumnHeader());
	this->PDISK = (gcnew System::Windows::Forms::TabPage());
	this->PD_LIST = (gcnew System::Windows::Forms::ListView());
	this->columnHeader7 = (gcnew System::Windows::Forms::ColumnHeader());
	this->columnHeader8 = (gcnew System::Windows::Forms::ColumnHeader());
	this->columnHeader9 = (gcnew System::Windows::Forms::ColumnHeader());
	this->columnHeader11 = (gcnew System::Windows::Forms::ColumnHeader());
	this->columnHeader12 = (gcnew System::Windows::Forms::ColumnHeader());
	this->columnHeader13 = (gcnew System::Windows::Forms::ColumnHeader());
	this->columnHeader14 = (gcnew System::Windows::Forms::ColumnHeader());
	this->columnHeader15 = (gcnew System::Windows::Forms::ColumnHeader());
	this->columnHeader25 = (gcnew System::Windows::Forms::ColumnHeader());
	this->PROCESS = (gcnew System::Windows::Forms::TabPage());
	this->TOTAL_COUNT_OF_PROCESSES = (gcnew System::Windows::Forms::Label());
	this->label32 = (gcnew System::Windows::Forms::Label());
	this->PROCESSES = (gcnew System::Windows::Forms::ListView());
	this->PROCESS_NAME = (gcnew System::Windows::Forms::ColumnHeader());
	this->PROCESS_ID = (gcnew System::Windows::Forms::ColumnHeader());
	this->PARENT_PROCESS_ID = (gcnew System::Windows::Forms::ColumnHeader());
	this->PROCESS_WORKING_SIZE = (gcnew System::Windows::Forms::ColumnHeader());
	this->PROCESS_EXEC_PATH = (gcnew System::Windows::Forms::ColumnHeader());
	this->PROCESS_HANDLE_COUNT = (gcnew System::Windows::Forms::ColumnHeader());
	this->PROCESS_THREADS_COUNT = (gcnew System::Windows::Forms::ColumnHeader());
	this->OS = (gcnew System::Windows::Forms::TabPage());
	this->OS_BUILD_NUMBER = (gcnew System::Windows::Forms::Label());
	this->label23 = (gcnew System::Windows::Forms::Label());
	this->OS_COMPUTER_NAME = (gcnew System::Windows::Forms::Label());
	this->OS_VERSION = (gcnew System::Windows::Forms::Label());
	this->OS_SERIAL_NUMBER = (gcnew System::Windows::Forms::Label());
	this->OS_DIRECTORY = (gcnew System::Windows::Forms::Label());
	this->OS_DEVICE = (gcnew System::Windows::Forms::Label());
	this->OS_PROCESS_COUNT = (gcnew System::Windows::Forms::Label());
	this->OS_MANUFACTURER = (gcnew System::Windows::Forms::Label());
	this->OS_SKU = (gcnew System::Windows::Forms::Label());
	this->compname = (gcnew System::Windows::Forms::Label());
	this->version = (gcnew System::Windows::Forms::Label());
	this->sernum = (gcnew System::Windows::Forms::Label());
	this->directory = (gcnew System::Windows::Forms::Label());
	this->device = (gcnew System::Windows::Forms::Label());
	this->processe = (gcnew System::Windows::Forms::Label());
	this->manufacturer = (gcnew System::Windows::Forms::Label());
	this->sku = (gcnew System::Windows::Forms::Label());
	this->OS_ARCHITECTURE = (gcnew System::Windows::Forms::Label());
	this->label25 = (gcnew System::Windows::Forms::Label());
	this->OS_NAME = (gcnew System::Windows::Forms::Label());
	this->label3 = (gcnew System::Windows::Forms::Label());
	this->MOTHERBOARD_AND_RAM = (gcnew System::Windows::Forms::TabPage());
	this->AVAIL_VIRTUAL_MEM = (gcnew System::Windows::Forms::Label());
	this->label30 = (gcnew System::Windows::Forms::Label());
	this->label31 = (gcnew System::Windows::Forms::Label());
	this->TOTAL_VIRTUAL_MEM = (gcnew System::Windows::Forms::Label());
	this->label29 = (gcnew System::Windows::Forms::Label());
	this->AVAIL_PHYS_MEM = (gcnew System::Windows::Forms::Label());
	this->label28 = (gcnew System::Windows::Forms::Label());
	this->TOTAL_PHYS_MEM = (gcnew System::Windows::Forms::Label());
	this->mem = (gcnew System::Windows::Forms::Label());
	this->BASEBOARD_SERIALNUMBER = (gcnew System::Windows::Forms::Label());
	this->label27 = (gcnew System::Windows::Forms::Label());
	this->BASEBOARD_DESCRIPTION = (gcnew System::Windows::Forms::Label());
	this->label26 = (gcnew System::Windows::Forms::Label());
	this->label4 = (gcnew System::Windows::Forms::Label());
	this->NETWORK = (gcnew System::Windows::Forms::TabPage());
	this->NET_LIST = (gcnew System::Windows::Forms::ListView());
	this->columnHeader16 = (gcnew System::Windows::Forms::ColumnHeader());
	this->columnHeader17 = (gcnew System::Windows::Forms::ColumnHeader());
	this->columnHeader18 = (gcnew System::Windows::Forms::ColumnHeader());
	this->columnHeader19 = (gcnew System::Windows::Forms::ColumnHeader());
	this->columnHeader20 = (gcnew System::Windows::Forms::ColumnHeader());
	this->columnHeader21 = (gcnew System::Windows::Forms::ColumnHeader());
	this->columnHeader22 = (gcnew System::Windows::Forms::ColumnHeader());
	this->columnHeader23 = (gcnew System::Windows::Forms::ColumnHeader());
	this->columnHeader24 = (gcnew System::Windows::Forms::ColumnHeader());
	this->BACKGROUND_WORK = (gcnew System::ComponentModel::BackgroundWorker());
	this->Hardware->SuspendLayout();
	this->CPU->SuspendLayout();
	this->GPU->SuspendLayout();
	this->LDISK->SuspendLayout();
	this->PDISK->SuspendLayout();
	this->PROCESS->SuspendLayout();
	this->OS->SuspendLayout();
	this->MOTHERBOARD_AND_RAM->SuspendLayout();
	this->NETWORK->SuspendLayout();
	this->SuspendLayout();
	// 
	// Hardware
	// 
	this->Hardware->Controls->Add(this->CPU);
	this->Hardware->Controls->Add(this->GPU);
	this->Hardware->Controls->Add(this->LDISK);
	this->Hardware->Controls->Add(this->PDISK);
	this->Hardware->Controls->Add(this->PROCESS);
	this->Hardware->Controls->Add(this->OS);
	this->Hardware->Controls->Add(this->MOTHERBOARD_AND_RAM);
	this->Hardware->Controls->Add(this->NETWORK);
	this->Hardware->Location = System::Drawing::Point(12, 12);
	this->Hardware->Name = L"Hardware";
	this->Hardware->SelectedIndex = 0;
	this->Hardware->Size = System::Drawing::Size(860, 397);
	this->Hardware->TabIndex = 0;
	// 
	// CPU
	// 
	this->CPU->BackColor = System::Drawing::Color::White;
	this->CPU->Controls->Add(this->CPU_PERCANTAGE);
	this->CPU->Controls->Add(this->CPU_L3CACHE);
	this->CPU->Controls->Add(this->CPU_L2CACHE);
	this->CPU->Controls->Add(this->CPU_LOG_PROC_COUNT);
	this->CPU->Controls->Add(this->CPU_THREADS);
	this->CPU->Controls->Add(this->CPU_COUNT_OF_PROC_AVAILPROC);
	this->CPU->Controls->Add(this->CPU_CUR_FREQ);
	this->CPU->Controls->Add(this->CPU_MAX_FREQUENCY);
	this->CPU->Controls->Add(this->CPU_ARCH_ADDRESSWIDTH);
	this->CPU->Controls->Add(this->CPU_FAMILY);
	this->CPU->Controls->Add(this->CPU_MANUFACTURER);
	this->CPU->Controls->Add(this->label15);
	this->CPU->Controls->Add(this->label14);
	this->CPU->Controls->Add(this->label13);
	this->CPU->Controls->Add(this->label12);
	this->CPU->Controls->Add(this->label11);
	this->CPU->Controls->Add(this->label10);
	this->CPU->Controls->Add(this->label9);
	this->CPU->Controls->Add(this->label8);
	this->CPU->Controls->Add(this->label7);
	this->CPU->Controls->Add(this->label6);
	this->CPU->Controls->Add(this->label5);
	this->CPU->Controls->Add(this->CPU_NAME);
	this->CPU->Controls->Add(this->label1);
	this->CPU->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->CPU->ImageKey = L"(отсутствует)";
	this->CPU->ImeMode = System::Windows::Forms::ImeMode::NoControl;
	this->CPU->Location = System::Drawing::Point(4, 22);
	this->CPU->Name = L"CPU";
	this->CPU->Padding = System::Windows::Forms::Padding(3);
	this->CPU->Size = System::Drawing::Size(852, 371);
	this->CPU->TabIndex = 0;
	this->CPU->Text = L"Процессор";
	// 
	// CPU_PERCANTAGE
	// 
	this->CPU_PERCANTAGE->AutoSize = true;
	this->CPU_PERCANTAGE->Font = (gcnew System::Drawing::Font(L"Times New Roman", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->CPU_PERCANTAGE->Location = System::Drawing::Point(181, 301);
	this->CPU_PERCANTAGE->Name = L"CPU_PERCANTAGE";
	this->CPU_PERCANTAGE->Size = System::Drawing::Size(22, 17);
	this->CPU_PERCANTAGE->TabIndex = 24;
	this->CPU_PERCANTAGE->Text = L"23";
	// 
	// CPU_L3CACHE
	// 
	this->CPU_L3CACHE->AutoSize = true;
	this->CPU_L3CACHE->Font = (gcnew System::Drawing::Font(L"Times New Roman", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->CPU_L3CACHE->Location = System::Drawing::Point(548, 256);
	this->CPU_L3CACHE->Name = L"CPU_L3CACHE";
	this->CPU_L3CACHE->Size = System::Drawing::Size(39, 17);
	this->CPU_L3CACHE->TabIndex = 23;
	this->CPU_L3CACHE->Text = L"3,072";
	// 
	// CPU_L2CACHE
	// 
	this->CPU_L2CACHE->AutoSize = true;
	this->CPU_L2CACHE->Font = (gcnew System::Drawing::Font(L"Times New Roman", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->CPU_L2CACHE->Location = System::Drawing::Point(545, 212);
	this->CPU_L2CACHE->Name = L"CPU_L2CACHE";
	this->CPU_L2CACHE->Size = System::Drawing::Size(29, 17);
	this->CPU_L2CACHE->TabIndex = 22;
	this->CPU_L2CACHE->Text = L"256";
	// 
	// CPU_LOG_PROC_COUNT
	// 
	this->CPU_LOG_PROC_COUNT->AutoSize = true;
	this->CPU_LOG_PROC_COUNT->Font = (gcnew System::Drawing::Font(L"Times New Roman", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->CPU_LOG_PROC_COUNT->Location = System::Drawing::Point(608, 169);
	this->CPU_LOG_PROC_COUNT->Name = L"CPU_LOG_PROC_COUNT";
	this->CPU_LOG_PROC_COUNT->Size = System::Drawing::Size(15, 17);
	this->CPU_LOG_PROC_COUNT->TabIndex = 21;
	this->CPU_LOG_PROC_COUNT->Text = L"2";
	// 
	// CPU_THREADS
	// 
	this->CPU_THREADS->AutoSize = true;
	this->CPU_THREADS->Font = (gcnew System::Drawing::Font(L"Times New Roman", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->CPU_THREADS->Location = System::Drawing::Point(505, 125);
	this->CPU_THREADS->Name = L"CPU_THREADS";
	this->CPU_THREADS->Size = System::Drawing::Size(15, 17);
	this->CPU_THREADS->TabIndex = 20;
	this->CPU_THREADS->Text = L"2";
	// 
	// CPU_COUNT_OF_PROC_AVAILPROC
	// 
	this->CPU_COUNT_OF_PROC_AVAILPROC->AutoSize = true;
	this->CPU_COUNT_OF_PROC_AVAILPROC->Font = (gcnew System::Drawing::Font(L"Times New Roman", 11.25F, System::Drawing::FontStyle::Regular,
		System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
	this->CPU_COUNT_OF_PROC_AVAILPROC->Location = System::Drawing::Point(590, 84);
	this->CPU_COUNT_OF_PROC_AVAILPROC->Name = L"CPU_COUNT_OF_PROC_AVAILPROC";
	this->CPU_COUNT_OF_PROC_AVAILPROC->Size = System::Drawing::Size(26, 17);
	this->CPU_COUNT_OF_PROC_AVAILPROC->TabIndex = 19;
	this->CPU_COUNT_OF_PROC_AVAILPROC->Text = L"2/2";
	// 
	// CPU_CUR_FREQ
	// 
	this->CPU_CUR_FREQ->AutoSize = true;
	this->CPU_CUR_FREQ->Font = (gcnew System::Drawing::Font(L"Times New Roman", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->CPU_CUR_FREQ->Location = System::Drawing::Point(208, 256);
	this->CPU_CUR_FREQ->Name = L"CPU_CUR_FREQ";
	this->CPU_CUR_FREQ->Size = System::Drawing::Size(39, 17);
	this->CPU_CUR_FREQ->TabIndex = 17;
	this->CPU_CUR_FREQ->Text = L"0,993";
	// 
	// CPU_MAX_FREQUENCY
	// 
	this->CPU_MAX_FREQUENCY->AutoSize = true;
	this->CPU_MAX_FREQUENCY->Font = (gcnew System::Drawing::Font(L"Times New Roman", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->CPU_MAX_FREQUENCY->Location = System::Drawing::Point(192, 212);
	this->CPU_MAX_FREQUENCY->Name = L"CPU_MAX_FREQUENCY";
	this->CPU_MAX_FREQUENCY->Size = System::Drawing::Size(32, 17);
	this->CPU_MAX_FREQUENCY->TabIndex = 16;
	this->CPU_MAX_FREQUENCY->Text = L"1,99";
	// 
	// CPU_ARCH_ADDRESSWIDTH
	// 
	this->CPU_ARCH_ADDRESSWIDTH->AutoSize = true;
	this->CPU_ARCH_ADDRESSWIDTH->Font = (gcnew System::Drawing::Font(L"Times New Roman", 11.25F, System::Drawing::FontStyle::Regular,
		System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
	this->CPU_ARCH_ADDRESSWIDTH->Location = System::Drawing::Point(238, 169);
	this->CPU_ARCH_ADDRESSWIDTH->Name = L"CPU_ARCH_ADDRESSWIDTH";
	this->CPU_ARCH_ADDRESSWIDTH->Size = System::Drawing::Size(66, 17);
	this->CPU_ARCH_ADDRESSWIDTH->TabIndex = 15;
	this->CPU_ARCH_ADDRESSWIDTH->Text = L"x64/64-bit";
	// 
	// CPU_FAMILY
	// 
	this->CPU_FAMILY->AutoSize = true;
	this->CPU_FAMILY->Font = (gcnew System::Drawing::Font(L"Times New Roman", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->CPU_FAMILY->Location = System::Drawing::Point(203, 125);
	this->CPU_FAMILY->Name = L"CPU_FAMILY";
	this->CPU_FAMILY->Size = System::Drawing::Size(44, 17);
	this->CPU_FAMILY->TabIndex = 14;
	this->CPU_FAMILY->Text = L"family";
	// 
	// CPU_MANUFACTURER
	// 
	this->CPU_MANUFACTURER->AutoSize = true;
	this->CPU_MANUFACTURER->Font = (gcnew System::Drawing::Font(L"Times New Roman", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->CPU_MANUFACTURER->Location = System::Drawing::Point(155, 84);
	this->CPU_MANUFACTURER->Name = L"CPU_MANUFACTURER";
	this->CPU_MANUFACTURER->Size = System::Drawing::Size(87, 17);
	this->CPU_MANUFACTURER->TabIndex = 13;
	this->CPU_MANUFACTURER->Text = L"manufacturer";
	// 
	// label15
	// 
	this->label15->AutoSize = true;
	this->label15->Font = (gcnew System::Drawing::Font(L"Times New Roman", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->label15->Location = System::Drawing::Point(43, 301);
	this->label15->Name = L"label15";
	this->label15->Size = System::Drawing::Size(132, 17);
	this->label15->TabIndex = 12;
	this->label15->Text = L"Загруженность (%):";
	// 
	// label14
	// 
	this->label14->AutoSize = true;
	this->label14->Font = (gcnew System::Drawing::Font(L"Times New Roman", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->label14->Location = System::Drawing::Point(394, 169);
	this->label14->Name = L"label14";
	this->label14->Size = System::Drawing::Size(208, 17);
	this->label14->TabIndex = 11;
	this->label14->Text = L"Кол-во логических процессоров:";
	// 
	// label13
	// 
	this->label13->AutoSize = true;
	this->label13->Font = (gcnew System::Drawing::Font(L"Times New Roman", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->label13->Location = System::Drawing::Point(394, 125);
	this->label13->Name = L"label13";
	this->label13->Size = System::Drawing::Size(105, 17);
	this->label13->TabIndex = 10;
	this->label13->Text = L"Кол-во потоков:";
	// 
	// label12
	// 
	this->label12->AutoSize = true;
	this->label12->Font = (gcnew System::Drawing::Font(L"Times New Roman", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->label12->Location = System::Drawing::Point(394, 84);
	this->label12->Name = L"label12";
	this->label12->Size = System::Drawing::Size(190, 17);
	this->label12->TabIndex = 9;
	this->label12->Text = L"Кол-во ядер/доступных ядер:";
	// 
	// label11
	// 
	this->label11->AutoSize = true;
	this->label11->Font = (gcnew System::Drawing::Font(L"Times New Roman", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->label11->Location = System::Drawing::Point(394, 256);
	this->label11->Name = L"label11";
	this->label11->Size = System::Drawing::Size(148, 17);
	this->label11->TabIndex = 8;
	this->label11->Text = L"Кэш 3-го уровня (Мб):";
	// 
	// label10
	// 
	this->label10->AutoSize = true;
	this->label10->Font = (gcnew System::Drawing::Font(L"Times New Roman", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->label10->Location = System::Drawing::Point(394, 212);
	this->label10->Name = L"label10";
	this->label10->Size = System::Drawing::Size(145, 17);
	this->label10->TabIndex = 7;
	this->label10->Text = L"Кэш 2-го уровня (Кб):";
	// 
	// label9
	// 
	this->label9->AutoSize = true;
	this->label9->Font = (gcnew System::Drawing::Font(L"Times New Roman", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->label9->Location = System::Drawing::Point(43, 256);
	this->label9->Name = L"label9";
	this->label9->Size = System::Drawing::Size(159, 17);
	this->label9->TabIndex = 6;
	this->label9->Text = L"Текущая частота (GGz):";
	// 
	// label8
	// 
	this->label8->AutoSize = true;
	this->label8->Font = (gcnew System::Drawing::Font(L"Times New Roman", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->label8->Location = System::Drawing::Point(43, 212);
	this->label8->Name = L"label8";
	this->label8->Size = System::Drawing::Size(143, 17);
	this->label8->TabIndex = 5;
	this->label8->Text = L"Макс. частота (GGz):";
	// 
	// label7
	// 
	this->label7->AutoSize = true;
	this->label7->Font = (gcnew System::Drawing::Font(L"Times New Roman", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->label7->Location = System::Drawing::Point(43, 169);
	this->label7->Name = L"label7";
	this->label7->Size = System::Drawing::Size(189, 17);
	this->label7->TabIndex = 4;
	this->label7->Text = L"Архитектура/ширина адреса:";
	// 
	// label6
	// 
	this->label6->AutoSize = true;
	this->label6->Font = (gcnew System::Drawing::Font(L"Times New Roman", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->label6->Location = System::Drawing::Point(43, 125);
	this->label6->Name = L"label6";
	this->label6->Size = System::Drawing::Size(154, 17);
	this->label6->TabIndex = 3;
	this->label6->Text = L"Семейство процессора:";
	// 
	// label5
	// 
	this->label5->AutoSize = true;
	this->label5->Font = (gcnew System::Drawing::Font(L"Times New Roman", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->label5->Location = System::Drawing::Point(43, 84);
	this->label5->Name = L"label5";
	this->label5->Size = System::Drawing::Size(106, 17);
	this->label5->TabIndex = 2;
	this->label5->Text = L"Производитель:";
	// 
	// CPU_NAME
	// 
	this->CPU_NAME->AutoSize = true;
	this->CPU_NAME->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->CPU_NAME->Location = System::Drawing::Point(41, 18);
	this->CPU_NAME->Name = L"CPU_NAME";
	this->CPU_NAME->Size = System::Drawing::Size(129, 25);
	this->CPU_NAME->TabIndex = 1;
	this->CPU_NAME->Text = L"CPU_NAME";
	// 
	// label1
	// 
	this->label1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
	this->label1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"label1.Image")));
	this->label1->Location = System::Drawing::Point(735, 3);
	this->label1->Name = L"label1";
	this->label1->Size = System::Drawing::Size(114, 113);
	this->label1->TabIndex = 0;
	// 
	// GPU
	// 
	this->GPU->Controls->Add(this->MONITOR_DISP_TYPE);
	this->GPU->Controls->Add(this->label36);
	this->GPU->Controls->Add(this->MONITOR_TYPE);
	this->GPU->Controls->Add(this->label35);
	this->GPU->Controls->Add(this->MONITOR_MANUFACTURER);
	this->GPU->Controls->Add(this->label34);
	this->GPU->Controls->Add(this->GPU_MEMORY_TYPE);
	this->GPU->Controls->Add(this->GPU_REFRESH_RATE);
	this->GPU->Controls->Add(this->GPU_RESOLUTION);
	this->GPU->Controls->Add(this->GPU_BITS_PER_PIXEL);
	this->GPU->Controls->Add(this->GPU_RAM);
	this->GPU->Controls->Add(this->GPU_ARCHITECTURE);
	this->GPU->Controls->Add(this->GPU_PROC);
	this->GPU->Controls->Add(this->GPU_CHIP);
	this->GPU->Controls->Add(this->label24);
	this->GPU->Controls->Add(this->label22);
	this->GPU->Controls->Add(this->label21);
	this->GPU->Controls->Add(this->label20);
	this->GPU->Controls->Add(this->label19);
	this->GPU->Controls->Add(this->label18);
	this->GPU->Controls->Add(this->label17);
	this->GPU->Controls->Add(this->label16);
	this->GPU->Controls->Add(this->GPU_NAME);
	this->GPU->Controls->Add(this->label2);
	this->GPU->Location = System::Drawing::Point(4, 22);
	this->GPU->Name = L"GPU";
	this->GPU->Padding = System::Windows::Forms::Padding(3);
	this->GPU->Size = System::Drawing::Size(852, 371);
	this->GPU->TabIndex = 1;
	this->GPU->Text = L"Видео контроллер";
	this->GPU->UseVisualStyleBackColor = true;
	// 
	// MONITOR_DISP_TYPE
	// 
	this->MONITOR_DISP_TYPE->AutoSize = true;
	this->MONITOR_DISP_TYPE->Font = (gcnew System::Drawing::Font(L"Times New Roman", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->MONITOR_DISP_TYPE->Location = System::Drawing::Point(136, 329);
	this->MONITOR_DISP_TYPE->Name = L"MONITOR_DISP_TYPE";
	this->MONITOR_DISP_TYPE->Size = System::Drawing::Size(56, 17);
	this->MONITOR_DISP_TYPE->TabIndex = 29;
	this->MONITOR_DISP_TYPE->Text = L"Чипсет:";
	// 
	// label36
	// 
	this->label36->AutoSize = true;
	this->label36->Font = (gcnew System::Drawing::Font(L"Times New Roman", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->label36->Location = System::Drawing::Point(42, 329);
	this->label36->Name = L"label36";
	this->label36->Size = System::Drawing::Size(88, 17);
	this->label36->TabIndex = 28;
	this->label36->Text = L"Тип дисплея:";
	// 
	// MONITOR_TYPE
	// 
	this->MONITOR_TYPE->AutoSize = true;
	this->MONITOR_TYPE->Font = (gcnew System::Drawing::Font(L"Times New Roman", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->MONITOR_TYPE->Location = System::Drawing::Point(145, 291);
	this->MONITOR_TYPE->Name = L"MONITOR_TYPE";
	this->MONITOR_TYPE->Size = System::Drawing::Size(56, 17);
	this->MONITOR_TYPE->TabIndex = 27;
	this->MONITOR_TYPE->Text = L"Чипсет:";
	// 
	// label35
	// 
	this->label35->AutoSize = true;
	this->label35->Font = (gcnew System::Drawing::Font(L"Times New Roman", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->label35->Location = System::Drawing::Point(42, 291);
	this->label35->Name = L"label35";
	this->label35->Size = System::Drawing::Size(97, 17);
	this->label35->TabIndex = 26;
	this->label35->Text = L"Тип монитора:";
	// 
	// MONITOR_MANUFACTURER
	// 
	this->MONITOR_MANUFACTURER->AutoSize = true;
	this->MONITOR_MANUFACTURER->Font = (gcnew System::Drawing::Font(L"Times New Roman", 11.25F, System::Drawing::FontStyle::Regular,
		System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
	this->MONITOR_MANUFACTURER->Location = System::Drawing::Point(217, 255);
	this->MONITOR_MANUFACTURER->Name = L"MONITOR_MANUFACTURER";
	this->MONITOR_MANUFACTURER->Size = System::Drawing::Size(56, 17);
	this->MONITOR_MANUFACTURER->TabIndex = 25;
	this->MONITOR_MANUFACTURER->Text = L"Чипсет:";
	// 
	// label34
	// 
	this->label34->AutoSize = true;
	this->label34->Font = (gcnew System::Drawing::Font(L"Times New Roman", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->label34->Location = System::Drawing::Point(42, 255);
	this->label34->Name = L"label34";
	this->label34->Size = System::Drawing::Size(169, 17);
	this->label34->TabIndex = 24;
	this->label34->Text = L"Производитель монитора:";
	// 
	// GPU_MEMORY_TYPE
	// 
	this->GPU_MEMORY_TYPE->AutoSize = true;
	this->GPU_MEMORY_TYPE->Font = (gcnew System::Drawing::Font(L"Times New Roman", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->GPU_MEMORY_TYPE->Location = System::Drawing::Point(500, 69);
	this->GPU_MEMORY_TYPE->Name = L"GPU_MEMORY_TYPE";
	this->GPU_MEMORY_TYPE->Size = System::Drawing::Size(56, 17);
	this->GPU_MEMORY_TYPE->TabIndex = 19;
	this->GPU_MEMORY_TYPE->Text = L"Чипсет:";
	// 
	// GPU_REFRESH_RATE
	// 
	this->GPU_REFRESH_RATE->AutoSize = true;
	this->GPU_REFRESH_RATE->Font = (gcnew System::Drawing::Font(L"Times New Roman", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->GPU_REFRESH_RATE->Location = System::Drawing::Point(519, 107);
	this->GPU_REFRESH_RATE->Name = L"GPU_REFRESH_RATE";
	this->GPU_REFRESH_RATE->Size = System::Drawing::Size(56, 17);
	this->GPU_REFRESH_RATE->TabIndex = 18;
	this->GPU_REFRESH_RATE->Text = L"Чипсет:";
	// 
	// GPU_RESOLUTION
	// 
	this->GPU_RESOLUTION->AutoSize = true;
	this->GPU_RESOLUTION->Font = (gcnew System::Drawing::Font(L"Times New Roman", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->GPU_RESOLUTION->Location = System::Drawing::Point(512, 182);
	this->GPU_RESOLUTION->Name = L"GPU_RESOLUTION";
	this->GPU_RESOLUTION->Size = System::Drawing::Size(56, 17);
	this->GPU_RESOLUTION->TabIndex = 17;
	this->GPU_RESOLUTION->Text = L"Чипсет:";
	// 
	// GPU_BITS_PER_PIXEL
	// 
	this->GPU_BITS_PER_PIXEL->AutoSize = true;
	this->GPU_BITS_PER_PIXEL->Font = (gcnew System::Drawing::Font(L"Times New Roman", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->GPU_BITS_PER_PIXEL->Location = System::Drawing::Point(209, 218);
	this->GPU_BITS_PER_PIXEL->Name = L"GPU_BITS_PER_PIXEL";
	this->GPU_BITS_PER_PIXEL->Size = System::Drawing::Size(56, 17);
	this->GPU_BITS_PER_PIXEL->TabIndex = 16;
	this->GPU_BITS_PER_PIXEL->Text = L"Чипсет:";
	// 
	// GPU_RAM
	// 
	this->GPU_RAM->AutoSize = true;
	this->GPU_RAM->Font = (gcnew System::Drawing::Font(L"Times New Roman", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->GPU_RAM->Location = System::Drawing::Point(124, 182);
	this->GPU_RAM->Name = L"GPU_RAM";
	this->GPU_RAM->Size = System::Drawing::Size(56, 17);
	this->GPU_RAM->TabIndex = 15;
	this->GPU_RAM->Text = L"Чипсет:";
	// 
	// GPU_ARCHITECTURE
	// 
	this->GPU_ARCHITECTURE->AutoSize = true;
	this->GPU_ARCHITECTURE->Font = (gcnew System::Drawing::Font(L"Times New Roman", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->GPU_ARCHITECTURE->Location = System::Drawing::Point(177, 107);
	this->GPU_ARCHITECTURE->Name = L"GPU_ARCHITECTURE";
	this->GPU_ARCHITECTURE->Size = System::Drawing::Size(56, 17);
	this->GPU_ARCHITECTURE->TabIndex = 14;
	this->GPU_ARCHITECTURE->Text = L"Чипсет:";
	// 
	// GPU_PROC
	// 
	this->GPU_PROC->AutoSize = true;
	this->GPU_PROC->Font = (gcnew System::Drawing::Font(L"Times New Roman", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->GPU_PROC->Location = System::Drawing::Point(166, 144);
	this->GPU_PROC->Name = L"GPU_PROC";
	this->GPU_PROC->Size = System::Drawing::Size(56, 17);
	this->GPU_PROC->TabIndex = 13;
	this->GPU_PROC->Text = L"Чипсет:";
	// 
	// GPU_CHIP
	// 
	this->GPU_CHIP->AutoSize = true;
	this->GPU_CHIP->Font = (gcnew System::Drawing::Font(L"Times New Roman", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->GPU_CHIP->Location = System::Drawing::Point(104, 69);
	this->GPU_CHIP->Name = L"GPU_CHIP";
	this->GPU_CHIP->Size = System::Drawing::Size(0, 17);
	this->GPU_CHIP->TabIndex = 12;
	// 
	// label24
	// 
	this->label24->AutoSize = true;
	this->label24->Font = (gcnew System::Drawing::Font(L"Times New Roman", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->label24->Location = System::Drawing::Point(375, 69);
	this->label24->Name = L"label24";
	this->label24->Size = System::Drawing::Size(119, 17);
	this->label24->TabIndex = 11;
	this->label24->Text = L"Тип видеопамяти:";
	// 
	// label22
	// 
	this->label22->AutoSize = true;
	this->label22->Font = (gcnew System::Drawing::Font(L"Times New Roman", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->label22->Location = System::Drawing::Point(42, 182);
	this->label22->Name = L"label22";
	this->label22->Size = System::Drawing::Size(76, 17);
	this->label22->TabIndex = 9;
	this->label22->Text = L"RAM (Гб):";
	// 
	// label21
	// 
	this->label21->AutoSize = true;
	this->label21->Font = (gcnew System::Drawing::Font(L"Times New Roman", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->label21->Location = System::Drawing::Point(42, 218);
	this->label21->Name = L"label21";
	this->label21->Size = System::Drawing::Size(161, 17);
	this->label21->TabIndex = 8;
	this->label21->Text = L"Кол-во бит на 1 пиксель:";
	// 
	// label20
	// 
	this->label20->AutoSize = true;
	this->label20->Font = (gcnew System::Drawing::Font(L"Times New Roman", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->label20->Location = System::Drawing::Point(375, 182);
	this->label20->Name = L"label20";
	this->label20->Size = System::Drawing::Size(131, 17);
	this->label20->TabIndex = 7;
	this->label20->Text = L"Разрешение экрана:";
	// 
	// label19
	// 
	this->label19->AutoSize = true;
	this->label19->Font = (gcnew System::Drawing::Font(L"Times New Roman", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->label19->Location = System::Drawing::Point(375, 107);
	this->label19->Name = L"label19";
	this->label19->Size = System::Drawing::Size(138, 17);
	this->label19->TabIndex = 6;
	this->label19->Text = L"Частота обновления:";
	// 
	// label18
	// 
	this->label18->AutoSize = true;
	this->label18->Font = (gcnew System::Drawing::Font(L"Times New Roman", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->label18->Location = System::Drawing::Point(42, 107);
	this->label18->Name = L"label18";
	this->label18->Size = System::Drawing::Size(136, 17);
	this->label18->TabIndex = 5;
	this->label18->Text = L"Видео-архитектура: ";
	// 
	// label17
	// 
	this->label17->AutoSize = true;
	this->label17->Font = (gcnew System::Drawing::Font(L"Times New Roman", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->label17->Location = System::Drawing::Point(42, 144);
	this->label17->Name = L"label17";
	this->label17->Size = System::Drawing::Size(118, 17);
	this->label17->TabIndex = 4;
	this->label17->Text = L"Видео-процессор:";
	// 
	// label16
	// 
	this->label16->AutoSize = true;
	this->label16->Font = (gcnew System::Drawing::Font(L"Times New Roman", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->label16->Location = System::Drawing::Point(42, 69);
	this->label16->Name = L"label16";
	this->label16->Size = System::Drawing::Size(56, 17);
	this->label16->TabIndex = 3;
	this->label16->Text = L"Чипсет:";
	// 
	// GPU_NAME
	// 
	this->GPU_NAME->AutoSize = true;
	this->GPU_NAME->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->GPU_NAME->Location = System::Drawing::Point(40, 18);
	this->GPU_NAME->Name = L"GPU_NAME";
	this->GPU_NAME->Size = System::Drawing::Size(130, 25);
	this->GPU_NAME->TabIndex = 2;
	this->GPU_NAME->Text = L"GPU_NAME";
	// 
	// label2
	// 
	this->label2->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
	this->label2->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"label2.Image")));
	this->label2->Location = System::Drawing::Point(732, 3);
	this->label2->Name = L"label2";
	this->label2->Size = System::Drawing::Size(114, 113);
	this->label2->TabIndex = 1;
	// 
	// LDISK
	// 
	this->LDISK->Controls->Add(this->LOGICAL_DISKS);
	this->LDISK->Location = System::Drawing::Point(4, 22);
	this->LDISK->Name = L"LDISK";
	this->LDISK->Size = System::Drawing::Size(852, 371);
	this->LDISK->TabIndex = 2;
	this->LDISK->Text = L"Логические диски";
	this->LDISK->UseVisualStyleBackColor = true;
	// 
	// LOGICAL_DISKS
	// 
	this->LOGICAL_DISKS->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(6) {
		this->columnHeader1,
			this->columnHeader2, this->columnHeader3, this->columnHeader4, this->columnHeader5, this->columnHeader6
	});
	this->LOGICAL_DISKS->GridLines = true;
	this->LOGICAL_DISKS->Location = System::Drawing::Point(3, 3);
	this->LOGICAL_DISKS->Name = L"LOGICAL_DISKS";
	this->LOGICAL_DISKS->Size = System::Drawing::Size(846, 365);
	this->LOGICAL_DISKS->TabIndex = 0;
	this->LOGICAL_DISKS->UseCompatibleStateImageBehavior = false;
	this->LOGICAL_DISKS->View = System::Windows::Forms::View::Details;
	// 
	// columnHeader1
	// 
	this->columnHeader1->Text = L"Имя диска";
	this->columnHeader1->Width = 101;
	// 
	// columnHeader2
	// 
	this->columnHeader2->Text = L"Файловая система";
	this->columnHeader2->Width = 134;
	// 
	// columnHeader3
	// 
	this->columnHeader3->Text = L"Тип диска";
	this->columnHeader3->Width = 119;
	// 
	// columnHeader4
	// 
	this->columnHeader4->Text = L"Вся память (Гб)";
	this->columnHeader4->Width = 172;
	// 
	// columnHeader5
	// 
	this->columnHeader5->Text = L"Свободная память (Гб)";
	this->columnHeader5->Width = 168;
	// 
	// columnHeader6
	// 
	this->columnHeader6->Text = L"Макс. длина компонента";
	this->columnHeader6->Width = 148;
	// 
	// PDISK
	// 
	this->PDISK->Controls->Add(this->PD_LIST);
	this->PDISK->Location = System::Drawing::Point(4, 22);
	this->PDISK->Name = L"PDISK";
	this->PDISK->Size = System::Drawing::Size(852, 371);
	this->PDISK->TabIndex = 3;
	this->PDISK->Text = L"Физические диски";
	this->PDISK->UseVisualStyleBackColor = true;
	// 
	// PD_LIST
	// 
	this->PD_LIST->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(9) {
		this->columnHeader7, this->columnHeader8,
			this->columnHeader9, this->columnHeader11, this->columnHeader12, this->columnHeader13, this->columnHeader14, this->columnHeader15,
			this->columnHeader25
	});
	this->PD_LIST->FullRowSelect = true;
	this->PD_LIST->GridLines = true;
	this->PD_LIST->Location = System::Drawing::Point(3, 3);
	this->PD_LIST->Name = L"PD_LIST";
	this->PD_LIST->Size = System::Drawing::Size(846, 365);
	this->PD_LIST->TabIndex = 0;
	this->PD_LIST->UseCompatibleStateImageBehavior = false;
	this->PD_LIST->View = System::Windows::Forms::View::Details;
	// 
	// columnHeader7
	// 
	this->columnHeader7->Text = L"Модель";
	this->columnHeader7->Width = 128;
	// 
	// columnHeader8
	// 
	this->columnHeader8->Text = L"Описание";
	this->columnHeader8->Width = 152;
	// 
	// columnHeader9
	// 
	this->columnHeader9->Text = L"Общий объём памяти (Гб)";
	this->columnHeader9->Width = 149;
	// 
	// columnHeader11
	// 
	this->columnHeader11->Text = L"Тип интерфейса";
	this->columnHeader11->Width = 114;
	// 
	// columnHeader12
	// 
	this->columnHeader12->Text = L"ID устройства";
	this->columnHeader12->Width = 85;
	// 
	// columnHeader13
	// 
	this->columnHeader13->Text = L"Кол-во байт на сектор";
	// 
	// columnHeader14
	// 
	this->columnHeader14->Text = L"Тип медиа";
	// 
	// columnHeader15
	// 
	this->columnHeader15->Text = L"Серийный номер";
	// 
	// columnHeader25
	// 
	this->columnHeader25->Text = L"Версия для прошивки";
	// 
	// PROCESS
	// 
	this->PROCESS->Controls->Add(this->TOTAL_COUNT_OF_PROCESSES);
	this->PROCESS->Controls->Add(this->label32);
	this->PROCESS->Controls->Add(this->PROCESSES);
	this->PROCESS->Location = System::Drawing::Point(4, 22);
	this->PROCESS->Name = L"PROCESS";
	this->PROCESS->Size = System::Drawing::Size(852, 371);
	this->PROCESS->TabIndex = 4;
	this->PROCESS->Text = L"Процессы";
	this->PROCESS->UseVisualStyleBackColor = true;
	// 
	// TOTAL_COUNT_OF_PROCESSES
	// 
	this->TOTAL_COUNT_OF_PROCESSES->AutoSize = true;
	this->TOTAL_COUNT_OF_PROCESSES->Font = (gcnew System::Drawing::Font(L"Times New Roman", 11.25F, System::Drawing::FontStyle::Regular,
		System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
	this->TOTAL_COUNT_OF_PROCESSES->Location = System::Drawing::Point(124, 336);
	this->TOTAL_COUNT_OF_PROCESSES->Name = L"TOTAL_COUNT_OF_PROCESSES";
	this->TOTAL_COUNT_OF_PROCESSES->Size = System::Drawing::Size(119, 17);
	this->TOTAL_COUNT_OF_PROCESSES->TabIndex = 13;
	this->TOTAL_COUNT_OF_PROCESSES->Text = L"Тип видеопамяти:";
	// 
	// label32
	// 
	this->label32->AutoSize = true;
	this->label32->Font = (gcnew System::Drawing::Font(L"Times New Roman", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->label32->Location = System::Drawing::Point(3, 336);
	this->label32->Name = L"label32";
	this->label32->Size = System::Drawing::Size(115, 17);
	this->label32->TabIndex = 12;
	this->label32->Text = L"Всего процессов:";
	// 
	// PROCESSES
	// 
	this->PROCESSES->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(7) {
		this->PROCESS_NAME, this->PROCESS_ID,
			this->PARENT_PROCESS_ID, this->PROCESS_WORKING_SIZE, this->PROCESS_EXEC_PATH, this->PROCESS_HANDLE_COUNT, this->PROCESS_THREADS_COUNT
	});
	this->PROCESSES->GridLines = true;
	this->PROCESSES->HeaderStyle = System::Windows::Forms::ColumnHeaderStyle::Nonclickable;
	this->PROCESSES->ImeMode = System::Windows::Forms::ImeMode::Off;
	this->PROCESSES->Items->AddRange(gcnew cli::array< System::Windows::Forms::ListViewItem^  >(1) { listViewItem3 });
	this->PROCESSES->Location = System::Drawing::Point(3, 3);
	this->PROCESSES->MultiSelect = false;
	this->PROCESSES->Name = L"PROCESSES";
	this->PROCESSES->Size = System::Drawing::Size(846, 330);
	this->PROCESSES->TabIndex = 0;
	this->PROCESSES->UseCompatibleStateImageBehavior = false;
	this->PROCESSES->View = System::Windows::Forms::View::Details;
	// 
	// PROCESS_NAME
	// 
	this->PROCESS_NAME->Text = L"Имя процесса";
	this->PROCESS_NAME->Width = 131;
	// 
	// PROCESS_ID
	// 
	this->PROCESS_ID->Text = L"ID процесса";
	this->PROCESS_ID->Width = 83;
	// 
	// PARENT_PROCESS_ID
	// 
	this->PARENT_PROCESS_ID->Text = L"ID родительского процесса";
	this->PARENT_PROCESS_ID->Width = 154;
	// 
	// PROCESS_WORKING_SIZE
	// 
	this->PROCESS_WORKING_SIZE->Text = L"Занимаемая память";
	this->PROCESS_WORKING_SIZE->Width = 121;
	// 
	// PROCESS_EXEC_PATH
	// 
	this->PROCESS_EXEC_PATH->Text = L"Путь к .exe файлу";
	this->PROCESS_EXEC_PATH->Width = 139;
	// 
	// PROCESS_HANDLE_COUNT
	// 
	this->PROCESS_HANDLE_COUNT->Text = L"Кол-во дескрипторов";
	this->PROCESS_HANDLE_COUNT->Width = 120;
	// 
	// PROCESS_THREADS_COUNT
	// 
	this->PROCESS_THREADS_COUNT->Text = L"Кол-во потоков";
	this->PROCESS_THREADS_COUNT->Width = 92;
	// 
	// OS
	// 
	this->OS->Controls->Add(this->OS_BUILD_NUMBER);
	this->OS->Controls->Add(this->label23);
	this->OS->Controls->Add(this->OS_COMPUTER_NAME);
	this->OS->Controls->Add(this->OS_VERSION);
	this->OS->Controls->Add(this->OS_SERIAL_NUMBER);
	this->OS->Controls->Add(this->OS_DIRECTORY);
	this->OS->Controls->Add(this->OS_DEVICE);
	this->OS->Controls->Add(this->OS_PROCESS_COUNT);
	this->OS->Controls->Add(this->OS_MANUFACTURER);
	this->OS->Controls->Add(this->OS_SKU);
	this->OS->Controls->Add(this->compname);
	this->OS->Controls->Add(this->version);
	this->OS->Controls->Add(this->sernum);
	this->OS->Controls->Add(this->directory);
	this->OS->Controls->Add(this->device);
	this->OS->Controls->Add(this->processe);
	this->OS->Controls->Add(this->manufacturer);
	this->OS->Controls->Add(this->sku);
	this->OS->Controls->Add(this->OS_ARCHITECTURE);
	this->OS->Controls->Add(this->label25);
	this->OS->Controls->Add(this->OS_NAME);
	this->OS->Controls->Add(this->label3);
	this->OS->Location = System::Drawing::Point(4, 22);
	this->OS->Name = L"OS";
	this->OS->Size = System::Drawing::Size(852, 371);
	this->OS->TabIndex = 5;
	this->OS->Text = L"ОС";
	this->OS->UseVisualStyleBackColor = true;
	// 
	// OS_BUILD_NUMBER
	// 
	this->OS_BUILD_NUMBER->AutoSize = true;
	this->OS_BUILD_NUMBER->Font = (gcnew System::Drawing::Font(L"Times New Roman", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->OS_BUILD_NUMBER->Location = System::Drawing::Point(504, 171);
	this->OS_BUILD_NUMBER->Name = L"OS_BUILD_NUMBER";
	this->OS_BUILD_NUMBER->Size = System::Drawing::Size(119, 17);
	this->OS_BUILD_NUMBER->TabIndex = 23;
	this->OS_BUILD_NUMBER->Text = L"Системная папка:";
	// 
	// label23
	// 
	this->label23->AutoSize = true;
	this->label23->Font = (gcnew System::Drawing::Font(L"Times New Roman", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->label23->Location = System::Drawing::Point(398, 171);
	this->label23->Name = L"label23";
	this->label23->Size = System::Drawing::Size(100, 17);
	this->label23->TabIndex = 22;
	this->label23->Text = L"Номер сборки:";
	// 
	// OS_COMPUTER_NAME
	// 
	this->OS_COMPUTER_NAME->AutoSize = true;
	this->OS_COMPUTER_NAME->Font = (gcnew System::Drawing::Font(L"Times New Roman", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->OS_COMPUTER_NAME->Location = System::Drawing::Point(167, 283);
	this->OS_COMPUTER_NAME->Name = L"OS_COMPUTER_NAME";
	this->OS_COMPUTER_NAME->Size = System::Drawing::Size(87, 17);
	this->OS_COMPUTER_NAME->TabIndex = 21;
	this->OS_COMPUTER_NAME->Text = L"Тип издания:";
	// 
	// OS_VERSION
	// 
	this->OS_VERSION->AutoSize = true;
	this->OS_VERSION->Font = (gcnew System::Drawing::Font(L"Times New Roman", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->OS_VERSION->Location = System::Drawing::Point(485, 133);
	this->OS_VERSION->Name = L"OS_VERSION";
	this->OS_VERSION->Size = System::Drawing::Size(87, 17);
	this->OS_VERSION->TabIndex = 20;
	this->OS_VERSION->Text = L"Тип издания:";
	// 
	// OS_SERIAL_NUMBER
	// 
	this->OS_SERIAL_NUMBER->AutoSize = true;
	this->OS_SERIAL_NUMBER->Font = (gcnew System::Drawing::Font(L"Times New Roman", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->OS_SERIAL_NUMBER->Location = System::Drawing::Point(519, 96);
	this->OS_SERIAL_NUMBER->Name = L"OS_SERIAL_NUMBER";
	this->OS_SERIAL_NUMBER->Size = System::Drawing::Size(87, 17);
	this->OS_SERIAL_NUMBER->TabIndex = 19;
	this->OS_SERIAL_NUMBER->Text = L"Тип издания:";
	// 
	// OS_DIRECTORY
	// 
	this->OS_DIRECTORY->AutoSize = true;
	this->OS_DIRECTORY->Font = (gcnew System::Drawing::Font(L"Times New Roman", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->OS_DIRECTORY->Location = System::Drawing::Point(167, 246);
	this->OS_DIRECTORY->Name = L"OS_DIRECTORY";
	this->OS_DIRECTORY->Size = System::Drawing::Size(87, 17);
	this->OS_DIRECTORY->TabIndex = 18;
	this->OS_DIRECTORY->Text = L"Тип издания:";
	// 
	// OS_DEVICE
	// 
	this->OS_DEVICE->AutoSize = true;
	this->OS_DEVICE->Font = (gcnew System::Drawing::Font(L"Times New Roman", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->OS_DEVICE->Location = System::Drawing::Point(292, 209);
	this->OS_DEVICE->Name = L"OS_DEVICE";
	this->OS_DEVICE->Size = System::Drawing::Size(87, 17);
	this->OS_DEVICE->TabIndex = 17;
	this->OS_DEVICE->Text = L"Тип издания:";
	// 
	// OS_PROCESS_COUNT
	// 
	this->OS_PROCESS_COUNT->AutoSize = true;
	this->OS_PROCESS_COUNT->Font = (gcnew System::Drawing::Font(L"Times New Roman", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->OS_PROCESS_COUNT->Location = System::Drawing::Point(266, 171);
	this->OS_PROCESS_COUNT->Name = L"OS_PROCESS_COUNT";
	this->OS_PROCESS_COUNT->Size = System::Drawing::Size(35, 17);
	this->OS_PROCESS_COUNT->TabIndex = 16;
	this->OS_PROCESS_COUNT->Text = L"Тип ";
	// 
	// OS_MANUFACTURER
	// 
	this->OS_MANUFACTURER->AutoSize = true;
	this->OS_MANUFACTURER->Font = (gcnew System::Drawing::Font(L"Times New Roman", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->OS_MANUFACTURER->Location = System::Drawing::Point(154, 133);
	this->OS_MANUFACTURER->Name = L"OS_MANUFACTURER";
	this->OS_MANUFACTURER->Size = System::Drawing::Size(87, 17);
	this->OS_MANUFACTURER->TabIndex = 15;
	this->OS_MANUFACTURER->Text = L"Тип издания:";
	// 
	// OS_SKU
	// 
	this->OS_SKU->AutoSize = true;
	this->OS_SKU->Font = (gcnew System::Drawing::Font(L"Times New Roman", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->OS_SKU->Location = System::Drawing::Point(135, 96);
	this->OS_SKU->Name = L"OS_SKU";
	this->OS_SKU->Size = System::Drawing::Size(87, 17);
	this->OS_SKU->TabIndex = 14;
	this->OS_SKU->Text = L"Тип издания:";
	// 
	// compname
	// 
	this->compname->AutoSize = true;
	this->compname->Font = (gcnew System::Drawing::Font(L"Times New Roman", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->compname->Location = System::Drawing::Point(42, 283);
	this->compname->Name = L"compname";
	this->compname->Size = System::Drawing::Size(119, 17);
	this->compname->TabIndex = 13;
	this->compname->Text = L"Имя компьютера:";
	// 
	// version
	// 
	this->version->AutoSize = true;
	this->version->Font = (gcnew System::Drawing::Font(L"Times New Roman", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->version->Location = System::Drawing::Point(398, 133);
	this->version->Name = L"version";
	this->version->Size = System::Drawing::Size(81, 17);
	this->version->TabIndex = 12;
	this->version->Text = L"Версия ОС:";
	// 
	// sernum
	// 
	this->sernum->AutoSize = true;
	this->sernum->Font = (gcnew System::Drawing::Font(L"Times New Roman", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->sernum->Location = System::Drawing::Point(398, 96);
	this->sernum->Name = L"sernum";
	this->sernum->Size = System::Drawing::Size(115, 17);
	this->sernum->TabIndex = 11;
	this->sernum->Text = L"Серийный номер:";
	// 
	// directory
	// 
	this->directory->AutoSize = true;
	this->directory->Font = (gcnew System::Drawing::Font(L"Times New Roman", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->directory->Location = System::Drawing::Point(42, 246);
	this->directory->Name = L"directory";
	this->directory->Size = System::Drawing::Size(119, 17);
	this->directory->TabIndex = 10;
	this->directory->Text = L"Системная папка:";
	// 
	// device
	// 
	this->device->AutoSize = true;
	this->device->Font = (gcnew System::Drawing::Font(L"Times New Roman", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->device->Location = System::Drawing::Point(42, 209);
	this->device->Name = L"device";
	this->device->Size = System::Drawing::Size(244, 17);
	this->device->TabIndex = 9;
	this->device->Text = L"Устройство, на котором хранится ОС:";
	// 
	// processe
	// 
	this->processe->AutoSize = true;
	this->processe->Font = (gcnew System::Drawing::Font(L"Times New Roman", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->processe->Location = System::Drawing::Point(42, 171);
	this->processe->Name = L"processe";
	this->processe->Size = System::Drawing::Size(218, 17);
	this->processe->TabIndex = 8;
	this->processe->Text = L"Количество процессов в системе:";
	// 
	// manufacturer
	// 
	this->manufacturer->AutoSize = true;
	this->manufacturer->Font = (gcnew System::Drawing::Font(L"Times New Roman", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->manufacturer->Location = System::Drawing::Point(42, 133);
	this->manufacturer->Name = L"manufacturer";
	this->manufacturer->Size = System::Drawing::Size(106, 17);
	this->manufacturer->TabIndex = 7;
	this->manufacturer->Text = L"Производитель:";
	// 
	// sku
	// 
	this->sku->AutoSize = true;
	this->sku->Font = (gcnew System::Drawing::Font(L"Times New Roman", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->sku->Location = System::Drawing::Point(42, 96);
	this->sku->Name = L"sku";
	this->sku->Size = System::Drawing::Size(87, 17);
	this->sku->TabIndex = 6;
	this->sku->Text = L"Тип издания:";
	// 
	// OS_ARCHITECTURE
	// 
	this->OS_ARCHITECTURE->AutoSize = true;
	this->OS_ARCHITECTURE->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular,
		System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
	this->OS_ARCHITECTURE->Location = System::Drawing::Point(40, 53);
	this->OS_ARCHITECTURE->Name = L"OS_ARCHITECTURE";
	this->OS_ARCHITECTURE->Size = System::Drawing::Size(175, 25);
	this->OS_ARCHITECTURE->TabIndex = 5;
	this->OS_ARCHITECTURE->Text = L"ARCHITECTURE";
	// 
	// label25
	// 
	this->label25->AutoSize = true;
	this->label25->Font = (gcnew System::Drawing::Font(L"Times New Roman", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->label25->Location = System::Drawing::Point(42, 96);
	this->label25->Name = L"label25";
	this->label25->Size = System::Drawing::Size(0, 17);
	this->label25->TabIndex = 4;
	// 
	// OS_NAME
	// 
	this->OS_NAME->AutoSize = true;
	this->OS_NAME->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->OS_NAME->Location = System::Drawing::Point(40, 18);
	this->OS_NAME->Name = L"OS_NAME";
	this->OS_NAME->Size = System::Drawing::Size(115, 25);
	this->OS_NAME->TabIndex = 3;
	this->OS_NAME->Text = L"OS_NAME";
	// 
	// label3
	// 
	this->label3->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
	this->label3->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"label3.Image")));
	this->label3->Location = System::Drawing::Point(735, 0);
	this->label3->Name = L"label3";
	this->label3->Size = System::Drawing::Size(114, 113);
	this->label3->TabIndex = 1;
	// 
	// MOTHERBOARD_AND_RAM
	// 
	this->MOTHERBOARD_AND_RAM->Controls->Add(this->AVAIL_VIRTUAL_MEM);
	this->MOTHERBOARD_AND_RAM->Controls->Add(this->label30);
	this->MOTHERBOARD_AND_RAM->Controls->Add(this->label31);
	this->MOTHERBOARD_AND_RAM->Controls->Add(this->TOTAL_VIRTUAL_MEM);
	this->MOTHERBOARD_AND_RAM->Controls->Add(this->label29);
	this->MOTHERBOARD_AND_RAM->Controls->Add(this->AVAIL_PHYS_MEM);
	this->MOTHERBOARD_AND_RAM->Controls->Add(this->label28);
	this->MOTHERBOARD_AND_RAM->Controls->Add(this->TOTAL_PHYS_MEM);
	this->MOTHERBOARD_AND_RAM->Controls->Add(this->mem);
	this->MOTHERBOARD_AND_RAM->Controls->Add(this->BASEBOARD_SERIALNUMBER);
	this->MOTHERBOARD_AND_RAM->Controls->Add(this->label27);
	this->MOTHERBOARD_AND_RAM->Controls->Add(this->BASEBOARD_DESCRIPTION);
	this->MOTHERBOARD_AND_RAM->Controls->Add(this->label26);
	this->MOTHERBOARD_AND_RAM->Controls->Add(this->label4);
	this->MOTHERBOARD_AND_RAM->Location = System::Drawing::Point(4, 22);
	this->MOTHERBOARD_AND_RAM->Name = L"MOTHERBOARD_AND_RAM";
	this->MOTHERBOARD_AND_RAM->Size = System::Drawing::Size(852, 371);
	this->MOTHERBOARD_AND_RAM->TabIndex = 6;
	this->MOTHERBOARD_AND_RAM->Text = L"Материнская плата и ОЗУ";
	this->MOTHERBOARD_AND_RAM->UseVisualStyleBackColor = true;
	// 
	// AVAIL_VIRTUAL_MEM
	// 
	this->AVAIL_VIRTUAL_MEM->AutoSize = true;
	this->AVAIL_VIRTUAL_MEM->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular,
		System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
	this->AVAIL_VIRTUAL_MEM->Location = System::Drawing::Point(427, 233);
	this->AVAIL_VIRTUAL_MEM->Name = L"AVAIL_VIRTUAL_MEM";
	this->AVAIL_VIRTUAL_MEM->Size = System::Drawing::Size(82, 25);
	this->AVAIL_VIRTUAL_MEM->TabIndex = 14;
	this->AVAIL_VIRTUAL_MEM->Text = L"label32";
	// 
	// label30
	// 
	this->label30->AutoSize = true;
	this->label30->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->label30->Location = System::Drawing::Point(41, 233);
	this->label30->Name = L"label30";
	this->label30->Size = System::Drawing::Size(380, 25);
	this->label30->TabIndex = 13;
	this->label30->Text = L"Свободная виртуальная память (Гб):";
	// 
	// label31
	// 
	this->label31->AutoSize = true;
	this->label31->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->label31->Location = System::Drawing::Point(41, 233);
	this->label31->Name = L"label31";
	this->label31->Size = System::Drawing::Size(0, 25);
	this->label31->TabIndex = 12;
	// 
	// TOTAL_VIRTUAL_MEM
	// 
	this->TOTAL_VIRTUAL_MEM->AutoSize = true;
	this->TOTAL_VIRTUAL_MEM->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular,
		System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
	this->TOTAL_VIRTUAL_MEM->Location = System::Drawing::Point(354, 190);
	this->TOTAL_VIRTUAL_MEM->Name = L"TOTAL_VIRTUAL_MEM";
	this->TOTAL_VIRTUAL_MEM->Size = System::Drawing::Size(82, 25);
	this->TOTAL_VIRTUAL_MEM->TabIndex = 11;
	this->TOTAL_VIRTUAL_MEM->Text = L"label30";
	// 
	// label29
	// 
	this->label29->AutoSize = true;
	this->label29->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->label29->Location = System::Drawing::Point(41, 190);
	this->label29->Name = L"label29";
	this->label29->Size = System::Drawing::Size(307, 25);
	this->label29->TabIndex = 10;
	this->label29->Text = L"Вся виртуальная память (Гб):";
	// 
	// AVAIL_PHYS_MEM
	// 
	this->AVAIL_PHYS_MEM->AutoSize = true;
	this->AVAIL_PHYS_MEM->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->AVAIL_PHYS_MEM->Location = System::Drawing::Point(264, 148);
	this->AVAIL_PHYS_MEM->Name = L"AVAIL_PHYS_MEM";
	this->AVAIL_PHYS_MEM->Size = System::Drawing::Size(82, 25);
	this->AVAIL_PHYS_MEM->TabIndex = 9;
	this->AVAIL_PHYS_MEM->Text = L"label29";
	// 
	// label28
	// 
	this->label28->AutoSize = true;
	this->label28->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->label28->Location = System::Drawing::Point(41, 148);
	this->label28->Name = L"label28";
	this->label28->Size = System::Drawing::Size(217, 25);
	this->label28->TabIndex = 8;
	this->label28->Text = L"Доступная ОЗУ (Гб):";
	// 
	// TOTAL_PHYS_MEM
	// 
	this->TOTAL_PHYS_MEM->AutoSize = true;
	this->TOTAL_PHYS_MEM->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->TOTAL_PHYS_MEM->Location = System::Drawing::Point(193, 105);
	this->TOTAL_PHYS_MEM->Name = L"TOTAL_PHYS_MEM";
	this->TOTAL_PHYS_MEM->Size = System::Drawing::Size(82, 25);
	this->TOTAL_PHYS_MEM->TabIndex = 7;
	this->TOTAL_PHYS_MEM->Text = L"label28";
	// 
	// mem
	// 
	this->mem->AutoSize = true;
	this->mem->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->mem->Location = System::Drawing::Point(41, 105);
	this->mem->Name = L"mem";
	this->mem->Size = System::Drawing::Size(146, 25);
	this->mem->TabIndex = 6;
	this->mem->Text = L"Вся ОЗУ (Гб):";
	// 
	// BASEBOARD_SERIALNUMBER
	// 
	this->BASEBOARD_SERIALNUMBER->AutoSize = true;
	this->BASEBOARD_SERIALNUMBER->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular,
		System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
	this->BASEBOARD_SERIALNUMBER->Location = System::Drawing::Point(236, 60);
	this->BASEBOARD_SERIALNUMBER->Name = L"BASEBOARD_SERIALNUMBER";
	this->BASEBOARD_SERIALNUMBER->Size = System::Drawing::Size(82, 25);
	this->BASEBOARD_SERIALNUMBER->TabIndex = 5;
	this->BASEBOARD_SERIALNUMBER->Text = L"label28";
	// 
	// label27
	// 
	this->label27->AutoSize = true;
	this->label27->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->label27->Location = System::Drawing::Point(41, 60);
	this->label27->Name = L"label27";
	this->label27->Size = System::Drawing::Size(189, 25);
	this->label27->TabIndex = 4;
	this->label27->Text = L"Серийный номер:";
	// 
	// BASEBOARD_DESCRIPTION
	// 
	this->BASEBOARD_DESCRIPTION->AutoSize = true;
	this->BASEBOARD_DESCRIPTION->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular,
		System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
	this->BASEBOARD_DESCRIPTION->Location = System::Drawing::Point(41, 18);
	this->BASEBOARD_DESCRIPTION->Name = L"BASEBOARD_DESCRIPTION";
	this->BASEBOARD_DESCRIPTION->Size = System::Drawing::Size(142, 25);
	this->BASEBOARD_DESCRIPTION->TabIndex = 3;
	this->BASEBOARD_DESCRIPTION->Text = L"BASEBOARD";
	// 
	// label26
	// 
	this->label26->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
	this->label26->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"label26.Image")));
	this->label26->Location = System::Drawing::Point(735, 113);
	this->label26->Name = L"label26";
	this->label26->Size = System::Drawing::Size(114, 113);
	this->label26->TabIndex = 2;
	// 
	// label4
	// 
	this->label4->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
	this->label4->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"label4.Image")));
	this->label4->Location = System::Drawing::Point(735, 0);
	this->label4->Name = L"label4";
	this->label4->Size = System::Drawing::Size(114, 113);
	this->label4->TabIndex = 1;
	// 
	// NETWORK
	// 
	this->NETWORK->Controls->Add(this->NET_LIST);
	this->NETWORK->Location = System::Drawing::Point(4, 22);
	this->NETWORK->Name = L"NETWORK";
	this->NETWORK->Size = System::Drawing::Size(852, 371);
	this->NETWORK->TabIndex = 7;
	this->NETWORK->Text = L"Сетевые адаптеры";
	this->NETWORK->UseVisualStyleBackColor = true;
	// 
	// NET_LIST
	// 
	this->NET_LIST->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(9) {
		this->columnHeader16, this->columnHeader17,
			this->columnHeader18, this->columnHeader19, this->columnHeader20, this->columnHeader21, this->columnHeader22, this->columnHeader23,
			this->columnHeader24
	});
	this->NET_LIST->GridLines = true;
	this->NET_LIST->Location = System::Drawing::Point(3, 3);
	this->NET_LIST->MultiSelect = false;
	this->NET_LIST->Name = L"NET_LIST";
	this->NET_LIST->Size = System::Drawing::Size(846, 365);
	this->NET_LIST->TabIndex = 2;
	this->NET_LIST->UseCompatibleStateImageBehavior = false;
	this->NET_LIST->View = System::Windows::Forms::View::Details;
	// 
	// columnHeader16
	// 
	this->columnHeader16->Text = L"Модель";
	this->columnHeader16->Width = 108;
	// 
	// columnHeader17
	// 
	this->columnHeader17->Text = L"Статус";
	this->columnHeader17->Width = 117;
	// 
	// columnHeader18
	// 
	this->columnHeader18->Text = L"NetID";
	this->columnHeader18->Width = 109;
	// 
	// columnHeader19
	// 
	this->columnHeader19->Text = L"Тип устройства";
	this->columnHeader19->Width = 104;
	// 
	// columnHeader20
	// 
	this->columnHeader20->Text = L"ID устройства";
	this->columnHeader20->Width = 89;
	// 
	// columnHeader21
	// 
	this->columnHeader21->Text = L"MACAddress";
	this->columnHeader21->Width = 119;
	// 
	// columnHeader22
	// 
	this->columnHeader22->Text = L"GUID";
	this->columnHeader22->Width = 85;
	// 
	// columnHeader23
	// 
	this->columnHeader23->Text = L"Производитель";
	this->columnHeader23->Width = 95;
	// 
	// columnHeader24
	// 
	this->columnHeader24->Text = L"Скорость соединения (Кбит/с)";
	this->columnHeader24->Width = 133;
	// 
	// BACKGROUND_WORK
	// 
	this->BACKGROUND_WORK->WorkerSupportsCancellation = true;
	this->BACKGROUND_WORK->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &MyForm::BACKGROUND_WORK_DoWork);
	this->BACKGROUND_WORK->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &MyForm::BACKGROUND_WORK_RunWorkerCompleted);
	// 
	// MyForm
	// 
	this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
	this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
	this->ClientSize = System::Drawing::Size(884, 421);
	this->Controls->Add(this->Hardware);
	this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
	this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
	this->MaximizeBox = false;
	this->MinimizeBox = false;
	this->Name = L"MyForm";
	this->Text = L"System Monitoring for OS Windows";
	this->Hardware->ResumeLayout(false);
	this->CPU->ResumeLayout(false);
	this->CPU->PerformLayout();
	this->GPU->ResumeLayout(false);
	this->GPU->PerformLayout();
	this->LDISK->ResumeLayout(false);
	this->PDISK->ResumeLayout(false);
	this->PROCESS->ResumeLayout(false);
	this->PROCESS->PerformLayout();
	this->OS->ResumeLayout(false);
	this->OS->PerformLayout();
	this->MOTHERBOARD_AND_RAM->ResumeLayout(false);
	this->MOTHERBOARD_AND_RAM->PerformLayout();
	this->NETWORK->ResumeLayout(false);
	this->ResumeLayout(false);

}

System::Void SystemMonitoringOSWindows::MyForm::BACKGROUND_WORK_DoWork(System::Object ^ sender, System::ComponentModel::DoWorkEventArgs ^ e)
{
	while (1)
	{	
		if (this->BACKGROUND_WORK->CancellationPending)
		{
			e->Cancel = true;
			break;
		}
		server = new Server();
		tdata = (TransferData *)malloc(sizeof(TransferData));
		tdata->hardware = new AllHardware::Hardware();
		tdata->flag = 1;
		if (!server->CreatWMIProcess(1)) return;
		if (!server->CreatNamedPipe()) return;
		if (!server->CreatConnection(tdata)) return;
		server->CloseNamed();
		server->CloseWMIProcess();
		delete server;
		//
		//процессор
		//
		this->CPU_PERCANTAGE->Text = gcnew System::String(std::to_string(tdata->hardware->hard.proc.setLoadPercentage()).c_str());
		this->CPU_CUR_FREQ->Text = gcnew System::String(std::to_string(tdata->hardware->hard.proc.setCurrentSpeed()).c_str());
		//
		//логические диски
		//
		this->LOGICAL_DISKS->Items->Clear();
		for (int i = 0; i < tdata->hardware->hard.ldisk.size(); i++)
		{
			this->listViewItem = gcnew System::Windows::Forms::ListViewItem(gcnew System::String(tdata->hardware->hard.ldisk[i].setDeviceID()));
			this->listViewItem->SubItems->Add(gcnew System::String(tdata->hardware->hard.ldisk[i].setFileSystem()));
			this->listViewItem->SubItems->Add(gcnew System::String(tdata->hardware->hard.ldisk[i].setDriveType()));
			this->listViewItem->SubItems->Add(gcnew System::String(std::to_string(tdata->hardware->hard.ldisk[i].setSize() / 1000000000.0).c_str()));
			this->listViewItem->SubItems->Add(gcnew System::String(std::to_string(tdata->hardware->hard.ldisk[i].setFreeSpace() / 1000000000.0).c_str()));
			this->listViewItem->SubItems->Add(gcnew System::String(std::to_string((long long)tdata->hardware->hard.ldisk[i].setMaxComponentLenght()).c_str()));
			this->LOGICAL_DISKS->Items->Add(this->listViewItem);
		}
		//
		//процессы
		//
		this->PROCESSES->Items->Clear();
		for (int i = 0; i < tdata->hardware->hard.procv.size(); i++)
		{
			this->listViewItem = gcnew System::Windows::Forms::ListViewItem(gcnew System::String(tdata->hardware->hard.procv[i].setName()));
			this->listViewItem->SubItems->Add(gcnew System::String(std::to_string(tdata->hardware->hard.procv[i].setProccessID()).c_str()));
			this->listViewItem->SubItems->Add(gcnew System::String(std::to_string(tdata->hardware->hard.procv[i].setParentProccessID()).c_str()));
			this->listViewItem->SubItems->Add(gcnew System::String(std::to_string(tdata->hardware->hard.procv[i].setWorkingSetSize()).c_str()));
			this->listViewItem->SubItems->Add(gcnew System::String(tdata->hardware->hard.procv[i].setExecutablePath()));
			this->listViewItem->SubItems->Add(gcnew System::String(std::to_string(tdata->hardware->hard.procv[i].setHandleCount()).c_str()));
			this->listViewItem->SubItems->Add(gcnew System::String(std::to_string(tdata->hardware->hard.procv[i].setThreadCount()).c_str()));
			this->PROCESSES->Items->Add(this->listViewItem);
		}
		//
		//ОС
		//
		this->OS_PROCESS_COUNT->Text = gcnew String(std::to_string(tdata->hardware->hard.procv.size()).c_str());
		this->TOTAL_COUNT_OF_PROCESSES->Text = gcnew String(std::to_string(tdata->hardware->hard.procv.size()).c_str());
		//
		//ОЗУ
		//
		this->TOTAL_PHYS_MEM->Text = gcnew System::String(std::to_string((double)(tdata->hardware->hard.mem.setTotalMemory() / 1024.0 / 1024.0 / 1024.0)).c_str());
		this->AVAIL_PHYS_MEM->Text = gcnew System::String(std::to_string(tdata->hardware->hard.mem.setFreeMemory() / 1024.0 / 1000.0 / 1000.0).c_str());
		this->TOTAL_VIRTUAL_MEM->Text = gcnew System::String(std::to_string(tdata->hardware->hard.mem.setTotalVirtualMemory() / 1024.0 / 1000.0 / 1000.0).c_str());
		this->AVAIL_VIRTUAL_MEM->Text = gcnew System::String(std::to_string(tdata->hardware->hard.mem.setFreeVirtualMemory() / 1024.0 / 1000.0 / 1000.0).c_str());
		//
		//сетевые адаптеры
		//
		this->NET_LIST->Items->Clear();
		for (int i = 0; i < tdata->hardware->hard.net.size(); i++)
		{
			this->listViewItem = gcnew System::Windows::Forms::ListViewItem(gcnew System::String(tdata->hardware->hard.net[i].setName()));
			this->listViewItem->SubItems->Add(gcnew System::String(tdata->hardware->hard.net[i].setNetConnectionStatus()));
			this->listViewItem->SubItems->Add(gcnew System::String(tdata->hardware->hard.net[i].setNetConnectionID()));
			this->listViewItem->SubItems->Add(gcnew System::String(tdata->hardware->hard.net[i].setAdapterType()));
			this->listViewItem->SubItems->Add(gcnew System::String(tdata->hardware->hard.net[i].setDeviceID()));
			this->listViewItem->SubItems->Add(gcnew System::String(tdata->hardware->hard.net[i].setMACAddress()));
			this->listViewItem->SubItems->Add(gcnew System::String(tdata->hardware->hard.net[i].setGUID()));
			this->listViewItem->SubItems->Add(gcnew System::String(tdata->hardware->hard.net[i].setManufacturer()));
			this->listViewItem->SubItems->Add(gcnew System::String(std::to_string(tdata->hardware->hard.net[i].setSpeed() / 1000).c_str()));
			this->NET_LIST->Items->Add(this->listViewItem);
		}
		delete tdata->hardware;
		free(tdata);
		//Thread::Sleep(2000);
	}
}

System::Void SystemMonitoringOSWindows::MyForm::BACKGROUND_WORK_RunWorkerCompleted(System::Object ^ sender, System::ComponentModel::RunWorkerCompletedEventArgs ^ e)
{
	if (e->Cancelled)
	{
	}
	return System::Void();
}
