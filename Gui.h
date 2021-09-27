#pragma once
#include"Bl.h"
#include<Windows.h>
namespace Gui
{
	int WhereX();
	int WhereY();
	void GotoXY(int,int);
	void ShowCur(bool);
	void Loading();
	void ClearTyping(std::string);
	void ClearRow(int FirstRow, int LastRow);
	int Random(int, int);
	std::string CreateId(std::string);
	class Account:public Bl::Account
	{
	public:
		bool CreatAccount();
		bool LoginAccount(Dto::Account&);
		bool MenuLogin(Dto::Account&);
	};
	class MenuInterface:public Bl::Person
	{
	public:
		void Set(Dto::Person&,Dto::Account);
		void Header(Dto::Account);
		void MainMenu(Dto::Account&);
	};
	class MenuForNewMember :public MenuInterface,Bl::Doctor,Bl::Patient
	{
	public:
		bool Menu(Dto::Account&);
		void Set(Dto::Account&);
	};
	class MenuForDoctor :public MenuInterface, Bl::Doctor
	{
	public:
		bool Menu(Dto::Account);
		void Set(Dto::Account);
		void GetInfor(Dto::Account);
		void Schedule(Dto::Account);
		void PatientRequest(Dto::Account);
		void AnswerQuestion(Dto::Account);
	};
	class MenuForPatient :public MenuInterface,Bl::Patient
	{
	public:
		bool Menu(Dto::Account);
		void Set(Dto::Account);
		void GetInfor(Dto::Account);
		void GetInforDoctor(Dto::Account);
		void SetTimeSchedule(Dto::Account);
		bool CheckId(Dto::Doctor&);
		bool MenuForExamination(Dto::Account);
		void PatientRequest(Dto::Account);
		void Schedule(Dto::Account);
		bool QuestionMenu(Dto::Account);
		void RequestQuestion(Dto::Account);
		void SetQuestion(Dto::Account);
		void AcceptedQuestion(Dto::Account);
	};
	
}