#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#include <cstring>
#include <thread>


#include "ServConnection.h"


#pragma warning(disable: 4996)


int main(int argc, char* argv[]) {


	ServConnection Connection;

	

	char msg[256] ="Hello";
	memset(msg, 0, 256);
	
	while (strcmp(msg, "exit") != 0)
	{

		Connection.SendMessageEveryone(msg);
		std::cout << "You: ";
		std::cin.getline(msg, 256, 10);


	}

	system("pause");
	return 0;
}



