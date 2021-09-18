
#include<iostream>
#include<fstream>
#include<cctype> //For character functions like toupper()
#include<iomanip>

using namespace std;

// class ACCOUNT for the account of the customers
class account
{

private:
	int acno;          			 // Account Number
	char name[500];    			 // Account Holder Name
	long long int balance;       // Account Balance
	char type;					 // Type of Account - Current or Savings

public:
	void create_account();
	void show_account() const;
	void modify_account();
	void deposit(int);
	void withdraw(int);
	void report() const;
	int ret_acno() const;
	int ret_balance() const;
	char ret_type() const;
};

int flag = 0;

void account::create_account()
{
	system("CLS");
	cout<<"\n\t\t\tEnter the Account No. : ";
	cin>>acno;
	cout<<"\n\n\t\t\tEnter the Name of Account holder : ";
	cin.ignore();
	cin.getline(name,500);
	cout<<"\n\t\t\tEnter Type of the Account (C/S) : ";
	cin>>type;
	type=toupper(type);
	cout<<"\n\t\t\tEnter The Initial amount (>=500) : ";
	cin>>balance;
	if(balance < 500)
	{
		cout<<"\n\t\tBalance is less than Minimum Required Balance.";
		cout<<"\n\t\tPress any key to return to main menu";
	}
	else
	{
		cout<<"\n\n\t\t\tCongratulations! Account Created...";
		flag = 1;
	}
}

void account::show_account() const
{
	cout<<"\n\t\t\tAccount Number : "<<acno;
	cout<<"\n\t\t\tAccount Holder Name : ";
	cout<<name;
	cout<<"\n\t\t\tType of Account : "<<type;
	cout<<"\n\t\t\tAccount Balance : "<<balance;
}


void account::modify_account()
{
	cout<<"\n\t\t\tAccount No. : "<<acno;
	cout<<"\n\t\t\tModify Account Holder Name : ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\n\t\t\tModify Type of Account : ";
	cin>>type;
	type=toupper(type);
}


void account::deposit(int x)
{
	balance+=x;
	cout<<"\n\t\tAmount Deposited...";
}

void account::withdraw(int x)
{

		balance = balance - x;
		cout<<"\n\t\t\tAmount withdrawn...";
	
}

void account::report() const
{
	cout<<acno<<setw(10)<<" "<<name<<setw(8)<<" "<<type<<setw(10)<<balance<<endl;
}

int account::ret_acno() const
{
	return acno;
}

int account::ret_balance() const
{
	return balance;
}

char account::ret_type() const
{
	return type;
}



void write_account();
void display_account(int);
void modify_account(int);
void delete_account(int);
void display_all();
void deposit_withdraw(int, int);

int main()
{
	int option;
	int num;
	do
	{
	system("CLS");
	cout<<"\n\n\t\t\t\t------------------------\n";
	cout<<"\t\t\t\t\tGringotts\n";
	cout<<"\n\t\t\t\tWelcome to Net-Banking!!";
	cout<<"\n\t\t\t\t------------------------\n";

		cout<<"\t\t\t\t    ::MAIN MENU::\n";
		cout<<"\t\t\t\t------------------------\n";
		cout<<"\n\t\t\t\t1. CREATE A NEW ACCOUNT";
		cout<<"\n\t\t\t\t2. DEPOSIT MONEY";
		cout<<"\n\t\t\t\t3. WITHDRAW MONEY";
		cout<<"\n\t\t\t\t4. BALANCE ENQUIRY";
		cout<<"\n\t\t\t\t5. LIST OF ALL ACCOUNTS";
		cout<<"\n\t\t\t\t6. CLOSE AN ACCOUNT";
		cout<<"\n\t\t\t\t7. MODIFY AN ACCOUNT";
		cout<<"\n\t\t\t\t8. EXIT";
		cout<<"\n\n\t\t\t\tEnter your choice (1-8): ";
		cin>>option;

		switch(option)
		{
		case 1:
			write_account();
			break;
		case 2:
			system("CLS");
			cout<<"\n\n\t\t\tEnter The account No. : "; cin>>num;
			deposit_withdraw(num, 1);
			break;
		case 3:
			system("CLS");
			cout<<"\n\n\t\t\tEnter The account No. : "; cin>>num;
			deposit_withdraw(num, 2);
			break;
		case 4:
			system("CLS");
			cout<<"\n\n\t\t\tEnter The account No. : "; cin>>num;
			display_account(num);
			break;
		case 5:
			display_all();
			break;
		case 6:
			system("CLS");
			cout<<"\n\n\t\t\tEnter The account No. : "; cin>>num;
			delete_account(num);
			break;
		 case 7:
		 	system("CLS");
			cout<<"\n\n\t\t\tEnter The account No. : "; cin>>num;
			modify_account(num);
			break;
		 case 8:
		 	system("CLS");
			cout<<"\n\n\t\t\tHope you Enjoyed";
			cout<<"\n\n\t\t\t\t- Kanupriya Jain";
			break;
		 default :
		 	cout<<"Wrong Input\n";
			cout<<"Press any key to see tha main menu";
		}
		cin.ignore();
		cin.get();
    }while(option != 8);
	return 0;
}


void write_account()
{
	account ac;
	ofstream outFile;
	outFile.open("account.dat",ios::binary|ios::app);
	ac.create_account();
	if(flag == 1)
	outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
	outFile.close();
}

void display_account(int n)
{
	account ac;
	bool flag=false;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\n\t\t\tACCOUNT DETAILS\n";
    	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if(ac.ret_acno()==n)
		{
			ac.show_account();
			flag=true;
		}
	}
    inFile.close();
	if(flag==false)
		cout<<"\n\n\t\t\tAccount number does not exist";
}



void modify_account(int n)
{
	bool found=false;
	account ac;
	fstream File;
    File.open("account.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if(ac.ret_acno()==n)
		{
			ac.show_account();
			cout<<"\n\n\t\t\tEnter The New Details of account"<<endl;
			ac.modify_account();
			int pos=(-1)*static_cast<int>(sizeof(account));
			File.seekp(pos,ios::cur); //fncallat1353
		    File.write(reinterpret_cast<char *> (&ac), sizeof(account));
		    cout<<"\n\n\t\t\tRecord Updated";
		    found=true;
		  }
	}
	File.close();
	if(found==false)
		cout<<"\n\n\t\t\tRecord Not Found ";
}



void delete_account(int n)
{
	int flag = 1;
	account ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	outFile.open("Temp.dat",ios::binary);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if(ac.ret_acno()!=n)
		{
			outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
		}
	}
    inFile.close();
	outFile.close();
	remove("account.dat");
	rename("Temp.dat","account.dat");
	cout<<"\n\n\t\t\tRecord Deleted ..";
}


void display_all()
{
	system("CLS");
	account ac;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\n\n\t\tACCOUNT HOLDER LIST\n\n";
	cout<<"====================================================\n";
	cout<<"A/c no.      NAME           Type     Balance\n";
	cout<<"====================================================\n";
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		ac.report();
	}
	inFile.close();
}


void deposit_withdraw(int n, int option)
{
	int amt;
	bool found=false;
	account ac;
	fstream File;
    File.open("account.dat", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if(ac.ret_acno()==n)
		{
			ac.show_account();
			if(option==1)
			{
				cout<<"\n\n\t\t\tTO DEPOSITSS AMOUNT";
				cout<<"\n\n\t\t\tEnter The amount to be deposited: ";
				cin>>amt;
				ac.deposit(amt);
			}
		    if(option==2)
			{
				cout<<"\n\n\t\t\tTO WITHDRAW AMOUNT";
				cout<<"\n\n\t\t\tEnter The amount to be withdraw: ";
				cin>>amt;
				int bal=ac.ret_balance()-amt;
				if(bal<0)
					cout<<"\n\t\t\tInsufficience balance";
				else if(bal < 500)
				{
					cout<<"\n\t\t\tCannot Withdraw, Minimum required balance is 500";
				}
				else
				{
					ac.withdraw(amt);
					cout<<"\n\n\t\t\tRecord Updated";
				}
		      }
			int pos=(-1)*static_cast<int>(sizeof(ac));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(account));
			found=true;
	       }
         }
    File.close();
	if(found==false)
		cout<<"\n\n\t\t\tRecord Not Found ";
}

