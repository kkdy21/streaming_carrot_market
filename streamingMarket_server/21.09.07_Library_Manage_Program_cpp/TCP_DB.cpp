#include "TCP_DB.h"

void TCP::Serv()
{
	// 1. Winsock 동적 라이브러리 활성화(초기화)
	int iniResult = WSAStartup(MAKEWORD(2, 2), &wsaData);		//주 버전, 부 버전 번호
	if (iniResult != 0)
	{
		cerr << "Can't initialize winsock!" << endl;
	}


	// 2. 리스닝 소켓 생성
	// socket(IPv4 or IPv6, TCP or UDP type, protocol)
	serv_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (serv_sock == INVALID_SOCKET)
	{
		cerr << "Can't create a socket!" << endl;
		WSACleanup();
	}

	// 3. 소켓 IP주소 PORT번호 할당
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family =		AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port =		htons(PORT);

	// 4. 바인딩
	// OS에 어떤 소켓이 특정 주소와 전송계층포트를 쓰겠다고 알려주는 절차
	int bindResult = bind(serv_sock, reinterpret_cast<SOCKADDR*>(&serv_addr), sizeof(serv_addr));
	if (bindResult == SOCKET_ERROR)
	{
		cerr << "Can't bind a socket!" << endl;
		closesocket(serv_sock);
		WSACleanup();
	}

	// 5. 클라이언트 소켓 연결 대기상태 만들기
	// 클라이언트의 요청은 serv_sock에서 받음
	// 클라이언트 요청 수에 특별한 제약이 없다면 SOMAXCONN
	int lisResult = listen(serv_sock, SOMAXCONN);
	if (serv_sock == SOCKET_ERROR)
	{
		cerr << "Can't listen a socket!" << endl;
		closesocket(serv_sock);
		WSACleanup();
	}

	cout << "대기 중..." << endl;

}



void TCP::Accept_Clnt()
{
	memset(&clnt_addr, 0, sizeof(clnt_addr));

	int clnt_size = sizeof(clnt_addr);
	clnt_sock = accept(serv_sock, reinterpret_cast<SOCKADDR*>(&clnt_addr), &clnt_size);

	cout << "접속"<< endl;

}




void TCP::Close_Serv()
{
	closesocket(serv_sock);
	closesocket(clnt_sock);
}




void TCP::Close_Clnt(SOCKET* sock)
{
	SOCKET temp_sock = (SOCKET) *sock;
	closesocket(temp_sock);
}




///////////////////////////////////////////////////
//////////////////// DB //////////////////////////
//////////////////////////////////////////////////
void DB::DB_Connect()
{
	mysql_init(&conn);
	mysql_set_character_set(&conn, "euckr");
	connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, DB_PORT, (char*)NULL, 0);

	if (connection == NULL)
	{
		cout << "DB connect error!" << endl;
	}
	else
		cout << "DB connect success" << endl;
}



void DB::DB_Disconnect()
{
	mysql_close(connection);
}