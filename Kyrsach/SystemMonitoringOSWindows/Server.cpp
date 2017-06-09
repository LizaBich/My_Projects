#include "Server.h"

bool Server::CreatWMIProcess(int flag)
{
	ZeroMemory(&this->data->startupinfo, sizeof(STARTUPINFO));
	this->data->startupinfo.cb = sizeof(STARTUPINFO);
	ZeroMemory(&this->data->procinfo, sizeof(PROCESS_INFORMATION));
	TCHAR CommandLine[] = TEXT("GetInfoWithWMI");
	this->data->hServerSemaphore = CreateSemaphore(NULL, 0, 1, L"ServerSemaphore");
	this->data->hClientSemaphore = CreateSemaphore(NULL, 0, 1, L"ClientSemaphore");
	if (flag == 1)
	{
		if (!CreateProcess(NULL, CommandLine, NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS | CREATE_NO_WINDOW, NULL, NULL, &this->data->startupinfo, &this->data->procinfo))
			return false;
	}
	else {
		if (!CreateProcess(NULL, CommandLine, NULL, NULL, FALSE, 0, NULL, NULL, &this->data->startupinfo, &this->data->procinfo))
			return false;
	}
	return true;
}

bool Server::CloseWMIProcess()
{
	CloseHandle(this->data->procinfo.hProcess);
	CloseHandle(this->data->procinfo.hThread);
	return false;
}

bool Server::CreatNamedPipe()
{
	this->data->hNamedPipe = CreateNamedPipe(L"\\\\.\\pipe\\new_pipe", PIPE_ACCESS_DUPLEX, PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT,
		PIPE_UNLIMITED_INSTANCES, BUFFER_SIZE, BUFFER_SIZE, NMPWAIT_USE_DEFAULT_WAIT, NULL);
	if (this->data->hNamedPipe == INVALID_HANDLE_VALUE)
	{
		return false;
	}
	ReleaseSemaphore(this->data->hClientSemaphore, 1, NULL);
	return true;
}

bool Server::CloseNamed()
{
	WaitForSingleObject(this->data->hServerSemaphore, INFINITE);
	CloseHandle(this->data->hNamedPipe);
	CloseHandle(this->data->hServerSemaphore);
	return true;
}

Server::Server()
{
	this->data = (Data *)malloc(sizeof(Data));
}

Server::~Server()
{
	if (this->data->procinfo.hProcess && this->data->procinfo.hThread)
	{
		TerminateProcess(this->data->procinfo.hProcess, 0);
		//CloseHandle(this->data->procinfo.hProcess);
		//CloseHandle(this->data->procinfo.hThread);
	}
	if (this->data->hNamedPipe) CloseHandle(this->data->hNamedPipe);
	if (this->data->hServerSemaphore) CloseHandle(this->data->hServerSemaphore);
	if (this->data->hClientSemaphore) CloseHandle(this->data->hClientSemaphore);
	free(this->data);
}

bool Server::CreatConnection(struct TransferData *tdata)
{
	WaitForSingleObject(this->data->hServerSemaphore, INFINITE);
	//if (!ConnectNamedPipe(this->data->hNamedPipe, NULL)) return false;

	DWORD dwWrite;

	if (!WriteFile(this->data->hNamedPipe, &tdata->flag, sizeof(int), &dwWrite, NULL))
		return false;
	ReleaseSemaphore(this->data->hClientSemaphore, 1, NULL);
	WaitForSingleObject(this->data->hServerSemaphore, INFINITE);
	tdata->hardware->ReadFromFile(tdata->flag);
	return true;
}
