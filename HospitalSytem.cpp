#include"Gui.h"
Dto::Account Account;
void CreateAllFile()
{
	std::ofstream f;
	f.open("account.txt",std::ios::app);
	f.close();
}
int main()
{
	srand((int)time(0));
	Gui::Account CurrentAccount;
	Gui::MenuInterface MenuInterface;
	CreateAllFile();
	while (true)
	{
		if (CurrentAccount.MenuLogin(Account) == false)
			return 0;
		MenuInterface.MainMenu(Account);
	}
}