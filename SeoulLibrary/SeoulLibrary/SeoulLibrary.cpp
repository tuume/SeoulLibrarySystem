/*
- 초기 계정 
	관리자 -> id: administer /pwd: 1111
	유저 -> id: tuumej /pwd: 1111
- 관리자 계정은 삭제할 수 없습니다. 

********추가 할 사항
0. 책 중복 대여 불가능
2. 관리자는 특별하게 세부 책 현황 볼수 있게 하기(어떤 책을 빌렸는지, 초과한 시간)
3. 대여 하시겠습니까? 같은 확인 문구 한번 더 띄우기

*/

#include "pch.h"
#include <iostream>
#include <ctime>
#include <string>
using namespace std;


class Date {                         // 대출일, 반납일 관리
private:
	int year, month, day;
public:
	Date() {}	//기본 생성자
	void t_Date(int year, int month, int day) { 
		this->year = year; 
		this->month = month;
		this->day = day;
	}
	
	int gapDates(Date d) { // d에 들어있는 것은 오늘일자
		if (year == d.year) { // 년도가 같으면
			if (month == d.month) // 월이 같으면
				return d.day - day;
			else {

			}
		}
	}
	void showDate() {
		cout << year << "-" << month << "-" << day;
	}
};

class Book {
private:
	int cnt, r_cnt;     // 총 권수, 대출 권수
	string title, writer, pub; //책 이름, 저자, 출판사
	bool state;         // 도서 대출 가능 상태
	Date bd, rd;    // 대여일, 반납일
public:
	Book() {}
	string check_title() { return title; }
	string check_writer() { return writer; }
	string check_pub() { return pub; }
	bool check_state() { return state; }
	int check_rcnt() { return r_cnt; }
	// 도서 등록
	void addBook(string t,string w, string p,int cnt) {
		title = t;
		writer = w;
		pub = p;
		this->cnt = cnt;
		r_cnt = 0;
		state = true;
	}
	// 도서 대출
	void borrowBook(int y,int m,int d) {
		bd.t_Date(y, m, d);
		rd.t_Date(y,m,d+7);
		r_cnt++;
	}
	
	// 도서 반납
	void returnBook() {
		r_cnt--;
	}
	// 도서 목록
	void showBook() {
		cout << title << " / " << writer << " / " << pub << " / " << cnt << "권 중 ";
		if (state == true) { cout << cnt - r_cnt << "권 대출 가능"; }
		else { cout << cnt - r_cnt << "권 대출중"; }
		cout << endl;
	}
	int restBook() {return cnt - r_cnt;}			// 남은 책 권수 반환
	void restDate() {								// 남은 일수 반환
		cout << bd.gapDates(rd) << "일";
	}

	void showDate() {
		bd.showDate();
		cout << " ~ ";
		rd.showDate();
	}
};


class Member {
private:
	string id, pwd;						// 아이디, 패스워드
	string name, email, phone;			// 이름, 이메일, 전화번호
	int b_cnt;							// 책 대여 권수
	char access;						// 접근 권한
	Book *b;						// 책 대여 목록

public:
	Member() {}
	void master(string id, string pwd) {
		this->id = id;
		this->pwd = pwd;
		access = 'm';
		b_cnt = 0;
	}
	void addMember(string id, string pwd, string name, string email, string phone) {	//유저 초기값 설정
		this->id = id;
		this->pwd = pwd;
		this->name = name; 
		this->email = email; 
		this->phone = phone; 
		access = 'u';
		b_cnt = 0;
		b = new Book[3];
	}

	string check_id() { return id; }
	string check_pwd() { return pwd; }
	char check_access() { return access; }
	string check_name() { return name; }
	string check_email() { return email; }
	string check_phone() { return phone; }
	int check_borrow() { return b_cnt; }	

	void borrowBook(Book *c[],int i,int y,int m,int d) {					// 책 빌리기
		c[i]->borrowBook(y,m,d);
		b[b_cnt] = *c[i];
		b_cnt++;
	}
	//대여 도서 확인
	bool returnBook(string title) {									//대출 도서 반납
		for (int i = 0; i < b_cnt; i++) {
			if(b[i].check_title() == title)
			{
				for (i; i < b_cnt; i++) {
					b[i] = b[i + 1];
					b_cnt--;
				}
				return true;
			}
		}
		return false;
	}
	// 대출 도서 중복 검사
	bool checkBook(string title) {
		for (int i = 0; i < b_cnt; i++) {
			if (b[i].check_title() == title)
			{
				return false;
			}
		}
		return true;
	}

	void showlist() {					//빌린 책 목록 보기
		for (int i = 0; i < b_cnt; i++) {
			cout << i + 1 << ") "; 
			cout << b[i].check_title() << " / " << b[i].check_writer() << " / "
				<< b[i].check_pub()<< " / "; 
			b[i].showDate();
			cout << " / ";
			b[i].restDate(); 
			cout << endl;
		}
		cout << endl;
	}
};

//함수 원형
void login(Member *mem[], Book *b[]);				// 로그인
void create_user(Member *mem[]);					// 회원 가입
void delete_user(Member *mem[]);					// 회원 탈퇴 - 먹튀 방지하기
void example_id(Member *mem[], Book *book[]);				// 유저와 관리자 미리 생성
void userSystem(Member *m[],Book *b[], int i);				//사용자 이용 시 서비스 화면
void show_mem(Member *mem[]);						// 사용자 현황
void masterSystem(Member *mem[], Book *b[]);		// 관리자 모드 시 서비스 화면
void addBook(Book *b[]);							// 도서 등록
void showBook(Book *b[]);							// 도서 현황
void delBook(Book *b[]);							// 도서 삭제
void borrowBook(Member *m[], Book *b[],int i);			// 도서 대출
void returnBook(Member *m[], Book *b[], int i);			// 도서 반납
void showBorrow(Member *m[], Book *b[],int i);				// 대출 도서 확인

int mem_cnt = 0;		// 회원 카운트
int book_cnt = 0;		// 책 카운트

int main()
{
	int n;
	Book *book[20];
	Member *member[20] ;// 회원 20명
	example_id(member,book);

	cout << "*************서울 공공 도서관**************\n";
	cout << "***서울 공공 도서관에 오신걸 환영합니다!***\n\n";
	cout << "\t[ 이용 안내 ]\n";
	cout << "- 1인당 최대 3권 대출 가능 \n";
	cout << "- 대출 기간은 휴관일을 제외한 7일 \n";
	cout << "- 예약이 없는 경우 1회 연장 가능(연장일로부터 7일) \n";
	cout << "- 무단 연장 시 기간만큼 대출 불가 \n";
	cout << "- 둘째 주 월요일은 휴관일 \n";
	cout << "*******************************************\n";
	cout << "\t1. 로그인\n";
	cout << "\t2. 회원 가입\n";
	cout << "\t3. 회원 탈퇴\n";
	cout << "\t4. 종료\n";
	while (true) {
		cout << "입력: ";
		cin >> n;
		switch (n) {
		case 1: login(member,book); break;
		case 2: create_user(member); break;
		case 3: delete_user(member); break;
		case 4: return 0;
		default: cout << "다시 입력해주세요.\n";

		}
	}
}
// 로그인 화면(아이디 확인, 비밀번호 확인 -> access 가 m 일경우 전부, u 일경우 일반
void login(Member *mem[],Book *b[]) {
	string id, pwd;
	int i;
	cout << "ID: "; cin >> id;
	for (i = 0; i < mem_cnt; i++) {			// 유저 아이디, 비밀번호 확인
		if (mem[i]->check_id() == id) { 
			cout << "PWD: "; cin >> pwd;
			if (mem[i]->check_pwd() == pwd) {
				//유저 아이디 비번 일치시 실행
				if (mem[i]->check_access() == 'u') {		// 관리자인지 유저인지 확인
					userSystem(mem,b,i);
				}
				else if (mem[i]->check_access() == 'm') {
					masterSystem(mem,b);
				}
				return;
			}
			else {
				cout << "잘못 입력하셨습니다.\n\n";
				return;
			}
		}
	}
	cout << "잘못 입력하셨습니다.\n\n";
	return;
}

// 회원 가입 화면
void create_user(Member *mem[]) {
	Member *m = new Member;
	string id, pwd, n, e, p;
	cout << "ID: "; cin >> id;
	for (int i = 0; i < mem_cnt; i++) {
		if (mem[i]->check_id() == id) { 
			cout << "동일한 아이디가 존재합니다\n\n"; 
			return;
		}
	}
	cout << "PWD: "; cin >> pwd;
	cout << "이름: "; cin >> n;
	cout << "이메일: "; cin >> e;
	cout << "전화번호: "; cin >> p;

	m->addMember(id, pwd, n, e, p);
	mem[mem_cnt] = m;
	mem_cnt++;
	cout << "아이디가 생성되었습니다.\n\n";
}

// 회원 탈퇴
void delete_user(Member *mem[]) {
	string id, pwd;
	int i;
	cout << "ID: "; cin >> id;
	for (i = 0; i < mem_cnt; i++) {			// 유저 아이디, 비밀번호 확인
		if (mem[i]->check_id() == id) {
			cout << "PWD: "; cin >> pwd;
			if (mem[i]->check_pwd() == pwd) {
				//유저 아이디 비번 일치시 실행
				if (mem[i]->check_access() == 'u') {		// 관리자인지 유저인지 확인
					for (i; i < mem_cnt; i++) {
						mem[i] = mem[i + 1];
						mem_cnt--;
					}
					cout << endl;
				}
				else if (mem[i]->check_access() == 'm') {
					cout << "관리자 계정은 삭제할 수 없습니다.\n\n";
				}
				return;
			}
			else {
				cout << "잘못 입력하셨습니다.\n\n";
				return;
			}
		}
	}
	cout << "잘못 입력하셨습니다.\n\n";
	return;
}

void userSystem(Member *m[],Book *b[],int i){		//사용자 계정 로그인 시 서비스
	int n;
	cout << endl;
	cout << m[i]->check_name() << "님 반값습니다!\n";
	cout << "1. 도서 대출\n";
	cout << "2. 도서 반납\n";
	cout << "3. 도서 목록\n";
	cout << "4. 대출 목록\n";
	cout << "5. 로그 아웃\n";
	while (true) {
		cout << "입력: "; cin >> n;
		switch (n) {
		case 1: borrowBook(m, b, i); break;
		case 2: returnBook(m, b, i); break;
		case 3: showBook(b); break;
		case 4: showBorrow(m,b,i); break;
		case 5: cout << "이용해 주셔서 감사합니다!\n\n"; return;
		default: cout << "다시 입력해주세요.\n"; break;
		}
	}
}

void borrowBook(Member *m[], Book *b[], int k) {			//도서 대출, k는 유저의 번호
	time_t t = time(0);				// 오늘 날짜 와 시간 출력
	struct tm now;
	localtime_s(&now, &t);

	string title;
	int i = 0;
	cin.ignore();
	cout << "도서 명: "; getline(cin, title);
	for (int j = 0; j < m[k]->check_borrow(); j++) {
		if (m[k]->checkBook(title) != true) {
			cout << "동일한 책을 대여중입니다.\n";
			cout << endl;
			return;
		}
	}
	for (i; i < book_cnt; i++) {
		if (b[i]->check_title() == title) {			// 책 제목으로 일치 확인
			if (b[i]->restBook() > 0) {				// 도서가 존재 유무
				if (m[k]->check_borrow() < 3) {
					m[k]->borrowBook(b,i, now.tm_year + 1900, now.tm_mon + 1, now.tm_mday);
					cout << endl;
					return;
				}
				else {
					cout << "도서 대여 가능 권수가 초과되었습니다.\n" << endl;
					return;
				}
			}
			else {
				cout << "대출 가능한 도서가 없습니다.\n";
				cout << endl;
				return;
			}
		}
	}
	cout << "해당 도서가 없습니다.\n";
	cout << endl;
}

void returnBook(Member *m[], Book *b[], int k) {			// 도서 반납, k= 유저 아이디 번호
	string title;
	int i = 0;
	cin.ignore();
	if (m[k]->check_borrow() == 0) { return; }
	cout << "도서 명: "; getline(cin, title);
	for (i; i < m[k]->check_borrow(); i++) {
		if (m[k]->returnBook(title) == true) {
			for (int j = 0; j < book_cnt; j++)
			{
				if (b[j]->check_title() == title) {
					b[j]->returnBook();
					cout << "도서 반납이 완료되었습니다.\n";
					cout << endl;
					return;
				}
			}
		}
	}
	cout << "대여 도서가 없습니다.\n";
}

void showBorrow(Member *m[],Book *b[],int i){					// 대출 목록
	if (m[i]->check_borrow() == 0) {
		cout << "대여 도서가 없습니다.\n\n";
		return;
	}
	cout << "*************대출 목록(도서 명/저자/출판사/대출 기간/남은 날)*************" << endl;
	m[i]->showlist();
}

void masterSystem(Member *mem[],Book *b[]){				// 관리자 모드 로그인
	int n;
	cout << "\n< 관리자 모드 >\n";
	cout << "1. 도서 등록\n";
	cout << "2. 도서 삭제\n";
	cout << "3. 도서 목록\n";
	cout << "4. 회원 현황\n";
	cout << "5. 종료\n";
	while (true) {
		cout << "입력: "; cin >> n;
		switch (n) {
		case 1: addBook(b); break;
		case 2: delBook(b); break;
		case 3: showBook(b); break;
		case 4: show_mem(mem); break;
		case 5: cout << "관리자 모드 종료\n\n"; return;
		default: cout << "다시 입력해주세요.\n"; break;
		}
	}
}

void addBook(Book *b[]) {				// 책 추가
	Book *a = new Book;
	string t, w, p;
	int cnt;
	cin.ignore();
	cout << "도서 명: "; getline(cin,t);
	cout << "저자: ";	getline(cin, w);
	cout << "출판사: ";	getline(cin, p);
	cout << "수량: ";	cin >> cnt;
	a->addBook(t, w, p, cnt);
	b[book_cnt] = a;
	book_cnt++;
	cout << endl;
}

void delBook(Book *b[]) {			// 책 삭제 - 사용자가 대여중이면 삭제 불가능
	string title;
	int i = 0;
	cin.ignore();
	cout << "도서 명: "; getline(cin,title);
	for (i; i < book_cnt; i++) {
		if (b[i]->check_title() == title) {			// 책 제목으로 일치 확인
			if (b[i]->check_rcnt() > 0) {				// 대여중인 책 구별
				cout << "대여중인 도서는 삭제 불가능합니다.\n";
				return;
			}
			for (i; i < book_cnt; i++) {
				b[i] = b[i + 1];
			}
			book_cnt--;
			cout << endl;
			return;
		}
	}
	cout << "일치하는 도서가 없습니다.\n";
}

void showBook(Book *b[]) {				// 도서 목록
	cout << "*****************도서 명 / 저자 / 출판사 / 대출 여부*****************" << endl;
	for (int i = 0; i < book_cnt; i++) {
		cout << i + 1 << ") "; b[i]->showBook();
	}
	cout << "*********************************************************************" << endl;
	cout << endl;
}

// 삭제 또는 예시용

void example_id(Member *mem[], Book *book[]) {
	Member *m = new Member;
	Member *n = new Member;
	Book *a = new Book;
	Book *b = new Book;
	m->master("administer", "1111");	 //관리자 첫 계정 생성
	mem[0] = m;
	n->addMember("tuumej", "1111", "임재원", "tuumej@naver.com", "010-7390-1412");	// 유저 계정
	mem[1] = n;
	a->addBook("고요할수록 밝아지는 것들", "혜민", "수오서재", 5);	// 책 등록
	book[0] = a;
	b->addBook("꽃을 보듯 너를 본다", "나태주", "지혜", 1);
	book[1] = b;
	mem_cnt += 2;			// 사용자cnt 2명 추가
	book_cnt += 2;			// 책cnt 2권 추가
}

void show_mem(Member *mem[]) {
	for (int i = 0; i < mem_cnt; i++) {
		cout << i + 1 << ") " << mem[i]->check_id() << "/" << mem[i]->check_name()
			<<"/"<< mem[i]->check_email() << "/" << mem[i]->check_phone() <<"/"
			<< mem[i]->check_borrow() << "권 대여중..\n";
	}
	cout << endl;
}