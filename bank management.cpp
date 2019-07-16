#include<iostream>
#include<iomanip>
#include <cstdlib>
#include<fstream>
#include<cctype>
using namespace std;
class Account
{
private:
	int account_no;
	char name[100];
	int deposit;
	char type;
public:
	void create_account();
	void show_account() const;
	void modify();
	void deposite(int);
	void withdraw(int);
	void report() const;
	int retaccount_no() const;
	int retdeposit() const;
	char rettype() const;
};


void Account::create_account()
{
	cout<<"\nEnter The account No. :";
	cin>>account_no;
	cout<<"\n\nEnter The Name of The account Holder : ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\nEnter Type of The account (Current/Saving) : ";
	cin>>type;
	type=toupper(type);
	cout<<"\nEnter The Initial amount(>=500 for Saving and >=1000 for current ) : ";
	cin>>deposit;
	cout<<"\n\n\nAccount Created..";
}

void Account::show_account() const
{
	cout<<"\nAccount No. : "<<account_no;
	cout<<"\nAccount Holder Name : ";
	cout<<name;
	cout<<"\nType of Account : "<<type;
	cout<<"\nBalance amount : "<<deposit;
}

void Account::modify()
{
	cout<<"\nAccount No. : "<<account_no;
	cout<<"\nModify Account Holder Name : ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\nModify Type of Account : ";
	cin>>type;
	type=toupper(type);
	cout<<"\nModify Balance amount : ";
	cin>>deposit;
}


void Account::deposite(int x)
{
	deposit+=x;
}

void Account::withdraw(int x)
{
	deposit-=x;
}

void Account::report() const
{
	cout<<account_no<<setw(10)<<" "<<name<<setw(10)<<" "<<type<<setw(6)<<deposit<<endl;
}


int Account::retaccount_no() const
{
	return account_no;
}

int Account::retdeposit() const
{
	return deposit;
}

char Account::rettype() const
{
	return type;
}


    void write_account();
    void display_sp(int);
    void modify_account(int);
    void delete_account(int);
    void display_all();
    void deposit_withdraw(int, int);
    void intro();


void write_account()
{
	Account ac;
	ofstream outFile;
	outFile.open("account.txt",ios::binary|ios::app);
	ac.create_account();
	outFile.write(reinterpret_cast<char *> (&ac), sizeof(Account));
	outFile.close();
}



void display_sp(int n)
{
	Account ac;
	bool flag=false;
	ifstream inFile;
	inFile.open("account.txt",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\nBALANCE DETAILS\n";

    	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(Account)))
	{
		if(ac.retaccount_no()==n)
		{
			ac.show_account();
			flag=true;
		}
	}
	inFile.close();
	if(flag==false)
		cout<<"\n\nAccount number does not exist";
}

void modify_account(int n)
{
	bool found=false;
	Account ac;
	fstream File;
	File.open("account.txt",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(Account));
		if(ac.retaccount_no()==n)
		{
			ac.show_account();
			cout<<"\n\nEnter The New Details of account"<<endl;
			ac.modify();
			int pos=(-1)*static_cast<int>(sizeof(Account));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(Account));
			cout<<"\n\n\t Record Updated";
			found=true;
		  }
	}
	File.close();
	if(found==false)
		cout<<"\n\n Record Not Found ";
}


void delete_account(int n)
{
	Account ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.txt",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	outFile.open("Temp.txt",ios::binary);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(Account)))
	{
		if(ac.retaccount_no()!=n)
		{
			outFile.write(reinterpret_cast<char *> (&ac), sizeof(Account));
		}
	}
	inFile.close();
	outFile.close();
	remove("account.txt");
	rename("Temp.txt","account.txt");
	cout<<"\n\n\tRecord Deleted ..";
}

void display_all()
{
	Account ac;
	ifstream inFile;
	inFile.open("account.txt",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(Account)))
	{
		ac.report();
	}
	inFile.close();
}

void deposit_withdraw(int n, int option)
{
	int amt;
	bool found=false;
	Account ac;
	fstream File;
	File.open("account.txt", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(Account));
		if(ac.retaccount_no()==n)
		{
			ac.show_account();
			if(option==1)
			{
				cout<<"\n\n\tTO DEPOSITE AMOUNT ";
				cout<<"\n\nEnter The amount to be deposited";
				cin>>amt;
				ac.deposite(amt);
			}
			if(option==2)
			{
				cout<<"\n\n\tTO WITHDRAW AMOUNT ";
				cout<<"\n\nEnter The amount to be withdraw";
				cin>>amt;
				int bal=ac.retdeposit()-amt;
				if((bal<500 && ac.rettype()=='S') || (bal<1000 && ac.rettype()=='C'))
                {
					cout<<"Insufficience balance";
                }
				else
                {
					ac.withdraw(amt);
                }
			}
			int pos=(-1)*static_cast<int>(sizeof(ac));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(Account));
			cout<<"\n\n\t Record Updated";
			found=true;
	       }
         }
	File.close();
	if(found==false)
		cout<<"\n\n Record Not Found ";
}

void intro()
{
    cout<<endl;
    cout<<endl;
    cout<<endl;
	cout<<setw(70)<< "BANK MANAGEMENT SYSTEM"<<endl;
	cout<<setw(60)<<"Press Enter."<<endl;
	cin.get();
}

int main()
{
	char ch;
	int num;
	intro();
	do
	{
		system("cls");
		cout<<setw(29)<<"MAIN MENU"<<endl;
		cout<<setw(35)<<"01. NEW ACCOUNT"<<endl;
		cout<<setw(38)<<"02. DEPOSIT AMOUNT"<<endl;
		cout<<setw(39)<<"03. WITHDRAW AMOUNT"<<endl;
		cout<<setw(39)<<"04. BALANCE ENQUIRY"<<endl;;
		cout<<setw(47)<<"05. ALL ACCOUNT HOLDER LIST"<<endl;
		cout<<setw(40)<<"06. CLOSE AN ACCOUNT"<<endl;
		cout<<setw(41)<<"07. MODIFY AN ACCOUNT"<<endl;
		cout<<setw(28)<<"08. EXIT"<<endl;
		cout<<setw(53)<<"Select Your Option From (1 To 8) ";
		cin>>ch;

		system("cls");

		switch(ch)
		{
		case '1':
			write_account();
			break;
		case '2':
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			deposit_withdraw(num, 1);
			break;
		case '3':
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			deposit_withdraw(num, 2);
			break;
		case '4':
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			display_sp(num);
			break;
		case '5':
			display_all();
			break;
		case '6':
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			delete_account(num);
			break;
		 case '7':
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			modify_account(num);
			break;
		 case '8':
			cout<<"\n\n\tThanks for using bank managemnt system";
			break;
		 default :cout<<"\a";
		}
		cin.ignore();
		cin.get();
	}
	while(ch!='8');
	return 0;
}
