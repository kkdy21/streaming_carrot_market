#include "TCP_DB.h"
#include "Carrot.h"

int main()
{
	//setlocale(LC_ALL, "Korean");
	//��ü ����
	Carrot c;
	//���� �ʱ�ȭ


	c.Serv();

	while (true)
	{
		//Ŭ���̾�Ʈ ����
		c.Accept_Clnt();

		//������ ����
		c.Start_thread();
	}

	return 0;
}