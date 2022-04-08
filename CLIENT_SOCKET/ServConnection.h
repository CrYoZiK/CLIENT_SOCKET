#pragma once

#include <winsock2.h>


class ServConnection
{

public:

	ServConnection();

	void Init();

	void Connect();

	void MessagesRecieveThread();

	void SendMessageEveryone(char msg[256]);

private:

	

	bool m_bListening;
	WSAData m_wsaData;
	WORD m_DLLVersion;
	SOCKADDR_IN m_addr;
	SOCKET m_sockCon;

};

