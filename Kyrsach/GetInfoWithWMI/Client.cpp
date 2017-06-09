#include "Client.h"
#include "C:\Users\top_user\Desktop\Kyrsach\SystemMonitoringOSWindows\SystemMonitoringOSWindows\NewHardware.h"

using namespace AllHardware;

bool Client::OpenConnection()
{
	//cout << "Open semaphores" << endl;
	this->data->hServerSemaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, TEXT("ServerSemaphore"));
	this->data->hClientSemaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, TEXT("ClientSemaphore"));
	
	WaitForSingleObject(this->data->hClientSemaphore, INFINITE);
	//cout << "Creat connect to duplex named pipe" << endl;
	this->data->hNamedPipe = CreateFile(L"\\\\.\\pipe\\new_pipe", GENERIC_WRITE | GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (this->data->hNamedPipe == INVALID_HANDLE_VALUE) return false;
	//cout << "Success" << endl;

	return true;
}

bool Client::CloseConnection()
{
	CloseHandle(this->data->hNamedPipe);
	CloseHandle(this->data->hClientSemaphore);
	ReleaseSemaphore(this->data->hServerSemaphore, 1, NULL);
	return true;
}

Client::Client(AllHardware::WMIClass *wmic)
{
	this->data = (Data *)malloc(sizeof(Data));
	this->wmi = wmic;
}

Client::~Client()
{
	free(this->data);
}

bool Client::ConnectionProcess(struct TransferData *tdata)
{
	ReleaseSemaphore(this->data->hServerSemaphore, 1, NULL);
	DWORD dwRead;
	WaitForSingleObject(this->data->hClientSemaphore, INFINITE);
	//cout << "Read data from pipe" << endl;
	if (!ReadFile(this->data->hNamedPipe, &tdata->flag, sizeof(int), &dwRead, NULL))
	{
		return false;
	}
	if (tdata->flag == 0)
	{
		this->wmi->getAllInfo(tdata->hardware);
	}
	else
	{
		this->wmi->getChangableInfo(tdata->hardware);
	}
	//cout << "Write class to file" << endl;
	tdata->hardware->WriteToFile(tdata->flag);
	ReleaseSemaphore(this->data->hServerSemaphore, 1, NULL);
	return true;
}
