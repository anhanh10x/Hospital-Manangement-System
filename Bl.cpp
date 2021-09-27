#include "Bl.h"

//************************************************* Bl.cpp******************************************

//***********************************************
//Function for Login
bool Bl::Account::CreatAccount(Dto::Account NewAccount)
{
	if (NewAccount.Password == NewAccount.RePass)
	{
		Dal::Account::CreatAccount(NewAccount);
		return true;
	}
	else
		return false;
}
bool Bl::Account::LoginAccount(Dto::Account &Account)
{
	std::list<Dto::Account> temp;
	std::list<Dto::Account> ::iterator head;
	Dal::Account::LoginAccount(temp);
	for (head = temp.begin(); head != temp.end(); ++head)
	{
		if (head->Password == Account.Password && head->Username == Account.Username) {
			Account = *head;
			temp.clear();
			return true;
		}
	}
	temp.clear();
	return false;
}
bool Bl::Account::CheckNameExis(std::string UserName)
{
	std::list<Dto::Account>list;
	Dal::Account::LoginAccount(list);
	std::list<Dto::Account> ::iterator head;
	for (head = list.begin(); head != list.end(); ++head)
	{
		if (head->Username == UserName)
			return true;
	}
	return false;
}
bool Bl::Account::CheckPassWord(std::string PassWord)
{
	bool CheckCharacter = false, CheckNumber = false;
	if (PassWord.length() < 6)
		return false;
	for (int i = 0; i < PassWord.length(); i++)
	{
		if ((int)PassWord[i] - 48 >= 0 && PassWord[i] - 48 <= 9)
			CheckNumber = true;
		else
			CheckCharacter = true;
	}
	if (CheckNumber != CheckCharacter)
		return false;
	return true;	
}

//**************************************
//Function for Person
bool Bl::Person::CheckString(std::string String,int MinLength,int MaxLength)
{
	if (String.find(' ') > String.length())
		return false;
	if (String.length() < MinLength && String.length() > MaxLength)
		return false;
	for (int i = 0; i < String.length(); i++) {
		if ((int)String[i] - 48 >= 0 && (int)String[i] - 48 <= 9)
			return false;
	}
	return true;	
}
bool Bl::Person::CheckAge(int Age)
{
	if (Age <= 0 || Age >= 100) {
		return false;
	}
	else
		return true;
}
bool Bl::Person::CheckChoice(int Choice,int Expectation)
{
	if(Choice!=Expectation)
	{
			return false;
	}
	return true;
}
bool Bl::Person::CheckPhoneNumber(std::string PhoneNumber,int Length)
{
	for (int i = 0; i < PhoneNumber.length(); i++)
	{
		if (PhoneNumber.length() != Length)
		{
			return false;
		}
		if ((int)PhoneNumber[i] - 48 < 0 && (int)PhoneNumber[i] > 9) {
			return false;
		}
	}
	return true;
}
bool Bl::Person::CheckHaveData(Dto::Account Account)
{
	if (Account.Id == "")
		return false;
	return true;
}
void Bl::Person::SaveIdAccount(std::string Id)
{
	Dal::Account SaveId;
	SaveId.SaveIdAccount(Id);
}
bool Bl::Person::RequestAccepted(std::list<Dto::Schedule>& list, Dto::Account Account)
{
	bool flag = false;
	std::list<Dto::Schedule> TempList;
	Dal::Person::GetSchedule(TempList);
	std::list<Dto::Schedule> ::iterator head;
	if (Account.Id[0] == 'D')
	{
		for (head = TempList.begin(); head != TempList.end(); ++head)
		{
			if (head->DoctorId == Account.Id)
			{
				flag = true;
				list.push_back(*head);
			}
		}
	}
	else
	{
		for (head = TempList.begin(); head != TempList.end(); ++head)
		{
			if (head->AccountName == Account.Username)
			{
				flag = true;
				list.push_back(*head);
			}
		}
	}
	TempList.clear();
	if (flag == false)
		return false;
	else
		return true;
}
bool Bl::Person::QueueRequest(std::list<Dto::Schedule>& list, Dto::Account Account)
{
	bool flag = false;
	bool check = false;
	std::list<Dto::Schedule> TempList;
	std::list<Dto::Schedule> RequestList;
	std::list<Dto::Schedule> AcceptedList;
	std::list<Dto::Schedule> DeniedList;
	Dal::Person::GetRequest(RequestList);
	Dal::Person::GetSchedule(AcceptedList);
	Dal::Person::GetRequestDenied(DeniedList);
	std::list<Dto::Schedule> ::iterator RequestHead;
	std::list<Dto::Schedule> ::iterator AcceptedHead;
	std::list<Dto::Schedule> ::iterator DeniedHead;
	if (Account.Id[0] == 'D')
	{
		for (RequestHead = RequestList.begin(); RequestHead != RequestList.end(); ++RequestHead)
		{
			if (RequestHead->DoctorId == Account.Id)
			{
				flag = true;
				for (AcceptedHead = AcceptedList.begin(); AcceptedHead != AcceptedList.end(); ++AcceptedHead)
				{
					if (*AcceptedHead == *RequestHead)
					{
						flag = false;
						break;
					}
				}
				if (flag == false)
					continue;
				else
				{
					check = true;
					TempList.push_back(*RequestHead);
				}
			}
		}
		for (RequestHead = TempList.begin(); RequestHead != TempList.end(); ++RequestHead)
		{
			flag = true;
			for (DeniedHead = DeniedList.begin(); DeniedHead != DeniedList.end(); ++DeniedHead)
			{
				if (*DeniedHead == *RequestHead)
				{
					flag = false;
					break;
				}
			}
			if (flag == false)
				continue;
			else
			{
				check= true;
				list.push_back(*RequestHead);
			}
		}
	}
	else
	{
		for (RequestHead = RequestList.begin(); RequestHead != RequestList.end(); ++RequestHead)
		{
			if (RequestHead->AccountName==Account.Username)
			{
				flag = true;
				for (AcceptedHead = AcceptedList.begin(); AcceptedHead != AcceptedList.end(); ++AcceptedHead)
				{
					if (*AcceptedHead == *RequestHead)
					{
						flag = false;
						break;
					}
				}
				if (flag == false)
					continue;
				else
				{
					check = true;
					TempList.push_back(*RequestHead);
				}
			}
		}
		for (RequestHead = TempList.begin(); RequestHead != TempList.end(); ++RequestHead)
		{
			flag = true;
			for (DeniedHead = DeniedList.begin(); DeniedHead != DeniedList.end(); ++DeniedHead)
			{
				if (*DeniedHead == *RequestHead)
				{
					flag = false;
					break;
				}
			}
			if (flag == false)
				continue;
			else
			{
				check = true;
				list.push_back(*RequestHead);
			}
		}
	}
	RequestList.clear();
	AcceptedList.clear();
	DeniedList.clear();
	if (check == false)
		return false;
	else
		return true;
}
void Bl::Person::SaveQuestion(Dto::Question Question)
{
	Dal::Person::SaveQuestion(Question);
}
bool Bl::Person::QueueQuestion(std::list<Dto::Question>& list,Dto::Account Account)
{
	std::list<Dto::Question> RequestList;
	std::list<Dto::Question> AcceptedList;
	std::list<Dto::Question> ::iterator RequestHead;
	std::list<Dto::Question> ::iterator AcceptedHead;
	Dal::Person::AcceptedQuestion(AcceptedList);
	Dal::Person::QueueQuestion(RequestList);
	bool flag, check;
	flag = check = false;
	if(Account.Id[0]=='D')
	{ 
		for (RequestHead = RequestList.begin(); RequestHead != RequestList.end(); ++RequestHead)
		{
			if (RequestHead->DoctorId == Account.Id)
			{
				flag = true;
				for (AcceptedHead = AcceptedList.begin(); AcceptedHead != AcceptedList.end(); ++AcceptedHead)
				{
					if (*AcceptedHead == *RequestHead)
					{
						flag = false;
						break;
					}
				}
				if (flag == false)
					continue;
				else
				{
					check = true;
					list.push_back(*RequestHead);
				}
			}
		}
	}
	else
	{
		for (RequestHead = RequestList.begin(); RequestHead != RequestList.end(); ++RequestHead)
		{
			if (RequestHead->AccountName == Account.Username)
			{
				flag = true;
				for (AcceptedHead = AcceptedList.begin(); AcceptedHead != AcceptedList.end(); ++AcceptedHead)
				{
					if (*AcceptedHead == *RequestHead)
					{
						flag = false;
						break;
					}
				}
				if (flag == false)
					continue;
				else
				{
					check = true;
					list.push_back(*RequestHead);
				}
			}
		}
	}
	RequestList.clear();
	AcceptedList.clear();
	if (check == false)
		return false;
	else
		return true;
}
bool Bl::Person::AcceptedQuestion(std::list<Dto::Question>& list, Dto::Account Account)
{
	bool flag = false;
	std::list<Dto::Question> TempList;
	Dal::Person::AcceptedQuestion(TempList);
	std::list<Dto::Question> ::iterator head;
	if (Account.Id[0] == 'D')
	{
		for (head = TempList.begin(); head != TempList.end(); ++head)
		{
			if (head->DoctorId == Account.Id)
			{
				flag = true;
				list.push_back(*head);
			}
		}
	}
	else
	{
		for (head = TempList.begin(); head != TempList.end(); ++head)
		{
			if (head->AccountName == Account.Username)
			{
				flag = true;
				list.push_back(*head);
			}
		}
	}
	TempList.clear();
	if (flag == false)
		return false;
	else
		return true;
}
//*************************************
//Function for Doctor
void Bl::Doctor::SaveInfor(Dto::Doctor Doctor)
{
	Dal::Doctor::SaveInfor(Doctor);
}
void Bl::Doctor::GetInfor(Dto::Doctor& Doctor, Dto::Account Account)
{
	Doctor.AccountName = Account.Username;
	Dal::Doctor::GetInfor(Doctor);
}
void Bl::Doctor::SaveSchedule(std::list<Dto::Schedule>list)
{
	Dal::Doctor::SaveSchedule(list);
}
void Bl::Doctor::SaveScheduleDenied(std::list<Dto::Schedule>list)
{
	Dal::Doctor::SaveScheduleDenied(list);
}
//***********************************************
//Function for Patient
void Bl::Patient::SaveInfor(Dto::Patient Patient)
{
	Dal::Patient::SaveInfor(Patient);
}
void Bl::Patient::GetInfor(Dto::Patient& Patient, Dto::Account Account)
{
	Patient.AccountName = Account.Username;
	Dal::Patient::GetInfor(Patient);
}
void Bl::Patient::GetDoctorInfor(std::list<Dto::Doctor>& list)
{
	Dto::Doctor Doctor;
	std::list<Dto::Account> ListAccount;
	Dal::Account::LoginAccount(ListAccount);
	std::list<std::string> ListString;
	std::list<Dto::Account> ::iterator head;
	for (head = ListAccount.begin(); head != ListAccount.end(); ++head)
	{
		if (head->Id[0] == 'D')
		{
			ListString.push_back(head->Username);
			continue;
		}
	}
	std::list<std::string> ::iterator ahead;
	for (ahead = ListString.begin(); ahead != ListString.end(); ++ahead)
	{
		Dto::Doctor Doctor;
		Doctor.AccountName = *ahead;
		Dal::Doctor::GetInfor(Doctor);
		list.push_back(Doctor);
	}
}
void Bl::Patient::SaveSchedule(Dto::Schedule Patient)
{
	Dal::Patient::SaveSchedule(Patient);
}
bool Bl::Patient::CheckId(Dto::Doctor &Doctor)
{
	if (Doctor.DoctorId[0] != 'D')
		return false;
	else
	{
		std::list<Dto::Doctor> list;
		Bl::Patient::GetDoctorInfor(list);
		std::list<Dto::Doctor> ::iterator head;
		for (head = list.begin(); head != list.end(); ++head)
		{
			if (Doctor.DoctorId == head->DoctorId)
			{
				Doctor = *head;
				return true;
			}
		}
		return false;
	}
}