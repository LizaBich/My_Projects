#pragma once
#include "stdafx.h"
#include <conio.h>
#include "NewHardware.h"

struct Data
{
	STARTUPINFO startupinfo;
	PROCESS_INFORMATION procinfo;
	HANDLE hNamedPipe;
	HANDLE hServerSemaphore;
	HANDLE hClientSemaphore;
};

class Server
{
	struct Data *data;


public:
	Server();
	~Server();

	bool CreatConnection(struct TransferData *);
	bool CreatWMIProcess(int);
	bool CloseWMIProcess();
	bool CreatNamedPipe();
	bool CloseNamed();
};