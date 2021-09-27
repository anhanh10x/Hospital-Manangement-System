#include"Gui.h"

//Function of Gui
void Gui::GotoXY(int x, int y)
{
    HANDLE a;
    COORD b;
    fflush(stdout);
    b.X = x;
    b.Y = y;
    a = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(a, b);
}
int Gui::WhereX()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
        return csbi.dwCursorPosition.X;
    return -1;
}
int Gui::WhereY()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
        return csbi.dwCursorPosition.Y;
    return -1;
}

void Gui::ShowCur(bool CursorVisibility)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursor = { 1, CursorVisibility };
    SetConsoleCursorInfo(handle, &cursor);
}
void Gui::Loading()
{
    system("cls");
    std::cout << std::setw(25);
    Gui::ShowCur(0);
    std::cout << "LOADING.......";
    std::cout << std::endl;
    for (int i = 1; i <= 10; i++)
    {
        std::cout << (char)177;
        Sleep(60);
    }
    for (int i = 10; i <= 11; i++)
    {
        std::cout << (char)177;
        Sleep(400);
    }
    for (int i = 11; i <= 14; i++)
    {
        std::cout << (char)177;
        Sleep(180);
    }
    for (int i = 14; i <= 31; i++)
    {
        std::cout << (char)177;
        Sleep(50);
    }
    Gui::ShowCur(1);
}
void Gui::ClearRow(int FirstRow, int LastRow)
{
    for(int i = FirstRow; i <= LastRow; i++)
    {
        GotoXY(0, i);
        std::cout << "                                                ";
    }
    Gui::GotoXY(0,FirstRow);
}
void Gui::ClearTyping(std::string StringBefore)
{
    std::string EmptySpace;
    for (int i = 1; i < 100; i++)
        EmptySpace.push_back(' ');
    GotoXY(0, WhereY() - 1);
    std::cout <<EmptySpace;
    GotoXY(StringBefore.length(), WhereY() - 1);
    for (int i = 1; i < 50; i++)
        EmptySpace.pop_back();
    std::cout << EmptySpace;
    GotoXY(StringBefore.length(), WhereY());
}
std::string Gui::CreateId(std::string Regency)
{
    std::string Id="";
    if (Regency == "Doctor") {
        Id.push_back('D');
        for (int i = 0; i < 4; i++)
        {
            Id.push_back((char)Gui::Random(0, 9) + 48);
        }
    }
    else
    {
        Id.push_back('P');
        for (int i = 0; i < 4; i++)
        {
            Id.push_back((char)Gui::Random(0, 9) + 48);
        }
    }
    return Id;
}
int Gui::Random(int minN, int maxN) {
    return minN + rand() % (maxN + 1 - minN);
}
//Function of Login Interface
bool Gui::Account::CreatAccount()
{
    system("cls");
    Dto::Account NewAccount;
    std::cout << std::setw(25);
    std::cout << "CREATE A NEW ACCOUNT" << std::endl;
    std::cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" << std::endl << std::endl;
    std::cout << "Account name: ";
    while (true)
    {
        std::getline(std::cin, NewAccount.Username);
        if (Bl::Account::CheckNameExis(NewAccount.Username) == true)
        {
            std::cout << "Ten tai khoan da ton tai. Vui long thu lai. " << std::endl;
            Sleep(1500);
            Gui::ClearTyping("Account name: ");
            continue;
        }
        break;
    }
    std::cout << "Password: ";
    while (true)
    {
        std::getline(std::cin, NewAccount.Password);
        if (Bl::Account::CheckPassWord(NewAccount.Password) == false)
        {
            std::cout << "It nhat 6 ky tu ca chu va so. Vui long thu lai. " << std::endl;
            Sleep(1500);
            Gui::ClearTyping("Password: ");
            continue;
        }
        break;
    }
    std::cout << "ReEnter Password: ";
    std::getline(std::cin, NewAccount.RePass);
    if (Bl::Account::CreatAccount(NewAccount) == true) {
        std::cout << "Creat Successful. Please Login Once!" << std::endl;
        Sleep(1500);
        return true;
    }
    else
    {
        std::cout << "Creat False. Wrong RePass. Try Again!" << std::endl;
        Sleep(1500);
        return false;
    }
}
bool::Gui::Account::LoginAccount(Dto::Account& CurrentAccount)
{
    system("cls");
    Dto::Account Account;
    std::cout << std::setw(25);
    std::cout << "LOGIN WITH YOUR ACCOUNT" << std::endl;
    std::cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" << std::endl << std::endl;
    std::cout << "Acount name: ";
    std::getline(std::cin, Account.Username);
    std::cout << "Password: ";
    std::getline(std::cin, Account.Password);
    if (Bl::Account::LoginAccount(Account) == true)
    {
        CurrentAccount = Account;
        return true;
    }
    return false;
  
}
bool Gui::Account::MenuLogin(Dto::Account &Account)
{
    system("cls");
    short choice;
    int count = 2;
    std::cout << std::setw(30);
    std::cout << "LOGIN INTERFACE" << std::endl;
    std::cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" << std::endl << std::endl;
    std::cout << "1. Login With Your Account Name" << std::endl;
    std::cout << "2. Creat A New Account Name" << std::endl;
    std::cout << "3. Log Out" << std::endl;
    std::cout << "Insert Your Choice: ";
    std::cin >> choice;
    std::cin.ignore(1);
    while (true)
    {
       
        switch (choice)
        {
        case 1:
            if (Gui::Account::LoginAccount(Account) == true)
            {
                std::cout << "Login Successfull!" << std::endl;
                Sleep(1500);
                Gui::Loading();
                return true;
            }
            else
            {
                std::cout << "Login False. Wrong UserName or PassWord. Try Again < Times: "<<count<<" > " << std::endl;;
                Sleep(1500);
                count--;
                if (count == -1)
                {
                    std::cout << "Ban da het so lan thu. Vui long tao tai khoan moi. " << std::endl;
                    Sleep(1500);
                    choice = 2;
                    break;
                }
                continue;
            }
        case 2:
            if (Gui::Account::CreatAccount() == true)
            {
                count = 3;
                choice = 1;
                break;
            }
            else {
                choice = 2;
                break;
            }
        case 3:
            return false;
        }
    }
}

//Function for MainMenu
void Gui::MenuInterface::Header(Dto::Account Account)
{
    system("cls");
    std::cout << "HOSPITAL MANAGEMANT" << std::endl;
    std::cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" << std::endl;
    std::cout << "Xin chao: " << Account.Username << std::endl << std::endl;
}

 void Gui::MenuInterface::Set(Dto::Person &Person,Dto::Account Account)
{
    system("cls");
    Gui::MenuInterface::Header(Account);
    std::string Age;
    Person.AccountName = Account.Username;
    std::cout << "Full Name: ";
    while (true)
    {
        std::getline(std::cin, Person.Name);
        if (Bl::Person::CheckString(Person.Name, 3, 30) == false)
        {
            std::cout << "Ten khong dung dinh dang. Vui long nhap lai. " << std::endl;
            Sleep(1500);
            Gui::ClearTyping("Full Name: ");
            continue;
        }
        break;
    }
    std::cout << "Age: ";
    while (true)
    {
        std::getline(std::cin, Age);
        if (Bl::Person::CheckAge(atoi(Age.c_str())) == false)
        {
            std::cout << "Tuoi khong dung dinh dang. Vui long nhap lai. " << std::endl;
            Sleep(1500);
            Gui::ClearTyping("Age: ");
            continue;
        }
        Person.Age = atoi(Age.c_str());
        break;
    }
    std::cout << "Sex <1. Man 2. Woman>: ";
    while (true)
    {
        getline(std::cin, Person.Sex);
        if (atoi(Person.Sex.c_str()) == 1)
            Person.Sex = "Man";
        else if (atoi(Person.Sex.c_str()) == 2)
            Person.Sex = "Woman";
        else
        {
            std::cout << "Ban nhap khong dung. Vui long nhap lai. " << std::endl;
            Sleep(1500);
            Gui::ClearTyping("Sex <1. Man 2. Woman>: ");
            continue;
        }
        break;
    }
    std::cout << "Address: ";
    while (true)
    {
        std::getline(std::cin, Person.Address);
   
        if (Bl::Person::CheckString(Person.Address, 3, 30) == false)
        {
            std::cout << "Dia chi khong dung dinh dang." << std::endl;
            Sleep(1500);
            Gui::ClearTyping("Address: ");
            continue;
        }
        break;
    }
    std::cout << "Phone Number: ";
    while (true)
    {
        std::getline(std::cin, Person.PhoneNumber);
        if (Bl::Person::CheckPhoneNumber(Person.PhoneNumber,10) == false)
        {
            std::cout << "So dien thoai khong dung dinh dang. Vui long thu lai. " << std::endl;
            Sleep(1500);
            Gui::ClearTyping("Phone Number: ");
            continue;
        }
        break;
    }
}
 void Gui::MenuInterface::MainMenu(Dto::Account &Account)
 {
     while (true)
     {
         if (Bl::Person::CheckHaveData(Account) == false)
         {
             system("cls");
             Gui::MenuForNewMember* NewMember = new Gui::MenuForNewMember;
             if (NewMember->Menu(Account) == true)
             {
                 Gui::Loading();
                 delete NewMember;
                 continue;
             }
             else
             {
                 return;
             }
         }
         else
         {
             if (Account.Id[0] == 'D')
             {
                 Gui::MenuForDoctor* MenuDoctor = new Gui::MenuForDoctor;
                 if (MenuDoctor->Menu(Account) == false)
                 {
                     delete MenuDoctor;
                     return;
                 }
             }
             else
             {
                 Gui::MenuForPatient* MenuPatient = new Gui::MenuForPatient;
                 if (MenuPatient->Menu(Account) == false)
                 {
                     delete MenuPatient;
                     return;
                 }
             }
         }
     }
 }

//Function for NoInformation Member
 void Gui::MenuForNewMember::Set(Dto::Account &Account)
 {
     short regency = 0;
     Dto::Person Person;
     Gui::MenuInterface::Set(Person,Account);
     std::cout << "Your Regency <1. Doctor 2. Patient.>: ";
     while (true)
     {
         std::cin >> regency;
         std::cin.ignore(1);
         if (regency == 1)
             Person.Regency = "Doctor";
         else if (regency == 2)
             Person.Regency = "Patient";
         else {
             std::cout << "Nhap khong dung dinh dang. Vui long nhap lai" << std::endl;
             Sleep(1500);
             Gui::ClearTyping("Your Regency <1. Doctor 2. Patient.>: ");
             continue;
         }
         break;
     }
     if (Person.Regency == "Doctor")
     {
         Dto::Doctor Doctor = Person;
         std::cout << "Your Major: ";
         while (true)
         {
             std::getline(std::cin, Doctor.Major);
             if (Gui::MenuInterface::CheckString(Doctor.Major, 3, 20) == false)
             {
                 std::cout << "Sai cu phap. Xin moi nhap lai. " << std::endl;
                 Sleep(1500);
                 Gui::ClearTyping("Your Major : ");
                 continue;
             }
             break;
         }
         Account.Id = Gui::CreateId(Doctor.Regency);
         std::cout << "Your Id: " << Account.Id << std::endl;
         Doctor.DoctorId = Account.Id;
         Bl::Doctor::SaveInfor(Doctor);
     }
     else
     {
         Dto::Patient Patient;
         Patient = Person;
         Account.Id = Gui::CreateId(Patient.Regency);
         std::cout << "Your Id: " << Account.Id << std::endl;
         Bl::Patient::SaveInfor(Patient);
     }
     Bl::Person::SaveIdAccount(Account.Id);
     std::cout << "Cap nhat thong tin thanh cong! Doi he thong loading lai. ";
     Sleep(2500);
 }
bool Gui::MenuForNewMember::Menu(Dto::Account &Account)
{
    system("cls");
    Gui::MenuInterface::Header(Account);
    std::cout << "1. Bo sung thong tin tai khoan." << std::endl;
    std::cout << "2. Log Out." << std::endl<<std::endl;
    std::cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" << std::endl;
    short choice;
    std::cout << "Nhap lua chon: ";
    while (true)
    {
        std::cin >> choice;
        std::cin.ignore(1);
        if (choice == 1) {
            Gui::MenuForNewMember::Set(Account);
            return true;
        }
        else if (choice == 2)
        {
            return false;
        }
        else
        {
            std::cout << "Wrong choice. Xin moi nhap lai!" << std::endl;
            Sleep(1500);
            Gui::ClearTyping("Nhap lua chon: ");
            continue;
        }
        break;
    }
    return true;
}

//Funtion For Doctor
void Gui::MenuForDoctor::Set(Dto::Account Account)
{
    Dto::Person Person;
    Gui::MenuInterface::Set(Person,Account);
    Dto::Doctor Doctor=Person;
    Doctor.Regency = "Doctor";
    std::cout << "Your Regency: Doctor" << std::endl;
    std::cout << "Your Major: ";
    while (true)
    {
        std::getline(std::cin, Doctor.Major);
        if (Bl::Person::CheckString(Doctor.Major, 4, 30) == false)
        {
            std::cout << "Sai cu phap. Vui long nhap lai. " << std::endl;
            Sleep(1500);
            continue;
        }
        break;
    }
    Doctor.DoctorId = Account.Id;
    std::cout << "Your Id: " << Doctor.DoctorId << std::endl;
    Bl::Doctor::SaveInfor(Doctor);
}
void Gui::MenuForDoctor::GetInfor(Dto::Account Account)
{
    Dto::Doctor Doctor;
    Bl::Doctor::GetInfor(Doctor, Account);
    Gui::MenuInterface::Header(Account);
    std::cout << "Full name: " << Doctor.Name << std::endl;
    std::cout << "Age: " << Doctor.Age << std::endl;
    std::cout << "Sex: " << Doctor.Sex << std::endl;
    std::cout << "Address: " << Doctor.Address << std::endl;
    std::cout << "Phone Number: " << Doctor.PhoneNumber << std::endl;
    std::cout << "Your Regency: Doctor" << std::endl;
    std::cout << "Your Major: " << Doctor.Major << std::endl;
    std::cout << "Your Id: " << Doctor.DoctorId << std::endl;
}
bool Gui::MenuForDoctor::Menu(Dto::Account Account)
{
    short choice;
    while(true)
    {
        system("cls");
        Gui::MenuInterface::Header(Account);
        std::cout << "1. Bo sung thong tin tai khoan." << std::endl;
        std::cout << "2. Xem thong tin ca nhan." << std::endl;
        std::cout << "3. Xem lich kham." << std::endl;
        std::cout << "4. Xem lich hen duoc de nghi." << std::endl;
        std::cout << "5. Tra loi cau hoi cau benh nhan." << std::endl;
        std::cout << "6. Log Out." << std::endl;
        std::cout << "Nhap lua chon: ";
        std::cin >> choice;
        std::cin.ignore(1);
        switch (choice)
        {
        case 1:
            Gui::MenuForDoctor::Set(Account);
            std::cout << "Cap nhat thong tin thanh cong. Quay lai man hinh chinh." << std::endl;
            Sleep(1500);
            break;
        case 2:
            Gui::MenuForDoctor::GetInfor(Account);
            while (true)
            {
                std::cout << "1. Quay lai." << std::endl;
                std::cout << "Nhap lua chon: ";
                std::cin >> choice;
                std::cin.ignore(1);
                if (choice == 1)
                    break;
                else
                {
                    std::cout << "Xin moi nhap lai" << std::endl;
                    Sleep(1500);
                    Gui::ClearTyping("Nhap lua chon: ");
                    continue;
                }
            }
            break;
        case 3:
            Gui::MenuForDoctor::Schedule(Account);
            while (true)
            {
                std::cout << "1. Quay lai. " << std::endl;
                std::cout << "Nhap lua chon: ";
                std::cin >> choice;
                std::cin.ignore(1);
                if (choice == 1)
                    break;
                else
                {
                    std::cout << "Xin moi nhap lai!" << std::endl;
                    Sleep(1500);
                    Gui::ClearTyping("Nhap lua chon: ");
                    continue;
                }
            }
            break;
        case 4:
            Gui::MenuForDoctor::PatientRequest(Account);
            while(true)
            {
                std::cout << "1. Quay lai." << std::endl;
                std::cout << "Nhap lua chon: ";
                std::cin >> choice;
                std::cin.ignore(1);
                if (choice == 1)
                    break;
                else
                {
                    std::cout << "Xin moi nhap lai!" << std::endl;
                    Sleep(1500);
                    Gui::ClearTyping("Nhap lua chon: ");
                    continue;
                }
            }
            break;
        case 5:
            Gui::MenuForDoctor::AnswerQuestion(Account);
            while (true)
            {
                std::cout << "1. Quay lai." << std::endl;
                std::cout << "Nhap lua chon: ";
                std::cin >> choice;
                std::cin.ignore(1);
                if (choice == 1)
                    break;
                else
                {
                    std::cout << "Xin moi nhap lai!" << std::endl;
                    Sleep(1500);
                    Gui::ClearTyping("Nhap lua chon: ");
                    continue;
                }
            }
            break;
        case 6:
            return false;
        }
    }
    return true;
}
void Gui::MenuForDoctor::PatientRequest(Dto::Account Account)
{
    system("cls");
    int choice;
    Gui::MenuInterface::Header(Account);
    std::list<Dto::Schedule> list;
    std::list<Dto::Schedule> AcceptedList;
    std::list<Dto::Schedule> DeniedList;
    if (Bl::Person::QueueRequest(list, Account) == false)
    {
        std::cout << "No Request Available. " << std::endl << std::endl;
        return;
    }
    else
    {
        int count = 1;
        std::list<Dto::Schedule> ::iterator head;
        for (head = list.begin(); head != list.end(); ++head)
        {
            Gui::MenuInterface::Header(Account);
            std::cout << "Full Name: " << head->Name << std::endl;
            std::cout << "Age: " << head->Age << std::endl;
            std::cout << "Sex: " << head->Sex << std::endl;
            std::cout << "Address: " << head->Address << std::endl;
            std::cout << "Phone Number: " << head->PhoneNumber << std::endl;
            std::cout << "Symptom: " << head->Symptom << std::endl;
            std::cout << "Date For Exammination: " << head->Date << std::endl;
            std::cout << "###############################" << std::endl << std::endl;
            std::cout << "Requests: " << count << " / " << list.size() << std::endl;
            count++;
            std::cout << "Nhap lua chon < 1. Chap nhan 2. Tu choi >: ";
            while (true)
            {
                std::cin >> choice;
                std::cin.ignore(1);
                if (choice == 1)
                {
                    AcceptedList.push_back(*head);
                    break;
                }
                else if (choice == 2)
                {
                    DeniedList.push_back(*head);
                    break;
                }
                else
                {
                    std::cout << "Sai cu phap. Vui long nhap lai. " << std::endl;
                    Sleep(1500);
                    Gui::ClearTyping("Nhap lua chon < 1. Chap nhan 2. Tu choi >: ");
                    continue;
                }
            }
        }
        Gui::MenuInterface::Header(Account);
        std::cout << "No Request Available. " << std::endl << std::endl;
    }
    Bl::Doctor::SaveSchedule(AcceptedList);
    Bl::Doctor::SaveScheduleDenied(DeniedList);
    return;
}
void Gui::MenuForDoctor::Schedule(Dto::Account Account)
{
    system("cls");
    int choice;
    Gui::MenuInterface::Header(Account);
    std::list<Dto::Schedule> list;
    std::list<Dto::Schedule> templist;
    if (Bl::Person::RequestAccepted(list, Account) == false)
    {
        std::cout << "No Request Available. " << std::endl << std::endl;
        return;
    }
    else
    {
        int count = 1;
        std::list<Dto::Schedule> ::iterator head;
        for (head = list.begin(); head != list.end(); ++head)
        {
            Gui::MenuInterface::Header(Account);
            std::cout << "Full Name: " << head->Name << std::endl;
            std::cout << "Age: " << head->Age << std::endl;
            std::cout << "Sex: " << head->Sex << std::endl;
            std::cout << "Address: " << head->Address << std::endl;
            std::cout << "Phone Number: " << head->PhoneNumber << std::endl;
            std::cout << "Symptom: " << head->Symptom << std::endl;
            std::cout << "Date For Exammination: " << head->Date << std::endl;
            std::cout << "###############################" << std::endl << std::endl;
            std::cout << "Requests: " << count << " / " << list.size() << std::endl;
            count++;
            std::cout << "Nhap lua chon < 1. Next >: ";
            while (true)
            {
                std::cin >> choice;
                std::cin.ignore(1);
                if (choice == 1)
                {
                    break;
                }
                else
                {
                    std::cout << "Sai cu phap. Vui long nhap lai. " << std::endl;
                    Sleep(1500);
                    Gui::ClearTyping("Nhap lua chon < 1. Next 2. Back>: ");
                    continue;
                }
            }
        }
        Gui::MenuInterface::Header(Account);
        std::cout << "No Request Available. " << std::endl << std::endl;
    }
    return;
}
void Gui::MenuForDoctor::AnswerQuestion(Dto::Account Account)
{
    std::list<Dto::Question> list;
    Bl::Person::QueueQuestion(list, Account);
    std::list<Dto::Question> ::iterator head;
    int count = 1;
    for (head = list.begin(); head != list.end(); ++head)
    {
        Gui::MenuInterface::Header(Account);
        std::cout << "Cau hoi cua: " << head->AccountName << std::endl;
        std::cout << "Cau hoi: " << head->PatientQuestion << std::endl;
        std::cout << "*********************" << std::endl;
        std::cout << "Requests: " << count << " / " << list.size() << std::endl << std::endl;
        std::cout << "Nhap cau tra loi cua ban: ";
        std::getline(std::cin, head->Answer);
        Bl::Person::SaveQuestion(*head);
        count++;
    }
    Gui::MenuInterface::Header(Account);
    std::cout << "No Question Available. " << std::endl << std::endl;
    return;
}
//Function for Patient
bool Gui::MenuForPatient::Menu(Dto::Account Account)
{
    short choice;
    while (true)
    {
        system("cls");
        Gui::MenuInterface::Header(Account);
        std::cout << "1. Bo sung thong tin tai khoan." << std::endl;
        std::cout << "2. Xem thong tin ca nhan." << std::endl;
        std::cout << "3. Xem thong tin bac si." << std::endl;
        std::cout << "4. Dat lich kham." << std::endl;
        std::cout << "5. Dat cau hoi cho bac si." << std::endl;
        std::cout << "6. Log Out." << std::endl;
        std::cout << "Nhap lua chon: ";
        std::cin >> choice;
        std::cin.ignore(1);
        switch (choice)
        {
        case 1:
            Gui::MenuForPatient::Set(Account);
            std::cout << "Cap nhat thong tin thanh cong. " << std::endl;
            Sleep(1500);
            break;
        case 2:
            Gui::MenuForPatient::GetInfor(Account);
            while (true)
            {
                std::cout << "1. Quay lai." << std::endl;
                std::cout << "Nhap lua chon: ";
                std::cin >> choice;
                if (choice == 1)
                    break;
                else
                {
                    std::cout << "Xin moi nhap lai" << std::endl;
                    Sleep(1500);
                    Gui::ClearTyping("Nhap lua chon: ");
                    continue;
                }
            }
            break;
        case 3:
            Gui::MenuInterface::Header(Account);
            Gui::MenuForPatient::GetInforDoctor(Account);
            while (true)
            {
                std::cout << "1. Quay lai." << std::endl;
                std::cout << "Nhap lua chon: ";
                std::cin >> choice;
                if (choice == 1)
                    break;
                else
                {
                    std::cout << "Xin moi nhap lai" << std::endl;
                    Sleep(1500);
                    Gui::ClearTyping("Nhap lua chon: ");
                    continue;
                }
            }
            break;
        case 4:
            while (true)
            {
                if (Gui::MenuForPatient::MenuForExamination(Account) == false)
                    break;
            }
            break;
        case 5:
            while (true)
            {
                if (Gui::MenuForPatient::QuestionMenu(Account) == false)
                    break;
            }
            break;
        case 6:
            return false;
        }
    }
    return true;
}
bool Gui::MenuForPatient::QuestionMenu(Dto::Account Account)
{
    system("cls");
    Gui::MenuInterface::Header(Account);
    std::cout << "1. Dat cau hoi. " << std::endl;
    std::cout << "2. Xem cau hoi dang cho. " << std::endl;
    std::cout << "3. Xem cau hoi da duoc tra loi. " << std::endl;
    std::cout << "4. Quay lai man hinh chinh. " << std::endl;
    std::cout << "#############################" << std::endl << std::endl;
    std::cout << "Nhap lua chon cua ban: ";
    int choice = 0;
    while (true)
    {
        std::cin >> choice;
        std::cin.ignore(1);
        switch (choice)
        {
        case 1:
            Gui::MenuForPatient::SetQuestion(Account);
            while (true)
            {
                std::cout << "1. Quay lai." << std::endl;
                std::cout << "Nhap lua chon: ";
                std::cin >> choice;
                if (choice == 1)
                    break;
                else
                {
                    std::cout << "Xin moi nhap lai" << std::endl;
                    Sleep(1500);
                    Gui::ClearTyping("Nhap lua chon: ");
                    continue;
                }
            }
            break;
        case 2:
            Gui::MenuForPatient::RequestQuestion(Account);
            while (true)
            {
                std::cout << "1. Quay lai. " << std::endl;
                std::cout << "Nhap lua chon: ";
                std::cin >> choice;
                std::cin.ignore(1);
                if (choice == 1)
                    break;
                else
                {
                    std::cout << "Xin moi nhap lai!" << std::endl;
                    Sleep(1500);
                    Gui::ClearTyping("Nhap lua chon: ");
                    continue;
                }
            }
            break;
        case 3:
            Gui::MenuForPatient::AcceptedQuestion(Account);
            while (true)
            {
                std::cout << "1. Quay lai. " << std::endl;
                std::cout << "Nhap lua chon: ";
                std::cin >> choice;
                std::cin.ignore(1);
                if (choice == 1)
                    break;
                else
                {
                    std::cout << "Xin moi nhap lai!" << std::endl;
                    Sleep(1500);
                    Gui::ClearTyping("Nhap lua chon: ");
                    continue;
                }
            }
            break;
        case 4:
            return false;
        default:
            std::cout << "Sai cu phap. Moi nhap lai. " << std::endl;
            Gui::ClearTyping("Nhap lua chon cua ban: ");
            continue;
        }
        return true;
    }
}
bool Gui::MenuForPatient::MenuForExamination(Dto::Account Account)
{
    system("cls");
    Gui::MenuInterface::Header(Account);
    std::cout << "1. Dat lich kham. " << std::endl;
    std::cout << "2. Xem lich kham dang cho. " << std::endl;
    std::cout << "3. Xem lich kham da duoc chap nhan. " << std::endl;
    std::cout << "4. Quay lai man hinh chinh. " << std::endl;
    std::cout << "##################################################" << std::endl << std::endl;
    std::cout << "Nhap lua chon cua ban: ";
    int choice = 0;
    while (true)
    {
        std::cin >> choice;
        std::cin.ignore(1);
        switch (choice)
        {
        case 1:
            Gui::MenuForPatient::SetTimeSchedule(Account);
            while (true)
            {
                std::cout << "1. Quay lai." << std::endl;
                std::cout << "Nhap lua chon: ";
                std::cin >> choice;
                if (choice == 1)
                    break;
                else
                {
                    std::cout << "Xin moi nhap lai" << std::endl;
                    Sleep(1500);
                    Gui::ClearTyping("Nhap lua chon: ");
                    continue;
                }
            }
            break;
        case 2:
            Gui::MenuForPatient::PatientRequest(Account);
            while (true)
            {
                std::cout << "1. Quay lai. " << std::endl;
                std::cout << "Nhap lua chon: ";
                std::cin >> choice;
                std::cin.ignore(1);
                if (choice == 1)
                    break;
                else
                {
                    std::cout << "Xin moi nhap lai!" << std::endl;
                    Sleep(1500);
                    Gui::ClearTyping("Nhap lua chon: ");
                    continue;
                }
            }
            break;
        case 3:
            Gui::MenuForPatient::Schedule(Account);
            while (true)
            {
                std::cout << "1. Quay lai. " << std::endl;
                std::cout << "Nhap lua chon: ";
                std::cin >> choice;
                std::cin.ignore(1);
                if (choice == 1)
                    break;
                else
                {
                    std::cout << "Xin moi nhap lai!" << std::endl;
                    Sleep(1500);
                    Gui::ClearTyping("Nhap lua chon: ");
                    continue;
                }
            }
            break;
        case 4:
            return false;
        default:
            std::cout << "Sai cu phap. Moi nhap lai. "<<std::endl;
            Gui::ClearTyping("Nhap lua chon cua ban: ");
            continue;
        }
        return true;
    }
}
void Gui::MenuForPatient::Set(Dto::Account Account)
{
    Dto::Person Person;
    Gui::MenuInterface::Set(Person,Account);
    Dto::Patient Patient = Person;
    Bl::Patient::SaveInfor(Patient);
    return;
}
void Gui::MenuForPatient::GetInfor(Dto::Account Account)
{
    Dto::Patient Patient;
    Bl::Patient::GetInfor(Patient, Account);
    Gui::MenuInterface::Header(Account);
    std::cout << "Full name: " << Patient.Name << std::endl;
    std::cout << "Age: " << Patient.Age << std::endl;
    std::cout << "Sex: " << Patient.Sex << std::endl;
    std::cout << "Address: " << Patient.Address << std::endl;
    std::cout << "Phone Number: " << Patient.PhoneNumber << std::endl;
    std::cout << "Your Regency: Patient" << std::endl;
}
void Gui::MenuForPatient::GetInforDoctor(Dto::Account Account)
{
    std::list<Dto::Doctor> list;
    Bl::Patient::GetDoctorInfor(list);
    std::list<Dto::Doctor> ::iterator head;
    int choice = 0;
    int count = 1;
    int FirstRow=0, LastRow=0;
    for (head = list.begin(); head != list.end(); ++head)
    {
        FirstRow = Gui::WhereY();
        std::cout << "Full Name: " << head->Name << std::endl;
        std::cout << "Age: " << head->Age << std::endl;
        std::cout << "Sex: " << head->Sex << std::endl;
        std::cout << "Address: " << head->Address << std::endl;
        std::cout << "Phone Number: " << head->PhoneNumber << std::endl;
        std::cout << "Major: " << head->Major<< std::endl;
        std::cout << "Doctor Id: " << head->DoctorId << std::endl;
        std::cout << "###############################" << std::endl << std::endl;
        std::cout << "Doctors: " << count << " / " << list.size() << std::endl;
        count++;
        LastRow = Gui::WhereY();
        std::cout << "Nhap lua chon < 1. Next >: ";
        while (true)
        {
            std::cin >> choice;
            std::cin.ignore(1);
            if (choice == 1)
            {
                Gui::ClearRow(FirstRow, LastRow);
                break;
            }
            else
            {
                std::cout << "Sai cu phap. Vui long nhap lai. " << std::endl;
                Sleep(1500);
                Gui::ClearTyping("Nhap lua chon < 1. Next >: ");
                continue;
            }
        }
    }
    Gui::ClearRow(FirstRow, LastRow);
    std::cout << "No Doctor Information Available. " << std::endl << std::endl;
    return;
}
bool Gui::MenuForPatient::CheckId(Dto::Doctor &Doctor)
{
    if (Bl::Patient::CheckId(Doctor) == false)
    {
        return false;
    }
    else
    {
        return true;
    }
}
void Gui::MenuForPatient::SetTimeSchedule(Dto::Account Account)
{
    system("cls");
    Dto::Person Person;
    Gui::MenuInterface::Set(Person, Account);
    Dto::Schedule Patient;
    Patient = Person;
    std::cout << "Your Symptom: ";
    while (true)
    {
        std::getline(std::cin, Patient.Symptom);
        if (Bl::Person::CheckString(Patient.Symptom, 3, 30) == false)
        {
            std::cout << "Khong dung dinh dang. Vui long nhap lai. " << std::endl;
            Sleep(1500);
            Gui::ClearTyping("Your Symptom: ");
            continue;
        }
        break;
    }
    std::cout << "Your Time You want to see Doctor: ";
    std::getline(std::cin, Patient.Date); 
    short choice = 0;
    std::cout << "Do you want to Doctor ID once again <1. Yes 2. No >: ";
    while (true)
    {
        std::cin >> choice;
        std::cin.ignore(1);
        if (choice == 1)
        {
            std::cout << std::endl;
            std::cout << "######################" << std::endl << std::endl;;
            Gui::MenuForPatient::GetInforDoctor(Account);
            break;
        }
        else if (choice == 2)
            break;
        else
        {
            std::cout << "Sai cu phap. Vui long nhap lai. " << std::endl;
            Sleep(1500);
            Gui::ClearTyping("Do you want to Doctor ID once again <1. Yes 2. No >: ");
            continue;
        }
    }
    std::cout << std::endl;
    std::cout << "Enter Doctor Id: ";
    while (true)
    {
        std::getline(std::cin, Patient.DoctorId);
        Dto::Doctor Doctor;
        Doctor.DoctorId = Patient.DoctorId;
        if (Gui::MenuForPatient::CheckId(Doctor) == true)
        {
            std::cout << "Doctor: " << Doctor.Name << " have choosen. " << std::endl;
            break;
        }
        else
        {
            std::cout << "Id khong hop le. Node: Id phai co 'D' dau tien. " << std::endl;
            Sleep(1500);
            Gui::ClearTyping("Enter Doctor Id: ");
            continue;
        }
    }
    std::cout << "Dat lich hen thanh cong. Hay doi bac si cua ban chap nhan nhe. " << std::endl;
    Bl::Patient::SaveSchedule(Patient);
}
void Gui::MenuForPatient::PatientRequest(Dto::Account Account)
{
    system("cls");
    int choice;
    Gui::MenuInterface::Header(Account);
    std::list<Dto::Schedule> list;
    if (Bl::Person::QueueRequest(list, Account) == false)
    {
        std::cout << "No Request Available. " << std::endl << std::endl;
        return;
    }
    else
    {
        int count = 1;
        std::list<Dto::Schedule> ::iterator head;
        for (head = list.begin(); head != list.end(); ++head)
        {
            Gui::MenuInterface::Header(Account);
            std::cout << "Full Name: " << head->Name << std::endl;
            std::cout << "Age: " << head->Age << std::endl;
            std::cout << "Sex: " << head->Sex << std::endl;
            std::cout << "Address: " << head->Address << std::endl;
            std::cout << "Phone Number: " << head->PhoneNumber << std::endl;
            std::cout << "Symptom: " << head->Symptom << std::endl;
            std::cout << "Date For Exammination: " << head->Date << std::endl;
            std::cout << "###############################" << std::endl << std::endl;
            std::cout << "Requests: " << count << " / " << list.size() << std::endl;
            count++;
            std::cout << "Nhap lua chon < 1. Next >: ";
            while (true)
            {
                std::cin >> choice;
                std::cin.ignore(1);
                if (choice == 1)
                {
                    break;
                }
                else if (choice == 2)
                {
                    break;
                }
                else
                {
                    std::cout << "Sai cu phap. Vui long nhap lai. " << std::endl;
                    Sleep(1500);
                    Gui::ClearTyping("Nhap lua chon < 1. Next >: ");
                    continue;
                }
            }
        }
        Gui::MenuInterface::Header(Account);
        std::cout << "No Request Available. " << std::endl << std::endl;
    }
    return;
}
void Gui::MenuForPatient::Schedule(Dto::Account Account)
{
    system("cls");
    int choice;
    Gui::MenuInterface::Header(Account);
    std::list<Dto::Schedule> list;
    std::list<Dto::Schedule> templist;
    if (Bl::Person::RequestAccepted(list, Account) == false)
    {
        std::cout << "No Request Available. " << std::endl << std::endl;
        return;
    }
    else
    {
        int count = 1;
        std::list<Dto::Schedule> ::iterator head;
        for (head = list.begin(); head != list.end(); ++head)
        {
            Gui::MenuInterface::Header(Account);
            std::cout << "Full Name: " << head->Name << std::endl;
            std::cout << "Age: " << head->Age << std::endl;
            std::cout << "Sex: " << head->Sex << std::endl;
            std::cout << "Address: " << head->Address << std::endl;
            std::cout << "Phone Number: " << head->PhoneNumber << std::endl;
            std::cout << "Symptom: " << head->Symptom << std::endl;
            std::cout << "Date For Exammination: " << head->Date << std::endl;
            std::cout << "###############################" << std::endl << std::endl;
            std::cout << "Requests: " << count << " / " << list.size() << std::endl;
            count++;
            std::cout << "Nhap lua chon < 1. Next >: ";
            while (true)
            {
                std::cin >> choice;
                std::cin.ignore(1);
                if (choice == 1)
                {
                    break;
                }
                else
                {
                    std::cout << "Sai cu phap. Vui long nhap lai. " << std::endl;
                    Sleep(1500);
                    Gui::ClearTyping("Nhap lua chon < 1. Next 2. Back>: ");
                    continue;
                }
            }
        }
        Gui::MenuInterface::Header(Account);
        std::cout << "No Request Available. " << std::endl << std::endl;
    }
    return;
}
void Gui::MenuForPatient::SetQuestion(Dto::Account Account)
{
    Gui::MenuInterface::Header(Account);
    std::cout << "***************** Type Your Question Below ***************" << std::endl;
    Dto::Question Question;
    std::cout << "Your Question: ";
    std::getline(std::cin, Question.PatientQuestion);
    std::cout << std::endl;
    int choice=0;
    std::cout << "Do you want to Doctor ID once again <1. Yes 2. No >: ";
    while (true)
    {
        std::cin >> choice;
        std::cin.ignore(1);
        if (choice == 1)
        {
            std::cout << std::endl;
            std::cout << "######################" << std::endl << std::endl;;
            Gui::MenuForPatient::GetInforDoctor(Account);
            break;
        }
        else if (choice == 2)
            break;
        else
        {
            std::cout << "Sai cu phap. Vui long nhap lai. " << std::endl;
            Sleep(1500);
            Gui::ClearTyping("Do you want to Doctor ID once again <1. Yes 2. No >: ");
            continue;
        }
    }
    std::cout << std::endl;
    std::cout << "Enter Doctor Id: ";
    while (true)
    {
        std::getline(std::cin, Question.DoctorId);
        Dto::Doctor Doctor;
        Doctor.DoctorId = Question.DoctorId;
        if (Gui::MenuForPatient::CheckId(Doctor) == true)
        {
            std::cout << "Doctor: " << Doctor.Name << " have choosen. " << std::endl;
            break;
        }
        else
        {
            std::cout << "Id khong hop le. Node: Id phai co 'D' dau tien. " << std::endl;
            Sleep(1500);
            Gui::ClearTyping("Enter Doctor Id: ");
            continue;
        }
    }
    std::cout << "Dat cau hoi thanh cong. Doi bac si cua ban tra loi nhe. " << std::endl;
    Question.AccountName = Account.Username;
    Question.Answer = "0";
    Bl::Person::SaveQuestion(Question);
}
void Gui::MenuForPatient::RequestQuestion(Dto::Account Account)
{
    system("cls");
    int choice;
    Gui::MenuInterface::Header(Account);
    std::list<Dto::Question> list;
    if (Bl::Person::QueueQuestion(list, Account) == false)
    {
        std::cout << "No Question Available. " << std::endl << std::endl;
        return;
    }
    else
    {
        int count = 1;
        Dto::Doctor Doctor;
        std::list<Dto::Question> ::iterator head;
        for (head = list.begin(); head != list.end(); ++head)
        {
            Gui::MenuInterface::Header(Account);
            std::cout << "Your Question: ";
            std::cout << head->PatientQuestion << std::endl << std::endl;
            std::cout << "Information Of The Doctor you chose: " << std::endl;
            Doctor.DoctorId = head->DoctorId;
            if (Gui::MenuForPatient::CheckId(Doctor) == true)
            {
                std::cout << "*******************************" << std::endl;
                std::cout << "Full Name: " << Doctor.Name << std::endl;
                std::cout << "Age: " << Doctor.Age << std::endl;
                std::cout << "Sex: " << Doctor.Sex << std::endl;
                std::cout << "Address: " << Doctor.Address << std::endl;
                std::cout << "Phone Number: " << Doctor.PhoneNumber << std::endl;
                std::cout << "Major: " << Doctor.Major << std::endl;
                std::cout << "*******************************" << std::endl << std::endl;
            }
            std::cout << "Questions: " << count << " / " << list.size() << std::endl;
            count++;
            std::cout << "Nhap lua chon < 1. Next >: ";
            while (true)
            {
                std::cin >> choice;
                std::cin.ignore(1);
                if (choice == 1)
                {
                    break;
                }
                else if (choice == 2)
                {
                    break;
                }
                else
                {
                    std::cout << "Sai cu phap. Vui long nhap lai. " << std::endl;
                    Sleep(1500);
                    Gui::ClearTyping("Nhap lua chon < 1. Next >: ");
                    continue;
                }
            }
        }
        Gui::MenuInterface::Header(Account);
        std::cout << "No Question Available. " << std::endl << std::endl;
    }
    return;
}
void Gui::MenuForPatient::AcceptedQuestion(Dto::Account Account)
{
    system("cls");
    int choice;
    Gui::MenuInterface::Header(Account);
    std::list<Dto::Question> list;
    if (Bl::Person::AcceptedQuestion(list, Account) == false)
    {
        std::cout << "No Question Available. " << std::endl << std::endl;
        return;
    }
    else
    {
        int count = 1;
        std::list<Dto::Question> ::iterator head;
        for (head = list.begin(); head != list.end(); ++head)
        {
            Gui::MenuInterface::Header(Account);
            std::cout << "Your Question: ";
            std::cout << head->PatientQuestion << std::endl << std::endl;
            std::cout << "Doctor Answer: ";
            std::cout << head->Answer << std::endl << std::endl;
            std::cout << "Questions: " << count << " / " << list.size() << std::endl;
            count++;
            std::cout << "Nhap lua chon < 1. Next >: ";
            while (true)
            {
                std::cin >> choice;
                std::cin.ignore(1);
                if (choice == 1)
                {
                    break;
                }
                else if (choice == 2)
                {
                    break;
                }
                else
                {
                    std::cout << "Sai cu phap. Vui long nhap lai. " << std::endl;
                    Sleep(1500);
                    Gui::ClearTyping("Nhap lua chon < 1. Next >: ");
                    continue;
                }
            }
        }
        Gui::MenuInterface::Header(Account);
        std::cout << "No Question Available. " << std::endl << std::endl;
    }
    return;
}
