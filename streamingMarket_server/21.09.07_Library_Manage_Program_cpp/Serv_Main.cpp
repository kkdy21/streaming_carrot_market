#include "TCP_DB.h"
#include "Carrot.h"

int main()
{
	//setlocale(LC_ALL, "Korean");
	//객체 생성
	Carrot c;
	//서버 초기화


	c.Serv();

	while (true)
	{
		//클라이언트 접속
		c.Accept_Clnt();

		//스레드 접속
		c.Start_thread();
	}

	return 0;
}