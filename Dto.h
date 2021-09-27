#include<iostream>
#include<string>
#include<iomanip>
#include<list>
#include<fstream>
#include <time.h>

namespace Dto
{
	class Account
	{
	public:
		std::string Username;
		std::string Password;
		std::string RePass;
		std::string Id;
		Account()
		{
			Username = Password = RePass = Id="";
		}
	};
	class Person
	{
	public:
		std::string AccountName;
		std::string Name;
		int Age;
		std::string Sex;
		std::string Address;
		std::string PhoneNumber;
		std::string Regency;
		Person()
		{
			AccountName = Name = Sex = Address = PhoneNumber = Regency = "";
			Age = 0;
		}
	};
	class Doctor:public Person
	{
	public:
		std::string Major;
		std::string DoctorId;
	public: 
		Doctor(const Doctor& old)
		{
			AccountName = old.AccountName;
			Name = old.Name;
			Age = old.Age;
			Sex = old.Sex;
			Address = old.Address;
			PhoneNumber = old.PhoneNumber;
			Regency = old.Regency;
			Major = old.Major;
			DoctorId = old.DoctorId;
		}
		Doctor()
		{
			AccountName = "";
			Name = "";
			Age = 0;
			Sex = "";
			Address = "";
			PhoneNumber = "";
			Regency = "";
			Major = "";
			DoctorId = "";
		}
		Doctor(Dto::Person &Person)
		{
			AccountName = Person.AccountName;
			Name = Person.Name;
			Age = Person.Age;
			Address = Person.Address;
			Sex = Person.Sex;
			Regency = Person.Regency;
			PhoneNumber = Person.PhoneNumber;
		}
	};
	class Patient :public Person
	{
	public:
		std::string Symptom;
		Patient()
		{

			AccountName = "";
			Name = "";
			Age = 0;
			Sex = "";
			Address = "";
			PhoneNumber = "";
			Regency = "";
			Symptom = "";
		}
		Patient(const Patient& old)
		{
			AccountName = old.AccountName;
			Name = old.Name;
			Age = old.Age;
			Sex = old.Sex;
			Address = old.Address;
			PhoneNumber = old.PhoneNumber;
			Regency = old.Regency;
			Symptom = old.Symptom;
		}
		Patient(Dto::Person Person)
		{
			AccountName = Person.AccountName;
			Name = Person.Name;
			Age = Person.Age;
			Address = Person.Address;
			Sex = Person.Sex;
			Regency = Person.Regency;
			PhoneNumber = Person.PhoneNumber;
		}
	};
	class Schedule
	{
	public:
	public:
		std::string AccountName;
		std::string Name;
		int Age;
		std::string Sex;
		std::string Address;
		std::string PhoneNumber;
		std::string Regency;
		std::string Date;
		std::string Symptom;
		std::string DoctorId;
	public:
		Schedule()
		{
			AccountName = "";
			Name = "";
			Age = 0;
			Sex = "";
			Address = "";
			PhoneNumber = "";
			DoctorId = "";
			Symptom = "";
			Date = "";
		}
		Schedule(Dto::Person Person)
		{
			AccountName = Person.AccountName;
			Name = Person.Name;
			Age = Person.Age;
			Address = Person.Address;
			Sex = Person.Sex;
			PhoneNumber = Person.PhoneNumber;
		}
		bool operator ==(Dto::Schedule& old)
		{
			if (AccountName == old.AccountName && Name==old.Name && Age==old.Age && Sex==old.Sex)
			{
				if (Address == old.Address && PhoneNumber == old.PhoneNumber &&  Symptom == old.Symptom && DoctorId == old.DoctorId)
					return true;
			}
			return false;
		}
	};
	class Question
	{
	public:
		std::string PatientQuestion;
		std::string DoctorId;
		std::string AccountName;
		std::string Answer;
	public:
		Question()
		{
			PatientQuestion = "";
			DoctorId = "";
			AccountName = "";
			Answer = "";
		}
		bool operator ==(Dto::Question& old)
		{
			if (PatientQuestion == old.PatientQuestion && AccountName == old.AccountName && DoctorId == old.DoctorId)
			{
					return true;
			}
			return false;
		}
	};
}