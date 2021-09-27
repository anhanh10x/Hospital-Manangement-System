#pragma once
#include"Dal.h"

namespace Bl
{
	class Account:public Dal::Account
	{
	public:
		bool CreatAccount(Dto::Account);
		bool LoginAccount(Dto::Account&);
		bool CheckNameExis(std::string);
		bool CheckPassWord(std::string);
	};
	class Person:protected Dal::Person
	{
	public:
		bool CheckString(std::string, int, int);
		bool CheckPhoneNumber(std::string, int);
		bool CheckAge(int);
		bool CheckChoice(int,int);
		bool CheckHaveData(Dto::Account);
		bool RequestAccepted(std::list<Dto::Schedule>&, Dto::Account);
		bool QueueRequest(std::list<Dto::Schedule>&, Dto::Account);
		void SaveIdAccount(std::string);
		void SaveQuestion(Dto::Question);
		bool QueueQuestion(std::list<Dto::Question>&,Dto::Account);
		bool AcceptedQuestion(std::list<Dto::Question>&, Dto::Account);
	};
	class Doctor:public Dal::Doctor,Bl::Person
	{
	public:
		void GetInfor(Dto::Doctor&,Dto::Account);
		void SaveInfor(Dto::Doctor);
		void SaveSchedule(std::list<Dto::Schedule>);
		void SaveScheduleDenied(std::list<Dto::Schedule>);
	};
	class Patient :public Dal::Patient, Bl::Person,Dal::Account, Dal::Doctor
	{
	public:
		void SaveInfor(Dto::Patient);
		void GetInfor(Dto::Patient&, Dto::Account);
		void GetDoctorInfor(std::list<Dto::Doctor>&);
		void SaveSchedule(Dto::Schedule);
		bool CheckId(Dto::Doctor&);
	};
}