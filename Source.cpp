#include<iostream>      // Input/output stream
#include<fstream>       // File handling
#include<cctype>        // Character handling (e.g. toupper)
#include<iomanip>       // Formatting output
using namespace std;

//=== CLASS: Bank Account ===//
class account {
	int acno;           // Account number
	char name[50];      // Account holder name
	int deposit;        // Balance
	char type;          // Account type (C/S)
public:
	void create_account();       // Create new account
	void show_account() const;   // Show account details
	void modify();               // Modify account
	void dep(int);               // Deposit
	void draw(int);              // Withdraw
	void report() const;         // Display in tabular form
	int retacno() const;         // Return account number
	int retdeposit() const;      // Return balance
	char rettype() const;        // Return account type
};

//=== FUNCTION: Create New Account ===//
void account::create_account() {
	system("clear");
	cout << "\n\t\t\tEnter the Account No. : ";
	cin >> acno;
	cout << "\n\n\t\t\tPlease Enter the Name of the Account holder Here : ";
	cin.ignore();
	cin.getline(name, 50);
	cout << "\n\t\t\tEnter Type of the Account (C/S) : ";
	cin >> type;
	type = toupper(type);
	cout << "\n\t\t\tEnter The Initial amount : ";
	cin >> deposit;
	cout << "\n\n\t\t\tAccount Created..";
}

//=== FUNCTION: Show Account Details ===//
void account::show_account() const {
	cout << "\n\t\t\tAccount No. : " << acno;
	cout << "\n\t\t\tAccount Holder Name : " << name;
	cout << "\n\t\t\tType of Account : " << type;
	cout << "\n\t\t\tBalance amount : " << deposit;
}

//=== FUNCTION: Modify Account ===//
void account::modify() {
	cout << "\n\t\t\tAccount No. : " << acno;
	cout << "\n\t\t\tModify Account Holder Name : ";
	cin.ignore();
	cin.getline(name, 50);
	cout << "\n\t\t\tModify Type of Account : ";
	cin >> type;
	type = toupper(type);
	cout << "\n\t\t\tModify Balance amount : ";
	cin >> deposit;
}

//=== FUNCTION: Deposit Amount ===//
void account::dep(int x) {
	deposit += x;
}

//=== FUNCTION: Withdraw Amount ===//
void account::draw(int x) {
	deposit -= x;
}

//=== FUNCTION: Tabular Display ===//
void account::report() const {
	cout << acno << setw(10) << " " << name << setw(10) << " " << type << setw(6) << deposit << endl;
}

//=== Getter Functions ===//
int account::retacno() const { return acno; }
int account::retdeposit() const { return deposit; }
char account::rettype() const { return type; }

//=== Function Declarations ===//
void write_account();
void display_sp(int);
void modify_account(int);
void delete_account(int);
void display_all();
void deposit_withdraw(int, int);

//=== MAIN MENU FUNCTION ===//
int main() {
	char ch;
	int num;
	do {
		system("CLS");
		cout << "\n\n\t\t\t\t======================\n";
		cout << "\t\t\t\tBANK MANAGEMENT SYSTEM";
		cout << "\n\t\t\t\t======================\n";

		//=== Menu Options ===//
		cout << "\t\t\t\t    ::MAIN MENU::\n";
		cout << "\n\t\t\t\t1. NEW ACCOUNT";
		cout << "\n\t\t\t\t2. DEPOSIT AMOUNT";
		cout << "\n\t\t\t\t3. WITHDRAW AMOUNT";
		cout << "\n\t\t\t\t4. BALANCE ENQUIRY";
		cout << "\n\t\t\t\t5. ALL ACCOUNT HOLDER LIST";
		cout << "\n\t\t\t\t6. CLOSE AN ACCOUNT";
		cout << "\n\t\t\t\t7. MODIFY AN ACCOUNT";
		cout << "\n\t\t\t\t8. EXIT";
		cout << "\n\n\t\t\t\tSelect Your Option (1-8): ";
		cin >> ch;

		switch (ch) {
		case '1':
			write_account(); break;
		case '2':
			system("CLS");
			cout << "\n\n\t\t\tEnter The account No. : "; cin >> num;
			deposit_withdraw(num, 1);
			break;
		case '3':
			system("CLS");
			cout << "\n\n\t\t\tEnter The account No. : "; cin >> num;
			deposit_withdraw(num, 2);
			break;
		case '4':
			system("CLS");
			cout << "\n\n\t\t\tEnter The account No. : "; cin >> num;
			display_sp(num);
			break;
		case '5':
			display_all(); break;
		case '6':
			system("CLS");
			cout << "\n\n\t\t\tEnter The account No. : "; cin >> num;
			delete_account(num);
			break;
		case '7':
			system("CLS");
			cout << "\n\n\t\t\tEnter The account No. : "; cin >> num;
			modify_account(num);
			break;
		case '8':
			system("CLS");
			cout << "\n\n\t\t\tBrought To You By Ahmad And Abdul Rehman";
			break;
		default:
			cout << "\a"; // Beep sound
		}
		cin.ignore();
		cin.get();
	} while (ch != '8');
	return 0;
}

//=== FUNCTION: Write New Account to File ===//
void write_account() {
	account ac;
	ofstream outFile("account.dat", ios::binary | ios::app);
	ac.create_account();
	outFile.write(reinterpret_cast<char*>(&ac), sizeof(account));
	outFile.close();
}

//=== FUNCTION: Show Specific Account ===//
void display_sp(int n) {
	account ac;
	bool flag = false;
	ifstream inFile("account.dat", ios::binary);
	if (!inFile) {
		cout << "File could not be open !! Press any Key...";
		return;
	}
	cout << "\n\t\t\tBALANCE DETAILS\n";
	while (inFile.read(reinterpret_cast<char*>(&ac), sizeof(account))) {
		if (ac.retacno() == n) {
			ac.show_account();
			flag = true;
		}
	}
	inFile.close();
	if (!flag)
		cout << "\n\n\t\t\tAccount number does not exist";
}

//=== FUNCTION: Modify Existing Account ===//
void modify_account(int n) {
	bool found = false;
	account ac;
	fstream File("account.dat", ios::binary | ios::in | ios::out);
	if (!File) {
		cout << "File could not be open !! Press any Key...";
		return;
	}
	while (!File.eof() && !found) {
		File.read(reinterpret_cast<char*>(&ac), sizeof(account));
		if (ac.retacno() == n) {
			ac.show_account();
			cout << "\n\n\t\t\tEnter The New Details of account" << endl;
			ac.modify();
			int pos = (-1) * static_cast<int>(sizeof(account));
			File.seekp(pos, ios::cur);
			File.write(reinterpret_cast<char*>(&ac), sizeof(account));
			cout << "\n\n\t\t\tRecord Updated";
			found = true;
		}
	}
	File.close();
	if (!found)
		cout << "\n\n\t\t\tRecord Not Found ";
}

//=== FUNCTION: Delete Account ===//
void delete_account(int n) {
	account ac;
	ifstream inFile("account.dat", ios::binary);
	if (!inFile) {
		cout << "File could not be open !! Press any Key...";
		return;
	}
	ofstream outFile("Temp.dat", ios::binary);
	while (inFile.read(reinterpret_cast<char*>(&ac), sizeof(account))) {
		if (ac.retacno() != n) {
			outFile.write(reinterpret_cast<char*>(&ac), sizeof(account));
		}
	}
	inFile.close();
	outFile.close();
	remove("account.dat");
	rename("Temp.dat", "account.dat");
	cout << "\n\nRecord Deleted ..";
}

//=== FUNCTION: Display All Accounts ===//
void display_all() {
	system("CLS");
	account ac;
	ifstream inFile("account.dat", ios::binary);
	if (!inFile) {
		cout << "File could not be open !! Press any Key...";
		return;
	}
	cout << "\n\n\t\tACCOUNT HOLDER LIST\n\n";
	cout << "====================================================\n";
	cout << "A/c no.      NAME           Type  Balance\n";
	cout << "====================================================\n";
	while (inFile.read(reinterpret_cast<char*>(&ac), sizeof(account))) {
		ac.report();
	}
	inFile.close();
}

//=== FUNCTION: Deposit or Withdraw ===//
void deposit_withdraw(int n, int option) {
	int amt;
	bool found = false;
	account ac;
	fstream File("account.dat", ios::binary | ios::in | ios::out);
	if (!File) {
		cout << "File could not be open !! Press any Key...";
		return;
	}
	while (!File.eof() && !found) {
		File.read(reinterpret_cast<char*>(&ac), sizeof(account));
		if (ac.retacno() == n) {
			ac.show_account();
			if (option == 1) {
				cout << "\n\n\t\t\tTO DEPOSIT AMOUNT";
				cout << "\n\n\t\t\tEnter The amount to be deposited: ";
				cin >> amt;
				ac.dep(amt);
			}
			else if (option == 2) {
				cout << "\n\n\t\t\tTO WITHDRAW AMOUNT";
				cout << "\n\n\t\t\tEnter The amount to be withdraw: ";
				cin >> amt;
				if (ac.retdeposit() - amt < 0)
					cout << "Insufficient balance";
				else
					ac.draw(amt);
			}
			int pos = (-1) * static_cast<int>(sizeof(ac));
			File.seekp(pos, ios::cur);
			File.write(reinterpret_cast<char*>(&ac), sizeof(account));
			cout << "\n\n\t\t\tRecord Updated";
			found = true;
		}
	}
	File.close();
	if (!found)
		cout << "\n\n\t\t\tRecord Not Found ";
}
