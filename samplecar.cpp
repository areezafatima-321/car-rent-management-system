#include<iostream>
#include<string>
#include<fstream>
using namespace std;

/* Function Declarations */
void showSignUp();
void showLogIn();
void showMainMenu();
void showUserMenu();

void signUp(int &count);
void signIn(int &count, int &count1);
void adminSignIn(int &count, int &count1);
void adminSignUp(int &count1);
void mainmenu(int &count, int &count1);
void usermenu(int &count, int &count1);
void loadUsers(int &count);
void addDetails(){};
void deleteDetails(){};
void rentCars(){};
void billing(){};  
void reciept(){};

bool hasSpecialChar(string pass);

/* Global Arrays */
string admin[3];
string adminPass[3];
string username[100];
string password[100];

/* Helper Function */
bool hasSpecialChar(string pass)
{
    for(char c : pass)
    {
        if(!isalnum(c))
            return true;
    }
    return false;
}

/* Menus */
void showMainMenu()
{
    cout<<"\n******** MAIN MENU ********\n";
    cout<<"1. User Sign Up\n";
    cout<<"2. User Log In\n";
    cout<<"3. Admin Sign Up\n";
    cout<<"4. Admin Log In\n";
    cout<<"5. Exit\n";
}

void showSignUp()
{
    cout<<"\n******** SIGN UP ********\n";
}

void showLogIn()
{
    cout<<"\n******** LOGIN ********\n";
}

void showUserMenu()
{
    cout<<"\n******** USER MENU ********\n";
    cout<<"1. ADD details\n";
    cout<<"2. Delete details\n";
   cout<<"3. Rent Cars\n";
    cout<<"4. Billing\n";
    cout<<"5. Receipt\n";
    cout<<"6. Logout\n";
}

/* User Signup */
void signUp(int &count)
{
    if(count >= 100)
    {
        cout<<"User limit reached!\n";
        return;
    }

    string u, p;
    showSignUp();

    cin.ignore();
    cout<<"Username: ";
    getline(cin, u);

    cout<<"Password (8 chars + special char): ";
    getline(cin, p);

    if(p.length() == 8 && hasSpecialChar(p))
    {
        username[count] = u;
        password[count] = p;
        count++;
        cout<<"Signup successful!\n";
        //file handling 
        ofstream file("users.txt", ios::app);
        file << u << " " << p << endl;
        file.close();
    }
    else
    {
        cout<<"Password must be 8 characters & contain a special character!\n";
    }
}
void loadUsers(int &count)
{
    ifstream file("users.txt");

    if(file.is_open())
    {
        while(file >> username[count] >> password[count])
        {
            count++;
        }
        file.close();
    }
}

/* User Login */
void signIn(int &count, int &count1)
{
    string u, p;
    bool found = false;

    showLogIn();
    cin.ignore();
    cout<<"Username: ";
    getline(cin, u);

    cout<<"Password: ";
    getline(cin, p);

    for(int i = 0; i < count; i++)
    {
        if(username[i] == u && password[i] == p)
        {
            found = true;
            break;
        }
    }

    if(found)
    {
        cout<<"Login Successful!\n";
        usermenu(count, count1);
    }
    else
    {
        cout<<"Invalid login!\n";
    }
}

/* Admin Signup */
void adminSignUp(int &count1)
{
    if(count1 >= 3)
    {
        cout<<"Admin limit reached!\n";
        return;
    }

    string u, p;
    showSignUp();

    cin.ignore();
    cout<<"Admin Username: ";
    getline(cin, u);

    cout<<"Password (8 chars): ";
    getline(cin, p);

    if(p.length() == 8)
    {
        admin[count1] = u;
        adminPass[count1] = p;
        count1++;
        cout<<"Admin signup successful!\n";
    }
    else
    {
        cout<<"Password must be 8 characters!\n";
    }
}

/* Admin Login */
void adminSignIn(int &count, int &count1)
{
    string u, p;
    bool found = false;

    showLogIn();
    cin.ignore();
    cout<<"Admin Username: ";
    getline(cin, u);

    cout<<"Password: ";
    getline(cin, p);

    for(int i = 0; i < count1; i++)
    {
        if(admin[i] == u && adminPass[i] == p)
        {
            found = true;
            break;
        }
    }

    if(found)
    {
        cout<<"Admin Login Successful!\n";
        usermenu(count, count1);
    }
    else
    {
        cout<<"Invalid Admin Login!\n";
    }
}

/* User Menu */
void usermenu(int &count, int &count1)
{
    int ch;
    showUserMenu();
    cout<<"enter choice:";
    cin>>ch;

    switch(ch)
    {
        case 1: addDetails(); break;
        case 2: deleteDetails(); break;
        case 3: rentCars(); break;
        case 4: billing();  break;
        case 5: reciept(); break;
        case 6:
            mainmenu(count, count1);
            break;
        default:
            cout<<"Feature not implemented yet.\n";
    }
}

/* Main Menu */
void mainmenu(int &count, int &count1)
{
    int choice;
    bool run = true;

    while(run)
    {
        showMainMenu();
        cout<<"Choice: ";
        cin>>choice;

        switch(choice)
        {
            case 1: signUp(count); break;
            case 2: signIn(count, count1); break;
            case 3: adminSignUp(count1); break;
            case 4: adminSignIn(count, count1); break;
            case 5: run = false; break;
            default: cout<<"Invalid choice!\n";
        }
    }
}
void addDetails() {
    string name,cnic,lisence;
    cout<<"enter name";
    getline(cin,name);
    cout<<"enter cnic";
    getline(cin,cnic);
    cout<<"enter lisence no";
    getline(cin,lisence )
}

/* Main */
int main()
{
    int count = 0;   // users
    int count1 = 0;  // admins
     loadUsers(count);
    mainmenu(count, count1);
    return 0;
}
