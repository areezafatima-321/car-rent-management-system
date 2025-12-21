#include<iostream>
#include<string>
using namespace std;

void showSignUp();
void showLogIn();
void showMainMenu();


void signUp(int &count);
void signIn(int &count, int &count1);
void adminSignIn(int &count, int &count1);
void adminSignUp(int &count1);
void mainmenu(int &count, int &count1);

string admin[12];
string adminPass[12];
string username[12];
string password[12];








void showMainMenu()
{
    cout<<"\n**********************************"<<endl;
    cout<<"            MAIN MENU \n    ";
    cout<<"\n**********************************"<<endl;
    cout<<"1.User Sign Up\n";
    cout<<"2.User Log In\n";
    cout<<"3.Admin Sign Up\n";
    cout<<"4.Admin Log In\n";
    cout<<"5.Exit\n";
}

void showSignUp()
{
    cout<<"\n**********************************"<<endl;
    cout<<"         SIGN UP PAGE\n    ";
    cout<<"\n**********************************"<<endl;
}

void showLogIn()
{
    cout<<"\n**********************************"<<endl;
    cout<<"            LOGIN PAGE\n    ";
    cout<<"\n**********************************"<<endl;
}

void signUp(int &count)
{
    string temporayPass, temporaryUser;
    if(count>=12)
    {
        cout<<"Limit Reached\n";
        return;
    }

    showSignUp();

    cout<<"Enter Your Username: ";
    cin.ignore();
    getline(cin,username[count]);

    cout<<"Enter Your Password of 8 Characters: ";
    getline(cin,password[count]);

    if(temporayPass.length() == 8)
    {  
        cout<<"Signed Up Successfully!\n";
        username[count] = temporaryUser;
        password[count] = temporayPass;
        count++;
    }
    else
    {
        cout<<" [warning]:Password should be 8 character long.\n";
    }

}

void adminSignUp(int &count1)
{
    string temporayPass, temporaryUser;
    if(count1>=12)
    {
        cout<<"Limit Reached\n";
        return;
    }

    showSignUp();

    cout<<"Enter Your Username: ";
    cin.ignore();
    getline(cin,temporaryUser);

    cout<<"Enter Your Password of 8 Characters: ";
    getline(cin,temporayPass);

    if(temporayPass.length() == 8)
    {  
        cout<<"Signed Up Successfully!\n";
        admin[count1] = temporaryUser;
        adminPass[count1] = temporayPass;
        count1++;
    }
    else
    {
        cout<<" [warning]:Password should be 8 character long.\n";
    }

}

void adminSignIn(int &count, int &count1)
{
    string u, p;
    bool found = false;
    char charr;
    showLogIn();

    cout<<"Enter Your Username: ";
    cin.ignore();
    getline(cin,u);

    cout<<"Enter Your Password of 8 Characters: ";
    getline(cin,p);

    for (int i = 0; i < count1; i++)
    {
        if (admin[i] == u && adminPass[i] == p)
        {
            found = true;
            break;
        }
    }
    
    if (found)
    {
        cout << "Login Successful!\n";
    }
    else
    {
        cout << "Invalid Username or Password!\n";
        cout<<"Press E to exit and C to continue: ";
        cin>> charr;

        if(charr== 'E'|| charr=='e')
        { 
            mainmenu(count, count1);
        }
        if(charr=='C'||charr=='c')
        {  
            adminSignIn(count ,count1);
        }
    }
        
   
}



void signIn(int &count, int &count1)
{
    string u, p;
    bool found = false;
    char charr;
    showLogIn();

    cout<<"Enter Your Username: ";
    cin.ignore();
    getline(cin,u);

    cout<<"Enter Your Password of 8 Characters: ";
    getline(cin,p);

    for (int i = 0; i < count; i++)
    {
        if (username[i] == u && password[i] == p)
        {
            found = true;
            break;
        }
    }
    
    if (found)
    {
        cout << "Login Successful!\n";
    }
    else
    {
        cout << "Invalid Username or Password!\n";
        cout<<"Press E to exit and C to continue: ";
        cin>> charr;

        if(charr== 'E'|| charr=='e')
        { 
            mainmenu(count, count1);
        }
        if(charr=='C'||charr=='c')
        {  
            signIn(count, count1);
        }
    }

}

void mainmenu(int &count, int &count1)
{
    bool check = true;
    while(check)
    {
        int ch;
        showMainMenu();

        cout<<"Enter Your Choice: ";
        cin>>ch;

        switch(ch)
        {
            case 1: signUp(count); break;
            case 2: signIn(count, count1);   break;
            case 3: adminSignUp(count1); break;
            case 4: adminSignIn(count, count1);   break;
            case 5: check = false; break;
            default:
            cout<<"Inavlid Choice";
        }
    }
}


int main()
{
    int count=0, count1=0;
    mainmenu(count, count1);
    return 0;
    
}