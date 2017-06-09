#pragma once
#include "NewWmiClass.h"
#include <conio.h>

struct Data
{
	HANDLE hNamedPipe;
	HANDLE hServerSemaphore;
	HANDLE hClientSemaphore;
};

class Client
{
	struct Data *data;
	AllHardware::WMIClass *wmi;

public:
	Client(AllHardware::WMIClass *);
	~Client();
	bool ConnectionProcess(struct TransferData *);
	bool OpenConnection();
	bool CloseConnection();
};