#pragma once
#ifndef _TCP_DB_
#define _TCP_DB_

#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <thread>
#include <mutex>

#include <fstream>
#include <sstream>
#include <ctime>

#include <WinSock2.h>
#include <sys/types.h>

#include <mysql.h>
#include <io.h>
#include <iostream>

#pragma comment(lib, "ws2_32")
#pragma comment(lib, "libmySQL.lib")
using namespace std;

#define DB_HOST "127.0.0.1"
#define DB_USER "root"
#define DB_PASS "1234"
#define DB_NAME "carrot"
#define DB_PORT 3306

#define IP "127.0.0.1"
#define PORT 9100

#define BUFFERSIZE 1024



class TCP
{
	protected:
		WSADATA			wsaData;			//Windows Sockets API를 의미
		SOCKET			serv_sock, clnt_sock;
		//vector<SOCKET>	socks;
		SOCKADDR_IN		serv_addr, clnt_addr;

		int* clnt_socks;
		//int clnt_cnt;

		mutex m;


	public:

		void Serv();
		void Accept_Clnt();

		void Send_To_All(string msg);

		void Close_Serv();
		void Close_Clnt(SOCKET* sock);	//특정 클라이언트 소켓만 종료

};



class DB
{
	protected:
		MYSQL* connection = NULL, conn;
		MYSQL_RES	*sql_result;
		MYSQL_ROW	sql_row;
		

	public:
		void DB_Connect();
		void DB_Disconnect();

};


#endif