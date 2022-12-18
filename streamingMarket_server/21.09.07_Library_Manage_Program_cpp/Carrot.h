#pragma once

#ifndef _Function_
#define _Function_

#include "TCP_DB.h"


class Carrot : public TCP, public DB
{
	private:
		vector<string> sales_list;
		vector<string> apnt_profile;
		vector<string> profilelist;
		vector<int> auction_fd;
		
		vector<string> UDP_Adr;


	public:
		//����
		Carrot()
		{ 
			connection = NULL;
			mysql_init(&conn);
		}
		~Carrot()	{ mysql_close(&conn); }



		//������ ����
		void	Start_thread();
		void	*_thread(void *sock);
		vector<string> Split(string s, string divid);





		string InsertNum(int chk);						// �Խñ� ��ȣ ã��
		
		string SearchNick(vector<string> info);			// �г��� ã��
		string SearchArea(vector<string> info);			// ���� ã��

		string Login(vector<string> v);					// �α���(login)
		string Enroll(vector<string> v, int sock);				// ȸ������(enroll)



		string Sales(vector<string> info);						// �Ϲ��Ǹ� ���(sales)
		string NewSales(vector<string> info);					// �Խñ��ۼ� - �Ϲ��Ǹ�(new_sales)
		string SalesDetails(vector<string> info);				// �Ϲ��Ǹ� - �Խñ�Ŭ��(sales_detail)
		int SalesImageNum_Num(vector<string> info);				// �Ϲ��Ǹ� - �Խñ� �̹��� ��
		

		string Auction(vector<string> info);					// ����Ǹ� ���(auction)
		string NewAuction(vector<string> info, int sock);		// �Խñ��ۼ� - ����Ǹ�(new_auction)
		int AuctionImageNum(vector<string> info);				// ��� - �Խñ� �̹��� �� 
		string AuctionDetails(vector<string> info, int sock);	// ��� - �Խñ�Ŭ��(auction_detail)
		
		int ImageNum_ID(vector<string> info, string tbl);		// �Խñ� �̹��� �� ID




		//==========================================================================================

		string SalesList(vector<string> info);			// �Ǹ� ���� - �Ϲ��Ǹ�(sale_sale)
		string AuctionList(vector<string> info);		// �Ǹ� ���� - ����Ǹ�(auction_sale)

		string SalesPay(vector<string> info);			// ���� ���� - �Ϲ��Ǹ�(sale_pay)
		string AuctionPay(vector<string> info);			// ���� ���� - ����Ǹ�(auction_pay)

	


		string MySales(vector<string> info);			// �� �ǸŸ��(my_sales)
		string MyDeal(vector<string> info);				// �Ϸ� �ŷ����(my_deal)
		string MyProfile(vector<string> info);			// �� ������ ����(profile)
														// �� ������ ����(Myprofile)





		void Review(vector<string> info, string type);	// �ŷ��ı� �ۼ�(review)
		string YourReview(vector<string> info);			// �ŷ��ı� ����(your_review)
		int ReviewCount(vector<string> info);			// �ŷ��ı� �� Ȯ��

		

		string B_List(vector<string> info);
		string BuyerSelect(vector<string> info);	
		

		string OnAir(vector<string> info, int sock);		// ��۽���
		string EndStream(vector<string> info, int sock);	// ��� ����





		void AucBid(vector<string> info, int sock);		// ����� - ����
		string AucChat(vector<string> info);			// ����� - ä��
		void AucQuiting(vector<string> info);			// ����� - ������
		void AuctionEnd(vector<string> info);			// ����Ǹ� ����






		string SalesEnd(vector<string> info);			// �Ϲ��Ǹ� ����






		void Send_Image(string filename, string dir, int cnt, int clnt_sock);		// �̹��� ������ - �����̸�
		string FindProfile(string num, string dir);					// ������ ���� ã��
		string FindFile(string num, string dir);					// ����ã��




		//==========================================================================================
		











		void ChatIn(vector<string> info, int sock);						// ù ä�� ����
		void ChatOnO(vector<string> info, int sock);					// 1:1 ä��

		string time_output();
		void convertToASCII(string letter, string e, int* myid, int* yourid);
		void Chat_list(vector<string> info, int sock);					//ä�ø��
		string Chat_list(string my_id, string u_id, int sock);			// ä�� ����Ʈ
		void ChatEnter(vector<string> info, int sock);					// ä������
		void ChatOut(vector<string> info);								// ä�ó�����
		string ChatList(vector<string> info);							// ä�� ����Ʈ



		



		//�̹��� �ۼ���
		void	Send_Image(vector<string> info, int cnt, string dir, int clnt_sock);
		void	Recv_Image(string dir);	
		unsigned char* Recv_Data(int* size);

};


#endif