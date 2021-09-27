#include"Dal.h"

//Function for Account
void Dal::Account::CreatAccount(Dto::Account NewAccount)
{
    std::ofstream f;
    f.open("account.txt", std::ios::app);
    f << NewAccount.Username << std::endl;
    f << NewAccount.Password << std::endl;
    f.close();
}
void Dal::Account::SaveIdAccount(std::string Id)
{
    std::ofstream f;
    f.open("account.txt", std::ios::app);
    f << Id<<std::endl;
    f.close();
}
void Dal::Account::LoginAccount(std:: list<Dto::Account>& list)
{
    std::ifstream f;
    f.open("account.txt", std::ios::in);
    while (true)
    {
        Dto::Account temp;
        f >> temp.Username;
        if (f.eof())
            break;
        f >> temp.Password;
        f >> temp.Id;
        list.push_back(temp);
    }
}
//Function for Person
void Dal::Person::GetSchedule(std::list<Dto::Schedule>&list)
{
    std::ifstream f;
    Dto::Schedule Schedule;
    std::string Age = "";
    f.open("RequestAccepted.txt", std::ios::in);
    while (true) {
        std::getline(f, Schedule.DoctorId,'#');
        if (f.eof())
            break;
        std::getline(f, Schedule.AccountName, '#');
        std::getline(f, Schedule.Name, '#');
        std::getline(f, Age, '#');
        Schedule.Age = atoi(Age.c_str());
        std::getline(f, Schedule.Sex, '#');
        std::getline(f, Schedule.Address, '#');
        std::getline(f, Schedule.PhoneNumber, '#');
        std::getline(f, Schedule.Symptom, '#');
        std::getline(f, Schedule.Date);
        list.push_back(Schedule);
    }
}
void Dal::Person::GetRequest(std::list<Dto::Schedule>& list)
{
    std::ifstream f;
    Dto::Schedule Schedule;
    std::string Age = "";
    f.open("PatientRequest.txt", std::ios::in);
    while (true) {
        std::getline(f, Schedule.DoctorId, '#');
        if (f.eof())
            break;
        std::getline(f, Schedule.AccountName, '#');
        std::getline(f, Schedule.Name, '#');
        std::getline(f, Age, '#');
        Schedule.Age = atoi(Age.c_str());
        std::getline(f, Schedule.Sex, '#');
        std::getline(f, Schedule.Address, '#');
        std::getline(f, Schedule.PhoneNumber, '#');
        std::getline(f, Schedule.Symptom, '#');
        std::getline(f, Schedule.Date);
        list.push_back(Schedule);
    }
}
void Dal::Person::GetRequestDenied(std::list<Dto::Schedule>& list)
{
    std::ifstream f;
    Dto::Schedule Schedule;
    std::string Age = "";
    f.open("PatientRequestDenied.txt", std::ios::in);
    while (true) {
        std::getline(f, Schedule.DoctorId, '#');
        if (f.eof())
            break;
        std::getline(f, Schedule.AccountName, '#');
        std::getline(f, Schedule.Name, '#');
        std::getline(f, Age, '#');
        Schedule.Age = atoi(Age.c_str());
        std::getline(f, Schedule.Sex, '#');
        std::getline(f, Schedule.Address, '#');
        std::getline(f, Schedule.PhoneNumber, '#');
        std::getline(f, Schedule.Symptom, '#');
        std::getline(f, Schedule.Date);
        list.push_back(Schedule);
    }
}
void Dal::Doctor::SaveSchedule(std::list<Dto::Schedule>list)
{
    std::ofstream f;
    f.open("RequestAccepted.txt", std::ios::app);
    std::list<Dto::Schedule> ::iterator head;
    for (head = list.begin(); head != list.end(); ++head)
    {
        f << head->DoctorId << "#" << head->AccountName << "#" << head->Name << "#" << head->Age <<"#" <<head->Sex << "#" << head->Address << "#" << head->PhoneNumber << "#" << head->Symptom << "#" << head->Date<< std::endl;
    }
    f.close();
    list.clear();
    return;    
}
void Dal::Doctor::SaveScheduleDenied(std::list<Dto::Schedule>list)
{
    std::ofstream f;
    f.open("PatientRequestDenied.txt", std::ios::app);
    std::list<Dto::Schedule> ::iterator head;
    for (head = list.begin(); head != list.end(); ++head)
    {
        f << head->DoctorId << "#" << head->AccountName << "#" << head->Name << "#" << head->Age << "#" << head->Sex << "#" << head->Address << "#" << head->PhoneNumber << "#" << head->Symptom << "#" << head->Date << std::endl;
    }
    f.close();
    list.clear();
    return;
}
//Function for Doctor
void Dal::Doctor::SaveInfor(Dto::Doctor Doctor)
{
    std::ofstream f;
    std::string filename = Doctor.AccountName + ".txt";
    f.open(filename.c_str(), std::ios::out);
    f << Doctor.DoctorId << "#" << Doctor.AccountName << "#" << Doctor.Name << "#" << Doctor.Age << "#" << Doctor.Sex << "#" << Doctor.Address << "#" << Doctor.PhoneNumber << "#" << Doctor.Major << std::endl;
    f.close();
}
void Dal::Doctor::GetInfor(Dto::Doctor &Doctor)
{
    std::string Age;
    std::ifstream f;
    std::string filename =  Doctor.AccountName + ".txt";
    f.open(filename.c_str(), std::ios::in);  
    std::getline(f, Doctor.DoctorId, '#');
    if (f.eof())
        return;
    std::getline(f, Doctor.AccountName, '#');
    std::getline(f, Doctor.Name, '#');
    std::getline(f, Age, '#');
    Doctor.Age = atoi(Age.c_str());
    std::getline(f, Doctor.Sex, '#');
    std::getline(f, Doctor.Address, '#');
    std::getline(f, Doctor.PhoneNumber, '#');
    std::getline(f, Doctor.Major);
}

//Function for Patient
void Dal::Patient::SaveInfor(Dto::Patient Patient)
{
    std::ofstream f;
    std::string filename = Patient.AccountName + ".txt";
    f.open(filename.c_str(), std::ios::out);
    f << Patient.AccountName << "#" << Patient.Name << "#" << Patient.Age << "#" << Patient.Sex << "#" << Patient.Address << "#" << Patient.PhoneNumber <<std::endl;
    f.close();
}
void Dal::Patient::GetInfor(Dto::Patient &Patient)
{
    std::string Age;
    std::ifstream f;
    std::string filename = Patient.AccountName + ".txt";
    f.open(filename.c_str(), std::ios::in);
    std::getline(f, Patient.AccountName, '#');
    if (f.eof())
        return;
    std::getline(f, Patient.Name, '#');
    std::getline(f, Age, '#');
    Patient.Age = atoi(Age.c_str());
    std::getline(f, Patient.Sex, '#');
    std::getline(f, Patient.Address, '#');
    std::getline(f, Patient.PhoneNumber);
}
void Dal::Patient::SaveSchedule(Dto::Schedule Patient)
{
    std::ofstream f;
    f.open("PatientRequest.txt", std::ios::app);
    f << Patient.DoctorId << "#" << Patient.AccountName << "#" << Patient.Name << "#" << Patient.Age << "#" << Patient.Sex << "#" << Patient.Address << "#" << Patient.PhoneNumber <<"#" << Patient.Symptom << "#" << Patient.Date << std::endl;
    f.close();
}
void Dal::Person::SaveQuestion(Dto::Question Question)
{
    std::ofstream f;
    f.open("AcceptedQuestion.txt", std::ios::app);
    f << Question.DoctorId << "#" << Question.AccountName << "#" << Question.PatientQuestion << "#" << Question.Answer << std::endl;
    f.close();
}
void Dal::Person::QueueQuestion(std::list<Dto::Question>& list)
{
    std::ifstream f;
    f.open("QueueQuestion.txt", std::ios::in);
    Dto::Question Question;
    while (true)
    {
        std::getline(f, Question.DoctorId, '#');
        if (f.eof())
            break;
        std::getline(f, Question.AccountName, '#');
        std::getline(f, Question.PatientQuestion, '#');
        std::getline(f, Question.Answer);
        list.push_back(Question);
    }
}
void Dal::Person::AcceptedQuestion(std::list<Dto::Question>& list)
{
    std::ifstream f;
    Dto::Question Question;
    f.open("AcceptedQuestion.txt", std::ios::in);
    while (true)
    {
        std::getline(f, Question.DoctorId, '#');
        if (f.eof())
            break;
        std::getline(f, Question.AccountName, '#');
        std::getline(f, Question.PatientQuestion, '#');
        std::getline(f, Question.Answer);
        list.push_back(Question);
    }
}