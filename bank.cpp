#include<iostream>
#include<conio.h>
#include<stdio.h>
#include<fstream>
#include<iomanip>
using namespace std;


class bank
{

    string name,add;
    char y;
    long int balance,acn;
    public:

void open_account()
{

    cout<<"enter your full name: ";
    cin>>name;
     cout<<"enter Account number alloted: ";
     cin>>acn;
    cout<<"enter your address: ";
    cin>>add;
    cout<<"what type of account you want to open saving(s) or current(c): ";
    cin>>y;
    cout<<"enter amount for deposit: ";
    cin>>balance;

}

void display_account()
{
    cout<<"\nyour full name: "<<name;
    cout<<"\nyour address: "<<add;
    cout<<"\ntype of account that you open: "<<y;
    cout<<"\ntotal amount deposited: "<<balance;
}


void deposite_money()
{
    int a;
    cout<<"\nenter amount to deposit: ";
    cin>>a;
    balance+=a;
    cout<<"\ntotal amount you deposited: \t"<<balance;
}


void withdraw_money()
{
    float amount;
    cout<<"\nenter amount to withdraw: ";
    cin>>amount;
    balance=balance-amount;
    cout<<"\nnow total amount is left: "<<balance;
}


        int  retacn()
        {
            return acn;
        }
};


class signIn
{
public:
    string idAttempt;
    string passAttempt;
    signIn()
    {
        accessGranted = 0;
    }
    void signin()
    {
        cout<<"\n\n\tEnter your User Id and Password:- ";
        cout<<"\n\n\tUser Id : ";
        cin>>idAttempt;
        if(idAttempt==id)
        {
            cout<<"\tPassword : ";
            cin>>passAttempt;
            if(passAttempt==password)
            {
                cout<<"\n\n\tAccess Granted!\n\n\n";
                system ("PAUSE");
                system("cls");
            }
            else
            {
                cout<<"Access Denied!\n\n\n\n\n";
                exit( 1 );

            }
        }
        else
        {
            cout<<"Access Denied!\n\n\n\n\n";
            exit(1);
        }
    }
private:
    string password="123";
    string id="abc";
    bool accessGranted;

};

fstream fb;
bank b;


void storeBank()
{
    fb.open("bank.dat",ios::out|ios::app);
    b.open_account();
    fb.write((char*)&b,sizeof(bank));
    fb.close();
    cout<<"\n\n Bank Account has been created!!! ";
    getch();
}


void searchBank(int acc)
{
    int flag=0;
    fb.open("bank.dat",ios::in);
    while(fb.read((char*)&b,sizeof(bank)))
    {
        if(b.retacn()==acc)
        {
            system("cls");
            b.display_account();
            flag=1;
        }
    }
    fb.close();
    if(flag==0)
        cout<<"\n\nRecord doesn't exist!!!";
    getch();
}



void displayBank()
{
    char name,add,y;
    int balance;
    system("cls");
    cout<<"\n\n\t\tDISPLAYING ALL RECORDS:- \n\n";
    fb.open("bank.dat",ios::in);
    while(fb.read((char*)&b,sizeof(bank)))
    {

         b.display_account();

        cout<<"\n___________________________________________________________";
    }
    fb.close();
    getch();
}


void modifyBank()
{
    int num,found=0;
    system("cls");
    cout<<"\n\n\tModify Record:- ";
    cout<<"\n\n\tPlease Enter The Account Number: ";
    cin>>num;
    fb.open("bank.dat",ios::in|ios::out);
    while(fb.read((char*)&b,sizeof(bank)) && found==0)
    {
        if(b.retacn()==num)
        {
            b.display_account();
            cout<<"\n\n\t\tPlease select the task:- "<<endl;
            cout<<"1) deposit money \n";
            cout<<"2) withdraw money \n";
            cout<<"3) back \n";
            char ch;
            ch=getche();
            switch(ch)
            {
                case '1':
                    b.deposite_money();
                    break;
                case '2':
                    b.withdraw_money();
                    break;
                case '3':
                    break;
            }
            int pos=-1*sizeof(b);
            fb.seekp(pos,ios::cur);
            fb.write((char*)&b,sizeof(bank));
            cout<<"\n\n\t\t Success!!!";
            found=1;
        }
    }
    fb.close();
    if(found==0)
        cout<<"\n\n Record Not Found!!!";
    getch();
}



void deleteBank()
{
    int num;
    system("cls");
    cout<<"\n\n\tDelete Record:- ";
    cout<<"\n\n\tPlease Enter The Account Number : ";
    cin>>num;
    fb.open("bank.dat",ios::in|ios::out);
    fstream fb2;
    fb2.open("Temp.dat",ios::out);
    fb.seekg(0,ios::beg);
    while(fb.read((char*)&b,sizeof(bank)))
    {
        if(b.retacn()!=num)
        {
            fb2.write((char*)&b,sizeof(bank));
        }
    }
    fb2.close();
    fb.close();
    remove("bank.dat");
    rename("Temp.dat","bank.dat");
    cout<<"\n\n\tRecord Deleted!!!";
    getch();
}


void main_menu()
{
    char ch;
    system("cls");
        cout<<"1) open account \n";
        cout<<"2) Transaction Menu \n";
        cout<<"3) Search Account \n";
        cout<<"4) Delete Account \n";
        cout<<"5) display account \n";
        cout<<"6) back";
        cout<<"\nselect the option from above \n";
        cin>>ch;
        switch(ch)
        {
          case '1':
              system("cls");
                storeBank();
                break;
          case '2':
                modifyBank();
                break;
          case '3':
                int num;
                system("cls");
                cout<<"\n\n\tPlease Enter Account number ";
                cin>>num;
                searchBank(num);
                break;
          case '4':
                deleteBank();
                break;
          case '5':
                displayBank();
                break;
          case '6':
                break;
          default :
            cout<<"\a";
            main_menu();
        }
}


int main()
{
    signIn lobj;
    lobj.signin();
    char ch;
    do
    {
        system("cls");
        cout<<"\n\tBANKING RECORD MANAGEMENT SYSTEM";
        cout<<"\n\n\n\t1. ENTER MAIN MENU";
        cout<<"\n\n\t2. EXIT";
        cout<<"\n\n\tPlease Select Your Option (1-2) ";
        ch=getche();
        switch(ch)
        {
        case '1':
            main_menu();
            break;
        case '2':
            exit(0);
        default :
            cout<<"\a";
        }
    }
    while(ch!='2');

}
