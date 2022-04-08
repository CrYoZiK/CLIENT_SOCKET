#include "ServConnection.h"
#include <iostream>
#include <cstring>
#include <chrono>
#include <thread>

using namespace std;
#pragma warning(disable: 4996)

ServConnection::ServConnection()
{
	Init();
}



void ServConnection::Init()
{
	cout << "Initialization SocketHandler" << endl;

	m_wsaData;
	m_DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(m_DLLVersion, &m_wsaData) != 0) {
		std::cout << "Error WSAStartup" << std::endl;
		exit(1);
	}
	cout << "WSAStartup successeful" << endl;


	m_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	m_addr.sin_port = htons(1111);
	m_addr.sin_family = AF_INET;


	m_sockCon = socket(AF_INET, SOCK_STREAM, NULL);

	cout << "Initialization SocketHandler was successful" << endl;

	Connect();

}

void ServConnection::Connect()
{
	cout << "Conecting...";

	int con = 1;

	while (con != 0)
	{
		con = connect(m_sockCon, (SOCKADDR*)&m_addr, sizeof(m_addr));
		cout << ".";
		std::this_thread::sleep_for(100ms);

	}
	
	cout << endl << "Conected" << endl;

	std::thread thrd_msgRecieve(&ServConnection::MessagesRecieveThread, this);
	thrd_msgRecieve.detach();

}

void ServConnection::MessagesRecieveThread()
{
	char msg[256];
	msg[0] = '\0';

	while (true)
	{
		recv(m_sockCon, msg, sizeof(msg), NULL);

		if (msg[0] != '\0')
		{
			std::cout << "(" << m_sockCon << ") Message: " << msg << std::endl;
			msg[0] = '\0';
		}

	}
}

void ServConnection::SendMessageEveryone(char msg[256])
{
	char sendMessage[256];

	for (int i = 0; i < sizeof(sendMessage); i++)
	{
		if (msg[i] == '\0')
		{
			sendMessage[i] = msg[i];
			break;
		}
		sendMessage[i] = msg[i];
	}

	send(m_sockCon, sendMessage, sizeof(sendMessage), NULL);
}