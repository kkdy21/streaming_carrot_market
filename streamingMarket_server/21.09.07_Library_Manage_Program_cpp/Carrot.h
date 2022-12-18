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
		//공통
		Carrot()
		{ 
			connection = NULL;
			mysql_init(&conn);
		}
		~Carrot()	{ mysql_close(&conn); }



		//스레드 구현
		void	Start_thread();
		void	*_thread(void *sock);
		vector<string> Split(string s, string divid);





		string InsertNum(int chk);						// 게시글 번호 찾기
		
		string SearchNick(vector<string> info);			// 닉네임 찾기
		string SearchArea(vector<string> info);			// 지역 찾기

		string Login(vector<string> v);					// 로그인(login)
		string Enroll(vector<string> v, int sock);				// 회원가입(enroll)



		string Sales(vector<string> info);						// 일반판매 목록(sales)
		string NewSales(vector<string> info);					// 게시글작성 - 일반판매(new_sales)
		string SalesDetails(vector<string> info);				// 일반판매 - 게시글클릭(sales_detail)
		int SalesImageNum_Num(vector<string> info);				// 일반판매 - 게시글 이미지 수
		

		string Auction(vector<string> info);					// 경매판매 목록(auction)
		string NewAuction(vector<string> info, int sock);		// 게시글작성 - 경매판매(new_auction)
		int AuctionImageNum(vector<string> info);				// 경매 - 게시글 이미지 수 
		string AuctionDetails(vector<string> info, int sock);	// 경매 - 게시글클릭(auction_detail)
		
		int ImageNum_ID(vector<string> info, string tbl);		// 게시글 이미지 수 ID




		//==========================================================================================

		string SalesList(vector<string> info);			// 판매 내역 - 일반판매(sale_sale)
		string AuctionList(vector<string> info);		// 판매 내역 - 경매판매(auction_sale)

		string SalesPay(vector<string> info);			// 구매 내역 - 일반판매(sale_pay)
		string AuctionPay(vector<string> info);			// 구매 내역 - 경매판매(auction_pay)

	


		string MySales(vector<string> info);			// 내 판매목록(my_sales)
		string MyDeal(vector<string> info);				// 완료 거래목록(my_deal)
		string MyProfile(vector<string> info);			// 내 프로필 보기(profile)
														// 내 프로필 수정(Myprofile)





		void Review(vector<string> info, string type);	// 거래후기 작성(review)
		string YourReview(vector<string> info);			// 거래후기 보기(your_review)
		int ReviewCount(vector<string> info);			// 거래후기 수 확인

		

		string B_List(vector<string> info);
		string BuyerSelect(vector<string> info);	
		

		string OnAir(vector<string> info, int sock);		// 방송시작
		string EndStream(vector<string> info, int sock);	// 방송 종료





		void AucBid(vector<string> info, int sock);		// 경매중 - 입찰
		string AucChat(vector<string> info);			// 경매중 - 채팅
		void AucQuiting(vector<string> info);			// 경매중 - 나가기
		void AuctionEnd(vector<string> info);			// 경매판매 종료






		string SalesEnd(vector<string> info);			// 일반판매 종료






		void Send_Image(string filename, string dir, int cnt, int clnt_sock);		// 이미지 보내기 - 파일이름
		string FindProfile(string num, string dir);					// 프로필 파일 찾기
		string FindFile(string num, string dir);					// 파일찾기




		//==========================================================================================
		











		void ChatIn(vector<string> info, int sock);						// 첫 채팅 접숙
		void ChatOnO(vector<string> info, int sock);					// 1:1 채팅

		string time_output();
		void convertToASCII(string letter, string e, int* myid, int* yourid);
		void Chat_list(vector<string> info, int sock);					//채팅목록
		string Chat_list(string my_id, string u_id, int sock);			// 채팅 리스트
		void ChatEnter(vector<string> info, int sock);					// 채팅접속
		void ChatOut(vector<string> info);								// 채팅나가기
		string ChatList(vector<string> info);							// 채팅 리스트



		



		//이미지 송수신
		void	Send_Image(vector<string> info, int cnt, string dir, int clnt_sock);
		void	Recv_Image(string dir);	
		unsigned char* Recv_Data(int* size);

};


#endif