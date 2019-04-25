#include<iostream>
#include<fstream>
#include<string>
#include<windows.h>
#include<conio.h>
using namespace std;
char ch;
namespace B2
{
    void header(int x)
    {
        for(int i=0;i<x;i++)
            cout<<"\xB2";
    }
}
namespace DB
{
    void header(int x)
    {
        for(int i=0;i<x;i++)
            cout<<"\xDB";
    }
}
void loading(int j);
void choice();
void Main_Menu();
///Patient Basic Profile Data
class Admit_New
{
protected:
    int SerialNo=0;
    string Name;
    string Address;
    char Gender;
    int Age;
    string Cause;
    int SeatNo;
public:
    void SNO_Intial()
    {
        ifstream files;
        files.open("PatientProfile.dat");
        if(!files.is_open())
        {
            cout<<"Cannot open file!\n";
        }
        while(!files.eof())
        {
            files>>SerialNo>>Name>>Address>>Gender>>Age>>Cause>>SeatNo;
        }
        files.close();
        SerialNo++;
    }
    void Input_Info()
    {
        SNO_Intial();
        cout<<"Name: ";
        cin>>Name;
        cout<<"Present Address: ";
        cin>>Address;
        cout<<"Gender(M/F): ";
        cin>>Gender;
        cout<<"Age: ";
        cin>>Age;
        cout<<"Cause: ";
        cin>>Cause;
        cout<<"Seat Number: ";
        cin>>SeatNo;
    }
    void File_Write()
    {
        ofstream file;
        file.open("PatientProfile.dat",ios::out | ios::app);
        if(!file)
        {
            throw "Cannot open file!\n";
        }
        file<<endl<<SerialNo<<"\t\t"<<Name<<"\t\t"<<Address<<"\t\t"<<Gender<<"\t\t"<<Age<<"\t\t"<<Cause<<"\t\t"<<SeatNo;
        file.close();
    }
    friend ostream &operator << (ostream &output, const Admit_New &token)
    {
        cout<<endl<<endl<<"\t\t\t\t\t\t";
        for(int i=0;i<20;i++)
            cout<<"-";
        output<<"\n\t\t\t\t\t\tSerial Number: "<<token.SerialNo<<"\n\t\t\t\t\t\tName: "<<token.Name<<"\n\t\t\t\t\t\tAddress: "<<token.Address<<"\n\t\t\t\t\t\tGender: "<<token.Gender<<"\n\t\t\t\t\t\tAge: "<<token.Age<<"\n\t\t\t\t\t\tSeat No: "<<token.SeatNo<<endl;
        cout<<"\t\t\t\t\t\t";
        for(int i=0;i<20;i++)
            cout<<"-";
        cout<<endl<<endl;
        return output;
    }
    Admit_New operator ++ (int)
    {
        SerialNo++;
    }
};
///Billing System
template<class T>
class Payment_System:protected Admit_New
{
protected:
    T SNO;
    T Amount;
public:
    void Check_SNO()
    {
        system("cls");
        cout<<"Enter Serial Number: ";
        cin>>SNO;
        int pcount=0,bcount=0;
        ifstream file("PatientProfile.dat"),file1("BillPayment.dat");
        if(!file.is_open() || !file1.is_open())
        {
            throw "Cannot open file!\n";
        }
        while(!file.eof())
        {
            file>>SerialNo>>Name>>Address>>Gender>>Age>>Cause>>SeatNo;
            if(SNO==SerialNo)
            {
                pcount=1;
            }

        }
        while(!file1.eof())
        {
            file1>>SerialNo>>Amount;
            if(SNO==SerialNo)
            {
                bcount=1;
            }
        }

        file.close();
        file1.close();

        if(bcount==1)
        {
            cout<<"Already created bill! Please go to add bill!\n";
        }
        else if(pcount==1)
        {
            try
            {
               New_Bill();
            }catch(const char* msg)
            {
                cerr<<msg;
            }
        }
        else
        {
            cout<<"Serial Number Not Found!\n";
            choice();
        }
    }
    void New_Bill()
    {
        cout<<"Enter Amount: ";
        cin>>Amount;
        ofstream file1;
        file1.open("BillPayment.dat", ios::out | ios::app);
        if(!file1.is_open())
        {
            throw "Cannot open file!";
        }
        else
        {
            file1<<endl<<SNO<<"\t"<<Amount;
            file1.close();
            cout<<"\t\t\t\t\t\tPayment Successful!\n";
        }

    }
    void Add_Bill()
    {
        system("cls");
        cout<<"Enter Serial Number: ";
        cin>>SNO;
        int NewAmount;
        int pcount=0,bcount=0;
        ifstream file("PatientProfile.dat");
        if(!file.is_open())
        {
            cout<<"Cannot open file!\n";
        }
        while(!file.eof())
        {
            file>>SerialNo>>Name>>Address>>Gender>>Age>>Cause>>SeatNo;
            if(SNO==SerialNo)
            {
                pcount=1;
            }

        }
        if(pcount==1)
        {

            ifstream old1("BillPayment.dat");
            ofstream new1;
            new1.open("new.dat",ios::out);
            if(!old1.is_open() || !new1.is_open())
            {
                throw "Cannot open file!\n";
            }
            while(!old1.eof())
            {
                old1>>SerialNo>>Amount;
                if(SNO==SerialNo)
                {
                    bcount=1;
                    cout<<"Enter Amount:";
                    cin>>NewAmount;
                    new1<<endl<<SerialNo<<"\t"<<Amount+NewAmount;

                }
            }
            old1.close();
            new1.close();
            remove("BillPayment.dat");
            rename("new.dat","BillPayment.dat");

            if(bcount==1)
            {
                cout<<"\t\t\t\t\t\tPayment Successful!\n";
            }
            else if(bcount==0)
            {
                cout<<"Serial Number Not Found!";
                choice();
            }
            else
            {
                choice();
            }
        }
        else if(pcount==0)
        {
            cout<<"\t\t\t\t\t\tPatient Relased!\n";
            choice();
        }


    }
    void File_Read()
    {
        string line;
        ifstream file1("BillPayment.dat");
        if(file1==NULL)
        {
            throw "Cannot open file!\n";
        }
        cout<<"\n\t\t\t\t\t\tSNO\tPaid\n";
        cout<<"\t\t\t\t\t\t---------------\n";
        while(getline(file1,line))
        {
            cout<<"\t\t\t\t\t\t"<<line<<endl;
        }
        file1.close();
    }
};
///Edit Patient Informatin
class Edit_Information:public Admit_New
{
protected:
    int SNO;
    int count=0;
public:
    void Edit_Info()
    {
        ifstream old1("PatientProfile.dat");
        ofstream new1;
        new1.open("new.dat", ios::out);
        if(!old1 || !new1)
        {
            throw "Cannot open file!";
        }
        cout<<"Enter Your Serial Number: ";
        cin>>SNO;
        while(!old1.eof())
        {
            old1>>SerialNo>>Name>>Address>>Gender>>Age>>Cause>>SeatNo;
            if(SNO==SerialNo)
            {
                count=1;
                cout<<"\n\n\t\t\t\t\tWhich Information You Want to Change?";
                cout<<"\n\n\t\t\t\t\t1 > Name";
                cout<<"\n\t\t\t\t\t2 > Address";
                cout<<"\n\t\t\t\t\t3 > Cause"<<endl;
                cout<<"\n\t\t\t\t\tNumber > ";
                ch=getche();
                if(ch=='1')
                {
                    cout<<"\nEnter Name: ";
                    cin>>Name;
                    new1<<endl<<SerialNo<<"\t\t"<<Name<<"\t\t"<<Address<<"\t\t"<<Gender<<"\t\t"<<Age<<"\t\t"<<Cause<<"\t\t"<<SeatNo;
                    cout<<"\n\t\t\t\t\t\tChanges Saved!\n";
                }
                else if(ch=='2')
                {
                    cout<<"\nEnter Address: ";
                    cin>>Address;
                    new1<<endl<<SerialNo<<"\t\t"<<Name<<"\t\t"<<Address<<"\t\t"<<Gender<<"\t\t"<<Age<<"\t\t"<<Cause<<"\t\t"<<SeatNo;
                    cout<<"\n\t\t\t\t\t\tChanges Saved!\n";
                }
                else if(ch=='3')
                {
                    cout<<"\nEnter Cause: ";
                    cin>>Cause;
                    new1<<endl<<SerialNo<<"\t\t"<<Name<<"\t\t"<<Address<<"\t\t"<<Gender<<"\t\t"<<Age<<"\t\t"<<Cause<<"\t\t"<<SeatNo;
                    cout<<"\n\t\t\t\t\t\tChanges Saved!\n";
                }
                else
                {
                    choice();
                }

            }
            else
            {
                new1<<endl<<SerialNo<<"\t\t"<<Name<<"\t\t"<<Address<<"\t\t"<<Gender<<"\t\t"<<Age<<"\t\t"<<Cause<<"\t\t"<<SeatNo;
            }
        }
        old1.close();
        new1.close();
        remove("PatientProfile.dat");
        rename("new.dat","PatientProfile.dat");

        if(count==0)
        {
            cout<<"\t\t\t\t\t\tSerial Number Not Found!\n";
            choice();
        }
        else
            choice();
    }
};
///Enquiry A Single Patient Information
template<class T>
class Enquiry_Information:public Admit_New
{
protected:
    T SNO;
    T Amount;
public:
    void Enq_Data()
    {
        int pcount=0;
        int bcount=0;
        cout<<"Enter Serial Number: ";
        cin>>SNO;
        ifstream profile("PatientProfile.dat"), bill("BillPayment.dat");
        if(!profile || !bill)
        {
            throw "Cannot Open File!\n";
        }
        while(!profile.eof())
        {
            profile>>SerialNo>>Name>>Address>>Gender>>Age>>Cause>>SeatNo;
            if(SNO==SerialNo)
            {
                pcount=1;
                cout<<"\n\n\t\t\t\t\t\tSerial Number: "<<SerialNo<<endl;
                cout<<"\t\t\t\t\t\tName: "<<Name<<endl;
                cout<<"\t\t\t\t\t\tAddress: "<<Address<<endl;
                cout<<"\t\t\t\t\t\tGender: "<<Gender<<endl;
                cout<<"\t\t\t\t\t\tAge: "<<Age<<endl;
                cout<<"\t\t\t\t\t\tCause: "<<Cause<<endl;
                cout<<"\t\t\t\t\t\tSeat Number: "<<SeatNo<<endl;
            }
        }
        while(!bill.eof())
        {
            bill>>SerialNo>>Amount;
            if(SNO==SerialNo)
            {
                bcount=1;
                cout<<"\t\t\t\t\t\tBill Paid: "<<Amount<<endl;
            }
        }
        profile.close();
        bill.close();
        if(pcount==0 && bcount==0)
        {
            cout<<"\t\t\t\t\t\tSerial Number Not Found!\n";
            choice();
        }
        else if(pcount==0 && bcount==1)
        {
            cout<<"\t\t\t\t\t\tPatient Relased!\n";
            choice();
        }
        else if(pcount==1 && bcount==0)
        {
            cout<<"\t\t\t\t\t\tDidn't paid any bill!\n";
            choice();
        }
        else
            choice();

    }
};
///Delete Patient Information
class Relase_Patient:public Admit_New
{
protected:
    int SNO;
    int count=0;
public:
    void Delete_Info()
    {
        ifstream old1("PatientProfile.dat");
        ofstream new1;
        new1.open("new.dat", ios::out);

        if(!old1 || !new1)
        {
            throw "\t\t\t\t\t\tCannot open file!\n";
        }
        cout<<"Enter Your Serial Number: ";
        cin>>SNO;
        while(!old1.eof())
        {
            old1>>SerialNo>>Name>>Address>>Gender>>Age>>Cause>>SeatNo;
            if(SNO!=SerialNo)
            {
                new1<<endl<<SerialNo<<"\t\t"<<Name<<"\t\t"<<Address<<"\t\t"<<Gender<<"\t\t"<<Age<<"\t\t"<<Cause<<"\t\t"<<SeatNo;
            }
            else
            {
                count=2;
                cout<<"\t\t\t\t\t\tPatient Relased!";
            }
        }
        old1.close();
        new1.close();
        remove("PatientProfile.dat");
        rename("new.dat","PatientProfile.dat");


        if(count==0)
        {
            cout<<"\t\t\t\t\t\tSerial Number Not Found!\n";
            choice();
        }
        else
        {
            choice();
        }
    }

};
class All_Information:public Admit_New
{
private:
    string line;
public:
    void File_Read()
    {
        ifstream file1("PatientProfile.dat");
        if(!file1)
        {
            throw "Cannot open file!\n";
        }
        cout<<"\n\nSNO\t\tName\t\tAddress\t\tGender\t\tAge\t\tCause\t\tSeat Number\n";
        for(int i=0;i<110;i++)
            cout<<"-";
        while(getline(file1,line))
        {
            cout<<line<<endl;
        }
        file1.close();
    }
};

int main()
{
    system("color 6");
    cout<<"\n\n\n\n\t\t\t";
    B2::header(62);
    cout<<endl<<"\t\t\t";
    B2::header(17);
    cout<<" Hospital Management System ";
    B2::header(17);
    cout<<endl<<"\t\t\t";
    B2::header(62);
    string user_pass,pass="iostream";
    cout<<"\n\n\n\n\t\t\t\t\tEnter System Password: ";
    cin>>user_pass;

    if(user_pass==pass)
    {
        system("cls");
        cout<<"\n\n\n\n\n\n\t\t\t\t\t\tLoading";
        for(int i=0;i<=10;i++)
        {
            loading(100000000);
            cout<<".";
        }
        Main_Menu();
    }
    else
    {
        system("cls");
        cout<<"\a\n\n\n\t\t\t\t\tWrong Password! Try Again!\n";
        main();
    }
    Main_Menu();

    getch();
    return 0;
}
void choice()
{
    while(1)
    {
        cout<<"\n\n\t\t\t(0 > Main Menu) \t\t\t\t (# > Exit)\n\n";
        cout<<"\t\t\t\t\t\tNumber > ";
        ch=getche();
        if(ch=='0')
        {
            system("cls");
            Main_Menu();
        }
        else if(ch=='#')
        {
            exit(0);
        }
    }
}
void loading(int j)
{   int i,k;
    for(i=0;i<j;i++)
         k=i;
}
void Main_Menu()
{
    while(1)
    {
        system("cls");
        All_Information add,display;
        Payment_System<int> *pay=new Payment_System<int>,*check=new Payment_System<int>;
        Edit_Information *edit=new Edit_Information;
        Enquiry_Information<int> *single=new Enquiry_Information<int>;
        Relase_Patient *delet=new Relase_Patient;

        cout<<"\n\n\n\n\n\n\t\t\t";
        system("color B");
        DB::header(56);
        cout<<endl<<"\t\t\t";
        DB::header(19);
        cout<<" M A I N  M E N U ";
        DB::header(19);
        cout<<endl<<"\t\t\t";
        DB::header(56);
        cout<<"\t\t\t"<<endl<<"\t\t\t\xDD"<<endl;
        cout<<"\t\t\t\xDD 1 > Admit New"<<endl;
        cout<<"\t\t\t\xDD 2 > Pay And Check Bill"<<endl;
        cout<<"\t\t\t\xDD 3 > Edit Information"<<endl;
        cout<<"\t\t\t\xDD 4 > Enquiry Informatin"<<endl;
        cout<<"\t\t\t\xDD 5 > Relase A Patient"<<endl;
        cout<<"\t\t\t\xDD 6 > Patient List"<<endl;
        cout<<"\t\t\t\xDD 7 > Admin Mode"<<endl;
        cout<<"\t\t\t\xDD 8 > Exit"<<endl<<"\t\t\t\xDD";
        cout<<"\n\t\t\t";
        DB::header(56);
        cout<<endl;

        cout<<"\t\t\t\t\t\tNumber >  ";
        ch=getche();
        switch(ch)
        {
        case '1':
            {
                system("cls");
                while(1)
                {
                    cout<<"\n\n\t\t\t\t\t\t\xB2\xB2\xB2 Admit New Patient \xB2\xB2\xB2"<<endl;
                    add.Input_Info();
                    try
                    {
                        add.File_Write();
                    }catch(const char* msg)
                    {
                        cerr<<msg<<endl;
                    }
                    cout<<add;
                    add++;

                    cout<<"\t\t\t\t\t\tAdmitted Succesfully!\n\n\n";
                    cout<<"\t\t\t\t\t\tAdmit Another? (Y/N): ";
                    ch=getche();
                    if(ch=='N' || ch=='n')
                    {
                        choice();

                    }
                    else if(ch=='Y' || ch=='y')
                    {
                        system("cls");
                        continue;
                    }
                    else
                        choice();
                }

                break;
            }
        case '2':
            {
                system("cls");
                cout<<"\n\n\t\t\t\t\t\t\xB2\xB2\xB2 Pay & Check Bill \xB2\xB2\xB2"<<endl;
                cout<<"\n\n\n\t\t\t\t\t\t1 > Pay Bill"<<endl;
                cout<<"\n\t\t\t\t\t\t2 > Check Bill"<<endl;


                cout<<"\n\t\t\t\t\t\tNumber > ";
                ch=getche();
                if(ch=='1')
                {
                    system("cls");
                    cout<<"\n\n\t\t\t\t\t\t\xB2\xB2\xB2 Pay Bill \xB2\xB2\xB2"<<endl;
                    cout<<"\n\n\t\t\t\t\t\t1 > New Bill\n";
                    cout<<"\t\t\t\t\t\t2 > Add Bill\n";
                    cout<<"\n\n\t\t\t\t\t\tNumber > ";
                    ch=getche();
                    if(ch=='1')
                    {
                        try
                        {
                           pay->Check_SNO();

                        }catch(const char* msg)
                        {
                            cerr<<msg;
                        }
                    }
                    else if(ch=='2')
                    {
                        try
                        {
                            pay->Add_Bill();
                        }catch(const char* msg)
                        {
                            cerr<msg;
                        }
                    }
                    else
                    {
                        choice();
                    }
                }
                else if(ch=='2')
                {
                    system("cls");
                    cout<<"\n\n\t\t\t\t\t\t\xB2\xB2\xB2 Check Bill \xB2\xB2\xB2"<<endl;
                    try
                    {
                       check->File_Read();
                    }catch(const char* msg)
                    {
                        cerr<msg;
                    }
                    choice();
                }
                delete pay;
                delete check;
                choice();
                break;

            }
        case '3':
            {
                system("cls");
                cout<<"\n\n\t\t\t\t\t\xB2\xB2\xB2 Edit Patient Information \xB2\xB2\xB2"<<endl;
                try
                {
                    edit->Edit_Info();
                }catch(const char* msg)
                {
                    cerr<<msg<<endl;
                }
                delete edit;
                break;

            }
        case '4':
            {
                system("cls");
                cout<<"\n\n\t\t\t\t\t\xB2\xB2\xB2 Enquiry Patient Information \xB2\xB2\xB2"<<endl;
                try
                {
                   single->Enq_Data();
                }catch(const char* msg)
                {
                    cerr<<msg<<endl;
                }
                delete single;
                break;
            }

        case '5':
            {
                system("cls");
                cout<<"\n\n\t\t\t\t\t\t\xB2\xB2\xB2 Relase Patient \xB2\xB2\xB2"<<endl;
                try
                {
                    delet->Delete_Info();
                }catch(const char* msg)
                {
                    cerr<<msg<<endl;
                }
                delete delet;
                break;
            }
        case '6':
            {
                system("cls");
                cout<<"\n\n\t\t\t\t\t\xB2\xB2\xB2 Patient Information \xB2\xB2\xB2"<<endl;
                try
                {
                    display.File_Read();
                }catch(const char* msg)
                {
                    cerr<<msg<<endl;
                }
                choice();
                break;
            }
        case '7':
            {
                break;
            }
        case '8':
            {
                exit(1);
                break;
            }

        }
    }
}
