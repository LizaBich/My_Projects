#pragma once

namespace SystemMonitoringOSWindows {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Text;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm()
		{
			this->InitializeComponent();
			this->InitializeClasses();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm();
		/*{
			this->BACKGROUND_WORK->CancelAsync();
			while (this->BACKGROUND_WORK->IsBusy);
			if (components)
			{
				delete components;
			}
		}*/
	private: System::Windows::Forms::TabControl^  Hardware;
	protected:

	private: System::Windows::Forms::TabPage^  CPU;
	private: System::Windows::Forms::TabPage^  GPU;
	private: System::Windows::Forms::TabPage^  LDISK;
	private: System::Windows::Forms::TabPage^  PDISK;
	private: System::Windows::Forms::TabPage^  PROCESS;
	private: System::Windows::Forms::TabPage^  OS;
	private: System::Windows::Forms::TabPage^  MOTHERBOARD_AND_RAM;
	private: System::Windows::Forms::TabPage^  NETWORK;
	private: System::Windows::Forms::Label^  label1;

	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  CPU_L3CACHE;
	private: System::Windows::Forms::Label^  CPU_L2CACHE;
	private: System::Windows::Forms::Label^  CPU_LOG_PROC_COUNT;
	private: System::Windows::Forms::Label^  CPU_THREADS;
	private: System::Windows::Forms::Label^  CPU_COUNT_OF_PROC_AVAILPROC;

	private: System::Windows::Forms::Label^  CPU_CUR_FREQ;
	private: System::Windows::Forms::Label^  CPU_MAX_FREQUENCY;
	private: System::Windows::Forms::Label^  CPU_ARCH_ADDRESSWIDTH;
	private: System::Windows::Forms::Label^  CPU_FAMILY;
	private: System::Windows::Forms::Label^  CPU_MANUFACTURER;
	private: System::Windows::Forms::Label^  label15;
	private: System::Windows::Forms::Label^  label14;
	private: System::Windows::Forms::Label^  label13;
	private: System::Windows::Forms::Label^  label12;
	private: System::Windows::Forms::Label^  label11;
	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label24;

	private: System::Windows::Forms::Label^  label22;
	private: System::Windows::Forms::Label^  label21;
	private: System::Windows::Forms::Label^  label20;
	private: System::Windows::Forms::Label^  label19;
	private: System::Windows::Forms::Label^  label18;
	private: System::Windows::Forms::Label^  label17;
	private: System::Windows::Forms::Label^  label16;
	private: System::Windows::Forms::Label^  GPU_NAME;
	private: System::Windows::Forms::ListView^  PROCESSES;
	private: System::Windows::Forms::ColumnHeader^  PROCESS_NAME;
	private: System::Windows::Forms::ColumnHeader^  PROCESS_ID;
	private: System::Windows::Forms::ColumnHeader^  PARENT_PROCESS_ID;
	private: System::Windows::Forms::ColumnHeader^  PROCESS_WORKING_SIZE;
	private: System::Windows::Forms::ColumnHeader^  PROCESS_EXEC_PATH;
	private: System::Windows::Forms::ColumnHeader^  PROCESS_HANDLE_COUNT;
	private: System::Windows::Forms::ColumnHeader^  PROCESS_THREADS_COUNT;

	private: System::Windows::Forms::Label^  CPU_PERCANTAGE;
	private: System::ComponentModel::BackgroundWorker^  BACKGROUND_WORK;

	private: System::Windows::Forms::Label^  GPU_MEMORY_TYPE;
	private: System::Windows::Forms::Label^  GPU_REFRESH_RATE;
	private: System::Windows::Forms::Label^  GPU_RESOLUTION;
	private: System::Windows::Forms::Label^  GPU_BITS_PER_PIXEL;
	private: System::Windows::Forms::Label^  GPU_RAM;
	private: System::Windows::Forms::Label^  GPU_ARCHITECTURE;
	private: System::Windows::Forms::Label^  GPU_PROC;
	private: System::Windows::Forms::Label^  GPU_CHIP;
	private: System::Windows::Forms::Label^  label25;
	private: System::Windows::Forms::Label^  OS_NAME;
	private: System::Windows::Forms::Label^  OS_ARCHITECTURE;
	private: System::Windows::Forms::Label^  sku;
	private: System::Windows::Forms::Label^  device;
	private: System::Windows::Forms::Label^  processe;
	private: System::Windows::Forms::Label^  manufacturer;
	private: System::Windows::Forms::Label^  compname;
	private: System::Windows::Forms::Label^  version;
	private: System::Windows::Forms::Label^  sernum;
	private: System::Windows::Forms::Label^  directory;
	private: System::Windows::Forms::Label^  OS_COMPUTER_NAME;
	private: System::Windows::Forms::Label^  OS_VERSION;
	private: System::Windows::Forms::Label^  OS_SERIAL_NUMBER;
	private: System::Windows::Forms::Label^  OS_DIRECTORY;
	private: System::Windows::Forms::Label^  OS_DEVICE;
	private: System::Windows::Forms::Label^  OS_PROCESS_COUNT;
	private: System::Windows::Forms::Label^  OS_MANUFACTURER;
	private: System::Windows::Forms::Label^  OS_SKU;
	private: System::Windows::Forms::ListViewItem^ listViewItem;
	private: System::Windows::Forms::Label^  AVAIL_VIRTUAL_MEM;
	private: System::Windows::Forms::Label^  label30;
	private: System::Windows::Forms::Label^  label31;
	private: System::Windows::Forms::Label^  TOTAL_VIRTUAL_MEM;
	private: System::Windows::Forms::Label^  label29;
	private: System::Windows::Forms::Label^  AVAIL_PHYS_MEM;
	private: System::Windows::Forms::Label^  label28;
	private: System::Windows::Forms::Label^  TOTAL_PHYS_MEM;
	private: System::Windows::Forms::Label^  mem;
	private: System::Windows::Forms::Label^  BASEBOARD_SERIALNUMBER;
	private: System::Windows::Forms::Label^  label27;
	private: System::Windows::Forms::Label^  BASEBOARD_DESCRIPTION;
	private: System::Windows::Forms::Label^  label26;
	private: System::Windows::Forms::ListView^  LOGICAL_DISKS;

	private: System::Windows::Forms::ColumnHeader^  columnHeader1;
	private: System::Windows::Forms::ColumnHeader^  columnHeader2;
	private: System::Windows::Forms::ColumnHeader^  columnHeader3;
	private: System::Windows::Forms::ColumnHeader^  columnHeader4;
	private: System::Windows::Forms::ColumnHeader^  columnHeader5;
	private: System::Windows::Forms::ColumnHeader^  columnHeader6;
	private: System::Windows::Forms::Label^  TOTAL_COUNT_OF_PROCESSES;
	private: System::Windows::Forms::Label^  label32;

	private: System::Windows::Forms::ListView^  PD_LIST;

	private: System::Windows::Forms::ColumnHeader^  columnHeader7;
	private: System::Windows::Forms::ColumnHeader^  columnHeader8;
	private: System::Windows::Forms::ColumnHeader^  columnHeader9;

	private: System::Windows::Forms::ColumnHeader^  columnHeader11;

	private: System::Windows::Forms::ListView^  NET_LIST;
	private: System::Windows::Forms::ColumnHeader^  columnHeader12;
	private: System::Windows::Forms::ColumnHeader^  columnHeader13;
	private: System::Windows::Forms::ColumnHeader^  columnHeader14;
	private: System::Windows::Forms::ColumnHeader^  columnHeader15;
	private: System::Windows::Forms::ColumnHeader^  columnHeader16;
	private: System::Windows::Forms::ColumnHeader^  columnHeader17;
	private: System::Windows::Forms::ColumnHeader^  columnHeader18;
	private: System::Windows::Forms::ColumnHeader^  columnHeader19;
	private: System::Windows::Forms::ColumnHeader^  columnHeader20;
	private: System::Windows::Forms::ColumnHeader^  columnHeader21;
	private: System::Windows::Forms::ColumnHeader^  columnHeader22;
	private: System::Windows::Forms::ColumnHeader^  columnHeader23;
	private: System::Windows::Forms::ColumnHeader^  columnHeader24;
private: System::Windows::Forms::ColumnHeader^  columnHeader25;
private: System::Windows::Forms::Label^  label34;




private: System::Windows::Forms::Label^  MONITOR_TYPE;
private: System::Windows::Forms::Label^  label35;
private: System::Windows::Forms::Label^  MONITOR_MANUFACTURER;
private: System::Windows::Forms::Label^  MONITOR_DISP_TYPE;
private: System::Windows::Forms::Label^  label36;
private: System::Windows::Forms::Label^  OS_BUILD_NUMBER;
private: System::Windows::Forms::Label^  label23;




	private: System::Windows::Forms::Label^  CPU_NAME;

	private: void InitializeClasses();

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent();
#pragma endregion
	private: System::Void BACKGROUND_WORK_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e);
	private: System::Void BACKGROUND_WORK_RunWorkerCompleted(System::Object^ sender, System::ComponentModel::RunWorkerCompletedEventArgs^ e);
};
}
