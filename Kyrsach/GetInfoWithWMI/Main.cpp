#include "Client.h"

int main()
{
	AllHardware::WMIClass *wmi = new AllHardware::WMIClass();
	Client *client = new Client(wmi);
	struct TransferData *tdata = (TransferData *)malloc(sizeof(TransferData));
	tdata->hardware = new AllHardware::Hardware();
	//cout << "Try to connect to the main process" << endl;
	if (!client->OpenConnection())
	{
		cout << "Error of opening connection" << endl;
		delete client;
		delete wmi;
		_getch();
		return 0;
	}
	if (!client->ConnectionProcess(tdata))
	{
		cout << "Error in ConnectionProcess" << endl;
		delete tdata->hardware;
		free(tdata);
		delete client;
		delete wmi;
		return 0;
	}
	
	cout << "Delete objects" << endl;
	delete tdata->hardware;
	free(tdata);
	delete wmi;
	cout << "Close pipe" << endl;
	client->CloseConnection();
	delete client;
	cout << "Return" << endl;
	return 0;
}