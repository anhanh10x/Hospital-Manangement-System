#pragma once
#include"Dto.h"
namespace Dal
{
	class Account
	{
	public:
		void SaveIdAccount(std::string);
		void CreatAccount(Dto::Account);
		void LoginAccount(std::list<Dto::Account>&);

	};
	class Person
	{
	public:
		void GetSchedule(std::list<Dto::Schedule>&);
		void GetRequest(std::list<Dto::Schedule>&);
		void GetRequestDenied(std::list<Dto::Schedule>&);
		void SaveQuestion(Dto::Question);
		void QueueQuestion(std::list<Dto::Question>&);
		void AcceptedQuestion(std::list<Dto::Question>&);
	};
	class Doctor:public Person
	{
	public:
		void SaveInfor(Dto::Doctor);
		void GetInfor(Dto::Doctor&);
		void SaveSchedule(std::list<Dto::Schedule>list);
		void SaveScheduleDenied(std::list<Dto::Schedule>);
	};
	class Patient:public Person
	{
	public:
		void SaveInfor(Dto::Patient);
		void GetInfor(Dto::Patient&);
		void SaveSchedule(Dto::Schedule);
	};
}