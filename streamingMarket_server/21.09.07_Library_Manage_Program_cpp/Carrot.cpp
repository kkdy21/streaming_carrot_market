#include "Carrot.h"

void Carrot::Start_thread()
{ 
	thread t1([&]() {_thread((void*)&clnt_sock); });

	t1.detach();
}


void* Carrot::_thread(void* sock)
{
	cout << "������ ����" << endl;
	int C_sock = *((int*)sock);
	int sig;
	char recv_msg[1024];

	vector<string> v;
	vector<string> info;
	string send_msg;




	while (true)
	{
		//.lock();
		cout << "rerere" << endl;
		memset(recv_msg, 0, sizeof(recv_msg));
		sig = recv(C_sock, recv_msg, sizeof(recv_msg), 0);

		cout << "recv_msg : " << recv_msg << endl;

		v = Split(recv_msg, "$");
		for (string i : v)
		{
			cout << "v : " << i << endl;
		}

		if (v.size() > 1)
		{
			info = Split(v[1].c_str(), "^");
		}

		for (string i : info)
		{
			cout << "info : " << i << endl;
		}


		// �α���
		if (strcmp(v[0].c_str(), "login") == 0)
		{
			//m.lock();
			cout << "�α���" << endl;
			send_msg = Login(info);
			cout << "�������� : " << send_msg << endl;
			send(C_sock, send_msg.c_str(), strlen(send_msg.c_str()), 0);
			//m.unlock();
		}

		// ȸ������
		else if (strcmp(v[0].c_str(), "enroll") == 0)
		{
			cout << "ȸ������" << endl;
			send_msg = Enroll(info, C_sock);
			cout << "�������� : " << send_msg << endl;
			send(C_sock, send_msg.c_str(), strlen(send_msg.c_str()), 0);
			if (send_msg == "true")
			{
				Recv_Image("profile");
			}

		}

		////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////


		
		// �Ϲ��Ǹ�
		else if (strcmp(v[0].c_str(), "sales") == 0)
		{
			
			cout << "�Ϲ��Ǹ� ���" << endl;
			send_msg = Sales(info);
			cout << "�������� : " << send_msg << endl;
			send(C_sock, send_msg.c_str(), strlen(send_msg.c_str()), 0);
			

		}

		// �Ϲ��Ǹ� - �Խñ�Ŭ��
		else if (strcmp(v[0].c_str(), "sales_detail") == 0)
		{
			

			cout << "�Ϲ� - �Խñ� Ŭ��" << endl;
			send_msg = SalesDetails(info);

			int cnt = SalesImageNum_Num(info);
			cout << "cnt : " << cnt << endl;
			char p[10];
			itoa(cnt, p, 10);
			send_msg += p;
			cout << "�������� : " << send_msg << endl;

			send(C_sock, send_msg.c_str(), strlen(send_msg.c_str()), 0);
			
			memset(recv_msg, 0, sizeof(recv_msg));
			recv(C_sock, recv_msg, sizeof(recv_msg), 0);
			cout << "recv : " << recv_msg << endl;

			string filename = FindProfile(info[0], "sales");

			Send_Image(filename, "profile", -1, C_sock);

			memset(recv_msg, 0, sizeof(recv_msg));
			recv(C_sock, recv_msg, sizeof(recv_msg), 0);
			cout << "recv : " << recv_msg << endl;

			for (int i = 0; i < cnt; i++)
			{
				cout << "�̹��� ������" << endl;
				Send_Image(info, i, "sales_detail", C_sock);
			}
			
		}

		// ���
		else if (strcmp(v[0].c_str(), "auction") == 0)
		{
			cout << "����Ǹ� ���" << endl;
			send_msg = Auction(info);
			cout << "�������� : " << send_msg << endl;
			send(C_sock, send_msg.c_str(), strlen(send_msg.c_str()), 0);
		}

		// ��� - �Խñ�Ŭ��
		else if (strcmp(v[0].c_str(), "auction_detail") == 0)
		{
			cout << "��� - �Խñ� Ŭ��" << endl;
			send_msg = AuctionDetails(info, C_sock);

			int cnt = AuctionImageNum(info);
			cout << "cnt : " << cnt << endl;
			char p[10];
			itoa(cnt, p, 10);
			send_msg += p;
			cout << "�������� : " << send_msg << endl;
			send(C_sock, send_msg.c_str(), strlen(send_msg.c_str()), 0);

			memset(recv_msg, 0, sizeof(recv_msg));
			recv(C_sock, recv_msg, sizeof(recv_msg), 0);
			cout << "recv : " << recv_msg << endl;

			string filename = FindProfile(info[1], "auction");

			Send_Image(filename, "profile", -1, C_sock);

			memset(recv_msg, 0, sizeof(recv_msg));
			recv(C_sock, recv_msg, sizeof(recv_msg), 0);
			cout << "recv : " << recv_msg << endl;

			for (int i = 0; i < cnt; i++)
			{
				cout << "�̹��� ������" << endl;
				Send_Image(info, i, "auction_detail", C_sock);
			}
		}
		
		

		// ä��
		else if (strcmp(v[0].c_str(), "chat") == 0)
		{
			cout << "ä��" << endl;
			ChatOnO(info, C_sock);
			//cout << "�������� : " << send_msg << endl;
		}
		

		// �ŷ��ı�
		else if (strcmp(v[0].c_str(), "your_review") == 0)
		{
			cout << "�ŷ��ı�" << endl;
			Review(info, info[5]);
			//send(C_sock, send_msg.c_str(), strlen(send_msg.c_str()), 0);
		}





		// ���� �ǸŸ��
		else if (strcmp(v[0].c_str(), "my_sales") == 0)
		{
			cout << "���� �ǸŸ��" << endl;
			send_msg = MySales(info);
			cout << "�������� : " << send_msg << endl;
			send(C_sock, send_msg.c_str(), strlen(send_msg.c_str()), 0);
		}

		// �Ϸ� �ŷ����
		else if (strcmp(v[0].c_str(), "my_deal") == 0)
		{
			cout << "�Ϸ� �ŷ����" << endl;
			send_msg = MyDeal(info);
			cout << "�������� : " << send_msg << endl;
			send(C_sock, send_msg.c_str(), strlen(send_msg.c_str()), 0);
		}

		// ������
		else if (strcmp(v[0].c_str(), "profile") == 0)
		{
			cout << "������" << endl;
			send_msg = MyProfile(info);
			cout << "�������� : " << send_msg << endl;
			send(C_sock, send_msg.c_str(), strlen(send_msg.c_str()), 0);

			memset(recv_msg, 0, sizeof(recv_msg));
			recv(C_sock, recv_msg, sizeof(recv_msg), 0);
			cout << "recv_msg : " << recv_msg << endl;

			Send_Image(info, 1, "profile", C_sock);

		}

		// ������ ����
		else if (strcmp(v[0].c_str(), "Myprofile") == 0)
		{
			cout << "������ ����" << endl;
			send_msg = "true";
			send(C_sock, send_msg.c_str(), strlen(send_msg.c_str()), 0);

			Recv_Image("profile");
		}


		
		// ��� - ����
		else if (strcmp(v[0].c_str(), "bid") == 0)
		{
			cout << "����" << endl;
			AucBid(info, C_sock);
			//cout << "�������� : " << send_msg << endl;
			// send(C_sock, send_msg.c_str(), strlen(send_msg.c_str()), 0);
		}

		// ��� - ä��
		else if (strcmp(v[0].c_str(), "auction_chat") == 0)
		{
			cout << "��� - ä��" << endl;
			send_msg = AucChat(info);
			cout << "�������� : " << send_msg << endl;
			send(C_sock, send_msg.c_str(), strlen(send_msg.c_str()), 0);
		}

		// ��� - ������
		else if (strcmp(v[0].c_str(), "bid_exit") == 0)
		{
			cout << "��� - ������" << endl;
			AucQuiting(info);
			/*send_msg = "EndThread";
			send(C_sock, send_msg.c_str(), strlen(send_msg.c_str()), 0);*/
		}

		// �������
		else if (strcmp(v[0].c_str(), "auction_end") == 0)
		{
			cout << "�������" << endl;
			AuctionEnd(info);
		}

		

		// �Խñ� �ۼ� - �Ϲ��Ǹ�
		else if (strcmp(v[0].c_str(), "new_sales") == 0)
		{
			cout << "�Խñ� - �Ϲ�" << endl;
			send_msg = NewSales(info);
			cout << "�������� : " << send_msg << endl;
			send(C_sock, send_msg.c_str(), strlen(send_msg.c_str()), 0);
			
			int cnt = stoi(info[4]);
			cout << "cnt : " << cnt << endl;
			for (int i = 0; i < cnt; i++)
			{
				Recv_Image("sales");
			}
		}

		// �Խñ� �ۼ� - ����Ǹ�
		else if (strcmp(v[0].c_str(), "new_auction") == 0)
		{
			cout << "�Խñ� - ���" << endl;
			send_msg = NewAuction(info, C_sock);
			cout << "�������� : " << send_msg << endl;
			send(C_sock, send_msg.c_str(), strlen(send_msg.c_str()), 0);
			
			int cnt = stoi(info[7]);
			for (int i = 0; i < cnt; i++)
			{
				Recv_Image("auction");
			}
		}

		// ä��
		else if (strcmp(v[0].c_str(), "chatlog") == 0)
		{
			ChatIn(info, C_sock);

			memset(recv_msg, 0, sizeof(recv_msg));
			sig = recv(C_sock, recv_msg, sizeof(recv_msg), 0);
			cout << "recv_msg : " << recv_msg << endl;

			Send_Image(info[1], "profile", -2, C_sock);
			
			
		}

		// ä�� ����
		else if (strcmp(v[0].c_str(), "chatEnter") == 0)
		{
			cout << "ä�� ����" << endl;
			ChatEnter(info, C_sock);
		}

		// ä�� ������
		else if (strcmp(v[0].c_str(), "chatout") == 0)
		{
		cout << "ä�� ������" << endl;
			ChatOut(info);
			send_msg = "chatout$";
			send(C_sock, send_msg.c_str(), strlen(send_msg.c_str()), 0);
		}

		// ä�� ����Ʈ
		else if (strcmp(v[0].c_str(), "chat_list") == 0)
		{
			cout << "ä�� ����Ʈ" << endl;
			send_msg = ChatList(info);
			cout << "�������� : " << send_msg << endl;
			send(C_sock, send_msg.c_str(), strlen(send_msg.c_str()), 0);
			// ������̵�^ �������޼���^ ����^ ����

			if (send_msg == "false")
			{
				cout << "����" << endl;
				continue;
			}

			

			char query[256];
			vector<string> ap_id;
			vector<string> ap_title;
			vector<string> ap_number;

			DB_Connect();
			string count;
			sprintf(query, "select count(*), ap_id from chat_list where id = '%s'", info[0].c_str());
			mysql_query(connection, query);
			sql_result = mysql_store_result(connection);
			int check = mysql_num_rows(sql_result);

			if (check == 0)
			{
				DB_Disconnect();
				continue;
			}

			else
			{
				while (sql_row = mysql_fetch_row(sql_result))
				{
					count = sql_row[0];
				}
			}

			sprintf(query, "select num, ap_id, title from chat_list where id = '%s'", info[0].c_str());
			mysql_query(connection, query);
			sql_result = mysql_store_result(connection);
			check = mysql_num_rows(sql_result);

			if (check == 0)
			{
				DB_Disconnect();
				continue;
			}

			else
			{
				
				ap_id.clear();
				ap_title.clear();
				while (sql_row = mysql_fetch_row(sql_result))
				{
					
					ap_number.push_back(sql_row[0]);
					ap_id.push_back(sql_row[1]);
					ap_title.push_back(sql_row[2]);
				}
			}
			


			


			int cnt = stoi(count);
			cout << "cnt : " << cnt << endl;
			string filename;

			cout << "�̹��� ������ ��" << endl;

			for (int i = 0; i < cnt; i++)
			{
				string wkr;

				sprintf(query, "select id from trade where num = '%s'", ap_number[i].c_str());
				mysql_query(connection, query);
				sql_result = mysql_store_result(connection);
				while (sql_row = mysql_fetch_row(sql_result))
				{
					wkr = sql_row[0];
				}


				memset(recv_msg, 0, sizeof(recv_msg));
				sig = recv(C_sock, recv_msg, sizeof(recv_msg), 0);
				cout << "recv_msg : " << recv_msg << endl;

				cout << "�̹���������" << endl;
				Send_Image(ap_id[i], "profile", -2, C_sock);

				memset(recv_msg, 0, sizeof(recv_msg));
				sig = recv(C_sock, recv_msg, sizeof(recv_msg), 0);
				cout << "recv_msg : " << recv_msg << endl;

				filename = wkr + "_" + ap_title[i] += "_0.png\0";
				Send_Image(filename, "sales", -1, C_sock);
			}

			DB_Disconnect();
		}



		// �ŷ��ı� ����
		else if (strcmp(v[0].c_str(), "review") == 0)
		{
			cout << "�ŷ��ı� ����" << endl;
			send_msg = YourReview(info);
			cout << "�������� : " << send_msg << endl;
			send(C_sock, send_msg.c_str(), strlen(send_msg.c_str()), 0);

			if (send_msg != "false")
			{
				for (int i = 0; i < apnt_profile.size(); i++)
				{
					cout << "�ŷ��ı� �̹��� ������" << endl;
					Send_Image(apnt_profile[i], "profile", -2, C_sock);
				}
			}

			
		}


		// �Խñ� �̹��� ���� - �Ϲ��Ǹ�
		else if (strcmp(v[0].c_str(), "sales_image") == 0)
		{
			cout << "�̹��� ���� (�Ϲ��Ǹ�)" << endl;
			vector<string> tt = Split(info[0], "_");
			for (string i : tt)
			{
				cout << "tt : " << i << endl;
			}
			Send_Image(info[0], "sales", 0, C_sock);
		}

		// �Խñ� �̹��� ���� - ����Ǹ�
		else if (strcmp(v[0].c_str(), "auction_image") == 0)
		{
			cout << "�̹��� ���� (����Ǹ�)" << endl;
			vector<string> tt = Split(info[0], "_");
			for (string i : tt)
			{
				cout << "tt : " << i << endl;
			}
		
			Send_Image(info[0], "auction", 0, C_sock);
		}






		// �Ǹ� ���� - �Ϲ��Ǹ�
		else if (strcmp(v[0].c_str(), "sale_sale") == 0)
		{
			cout << "�Ǹ� ���� - �Ϲ��Ǹ�" << endl;
			send_msg = SalesList(info);
			cout << "�������� : " << send_msg << endl;
			send(C_sock, send_msg.c_str(), strlen(send_msg.c_str()), 0);



		}

		// �Ǹ� ���� - ����Ǹ�
		else if (strcmp(v[0].c_str(), "auction_sale") == 0)
		{
			cout << "�Ǹ� ���� - ����Ǹ�" << endl;
			send_msg = AuctionList(info);
			cout << "�������� : " << send_msg << endl;
			send(C_sock, send_msg.c_str(), strlen(send_msg.c_str()), 0);
		}

		// ���� ���� - �Ϲ��Ǹ�
		else if (strcmp(v[0].c_str(), "sale_pay") == 0)
		{
			cout << "���� ���� - �Ϲݱ���" << endl;
			send_msg = SalesPay(info);
			cout << "�������� : " << send_msg << endl;
			send(C_sock, send_msg.c_str(), strlen(send_msg.c_str()), 0);
		}

		// ���� ���� - ����Ǹ�
		else if (strcmp(v[0].c_str(), "auction_pay") == 0)
		{
			cout << "���� ���� - ��ű���" << endl;
			send_msg = AuctionPay(info);
			cout << "�������� : " << send_msg << endl;
			send(C_sock, send_msg.c_str(), strlen(send_msg.c_str()), 0);
		}


		// ������ ã��
		else if (strcmp(v[0].c_str(), "buyerselect") == 0)
		{
			cout << "������ã��" << endl;
			send_msg = B_List(info);
			cout << "�������� : " << send_msg << endl;
			send(C_sock, send_msg.c_str(), strlen(send_msg.c_str()), 0);
			
			for (int i = 0; i < profilelist.size(); i++)
			{
				Send_Image(profilelist[i], "profile", -2, C_sock);
			}


			


		}


		// ��Ʈ����
		else if (strcmp(v[0].c_str(), "OnAir") == 0)
		{

			cout << "��Ʈ���� ����" << endl;
			send_msg = OnAir(info, C_sock);
			cout << "�������� : " << send_msg << endl;
			//send(C_sock, send_msg.c_str(), strlen(send_msg.c_str()), 0);


		}


		// ��Ʈ���� ����
		else if (strcmp(v[0].c_str(), "EndStreaming") == 0)
		{
			cout << "��Ʈ���� ����" << endl;
			send_msg = EndStream(info, C_sock);
			cout << "�������� : " << send_msg << endl;
			send(C_sock, send_msg.c_str(), strlen(send_msg.c_str()), 0);
		}















		
		// ������ ����
		else if (strcmp(v[0].c_str(), "EndThread") == 0)
		{
			cout << "����������" << endl;
			send_msg = "EndThread";
			send(C_sock, send_msg.c_str(), strlen(send_msg.c_str()), 0);
		}

		//����
		else if (strcmp(v[0].c_str(), "close") == 0)
		{
			closesocket(clnt_sock);
			break;
		}

		


		//m.unlock();
	}


	return NULL;
}








// �α���
string Carrot::Login(vector<string> v)
{
	char query[256];
	string temp = "false";

	DB_Connect();
	sprintf(query, "select count(*) from customer where id = '%s' and pw = '%s'", v[0].c_str(), v[1].c_str());
	int check = mysql_query(connection, query);
	sql_result = mysql_store_result(connection);
	sql_row = mysql_fetch_row(sql_result);

	if (strcmp(sql_row[0], "1") == 0)
		temp = "true";

	DB_Disconnect();

	return temp;
}



// ȸ������

string Carrot::Enroll(vector<string> v, int sock)
{
	char query[256];
	string temp = "false";
	//string image_path = "C:\\Users\\iot2105\\Desktop\\���\\profile\\";
	string image_path = "C:/Users/iot2105/Desktop/���/profile/";
	image_path += v[0];
	image_path += "_profile.png";


	cout << image_path << endl;

	DB_Connect();
	sprintf(query, "insert into customer values('%s', '%s', '%s', '%s', '%s', '%s', '50', '%s')",
		v[0].c_str(), v[1].c_str(), v[2].c_str(), v[3].c_str(), v[4].c_str(), v[5].c_str(), image_path.c_str());
	int check = mysql_query(connection, query);

	sql_result = mysql_store_result(connection);
	sprintf(query, "insert into chat_tbl (id,login, fd) values('%s',0, '%d')", v[0].c_str(), sock);
	int check2 = mysql_query(connection, query);
	sql_result = mysql_store_result(connection);

	DB_Disconnect();

	cout << "check : " << check << endl;
	if (check == 0)
		temp = "true";


	return temp;
}


// �Ϲ��Ǹ�
string Carrot::Sales(vector<string> info)
{
	char query[256];
	string temp = "sales$";
	string u_area = SearchArea(info);

	if (u_area.c_str() == "false")
	{
		cout << "return" << endl;
		return "false";
	}

	// ã�� ������ �´� �ǸŸ�� ������
	DB_Connect();
	sprintf(query, "select * from trade where area = '%s' and onsale = 'false'", u_area.c_str());
	mysql_query(connection, query);
	sql_result = mysql_store_result(connection);
	int check = mysql_num_rows(sql_result);

	if (check == 0)
	{
		DB_Disconnect();
		return "false";
	}

	// �Խñ۹�ȣ1^�ۼ���id1^�ۼ��ڴг���1^����1^����1^�ð�1#2���Խñ�...
	else
	{
		while (sql_row = mysql_fetch_row(sql_result))
		{
			temp += sql_row[0];
			temp += "^";
			temp += sql_row[2];
			temp += "^";
			temp += sql_row[3];
			temp += "^";
			temp += sql_row[4];
			temp += "^";
			temp += sql_row[6];
			temp += "^";
			temp += sql_row[8];
			temp += "#";
		}
		DB_Disconnect();
	}

	return temp;
}


// �Ϲ��Ǹ� - �Խñ� Ŭ��
string Carrot::SalesDetails(vector<string> info)
{
	char query[256];
	string temp = "sales_detail$";

	DB_Connect();
	sprintf(query, "select * from trade where num = '%s'",
		info[0].c_str());
	mysql_query(connection, query);
	sql_result = mysql_store_result(connection);
	int check = mysql_num_rows(sql_result);

	cout << "���� : " <<  query << endl;

	if (check == 0)
	{
		DB_Disconnect();
		return "false";
	}


	// sales_detail$�Խñ۹�ȣ, �ۼ���ID, �ۼ��ڴг���, ����, ����, �ۼ��ð�
	// �Խñ۹�ȣ, �ۼ���ID, �ۼ��ڴг���, ����, ����, �ۼ��ð�
	else
	{
		while (sql_row = mysql_fetch_row(sql_result))
		{
			temp += sql_row[2];		//id
			temp += "^";
			temp += sql_row[5];		//����
			temp += "^";
			temp += sql_row[1];		//����
			temp += "^";

			/*temp += sql_row[0];
			temp += "^";
			temp += sql_row[2];
			temp += "^";
			temp += sql_row[3];
			temp += "^";
			temp += sql_row[4];
			temp += "^";
			temp += sql_row[6];
			temp += "^";
			temp += sql_row[8];*/
		}
		DB_Disconnect();
	}
	

	return temp;
}


// �Ϲ��Ǹ� - �̹��� �� ���ϱ�
int Carrot::SalesImageNum_Num(vector<string> info)
{
	char query[256];
	int temp = 0;

	DB_Connect();

	sprintf(query, "select * from trade where num = '%s'",
		info[0].c_str());
	mysql_query(connection, query);
	sql_result = mysql_store_result(connection);
	int check = mysql_num_rows(sql_result);

	if (check == 0)
	{
		DB_Disconnect();
		return 0;
	}

	else
	{
		while (sql_row = mysql_fetch_row(sql_result))
		{
			string image1 = sql_row[11];
			string image2 = sql_row[12];
			if (image1 == "none")
				temp = 1;

			else if (image2 == "none")
				temp = 2;

			else
				temp = 3;
		}
		DB_Disconnect();
	}

	return temp;
}


// �̹��� �� ���ϱ�
int Carrot::ImageNum_ID(vector<string> info, string tbl)
{
	char query[256];
	int temp = 0;

	DB_Connect();

	if (tbl == "sales")
	{
		sprintf(query, "select * from trade where id = '%s' and title = '%s'",
			info[0].c_str(), info[1].c_str());
	}

	else if (tbl == "auction")
	{
		sprintf(query, "select * from auction where id = '%s' and title = '%s'",
			info[0].c_str(), info[1].c_str());
	}

	mysql_query(connection, query);
	sql_result = mysql_store_result(connection);
	int check = mysql_num_rows(sql_result);

	if (check == 0)
	{
		DB_Disconnect();
		return 0;
	}

	else
	{
		while (sql_row = mysql_fetch_row(sql_result))
		{
			string image1 = sql_row[10];
			string image2 = sql_row[11];
			if (image1 == "none")
				temp = 1;

			else if (image2 == "none")
				temp = 2;

			else
				temp = 3;
		}
		DB_Disconnect();
	}

	return temp;
}







// ����Ǹ� - �̹��� �� ���ϱ�
int Carrot::AuctionImageNum(vector<string> info)
{
	char query[256];
	int temp = 0;

	vector<string> v;

	DB_Connect();
	sprintf(query, "select image from auction where num = '%s'",
		info[1].c_str());
	mysql_query(connection, query);
	sql_result = mysql_store_result(connection);
	int check = mysql_num_rows(sql_result);

	if (check == 0)
	{
		DB_Disconnect();
		return 0;
	}

	else
	{
		while (sql_row = mysql_fetch_row(sql_result))
		{
			//v = Split(sql_row[12], "^");
			//temp = v.size() - 1;
			temp = stoi(sql_row[0]);
		}
		DB_Disconnect();
	}

	return temp;
}





// ���
string Carrot::Auction(vector<string> info)
{
	char query[256];
	string temp = "auction$";
	string u_area = SearchArea(info);

	if (u_area.c_str() == "false")
	{
		return "false";
	}

	
	// ã�� ������ �´� �ǸŸ�� ������
	DB_Connect();
	sprintf(query, "select * from auction where area = '%s'", u_area.c_str());
	mysql_query(connection, query);
	sql_result = mysql_store_result(connection);
	int check = mysql_num_rows(sql_result);

	if (check == 0)
	{
		DB_Disconnect();
		return "false";
	}


	//��ȣ, �ۼ��� ���̵�, �г���, ����, ����, �ۼ��ð�, ����ð�
	else
	{
		while (sql_row = mysql_fetch_row(sql_result))
		{
			temp += sql_row[0];
			temp += "^";
			temp += sql_row[2];
			temp += "^";
			temp += sql_row[3];
			temp += "^";
			temp += sql_row[4];
			temp += "^";
			temp += sql_row[6];
			temp += "^";
			temp += sql_row[9];
			temp += "^";
			temp += sql_row[10];
			temp += "#";
		}
		DB_Disconnect();
	}


	return temp;
}

// ��� - �Խñ� Ŭ��
string Carrot::AuctionDetails(vector<string> info, int sock)
{
	char query[256];
	string temp = "auction_detail$";
	string u_nick = SearchNick(info);

	if (u_nick.c_str() == "false")
	{
		return "false";
	}

	DB_Connect();
	sprintf(query, "select * from auction where num = '%s'",
		info[1].c_str());
	mysql_query(connection, query);
	sql_result = mysql_store_result(connection);
	int check = mysql_num_rows(sql_result);

	if (check == 0)
	{
		DB_Disconnect();
		return "false";
	}

	// auction_detail$�������̵�,��������,�����ְ� ���̵�,�����ְ�, �ּ�������, �Խñ۳���,�̹�������

	else
	{
		while (sql_row = mysql_fetch_row(sql_result))
		{
			temp += sql_row[2];
			temp += "^";
			temp += sql_row[1];
			temp += "^";
			temp += sql_row[13];
			temp += "^";
			temp += sql_row[6];
			temp += "^";
			temp += sql_row[8];
			temp += "^";
			temp += sql_row[5];
			temp += "^";
		}
		
		

		// ����ο�����
		sprintf(query, "insert into auction_tbl values('%s', '%d', '%s')",
			info[1].c_str(), sock, info[0].c_str());
		mysql_query(connection, query);
		sql_result = mysql_store_result(connection);

		DB_Disconnect();
	}

	return temp;
}

// �ŷ��ı� ���
void Carrot::Review(vector<string> info, string type)
{
	char query[256];
	DB_Connect();
	
	cout << "type : " << type << endl;

	if (type == "Seller")
	{
		cout << "seller" << endl;
		sprintf(query, "insert into review values('%s', '%s', '%s', '%s', '%s')",
			info[0].c_str(), info[1].c_str(), info[2].c_str(), info[3].c_str(), info[4].c_str());
	}

	else if (type == "buyer")
	{
		cout << "buyer" << endl;
		sprintf(query, "insert into review values('%s', '%s', '%s', '%s', '%s')",
			info[0].c_str(), info[2].c_str(), info[1].c_str(), info[3].c_str(), info[4].c_str());
	}
	
	
	// num, seller, buyer, review, comment
	/*sprintf(query, "insert into review values('%s', '%s', '%s', '%s', '%s')",
		info[0].c_str(), info[1].c_str(), info[2].c_str(), info[3].c_str(), info[4].c_str());*/
	mysql_query(connection, query);
	sql_result = mysql_store_result(connection);

	cout << "������" << endl;



	if (type == "Seller")
	{
		sprintf(query, "update trade set onsale = 'true', buyer = '%s' where num = '%s'",
			info[2].c_str() ,info[0].c_str());
	}

	else if (type == "buyer")
	{
		sprintf(query, "update trade set onsale = 'true', buyer = '%s' where num = '%s'",
			info[1].c_str(), info[0].c_str());
	}




	/*sprintf(query, "update trade set onsale = 'true' where num = '%s'",
		info[0].c_str());*/
	mysql_query(connection, query);
	sql_result = mysql_store_result(connection);

	cout << "��ǰó��" << endl;



	if (type == "Seller")
	{
		sprintf(query, "update customer set trust = trust + %s where id = '%s'",
			info[3].c_str(), info[2].c_str());
	}

	else if (type == "buyer")
	{
		sprintf(query, "update customer set trust = trust + %s where id = '%s'",
			info[3].c_str(), info[1].c_str());
	}

	/*sprintf(query, "update customer set trust = trust + %s where id = '%s'",
		info[3].c_str(), info[1].c_str());*/

	mysql_query(connection, query);
	sql_result = mysql_store_result(connection);

	
	
	cout << "�ŷڵ�ó��" << endl;



	DB_Disconnect();
}

// �� �ǸŸ��
string Carrot::MySales(vector<string> info)
{
	char query[256];
	string temp = "my_sales$";
	string u_nick = SearchNick(info);
	if (u_nick.c_str() == "false")
	{
		return "false";
	}

	// ã�� �гۿ� �´� �ǸŸ�� ������
	DB_Connect();
	sprintf(query, "select * from trade where area = '%s'", u_nick.c_str());
	mysql_query(connection, query);
	sql_result = mysql_store_result(connection);
	int check = mysql_num_rows(sql_result);

	if (check == 0)
	{
		DB_Disconnect();
		return "false";
	}

	else
	{
		while (sql_row = mysql_fetch_row(sql_result))
		{
			temp += sql_row[0];
			temp += "^";
			temp += sql_row[3];
			temp += "^";
			temp += sql_row[4];
			temp += "#";
		}
		DB_Disconnect();
	}

	return temp;
}

// �Ϸ� �ŷ����
string Carrot::MyDeal(vector<string> info)
{
	char query[256];
	string temp = "my_deal$";
	string u_nick = SearchNick(info);
	
	if (u_nick.c_str() == "false")
	{
		return "false";
	}

	// ã�� �гۿ� �´� �Ϸ� �ǸŸ�� ������
	DB_Connect();
	sprintf(query, "select * from trade where nickname = '%s' and onsale = 'true'", u_nick.c_str());
	mysql_query(connection, query);
	sql_result = mysql_store_result(connection);
	int check = mysql_num_rows(sql_result);

	if (check == 0)
	{
		DB_Disconnect();
		return "false";
	}

	else
	{
		while (sql_row = mysql_fetch_row(sql_result))
		{
			temp += sql_row[0];
			temp += "^";
			temp += sql_row[3];
			temp += "^";
			temp += sql_row[4];
			temp += "#";
		}
		DB_Disconnect();
	}

	return temp;
}

string Carrot::MyProfile(vector<string> info)
{
	char query[256];
	string temp = "profile$";
	DB_Connect();
	sprintf(query, "select * from customer where id = '%s'",
		info[0].c_str());
	mysql_query(connection, query);
	sql_result = mysql_store_result(connection);
	int check = mysql_num_rows(sql_result);

	if (check == 0)
	{
		DB_Disconnect();
		return "false";
	}

	else
	{
		while (sql_row = mysql_fetch_row(sql_result))
		{
			temp += sql_row[2];
			temp += "^";
			temp += sql_row[4];
			temp += "^";
			temp += sql_row[5];
			temp += "^";
			temp += sql_row[6];
		}
		DB_Disconnect();
	}

	return temp;
}






int Carrot::ReviewCount(vector<string> info)
{
	char query[256];
	int temp = 0;
	DB_Connect();
	sprintf(query, "select count(*) from review where seller = '%s' or buyer = '%s'",
		info[0].c_str(), info[0].c_str());
	mysql_query(connection, query);
	sql_result = mysql_store_result(connection);
	int check = mysql_num_rows(sql_result);


	while (sql_row = mysql_fetch_row(sql_result))
	{
		temp = stoi(sql_row[0]);
	}

	return temp;
}




string Carrot::YourReview(vector<string> info)
{
	char query[256];
	string temp = "review$";
	string u_area = SearchArea(info);

	DB_Connect();
	sprintf(query, "select * from review where seller = '%s' or buyer = '%s'",
		info[0].c_str(), info[0].c_str());
	mysql_query(connection, query);
	sql_result = mysql_store_result(connection);
	int check = mysql_num_rows(sql_result);

	if (check == 0)
	{
		DB_Disconnect();
		return "false";
	}

	else
	{
		apnt_profile.clear();
		while (sql_row = mysql_fetch_row(sql_result))
		{
			if (info[0] == sql_row[1])
			{
				temp += sql_row[2];
				temp += "^";
			}
			else if (info[0] == sql_row[2])
			{
				temp += sql_row[1];
				temp += "^";
			}
			temp += u_area;
			temp += "^";
			temp += sql_row[4];
			temp += "#";

			string seller = sql_row[1];
			string buyer = sql_row[2];
			if (info[0] == seller)
			{
				//buyer += "_profile.png\0";
				apnt_profile.push_back(buyer);
			}
			else if (info[0] == buyer)
			{
				//seller += "_profile.png\0";
				apnt_profile.push_back(seller);
			}
		}
		DB_Disconnect();
	}

	return temp;
}



string Carrot::B_List(vector<string> info)
{
	char query[256];
	string temp = "buyerselect$";
	//string u_area = SearchArea(info);

	// ��id, �Խñ۹�ȣ

	//���� ä���� ��� ID ��������
	//�ش� ����� ������ ��� ��������

	DB_Connect();
	//sprintf(query, "select count(*) from review where seller = '%s' or buyer = '%s'",
	//	info[0].c_str(), info[0].c_str());
	sprintf(query, "select ap_id from chat_list where id = '%s'and num = '%s'",
		info[0].c_str(), info[1].c_str());
	mysql_query(connection, query);
	sql_result = mysql_store_result(connection);
	int check = mysql_num_rows(sql_result);

	if (check == 0)
	{
		DB_Disconnect();
		return "false";
	}

	else
	{
		profilelist.clear();
		while (sql_row = mysql_fetch_row(sql_result))
		{
			temp += sql_row[0];
			temp += "^";

			string c = sql_row[0];
			profilelist.push_back(c);

			/*string seller = sql_row[1];
			string buyer = sql_row[2];
			if (info[0] == seller)
			{
				buyer += "_profile.png\0";
				apnt_profile.push_back(buyer);
			}
			else if (info[0] == buyer)
			{
				seller += "_profile.png\0";
				apnt_profile.push_back(seller);
			}*/
		}
		DB_Disconnect();
	}

	return temp;
}








string Carrot::BuyerSelect(vector<string> info)
{
	char query[256];
	string temp = "buyerselect$";
	string u_area = SearchArea(info);

	// ��id, �Խñ۹�ȣ

	//���� ä���� ��� ID ��������
	//�ش� ����� ������ ��� ��������

	DB_Connect();
	//sprintf(query, "select count(*) from review where seller = '%s' or buyer = '%s'",
	//	info[0].c_str(), info[0].c_str());
	sprintf(query, "select ap_id from chat_list where id = '%s'and num = '%s'",
		info[0].c_str(), info[1].c_str());
	mysql_query(connection, query);
	sql_result = mysql_store_result(connection);
	int check = mysql_num_rows(sql_result);

	if (check == 0)
	{
		DB_Disconnect();
		return "false";
	}

	else
	{
		apnt_profile.clear();
		while (sql_row = mysql_fetch_row(sql_result))
		{
			temp += sql_row[1];
			temp += "^";
			temp += sql_row[2];
			temp += "^";
			temp += u_area;
			temp += "^";
			temp += sql_row[4];
			temp += "#";

			string seller = sql_row[1];
			string buyer = sql_row[2];
			if (info[0] == seller)
			{
				buyer += "_profile.png\0";
				apnt_profile.push_back(buyer);
			}
			else if (info[0] == buyer)
			{
				seller += "_profile.png\0";
				apnt_profile.push_back(seller);
			}
		}
		DB_Disconnect();
	}

	return temp;
}










// �Ǹų��� - �Ϲ��Ǹ�
string Carrot::SalesList(vector<string> info)
{
	char query[256];
	string temp = "sale_sale$";
	// string u_area = SearchArea(info);
	//	int repeat = 0;
	
	DB_Connect();
	

	sprintf(query, "select * from trade where id = '%s'",
		info[0].c_str());
	mysql_query(connection, query);
	sql_result = mysql_store_result(connection);
	int check = mysql_num_rows(sql_result);

	if (check == 0)
	{
		DB_Disconnect();
		temp = "false";
		return temp;
	}


	// sales$�Խñ۹�ȣ1^�ۼ���id1^�ۼ��ڴг���1^����1^����1^�ð�1#2���Խñ�...
	// �Խñ۹�ȣ, �ۼ���ID, �ۼ��ڴг���, ����, ����, �ǸſϷῩ��, �ۼ��ð�
	// �Խñ۹�ȣ, �ۼ���ID, �ۼ��ڴг���, ����, ����, �ۼ��ð�, �ǸſϷῩ��, �ı��ۼ�����
	else
	{
		while (sql_row = mysql_fetch_row(sql_result))
		{
			temp += sql_row[0];
			temp += "^";
			temp += sql_row[2];
			temp += "^";
			temp += sql_row[3];
			temp += "^";
			temp += sql_row[4];
			temp += "^";
			temp += sql_row[6];
			temp += "^";
			temp += sql_row[8];
			temp += "^";
			temp += sql_row[7];
			temp += "^";
			temp += sql_row[9];
			temp += "#";

			/*if ((repeat % 3) == 0)
			{
				sales_list.push_back(temp);
				temp.clear();
			}*/
		}
		DB_Disconnect();
	}




	return temp;
}


// ��� �Ǹ� ���
string Carrot::AuctionList(vector<string> info)
{
	char query[256];
	string temp = "auction_sales$";
	//string u_area = SearchArea(info);

	DB_Connect();
	sprintf(query, "select * from auction where id = '%s'",
		info[0].c_str());
	mysql_query(connection, query);
	sql_result = mysql_store_result(connection);
	int check = mysql_num_rows(sql_result);

	if (check == 0)
	{
		DB_Disconnect();
		temp += "false";
		return temp;
	}


	// �Խñ۹�ȣ1^�ۼ���id^����1^����1^�ð�1^����ð�1#2���Խñ�...
	// �Խñ۹�ȣ, �ۼ���ID, �ۼ��ڴг���, ����, �����ǸŰ���, �ǸſϷῩ��, ����ð�, �ۼ��ð�
	// �Խñ۹�ȣ, �ۼ���ID, �ۼ��ڴг���, ����, �����ǸŰ���, �ۼ��ð�, ����ð�, �ǸſϷῩ��, �ı��ۼ�����
	else
	{
		while (sql_row = mysql_fetch_row(sql_result))
		{
			temp += sql_row[0];
			temp += "^";
			temp += sql_row[2];
			temp += "^";
			temp += sql_row[3];
			temp += "^";
			temp += sql_row[4];
			temp += "^";
			temp += sql_row[6];
			temp += "^";
			temp += sql_row[9];
			temp += "^";
			temp += sql_row[10];
			temp += "^";
			temp += sql_row[11];
			temp += "^";
			temp += sql_row[12];
			temp += "#";
		}
		DB_Disconnect();
	}

	return temp;
}



// �Ϲ� ���� ���
string Carrot::SalesPay(vector<string> info)
{
	char query[256];
	string temp = "sale_pay$";
	string u_area = SearchArea(info);

	DB_Connect();
	//sprintf(query, "select * from trade where area = '%s' and onsale = 'false'", u_area.c_str());
	sprintf(query, "select * from trade where area = '%s' and onsale = 'true' and buyer = '%s'", u_area.c_str(), info[0].c_str());
	mysql_query(connection, query);
	sql_result = mysql_store_result(connection);
	int check = mysql_num_rows(sql_result);

	if (check == 0)
	{
		DB_Disconnect();
		temp = "false";
		return temp;
	}


	// �Խñ۹�ȣ1^�ۼ���id^����1^����1^�ð�1^����ð�1#2���Խñ�...
	// �Խñ۹�ȣ, �ۼ���ID, �ۼ��ڴг���, ����, ����, �ǸſϷῩ��, �ۼ��ð�
	// �Խñ۹�ȣ, �ۼ���ID, �ۼ��ڴг���, ����, ����, �ۼ��ð�, �ǸſϷῩ��, �ı��ۼ�����
	else
	{
		while (sql_row = mysql_fetch_row(sql_result))
		{
			temp += sql_row[0];
			temp += "^";
			temp += sql_row[2];
			temp += "^";
			temp += sql_row[3];
			temp += "^";
			temp += sql_row[4];
			temp += "^";
			temp += sql_row[6];
			temp += "^";
			temp += sql_row[8];
			temp += "^";
			temp += sql_row[7];
			temp += "^";
			temp += sql_row[9];
			temp += "#";
		}
		DB_Disconnect();
	}

	return temp;
}



// ��� ���� ���
string Carrot::AuctionPay(vector<string> info)
{
	char query[256];
	string temp = "auction_pay$";
	string u_area = SearchArea(info);
	DB_Connect();
	sprintf(query, "select * from auction where area = '%s' and onsale = 'false'",
		u_area.c_str());
	mysql_query(connection, query);
	sql_result = mysql_store_result(connection);
	int check = mysql_num_rows(sql_result);

	if (check == 0)
	{
		DB_Disconnect();
		temp += "false";
		return temp;
	}


	// �Խñ۹�ȣ1^�ۼ���id^����1^����1^�ð�1^����ð�1#2���Խñ�...
	// �Խñ۹�ȣ, �ۼ���ID, �ۼ��ڴг���, ����, �����ǸŰ���, �ǸſϷῩ��, ����ð�, �ۼ��ð� 
	// �Խñ۹�ȣ, �ۼ���ID, �ۼ��ڴг���, ����, �����ǸŰ���,  �ۼ��ð�, ����ð�, �ǸſϷῩ��, �ı��ۼ�����

	else
	{
		while (sql_row = mysql_fetch_row(sql_result))
		{
			temp += sql_row[0];
			temp += "^";
			temp += sql_row[2];
			temp += "^";
			temp += sql_row[3];
			temp += "^";
			temp += sql_row[4];
			temp += "^";
			temp += sql_row[6];
			temp += "^";
			temp += sql_row[9];
			temp += "^";
			temp += sql_row[10];
			temp += "^";
			temp += sql_row[11];
			temp += "^";
			temp += sql_row[12];
			temp += "#";
		}
		DB_Disconnect();
	}

	return temp;
}










// �Խñ��ۼ� - �Ϲ��Ǹ�
string Carrot::NewSales(vector<string> info)
{
	char query[1024];
	string temp = "";
	//string image_path = "C:\\Users\\iot2105\\Desktop\\���\\sales\\" + info[0] + "_" + info[1] + "_";
	string image_path = "C:/Users/iot2105/Desktop/���/sales/"  + info[0] + "_" + info[1] + "_";
	int image_num = 0;
	string image_name[3];
	string num = InsertNum(0);
	string u_nick = SearchNick(info);
	if (u_nick.c_str() == "false")
	{
		return "false";
	}
	string u_area = SearchArea(info);
	if (u_area.c_str() == "false")
	{
		return "false";
	}

	int cnt = stoi(info[4]);
	for (int i = 0; i < cnt; i++)
	{
		string str = to_string(image_num) + ".png\0";
		image_name[i] = image_path + str;
		image_num++;
		cout << "image_name : " << image_name[i] << endl;
	}

	DB_Connect();
	switch (cnt)
	{
	case 1:
		sprintf(query, "insert into trade values('%s', '%s', '%s', '%s', '%s', '%s', '%s', 'false', now(), 'false', '%s', '%s', '%s', '%s')",
			num.c_str(), u_area.c_str(), info[0].c_str(), u_nick.c_str(), info[1].c_str(), info[2].c_str(), info[3].c_str(), image_name[0].c_str(), "none", "none", "none");
		break;
	case 2:
		sprintf(query, "insert into trade values('%s', '%s', '%s', '%s', '%s', '%s', '%s', 'false', now(), 'false', '%s', '%s', '%s', '%s')",
			num.c_str(), u_area.c_str(), info[0].c_str(), u_nick.c_str(), info[1].c_str(), info[2].c_str(), info[3].c_str(), image_name[0].c_str(), image_name[1].c_str(), "none", "none");
		break;
	case 3:
		sprintf(query, "insert into trade values('%s', '%s', '%s', '%s', '%s', '%s', '%s', 'false', now(), 'false', '%s', '%s', '%s', '%s')",
			num.c_str(), u_area.c_str(), info[0].c_str(), u_nick.c_str(), info[1].c_str(), info[2].c_str(), info[3].c_str(), image_name[0].c_str(), image_name[1].c_str(), image_name[2].c_str(), "none");
		break;
	default:
		return "false";
		break;
	}

	cout << query << endl;
	// ��id^ ����^ ����^ �ǸŰ���^ �̹�������
	// num, area, id, nickname, title, context, price, onsale, image123
	/*sprintf(query, "insert into trade values('%s', '%s', '%s', '%s', '%s', 'on', '%s', '%s', '%s')",
		num.c_str(), info[1].c_str(), u_nick.c_str(), info[2].c_str(), info[3].c_str(), "none", "none", "none");*/

	mysql_query(connection, query);
	//sql_result = mysql_store_result(connection);
	/*check = mysql_num_rows(sql_result);

	if (check == 0)
	{
		DB_Disconnect();
		return "false";
	}*/

	DB_Disconnect();
	temp = "true";
	return temp;
}


// �Խñ��ۼ� - ���
string Carrot::NewAuction(vector<string> info, int sock)
{
	char query[256];
	string temp = "";
	//string image_path = "C:\\Users\\iot2105\\Desktop\\���\\auction\\" + info[0] + "_" + info[1] + "_";
	string image_path = "C:/Users/iot2105/Desktop/���/auction/" + info[0] + "_" + info[1] + "_";
	int image_num = 0;
	string image_name;
	string num = InsertNum(1);
	cout << "num : " << num << endl;
	string u_nick = SearchNick(info);
	if (u_nick.c_str() == "false")
	{
		return "false";
	}

	string u_area = SearchArea(info);
	if (u_area.c_str() == "false")
	{
		return "false";
	}

	//int cnt = stoi(info[7]);
	/*for (int i = 0; i < cnt; i++)
	{
		string str = to_string(image_num);
		str += ".png\0";
		image_name += image_path + str + "^";
		image_num++;
		cout << "image_name : " << image_name << endl;
	}*/



	DB_Connect();
	int timer = stoi(info[6]);
	
	// ��id^����^����^�ּҰ���^���۰���^��������^���ѽð�^�̹�������
	// num, area, nick, title, context, start_price, min_price, unit, timer, onsale
	sprintf(query, "insert into auction values('%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', NOW(), DATE_ADD(NOW(), interval %d minute), 'false', 'false', 'none', '%s')",
		num.c_str(), u_area.c_str(), info[0].c_str(), u_nick.c_str(), info[1].c_str(), info[2].c_str(), info[4].c_str(), info[3].c_str(), info[5].c_str(), timer, info[7].c_str());
	mysql_query(connection, query);

	cout << query << endl;

	sql_result = mysql_store_result(connection);
	
	//// ����ο�����
	//sprintf(query, "insert into auction_tbl values('%s', '%d', '%s',)",
	//	num.c_str(), sock, u_nick.c_str());
	//mysql_query(connection, query);
	//sql_result = mysql_store_result(connection);

	DB_Disconnect();
	temp = "true";
	return temp;
}



// ����� - ����
void Carrot::AucBid(vector<string> info, int sock)
{
	char query[256];
	string temp;
	//string num = InsertNum(1);
	//string u_nick = SearchNick(info);	
	vector<int> fds;

	DB_Connect();
	
	sprintf(query, "select fd from auction_tbl where num = '%s'", info[2].c_str());
	mysql_query(connection, query);
	sql_result = mysql_store_result(connection);
	
	int check = mysql_num_rows(sql_result);
	if (check == 0)
	{
		DB_Disconnect();
		temp = "false";
		send(sock, temp.c_str(), strlen(temp.c_str()), 0);
		return;
	}

	else
	{
		fds.clear();
		while (sql_row = mysql_fetch_row(sql_result))
		{
			int fd = stoi(sql_row[0]);
			fds.push_back(fd);
		}
	}

	sprintf(query, "update auction set input_id = '%s', start_price = '%s' where num = '%s'", info[0].c_str(), info[1].c_str(), info[2].c_str());
	mysql_query(connection, query);
	DB_Disconnect();

	temp = "bid$" + info[0] + "^" + info[1];

	for (int i : fds)
	{
		cout << "sock : " << sock << endl;
		cout << temp << endl;
		send(i, temp.c_str(), strlen(temp.c_str()), 0);
	}
	

	return;
	
}


// ����� - ä��
string Carrot::AucChat(vector<string> info)
{
	char query[256];
	string temp = "";
	string num = InsertNum(1);
	string u_nick = SearchNick(info);
	if (u_nick.c_str() == "false")
	{
		return "false";
	}

	/*
	DB_Connect();
	sprintf(query, "select fd from auction_tbl");
	mysql_query(connection, query);
	sql_result = mysql_store_result(connection);

	int check = mysql_num_rows(sql_result);
	if (check == 0)
	{
		DB_Disconnect();
		return "false";
	}

	else
	{
		auction_fd.clear();
		while (sql_row = mysql_fetch_row(sql_result))
		{
			int fd = stoi(sql_row[0]);
			auction_fd.push_back(fd);
		}
		DB_Disconnect();
	}


	*/

	return temp;

}


// ����� - ������
void Carrot::AucQuiting(vector<string> info)
{
	//bid_exit
	char query[256];
	/*string temp = "";
	string num = InsertNum(1);
	string u_nick = SearchNick(info);
	if (u_nick.c_str() == "false")
	{
		return;
	}*/

	
	DB_Connect();
	sprintf(query, "delete from auction_tbl where id = '%s'", info[0].c_str());
	mysql_query(connection, query);
	sql_result = mysql_store_result(connection);
	DB_Disconnect();

	/*int check = mysql_num_rows(sql_result);
	if (check == 0)
	{
		DB_Disconnect();
		return;
	}

	else
	{
		auction_fd.clear();
		while (sql_row = mysql_fetch_row(sql_result))
		{
			int fd = stoi(sql_row[0]);
			auction_fd.push_back(fd);
		}
		DB_Disconnect();
	}*/

	

	return;

}



// �������
void Carrot::AuctionEnd(vector<string> info)
{
	//bid_exit
	char query[256];

	DB_Connect();
	sprintf(query, "delete from auction_tbl where num = '%s'", info[0].c_str());
	mysql_query(connection, query);
	//sql_result = mysql_store_result(connection);

	sprintf(query, "update auction set onsale = 'true' where num = '%s'", info[0].c_str());
	mysql_query(connection, query);


	DB_Disconnect();

	return;

}














void Carrot::convertToASCII(string letter, string e, int* myid, int* yourid)// �α����� txt����
{
	for (int i = 0; i < letter.length(); i++)
	{
		char x = letter.at(i);
		*myid = int(x);
	}

	for (int i = 0; i < e.length(); i++)
	{
		char x = e.at(i);
		*yourid = int(x);
	}
}

string Carrot::time_output() //�ð����
{
	time_t timer = time(NULL);
	struct tm* t = localtime(&timer);
	string current_time;
	int hour = t->tm_hour;
	int min = t->tm_min;


	string time_out = to_string(hour) + ":" + to_string(min);
	return time_out;

}





void Carrot::ChatIn(vector<string> info, int sock)
{

	cout << "ä�� - �α�" << endl;
	//send_msg = NewAuction(info, C_sock);

	//string nic_A; //�޾ƿ� �г��� 1
	//string nic_B; //�޾ƿ� �г��� 2
	//nic_A = info[0];
	//nic_B = info[1];

	//fstream file;
	string data; // �޾ƿ� ������x
	data = info[1];
	int myid, yourid;
	convertToASCII(info[0], info[1], &myid, &yourid);
	string file_name = "C:/Users/iot2105/Desktop/���/chat/"; // �޾ƿ� �г��� 1,2�� ���ļ� txt���Ϸ� ����

	if (myid > yourid)
		file_name += info[0] + info[1] + ".txt\0";
	else if (myid <= yourid)
		file_name += info[1] + info[0] + ".txt\0";

	cout << file_name << endl;


	//file.open(file_name, ios::app); 
	// ���� �̾��
	/*
	if (file.is_open())
	{

		file << data << "&";
		file << msg << "&";
		file << time_output() << "@" << endl;
	}
	file.close();
	*/
	ifstream file;
	
	file.open(file_name);

	if (!(file.is_open()))
	{
		cout << "1111111111111111111111111111111111111111111111111111" << endl;
		ofstream writhfile(file_name);
		writhfile.close();
		file.close();


		// chat_list ���̺�
		char query[255];
		string number;
		string title;
		string price;

		DB_Connect();
		sprintf(query, "select num, title, price from trade where id = '%s' and title = '%s'", info[1].c_str(), info[2].c_str());
		mysql_query(connection, query);
		sql_result = mysql_store_result(connection);
		int check = mysql_num_rows(sql_result);
		if (check == 0)
		{
			DB_Disconnect();
			return;
		}

		else
		{
			while (sql_row = mysql_fetch_row(sql_result))
			{
				number = sql_row[0];
				title = sql_row[1];
				price = sql_row[2];
			}
		}


		sprintf(query, "insert into chat_list values('%s', '%s', '%s', '%s', '%s')", number.c_str(), info[0].c_str(), info[1].c_str(), title.c_str(), price.c_str());
		mysql_query(connection, query);
		sql_result = mysql_store_result(connection);

		cout << query << endl;

		sprintf(query, "insert into chat_list values('%s', '%s', '%s', '%s', '%s')", number.c_str(), info[1].c_str(), info[0].c_str(), title.c_str(), price.c_str());
		mysql_query(connection, query);
		sql_result = mysql_store_result(connection);

		DB_Disconnect();


		fstream file2;
		file2.open(file_name);
		if (file2.is_open())
		{
			string data = "\n" + info[0] + "&" + "*" + "&" + time_output() + "@";
			file2 << data;
		}
		file2.close();
		file2.open(file_name);
		file2.close();



		file.open(file_name, ios_base::app);

	}

	string line = "chatlog$";
	string temp = "";

	cout << "����Ž�� ����" << endl;
	while (!file.eof()) // ���� ������ Ž���ؼ� ���
	{
		temp.clear();
		getline(file, temp);
		line += temp;
		cout << line << endl;
	}


	file.close();
	file.open(file_name);
	file.close();
	cout << "����Ž�� ��" << endl;
	int len = send(sock, line.c_str(), strlen(line.c_str()), 0);
	cout << "hi" << len << endl;


	

	cout << "����ֱ�" << endl;

}

void Carrot::ChatOnO(vector<string> info, int sock)
{
	info[0]; //�����̵�
	info[1]; //�����̵�
	info[2]; //ä��
	char query[255];
	DB_Connect();
	sql_result = mysql_store_result(connection);
	sprintf(query, "update chat_tbl set login=1, fd = '%d' where id = '%s'", sock, info[0].c_str());
	int check2 = mysql_query(connection, query);
	sql_result = mysql_store_result(connection);
	
	cout << query << endl;

	sprintf(query, "select fd, login from chat_tbl where id = '%s'",info[1].c_str());
	mysql_query(connection, query);


	sql_result = mysql_store_result(connection);
	int check = mysql_num_rows(sql_result);
	int a;
	int fd;
	if (check == 0)
	{
		DB_Disconnect();
		return;
	}

	else
	{
		while (sql_row = mysql_fetch_row(sql_result))
		{
			fd = stoi(sql_row[0]);
			a = stoi(sql_row[1]);
		}
		DB_Disconnect();
	}
	
	string read_msg = "chat$" + info[0] + "^" + info[2] + "^" + time_output();
	cout << read_msg << endl;
	cout << "sock : " << sock << endl;
	cout << "a_sock : " << a << endl;
	if (a == 1)
	{
		send(sock, read_msg.c_str(), strlen(read_msg.c_str()), 0);
		send(fd, read_msg.c_str(), strlen(read_msg.c_str()), 0);
	}
	else
	{
		send(sock, read_msg.c_str(), strlen(read_msg.c_str()), 0);
	}

	//string temp2 = "\n" + info[0] + "&" + info[2] + "&" + time_output() + "@";
	//string data = temp2.substr(0, temp2.size() - 1);
	string data = "\n" + info[0] + "&" + info[2] + "&" + time_output() + "@";




	fstream file;
	int myid, yourid;
	convertToASCII(info[0], info[1], &myid, &yourid);
	string file_name = "C:/Users/iot2105/Desktop/���/chat/"; // �޾ƿ� �г��� 1,2�� ���ļ� txt���Ϸ� ����

	if (myid > yourid)
		file_name += info[0] + info[1] + ".txt\0";
	else if (myid <= yourid)
		file_name += info[1] + info[0] + ".txt\0";

	file.open(file_name, ios::app);           // ���� �̾��
	if (file.is_open())
		file << data;
	file.close();
}



void Carrot::Chat_list(vector<string> info, int sock) //ä�� ���
{

	string path = "C:/Users/iot2105/Desktop/���/chat/*.txt";

	struct _finddata_t fd;
	intptr_t handle;
	string data; //��ȭ�� �̸�
	int cnt = 0; //ä�ù� ����
	
	if ((handle = _findfirst(path.c_str(), &fd)) == -1L)

		cout << "ä�ù����" << endl;
	do

	{

		cout << fd.name << endl;
		data += fd.name;
		cnt++;
	} while (_findnext(handle, &fd) == 0);

	cout << data;  //txt �� �߶��ְ�
	cout << cnt;
	_findclose(handle);
	cout << "ä�� - ���" << endl;
	fstream file;
	char query[255];
	int myid, yourid;
	convertToASCII(info[0], info[1], &myid, &yourid);
	string dif_id;
	DB_Connect();
	sprintf(query, "select id from chat_tbl");
	mysql_query(connection, query);
	sql_result = mysql_store_result(connection);
	int check = mysql_num_rows(sql_result);
	if (check == 0)
	{
		DB_Disconnect();
	}

	else
	{
		while (sql_row = mysql_fetch_row(sql_result))
		{
			cout << sql_row[0] << endl;
			dif_id = sql_row[0];
		}
	}

	string line = "chat_list$";
	string last_msg;
	for (int i = 0; i <= file.eof(); i++)
	{
		string temp;
		cout << line << endl;
		if (i == file.eof())
		{
			getline(file, temp);
			line += temp;
		}

	};
	//cout << " ���Ȯ��" << line << endl;
	int len = send(sock, line.c_str(), strlen(line.c_str()), 0);
	//cout << "hi" << len << endl;

	file.close();
	DB_Disconnect();

}


// ä�� ���
string Carrot::Chat_list(string my_id, string u_id, int sock) 
{

	string path = "C:/Users/iot2105/Desktop/���/chat/*.txt";

	struct _finddata_t fd;
	intptr_t handle;
	string data; //��ȭ�� �̸�
	int cnt = 0; //ä�ù� ����

	if ((handle = _findfirst(path.c_str(), &fd)) == -1L)

		cout << "ä�ù����" << endl;
	do

	{

		cout << fd.name << endl;
		data += fd.name;
		cnt++;
	} while (_findnext(handle, &fd) == 0);


	cout << data;  //txt �� �߶��ְ�
	cout << cnt;
	_findclose(handle);
	cout << "ä�� - ���" << endl;

	fstream file;
	char query[255];
	int myid, yourid;
	convertToASCII(my_id, u_id, &myid, &yourid);
	string dif_id;

	DB_Connect();
	sprintf(query, "select id from chat_tbl");
	mysql_query(connection, query);
	sql_result = mysql_store_result(connection);
	int check = mysql_num_rows(sql_result);
	if (check == 0)
	{
		DB_Disconnect();
	}

	else
	{
		while (sql_row = mysql_fetch_row(sql_result))
		{
			cout << sql_row[0] << endl;
			dif_id = sql_row[0];
		}
	}


	DB_Disconnect();

	string filename = "C:/Users/iot2105/Desktop/���/chat/" + my_id + u_id + ".txt\0";
	file.open(filename);

	if (!(file.is_open()))
	{
		file.close();
		filename = "C:/Users/iot2105/Desktop/���/chat/" + u_id + my_id + ".txt\0";
		file.open(filename);
	}

	string line = "";
	string last_msg;

	//for (int i = 0; i <= file.eof(); i++)
	//{
	//	string temp;
	//	cout << line << endl;
	//	if (i == file.eof())
	//	{
	//		getline(file, temp);
	//		//line += temp;
	//		line = temp;
	//	}

	//};

	cout << filename << endl;

	string temp;
	cout << "����Ž�� ����" << endl;
	while (!file.eof()) // ���� ������ Ž���ؼ� ���
	{
		getline(file, line);
		temp = line;
		//cout << temp << endl;
	}
	cout << " ���Ȯ��" << temp << endl;
	
	vector<string> t = Split(temp, "&");


	file.close();
	file.open(filename);
	file.close();

	if (t.size() < 1)
		return " ";
	else
		return t[1];

	/*int len = send(sock, line.c_str(), strlen(line.c_str()), 0);
	cout << "hi" << len << endl;*/


}














void Carrot::ChatEnter(vector<string> info, int sock)
{
	char query[256];

	DB_Connect();
	sprintf(query, "update chat_tbl set fd = '%d', login = '1' where id = '%s'",
		sock, info[0].c_str());
	mysql_query(connection, query);
	sql_result = mysql_store_result(connection);
	// int check = mysql_num_rows(sql_result);

	cout << query << endl;

	DB_Disconnect();

	return;
}


void Carrot::ChatOut(vector<string> info)
{
	char query[256];

	DB_Connect();
	sprintf(query, "update chat_tbl set login = '0' where id = '%s'",
		info[0].c_str());
	mysql_query(connection, query);
	sql_result = mysql_store_result(connection);
	// int check = mysql_num_rows(sql_result);

	DB_Disconnect();

	return;
}







string Carrot::ChatList(vector<string> info)
{
	// ��^������̵�^�������޼���^����^����
	char query[256];
	string temp = "chat_list$";
	string num;
	DB_Connect();
	
	sprintf(query, "select ap_id, title, price from chat_list where id = '%s'",
		info[0].c_str());
	mysql_query(connection, query);
	MYSQL_RES* sql_result2 = mysql_store_result(connection);
	MYSQL_ROW sql_row2;
	int check = mysql_num_rows(sql_result2);

	cout << query << endl;

	if (check == 0)
	{
		DB_Disconnect();
		return "false";
	}


	else
	{
		while (sql_row2 = mysql_fetch_row(sql_result2))
		{
			//cout << sql_row2[0] << sql_row2[1] << sql_row2[2] <<sql_row2[3];
			temp += sql_row2[0];
			temp += "^";
			temp += Chat_list(info[0], sql_row2[0], 0);
			temp += "^";
			temp += sql_row2[1];
			temp += "^";
			temp += sql_row2[2];
			temp += "@";
		}
	}

	DB_Disconnect();

	return temp;
}








// �г��� ã��
string Carrot::SearchNick(vector<string> info)
{
	char query[256];
	string u_nick;

	DB_Connect();
	// �г��� ã�Ƽ� ����
	sprintf(query, "select nickname from customer where id = '%s'",
		info[0].c_str());
	mysql_query(connection, query);
	sql_result = mysql_store_result(connection);
	int check = mysql_num_rows(sql_result);

	if (check == 0)
	{
		DB_Disconnect();
		return "false";
	}

	else
	{
		while (sql_row = mysql_fetch_row(sql_result))
		{
			cout << sql_row[0] << endl;
			u_nick = sql_row[0];
		}
	}

	DB_Disconnect();
	cout << "�г� : " << u_nick << endl;
	return u_nick;
}

// ���� ã��
string Carrot::SearchArea(vector<string> info)
{
	char query[256];
	string u_area;

	// ���̵�� ����ã��
	DB_Connect();
	sprintf(query, "select area from customer where id = '%s'", info[0].c_str());
	mysql_query(connection, query);
	sql_result = mysql_store_result(connection);
	int check = mysql_num_rows(sql_result);
	if (check == 0)
	{
		DB_Disconnect();
		return "false";
	}

	else
	{
		while (sql_row = mysql_fetch_row(sql_result))
		{
			cout << sql_row[0] << endl;
			u_area = sql_row[0];
		}
	}
	DB_Disconnect();

	cout << "���� : " << u_area << endl;
	return u_area;
}



// �ۼ��� ������ ã��
string Carrot::FindProfile(string num, string dir)
{
	char query[256];
	string u_id;

	// ���̵�� ����ã��
	DB_Connect();

	if (dir == "sales")
		sprintf(query, "select id from trade where num = '%s'", num.c_str());
	else if (dir == "auction")
		sprintf(query, "select id from auction where num = '%s'", num.c_str());

	cout << "���� : " << query << endl;

	mysql_query(connection, query);
	sql_result = mysql_store_result(connection);
	int check = mysql_num_rows(sql_result);

	if (check == 0)
	{
		DB_Disconnect();
		return "false";
	}

	else
	{
		while (sql_row = mysql_fetch_row(sql_result))
		{
			cout << sql_row[0] << endl;
			u_id = sql_row[0];
		}
	}
	DB_Disconnect();

	cout << "���̵� : " << u_id << endl;
	u_id += "_profile.png\0";
	return u_id;
}

// �����̸� ã��
string Carrot::FindFile(string num, string dir)
{
	char query[256];
	string temp;

	DB_Connect();

	if (dir == "sales")
		sprintf(query, "select id, title from trade where num = '%s'",num.c_str());
	else if (dir == "auction")
		sprintf(query, "select id, title from auction where num = '%s'", num.c_str());

	mysql_query(connection, query);
	sql_result = mysql_store_result(connection);
	int check = mysql_num_rows(sql_result);

	if (check == 0)
	{
		DB_Disconnect();
		return "false";
	}

	else
	{
		while (sql_row = mysql_fetch_row(sql_result))
		{
			cout << sql_row[0] << endl;
			temp += sql_row[0];
			temp += "_";
			temp += sql_row[1];
			temp += "_";
		}
	}
	DB_Disconnect();

	return temp;
}






// ��Ʈ���� ����
string Carrot::OnAir(vector<string> info, int sock)
{
	char query[256];
	string temp = "OnAir$";
	string temp2 = "Play$";
	//string udp = "udp://@239.0.0.0:4000";

	int ip = UDP_Adr.size();

	sprintf(query, "udp://239.0.0.%d:4000", ip);
	string udp = query;
	temp += udp;
	

	sprintf(query, "udp://@239.0.0.%d:4000", ip);
	udp = query;
	temp2 += udp;

	// 
	UDP_Adr.push_back(udp);
	cout << "UDP : " << udp << endl;

	DB_Connect();
	sprintf(query, "select fd, login from chat_tbl where id = '%s'", info[1].c_str());
	mysql_query(connection, query);

	cout << query << endl;

	sql_result = mysql_store_result(connection);
	int check = mysql_num_rows(sql_result);
	int a;
	int fd;
	if (check == 0)
	{
		DB_Disconnect();
		return "false";
	}

	else
	{

		while (sql_row = mysql_fetch_row(sql_result))
		{
			fd = stoi(sql_row[0]);
			a = stoi(sql_row[1]);

		}
		DB_Disconnect();
	}

	//string read_msg = "chat$" + info[0] + "^" + info[2] + "^" + time_output();
	//cout << read_msg << endl;
	cout << "sock : " << sock << endl;
	cout << "a_sock : " << a << endl;
	if (a == 1)
	{
		send(sock, temp.c_str(), strlen(temp.c_str()), 0);
		send(fd, temp2.c_str(), strlen(temp2.c_str()), 0);
	}
	else
	{
		send(sock, temp.c_str(), strlen(temp.c_str()), 0);
	}




	return temp;
}



// ��Ʈ���� ����
string Carrot::EndStream(vector<string> info, int sock)
{
	char query[256];
	string temp = "EndStreaming$";
	string temp2 = "Play$";
	//string udp = "udp://@239.0.0.0:4000";



	/*sprintf(query, "udp://239.0.0.%d:4000", UDP_Adr.size());
	string udp = query;
	temp += udp;


	sprintf(query, "udp://@239.0.0.%d:4000", UDP_Adr.size());
	udp = query;
	temp2 += udp;*/

	// 
	//UDP_Adr.push_back(udp);
	//cout << "UDP : " << udp << endl;

	//DB_Connect();
	//sprintf(query, "select fd, login from chat_tbl where id = '%s'", info[1].c_str());
	//mysql_query(connection, query);

	//cout << query << endl;

	//sql_result = mysql_store_result(connection);
	//int check = mysql_num_rows(sql_result);
	//int a;
	//int fd;
	//if (check == 0)
	//{
	//	DB_Disconnect();
	//	return "false";
	//}

	//else
	//{
	//	while (sql_row = mysql_fetch_row(sql_result))
	//	{
	//		fd = stoi(sql_row[0]);
	//		a = stoi(sql_row[1]);
	//	}
	//	DB_Disconnect();
	//}

	////string read_msg = "chat$" + info[0] + "^" + info[2] + "^" + time_output();
	////cout << read_msg << endl;
	//cout << "sock : " << sock << endl;
	//cout << "a_sock : " << a << endl;

	//if (a == 1)
	//{
	//	send(sock, temp.c_str(), strlen(temp.c_str()), 0);
	//	send(fd, temp.c_str(), strlen(temp.c_str()), 0);
	//}
	//else
	//{
	//	send(sock, temp.c_str(), strlen(temp.c_str()), 0);
	//}




	return temp;
}




















void Carrot::Send_Image(vector<string> info, int cnt, string dir, int clnt_sock)
{
	//=================================================================
	//====================== C++ ����, C# Ŭ�� =========================
	//===================== ���� ���� -> Ŭ�� �ޱ� =====================
	//=================================================================
	// ���ϻ����� ���� --> ���ۿ��� �ޱ� --> ���ϵ����� ���� --> ���ۿ��� �ޱ�

	int image_num = cnt;
	//for (int i = 0; i < cnt; i++)
	//{
		//image_num++;

		

		string path;
		string str;
		string image_name;
		
		// ��id_����_�̹�����ȣ
		if (dir == "profile")
		{
			cout << "������ �̹���" << endl;
			//path = "C:\\Users\\iot2105\\Desktop\\���\\profile\\" + image_name;
			image_name += info[0].c_str();
			image_name += "_profile.png\0";
			path = "C:/Users/iot2105/Desktop/���/profile/" + image_name;
			cout << path << endl;

		}
		else if (dir == "sales")
		{
			str = to_string(image_num);
			image_name = info[1] + str + ".png\0";
			path = "C:/Users/iot2105/Desktop/���/sales/" + image_name;

		}
		else if (dir == "auction")
		{
			//path = "C:\\Users\\iot2105\\Desktop\\���\\auction\\" + image_name;
			path = "C:/Users/iot2105/Desktop/���/auction/" + image_name;

		}

		else if (dir == "sales_detail")
		{
			// += id += ���� += �̹�����ȣ
			str = to_string(image_num);
			image_name = FindFile(info[0], "sales");
			image_name += str;
			image_name += ".png\0";
			path = "C:/Users/iot2105/Desktop/���/sales/" + image_name;
		}

		else if (dir == "auction_detail")
		{
			// += id += ���� += �̹�����ȣ
			str = to_string(image_num);
			image_name = FindFile(info[1], "auction");
			image_name += str;
			image_name += ".png\0";
			path = "C:/Users/iot2105/Desktop/���/auction/" + image_name;
		}


		cout << "�̹��� ��� : " << path << endl;
		

		FILE* fp = fopen(path.c_str(), "rb");		//���� �Ű������� const char* �� �� ����


		// ��� ���н� ����
		if (fp == NULL)
		{
			cout << "File open failed" << endl;
			return;
		}

		// ���� ���� ���
		fseek(fp, 0, SEEK_END);
		int size = ftell(fp);
		fseek(fp, 0, SEEK_SET);
		// ���� �����͸� �о�´�.
		unsigned char* data = new unsigned char[size];
		fread(data, 1, size, fp);
		// ���� ���ҽ� �ݱ�
		fclose(fp);



		char recv_data[BUFFERSIZE];

		// ���� ������ ����
		send(clnt_sock, (char*)&size, 4, 0);
		recv(clnt_sock, recv_data, sizeof(recv_data), 0);
		cout << "file size : " << size << endl;
		cout << recv_data << endl;


		// ���� ������ ����
		send(clnt_sock, (char*)data, size, 0);
		recv(clnt_sock, recv_data, sizeof(recv_data), 0);
		cout << recv_data << endl;
	//}
}



void Carrot::Send_Image(string filename, string dir, int cnt, int clnt_sock)
{
	string path;
	string str;
	string image_name;

	// ��id_����_�̹�����ȣ

	if (dir == "sales")
	{
		if (cnt != -1)
		{
			str = to_string(cnt);
			image_name = filename + "_" + str + ".png\0";
		}
		else
		{
			image_name = filename;
		}
		path = "C:/Users/iot2105/Desktop/���/sales/" + image_name;

	}
	else if (dir == "auction")
	{
		if (cnt != -1)
		{
			str = to_string(cnt);
			image_name = filename + "_" + str + ".png\0";
		}
		else
		{
			image_name = filename;
		}
		path = "C:/Users/iot2105/Desktop/���/auction/" + image_name;
	}

	else if (dir == "profile")
	{
		if (cnt == -2)
		{
			image_name = filename;
			image_name += "_profile.png\0";
		}
		else if (cnt != -1)
		{
			str = to_string(cnt);
			image_name = filename + "_" + str + ".png\0";
		}
		else
		{
			image_name = filename;
		}
		path = "C:/Users/iot2105/Desktop/���/profile/" + image_name;
	}


	cout << "�̹��� ��� : " << path << endl;


	FILE* fp = fopen(path.c_str(), "rb");		//���� �Ű������� const char* �� �� ����


	// ��� ���н� ����
	if (fp == NULL)
	{
		cout << "File open failed" << endl;
		return;
	}

	// ���� ���� ���
	fseek(fp, 0, SEEK_END);
	int size = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	// ���� �����͸� �о�´�.
	unsigned char* data = new unsigned char[size];
	fread(data, 1, size, fp);
	// ���� ���ҽ� �ݱ�
	fclose(fp);



	char recv_data[BUFFERSIZE];

	// ���� ������ ����
	send(clnt_sock, (char*)&size, 4, 0);
	recv(clnt_sock, recv_data, sizeof(recv_data), 0);
	cout << "file size : " << size << endl;
	cout << recv_data << endl;


	// ���� ������ ����
	send(clnt_sock, (char*)data, size, 0);
	recv(clnt_sock, recv_data, sizeof(recv_data), 0);
	cout << recv_data << endl;
	//}
}









void Carrot::Recv_Image(string dir)
{
	// �������� ������ ����
	int size;
	// ������ ���丮
	wchar_t buffer[BUFFERSIZE] = L"C:\\Users\\iot2105\\Desktop\\carrot\\profile\\";
	
	
	//setlocale(LC_ALL, "");

		
	if (dir == "profile")
	{
		cout << "������" << endl;
		wchar_t source[BUFFERSIZE] = L"C:\\Users\\iot2105\\Desktop\\���\\profile\\";
		wcscpy(buffer, source);
	}
	else if (dir == "sales")
	{
		cout << "�Ϲ�" << endl;
		wchar_t source[BUFFERSIZE] = L"C:\\Users\\iot2105\\Desktop\\���\\sales\\";
		wcscpy(buffer, source);
	}
	else if (dir == "auction")
	{
		cout << "���" << endl;
		wchar_t source[BUFFERSIZE] = L"C:\\Users\\iot2105\\Desktop\\���\\auction\\";
		wcscpy(buffer, source);
	}

	
	
	// buffer[BUFFERSIZE] = L"C:\\Users\\iot2105\\Desktop\\���\\profile\\";			//���� ��ġ �ٲ��ֱ�
	// ������ ���ϸ� ����
	wchar_t filename[BUFFERSIZE];

	// �����͸� �޴´�.
	unsigned char* data = Recv_Data(&size);

	// ù��°�� ���ϸ��̴�. �̹����� C#���� unicode���� �ƴ� utf8�������� ���ϸ��� ���´�.
	// c++������ unicode�� �ٷ�� ������ ��ȯ�� �ʿ��ϴ�. (MB_ERR_INVALID_CHARS)
	MultiByteToWideChar(CP_UTF8, 0, (const char*)data, size, filename, BUFFERSIZE);



	// ���� �����͸� �޸𸮿��� ����
	delete data;
	// ���丮 + ���ϸ�
	wcscat(buffer, filename);
	// �����͸� �ٽ� �޴´�. �̹��� ���ε��ϴ� ���� �������̴�.
	data = Recv_Data(&size);
	// ������ ���� ��ü�� �޴´�.
	FILE* fp = _wfopen(buffer, L"wb");
	if (fp != NULL)
	{
		// ���� ����
		fwrite(data, 1, size, fp);
		fclose(fp);

		cout << "�������� �Ϸ�!" << endl;
	}
	else
	{
		cout << "File store failed" << endl;
	}
}






unsigned char* Carrot::Recv_Data(int* size)
{
	char send_data[BUFFERSIZE];		//������ �� �޾Ҵٴ� ��ȣ
	strcpy(send_data, "true");
	
	


	// ó������ �������� ����� �´�. C++�� C#�� �⺻������ �� ������̱� ������ ����� ��ȯ�� �ʿ����.
	// char*�� 4����Ʈ�� �޾ƹ����� int���� �ȴ�.
	if (recv(clnt_sock, (char*)size, 4, 0) == SOCKET_ERROR)
	{
		cout << "error" << endl;
		return nullptr;
	}
	send(clnt_sock, send_data, sizeof(send_data), 0);


	// �����͸� unsigned char�������� �޴´�. =byte
	unsigned char* buffer = new unsigned char[*size];
	if (recv(clnt_sock, (char*)buffer, *size, 0) == SOCKET_ERROR)
	{
		cout << "error" << endl;
		return nullptr;
	}
	send(clnt_sock, send_data, sizeof(send_data), 0);

	// ���� �����͸� �����Ѵ�.
	return buffer;
}




string Carrot::InsertNum(int chk)
{
	char query[256];
	char st[10];
	string temp;
	int number = 0;

	DB_Connect();

	if (chk == 0)
		sprintf(query, "select num from trade order by num desc limit 1");
	else if (chk == 1)
		sprintf(query, "select num from auction order by num desc limit 1");

	mysql_query(connection, query);
	sql_result = mysql_store_result(connection);
	int check = mysql_num_rows(sql_result);

	if (check == 0)
	{
		DB_Disconnect();
		return "1";
	}

	else
	{
		while (sql_row = mysql_fetch_row(sql_result))
		{
			cout << sql_row[0] << endl;
			temp = sql_row[0];
			number = stoi(temp);
		}
	}
	DB_Disconnect();
	number++;
	itoa(number, st, 10);
	temp = st;
	cout << "num : " << temp << endl;
	return temp;
	
}



vector<string> Carrot::Split(string s, string divid)
{
	vector<string> v;
	char* c = strtok((char*)s.c_str(), divid.c_str());
	while (c)
	{
		v.push_back(c);
		c = strtok(NULL, divid.c_str());
	}
	return v;
}