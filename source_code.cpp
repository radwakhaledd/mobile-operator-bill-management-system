
//This is a program for a mobile operator to manage the bills of different call plans.

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// a base abstract class
class Plan
{
protected:
    string CustomerName;
    string PhoneNumber;
    int BillMonth;
    static string months[12];

public:
    //A parameterized constructor.
    Plan(string Cn, string Pn, int Bm)
    {
        CustomerName = Cn;
        PhoneNumber = Pn;
        BillMonth = Bm;
    }
    // pure virtual functions
    virtual double calculateBill() = 0;
    virtual void readCalls(ifstream&, int&, int&) = 0;
    //printAccountDetails virtual function is to  print the account’s customer name, phone number& month of the bill as one of the months
    virtual void printAccountDetails()
    {
        cout << "customer's name: " << CustomerName << endl;
        cout << "phone number: " << PhoneNumber << endl;
        cout << "bill month: " << months[BillMonth - 1] << endl;
    }
};
string Plan::months[12] = { "Jan","Feb","March","April","May","Jun","Jul","Aug","Sept","Oct","Nov","Dec" };

//a derived class from the base (Plan)
class Packageplan : public Plan
{
private:
    int sameMins, otherMins, monthlyCost;
    float outRate;
    int Tmins, remainingMins, outOfpackMins;
public:
    //A parameterized constructor
    Packageplan(string Cn, string Pn, int Bm, int SM, int OM, int C, float R) : Plan(Cn, Pn, Bm)
    {
        sameMins = SM;
        otherMins = OM;
        outRate = R;
        monthlyCost = C;
        outOfpackMins = 0;
        remainingMins = SM + OM;
    }
    // calculateBill overridden member function is to calculate & display the details of the bill.
    double calculateBill()
    {
        return (monthlyCost + (outOfPackageMins() * outRate));
    }
    //readCalls overridden member function is to set the second parameter to the minutes to the same operator & the third parameter to minutes to othe operators.
    void readCalls(ifstream& ifile, int& sameM, int& otherM) {
        Tmins = 0;
        ifile.open("calls.txt");
        ifile.clear();
        ifile.seekg(0, ios::beg);
        string time, mins1 = "", secs1 = "", mins2 = "", secs2 = "", PhoneNumber;

        sameM = 0;
        otherM = 0;
        int num = 0;                   //num is the position of each character in time
        if (ifile)
        {
            ifile >> time;
            ifile >> PhoneNumber;
            while (!ifile.eof()) {
                mins1 = "";
                secs1 = "";
                mins2 = "";
                secs2 = "";

                int size = 0;
                size = time.length();
                //to see the num of digits of mins (before ':') in order to separate between minutes and secs
                for (int i = 0; i < size; i++)
                {
                    if (time[i] == ':')
                        num = i;
                }

                //checks if the phone numbers of this operator start with 033 or not.
                if (PhoneNumber[0] == '0' && PhoneNumber[1] == '3' && PhoneNumber[2] == '3')
                {
                    int m1;
                    int s1;
                    //calculate  the minutes to the same operator
                    for (int j = 0; j < num; j++)                 //checks the num of digits of minutes(before ":")
                    {
                        mins1 = mins1 + time[j];
                    }

                    m1 = stoi(mins1);                  //converts the minutes we calculated as a string to an integer value
                    //calculate  the seconds to the same operator
                    for (int j = num + 1; j < size; j++)            //checks the num of digits of seconds(after ":")
                    {
                        secs1 = secs1 + time[j];
                    }

                    s1 = stoi(secs1);                  //converts the secs we calculated as a string to an integer value
                    //to round up the call duration to minutes
                    if (s1 > 0)
                        m1++;
                    //sums up all the minutes of the same operator
                    sameM = sameM + m1;
                }
                else
                {
                    int m2;
                    int s2;
                    //calculate  the minutes to other operators
                    for (int j = 0; j < num; j++)                 //checks the num of digits of minutes(before ":")
                    {
                        mins2 = mins2 + time[j];
                    }

                    m2 = stoi(mins2);
                    //converts the minutes we calculated as a string to an integer value
                    //calculate  the seconds to other operators
                    for (int j = num + 1; j < size; j++)            //checks the num of digits of seconds(after ":")
                    {
                        secs2 = secs2 + time[j];
                    }

                    s2 = stoi(secs2);                  //converts the secs we calculated as a string to an integer value
                    //to round up the call duration to minutes
                    if (s2 > 0)
                        m2++;
                    //sums up all the minutes of other operators
                    otherM = otherM + m2;
                }

                //to calculate total minutes consumed
                ifile >> time;
                ifile >> PhoneNumber;
                Tmins = sameM + otherM;


            }
        }
    }
    // printAccountDetails overridden function is to print all account’s details represented in Plan and PackagePlan
    void printAccountDetails()
    {
        ifstream ifile;
        int S_used;
        int O_used;
        S_used = 0;
        O_used = 0;
        //calling readCalls function to calculate the used minutes for both same and other operators
        readCalls(ifile, S_used, O_used);
        cout << "customer's name: " << CustomerName << endl <<
             "phone number: " << PhoneNumber << endl <<
             "bill month: " << months[BillMonth - 1] << endl <<
             "Same operator minutes available: " << sameMins << endl <<
             "Other operators minutes available: " << otherMins << endl <<
             "Monthly cost: " << monthlyCost << endl <<
             "Rate of out of package minutes: " << outRate << endl <<
             "Total minutes consumed: " << Tmins << "minutes" << endl <<
             "Same operator minutes: " << S_used << endl <<
             "Other operators minutes: " << O_used << endl <<
             "Monthly Bill: " << calculateBill() << endl <<
             "Remaining minutes: " << remainingMinutes() << endl <<
             "Out of package minutes: " << outOfPackageMins() << endl;
    }
    //remainingMinutes member function is to calculate the remaining available minutes in the package.
    int remainingMinutes()
    {
        ifstream ifile;
        int S_used;
        int O_used;
        S_used = 0;
        O_used = 0;
        //calling readCalls function to calculate the used minutes for both same and other operators
        readCalls(ifile, S_used, O_used);
        //the implementation of the if conditions is to see weather minutes available>minutes used or not either in same or other operators
        //if yes then the difference is the remaining minutes
        if ((sameMins - S_used) > 0 && (otherMins - O_used) > 0)
            remainingMins = (sameMins - S_used) + (otherMins - O_used);
        else if ((sameMins - S_used) < 0 && (otherMins - O_used) > 0)
            remainingMins = (otherMins - O_used);
        else if ((sameMins - S_used) > 0 && (otherMins - O_used) < 0)
            remainingMins = (sameMins - S_used);
        else if ((sameMins - S_used) < 0 && (otherMins - O_used) < 0)
            remainingMins = 0;
        return remainingMins;
    }
    //outOfPackageMins member function is to return extra minutes outside of the package.
    int outOfPackageMins()
    {
        ifstream ifile;
        int S_used;
        int O_used;
        S_used = 0;
        O_used = 0;
        //calling readCalls function to calculate the used minutes for both same and other operators
        readCalls(ifile, S_used, O_used);
        //the implementation of the if conditions is to see weather minutes used>minutes available or not either in same or other operators
        //if yes then the difference is the out of pack minutes
        if ((S_used - sameMins) > 0 && (O_used - otherMins) > 0)
            outOfpackMins = (S_used - sameMins) + (O_used - otherMins);
        else if ((S_used - sameMins) < 0 && (O_used - otherMins) > 0)
            outOfpackMins = (O_used - otherMins);
        else if ((S_used - sameMins) > 0 && (O_used - otherMins) < 0)
            outOfpackMins = (S_used - sameMins);
        else if ((S_used - sameMins) < 0 && (O_used - otherMins) < 0)
            outOfpackMins = 0;
        return outOfpackMins;
    }
};

//a derived class from the base (Plan)
class RatePlan : public Plan
{
private:
    double callRate, favNumRate;
    string favNum;
    int Tmins;
public:
    //A parameterized constructor
    RatePlan(string Cn, string Pn, int Bm, double Cr, double fNRate, string fN) : Plan(Cn, Pn, Bm)
    {
        callRate = Cr;
        favNumRate = fNRate;
        favNum = fN;
    }
    //calculateBill overridden function is to calculate & display the details of the bill.
    double calculateBill()
    {
        ifstream ifile;
        int fav_used;
        int O_used;
        fav_used = 0;
        O_used = 0;
        //calling readCalls function to calculate the used minutes for both same and other operators
        readCalls(ifile, fav_used, O_used);
        return (fav_used * favNumRate + O_used * callRate);
    }
    //readCalls overridden member function is to return the second parameter as the duration of the calls to the favorite number, and the third parameter as the calls to numbers other than the favorite number.
    void readCalls(ifstream& ifile, int& favM, int& otherM)
    {
        Tmins = 0;
        ifile.open("calls.txt");
        ifile.clear();
        ifile.seekg(0, ios::beg);
        string time, mins1 = "", secs1 = "", mins2 = "", secs2 = "", PhoneNumber;

        favM = 0;
        otherM = 0;
        int num;                   //num is the position of each character in time
        while (!ifile.eof())
        {
            mins1 = "";
            secs1 = "";
            mins2 = "";
            secs2 = "";
            ifile >> time;
            ifile >> PhoneNumber;
            int size = 0;
            size = time.length();
            //to see the num of digits of mins (before ':') in order to separate between minutes and secs
            for (int i = 0; i < size; i++)
            {
                if (time[i] == ':')
                    num = i;
            }
            //checks if the phone number is the favorite number or not
            if (PhoneNumber == favNum)
            {
                int m1;
                int s1;
                //calculate  the minutes done to the favorite number
                for (int j = 0; j < num; j++)                 //checks the num of digits of minutes(before ":")
                {
                    mins1 = mins1 + time[j];
                }
                m1 = stoi(mins1);                  //converts the minutes we calculated as a string to an integer value
                //calculate  the seconds done to the favorite number
                for (int j = num + 1; j < size; j++)            //checks the num of digits of seconds(after ":")
                {
                    secs1 = secs1 + time[j];
                }
                s1 = stoi(secs1);                  //converts the secs we calculated as a string to an integer value
                //to round up the call duration to minutes
                if (s1 > 0)
                    m1++;
                //sums up all the minutes of the same operator
                favM = favM + m1;
            }
            else
            {
                int m2;
                int s2;
                //calculate  the minutes to other operators
                for (int j = 0; j < num; j++)                 //checks the num of digits of minutes(before ":")
                {
                    mins2 = mins2 + time[j];
                }
                m2 = stoi(mins2);                  //converts the minutes we calculated as a string to an integer value
                //calculate  the seconds to other operators
                for (int j = num + 1; j < size; j++)            //checks the num of digits of seconds(after ":")
                {
                    secs2 = secs2 + time[j];
                }
                s2 = stoi(secs2);                  //converts the secs we calculated as a string to an integer value
                //to round up the call duration to minutes
                if (s2 > 0)
                    m2++;
                //sums up all the minutes of other operators
                otherM = otherM + m2;
            }
            //to calculate total minutes consumed
            Tmins = favM + otherM;

        }
    }
    //printAccountDetails  overridden function is to print all account’s details represented in Plan and RatePlan.
    void printAccountDetails()
    {
        ifstream ifile;
        int fav_used;
        int O_used;
        fav_used = 0;
        O_used = 0;
        //calling readCalls function to calculate the used minutes for both same and other operators
        readCalls(ifile, fav_used, O_used);
        cout << "customer's name: " << CustomerName << endl <<
             "phone number: " << PhoneNumber << endl <<
             "bill month: " << months[BillMonth - 1] << endl <<
             "Call rate: " << callRate << endl <<
             "Favorite number: " << favNum << endl <<
             "Favorite rate: " << favNumRate << endl <<
             "Total minutes consumed: " << Tmins << "minutes" << endl <<
             "Favorite minutes: " << fav_used << endl <<
             "Others minutes: " << O_used << endl <<
             "Monthly Bill: " << calculateBill() << endl;
    }
};

int main()
{
    int choose;
    string CustomerName;
    string PhoneNumber;
    int BillMonth;
    int sameMins, otherMins, monthlyCost;
    float outRate;
    int Tmins, remainingMins, outOfpackMins;
    double callRate, favNumRate;
    string favNum;
    /*ifstream ifile("calls.txt");
    ifile.open("calls.txt");
    int S_used;
    int O_used;
    int fav_used;
    S_used=0;
    O_used=0;
    fav_used=0;*/
    Plan* plans[5];
    ifstream file;

    for (int i = 0; i < 5; i++)
    {
        cout << "Please insert either '0' or '1' " << endl;
        cout << "Enter (0) for package plan and (1) for rate plan: " << endl;
        cin >> choose;
        if (choose == 0)
        {
            //plans[i] = new Packageplan(CustomerName, PhoneNumber, BillMonth, sameMins, otherMins, monthlyCost, outRate);
            cout << "Enter Customer Name : " << endl;
            cin.ignore();
            getline(cin, CustomerName);
            //cin>>CustomerName;
            cout << "Enter Phone Number : " << endl;
            cin >> PhoneNumber;
            cout << "Enter Month (1-12) : " << endl;
            cin >> BillMonth;
            cout << "Enter available minutes to the same operator : " << endl;
            cin >> sameMins;
            cout << "Enter available minutes to other operators : " << endl;
            cin >> otherMins;
            cout << "Enter monthly cost : " << endl;
            cin >> monthlyCost;
            cout << "Enter rate of out of package minutes : " << endl;
            cin >> outRate;
            plans[i] = new Packageplan(CustomerName, PhoneNumber, BillMonth, sameMins, otherMins, monthlyCost, outRate);
            //plans[i]->readCalls(ifile,S_used,O_used);
        }
        else if (choose == 1)
        {
            cout << "Enter Customer Name : " << endl;
            cin.ignore();
            getline(cin, CustomerName);
            cout << "Enter Phone Number : " << endl;
            cin >> PhoneNumber;
            cout << "Enter Month (1-12) : " << endl;
            cin >> BillMonth;
            cout << "Enter call rate : " << endl;
            cin >> callRate;
            cout << "Enter favorite number : " << endl;
            cin >> favNum;
            cout << "Enter favorite rate : " << endl;
            cin >> favNumRate;
            plans[i] = new RatePlan(CustomerName, PhoneNumber, BillMonth, callRate, favNumRate, favNum);
            //plans[i]->readCalls(ifile,fav_used,O_used);
        }
        else
            cout << "INVALID CHOICE" << endl;
        cout << endl << "_______________________________________________" << endl;
    }
    for (int i = 0; i < 5; i++)
    {
        plans[i]->printAccountDetails();
        cout << endl << plans[i]->calculateBill() << endl;
        cout << endl << "_______________________________________________" << endl;
    }

    return 0;
}
