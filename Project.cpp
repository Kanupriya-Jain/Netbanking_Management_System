// Include all required Built-in libraries
#include <bits/stdc++.h>
#include <conio.h>
#include <windows.h>
#include <unistd.h>

using namespace std;

// class ACCOUNT for the account of the customers
class account
{
 private:

  int accountno;
  string name;
  long balance;
  string password;

 public:

  string retname();
  string retpass();
  int retaccno();
  void new_account();
  void show_account();
  void add_deposit();
  void withdraw();
  void modify();
  void printname();
  void printpass();
};

void account::printname()
{
  cout<<name;
}

void account::printpass()
{
  cout<<password;
}


// Function to make a new account while signing up...
void account::new_account()
{
 cout<<"Enter the Account Number  ";
 cin>>accountno;
 cout<<"Enter your name  ";
 cin.ignore(256, '\n');
 getline (cin, name);
 cout<<"Enter the initial amount (>=500)  ";
 cin>>balance;
 cout<<"Create a password  ";
 for( int i=0; i<5; i++)
 {
  char c;
  c=getch();
  if(c == '\r')
    break;
  cout<<"*";
  password.push_back(c);
 }
 

 if(balance<500)
  {
   cout<<"\n\nCannot create the account. Low balance";
   cout<<"\n\n\tTry again ";
   cout<<"\n\nPress any key to go to the HOME PAGE ";
  }

 else
 {
  cout<<"\n\nAccount created Successfully";
  cout<<"\n\nNow, login using this account ";
  cout<<"\n\nPress any key to go to the HOME PAGE ";
 }

 getch();
}


// Function to show the account delails
void account::show_account()
{
 cout<<"\n\tAccount details are as follows \n";
 cout<<"\n\tAccount Number: "<<accountno;
 cout<<"\n\tName: "<<name;
 cout<<"\n\tCurrent Balance: "<<balance;
}


// Funtion to add money to the account
void account::add_deposit()
{
 int add;
 cout<<"Enter the amount to be added ";
 cin>>add;
 balance=balance+add;
 cout<<"\n\tYour final balance is: "<<balance;
}


//Funtion to withdraw money from the account
void account::withdraw()
{
 int subtract;
 cout<<"Enter the amount to be withdrawn ";
 cin>>subtract;
 if(balance<subtract)
  cout<<" Money can't be withdrawn. Low balance";
 else
  balance=balance-subtract;
 cout<<"Your final balance is: "<<balance;
}


//Function to modify details of your account
void account::modify()
{
cout<<"\nEnter new account number \n";
cin>>accountno;
cout<<"Enter new name ";
cin.ignore(256, '\n');
getline (cin, name);
cout<<"Enter new password ";
 for( int i=0; i<5; i++)
 {
  char c;
  c = getch();
  if(c== '\r')
    break;
  cout<<"*";
  password.push_back(c);
 }

 cout<<"\n\n\tDetails have been updated";
}


//Function to return data members
string account::retname()
{
 return name;
}

string account::retpass()
{
 return password;
}

int account::retaccno()
{
 return accountno;
}

//Function to delete the account
void deletion()
{
 ifstream fin("BANK.DAT", ios::binary);
 ofstream fout("ABC.DAT", ios::binary);
 account a;
 int num;
 int var=0;
 cout<<"Enter the account no. to be deleted ";
 cin>>num;
 while(!fin.eof())
 {
  fin.read((char*)&a,sizeof a);
  if(num!=a.retaccno())
   {
    fout.write((char*)&a, sizeof a);
   }
  else
   cout<<"Account Deleted ";
   var++;
 }
 if(var==0)
  cout<<"Account not found";
 fin.close();
 fout.close();
 remove("BANK.DAT");
 rename("ABC.DAT","BANK.DAT");
}


// Here, the execution starts
int main()
{
 system("cls");
 int choice = 0;
 string name;
 string pass;
 fstream file("BANK.DAT");
 account acc;

// Page 1 begins
while (choice != 3) 
{
 cout<<"\n      ______________________\n";
 cout<<"\n             GRINGOTTS";
 cout<<"\n      Welcome to Net Banking!!";
 cout<<"\n      ______________________";

 cout<<"\n\n";
 cout<<" 1.Login (Only after Signup)";
 cout<<"\n 2.Signup ";
 cout<<"\n 3.Exit ";
 cout<<"\n\n Enter your choice  ";
 cin>>choice;

 if(choice == 1)
 {
	  int flag = 0;
    system("cls");
	  cout<<"Enter your username: ";
    cin.ignore(256, '\n');
    getline (cin, name);
	  cout<<"Enter your password (exactly 5 characters)  ";
	  for(int i=0; i<5; i++)
	  {
      char c;
      c=getch();
      if (c == '\r')
        break;
	    cout<<"*";
      pass.push_back(c);
	  }
  fstream file;
	file.open("BANK.DAT",ios::binary|ios::app);
	file.seekg(0);
	while(!file.eof())
	{
	  file.read((char*)&acc, sizeof(acc));
    
	  if( name.compare(acc.retname())==0 && pass.compare(acc.retpass())==0)
		{
		  flag = 1;
		  system("cls");
		  int option;
		  do
		  {
		  cout<<"\n\n";
		  cout<<"Hello "<<acc.retname();
		  cout<<"\nSelect a service: \n";
		  cout<<"  1.Show Account info \n";
		  cout<<"  2.add deposit \n";
		  cout<<"  3.withdraw money\n";
		  cout<<"  4.Modify your account\n";
		  cout<<"  5.Delete your account\n";
		  cout<<"  6.Exit\n";
		  cout<<"\n Enter your choice ";
		  cin>>option;
		  switch(option)
		  {
		   case 1: {
			   acc.show_account();
			   getch();
			  }
		    break;
		   case 2: {
			   acc.add_deposit();
			   getch();
			  }
		    break;
		   case 3: {
			   acc.withdraw();
			   getch();
			  }
		    break;
		   case 4: {
			   file.seekg(-(sizeof acc), ios::cur);
			   acc.modify();
			   file.write((char*)&acc, sizeof acc);
			   getch();
			  }
		    break;
		   case 5: {
			   deletion();
			   getch();
			  }
		    break;
		  }

		  } while(option!=6);
		}


   }
   file.close();
   if(flag==0)
   {
    cout<<"\n\n Inavlid Credentials ";
    
   }


  }

else if(choice == 2)
  {
    system("cls");
    ofstream outfile;
    outfile.open("BANK.DAT",ios::binary|ios::app);
    acc.new_account();
    
    outfile.write((char*)&acc,sizeof acc);
    
    outfile.close();
    
  }

else if (choice != 1 && choice != 2 && choice != 3)
  {
    cout<<"\n Invalid Choice ";
    cout<<"\n Press any key to re-enter your choice ";
    getch();
  }
}
getch();
return 0;
}
