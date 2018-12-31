/**
* @file lab8.cpp
* @Nikola Maeda
* @Date 7/18/2018
* @version 1.0
* @section It reads the stock data of excel file and outputs a result on command line and text file.
*/

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

ifstream fin("StockPrices.csv");

//function to extract necessary data from Excel file
//it return true when it finishes the line or return false after reading all whole Excel file
bool store(int &day, int &month, int &year, double &high)
{
	string themonth,theday,theyear,date,skip,thehigh;
	for(int i=0; i<9;i++)
	{
	    //1st column: month
		if(i == 0)
		{
			if(getline(fin,themonth,'/'))
			{
				month = stoi(themonth);
				themonth.clear();
			}
			else
			{
				return false;
			}
		}
		//2nd column: day
		else if(i == 1)
		{
			if(getline(fin,theday,'/'))
			{
				day = stoi(theday);
				theday.clear();
			}
			else
			{
				return false;
			}
		}
		//3rd column: year
		else if(i == 2)
		{
			if(getline(fin,theyear,','))
			{
				year = stoi(theyear);
				theyear.clear();
			}
			else
			{
				return false;
			}
		}
		//4th column: high price
		else if(i == 4)
		{
			if(getline(fin,thehigh,','))
			{
				high = stod(thehigh);
				thehigh.clear();
			}
			else
			{
				return false;
			}
		}
		//last column: skip
		else if(i == 8)
		{
			if(getline(fin,skip))
			{
				skip.clear();
			}
			else
			{
				return false;
			}
		}
		//other
		else
		{
			if(getline(fin,skip,','))
			{
				skip.clear();
			}
			else
			{
				return false;
			}
		}
	}
	return true;
}

//Class Stock to store stock data
class Stock
{
public:
	Stock();
	Stock(const double &thehigh,const int &themonth,const int &thedate,const int &theyear);

    int getMonth() const;
    int getDate() const;
    int getYear() const;
    double getHigh() const;

    friend void averageMonth(vector<Stock> st);
	friend void averageYear(vector<Stock> st);
	friend void lowestandhighest(vector<Stock> st);
	friend bool hightolow(Stock a, Stock b);
	friend bool lowtohigh(Stock a, Stock b);
	friend ostream& operator << (ostream& outs, Stock &stock);

private:
	double high;
	int month;
	int date;
	int year;
};

//Default constructor
Stock::Stock()
{
	high = 0;
	month = 0;
	date = 0;
	year = 0;
}

//Constructor
Stock::Stock(const double &thehigh,const int &themonth,const int &thedate,const int &theyear)
{
	high = thehigh;
	month = themonth;
	date = thedate;
	year = theyear;
}

//returns month
int Stock::getMonth() const
{
     return month;
}
//returns date
int Stock::getDate() const
{
    return date;

}
//returns year
int Stock::getYear() const
{
    return year;
}
//returns high price
double Stock::getHigh() const
{
    return high;
}
//overloaded << operator
ostream& operator << (ostream& outs, Stock &stock)
{
    outs<<stock.month<<"/"<<stock.date<<"/"<<stock.year<<":"<<stock.high<<endl;
    return outs;
}
//displays average price of each year
void averageYear(vector<Stock> st)
{
	int i = 0;
	int year = st[i].year;
	double total = 0;
	while(st.size()>i)
	{
	    int j = 0;
		while(st[i].year == year && st.size()!=i)
		{
			total += st[i].high;
			i++;
			j++;
		}
		cout<<"The average of "<<year<<" is: "<<total/j<<endl;
		total = 0;
		year ++;
	}
}

//displays average price of each month
void averageMonth (vector<Stock> st)
{
    int i =0;
    int month =st[i].month;
    int year = st[i].year;
    double total = 0;
    while(st.size()>i)
    {
        int j =0;
        while(st[i].month == month && st.size()!=i)
        {
            total += st[i].high;
            i++;
            j++;
        }
        cout<<"The average of "<<month<<"/"<<year<<" is "<<total/j<<endl;
        total = 0;
        month++;
        if(month>12)
        {
            month = 1;
            year ++;
        }

    }
}
//Display lowest and highest data of each year using linear search
void lowestandhighest(vector<Stock> st)
{
    int i = 0;
    int year = st[i].year;
    int lowindex,highindex;
    double low, high;
    while(i<st.size())
    {
        low = st[i].high;
        high = st[i].high;
        while(year==st[i].year)
        {
            if(low>st[i].high)
            {
                low = st[i].high;
                lowindex = i;
            }
            if(high<st[i].high)
            {
                high = st[i].high;
                highindex = i;
            }
            i++;
        }
        cout<<year<<", Low:"<<low<<" on "<<st[lowindex].month<<"/"<<st[lowindex].date<<" High:"<<high<<" on "<<st[highindex].month<<"/"<<st[highindex].date<<endl;
        year ++;
    }

}
//conditional function
bool hightolow(Stock a, Stock b)
{
    return a.high>b.high;
}
//conditional function
bool lowtohigh(Stock a, Stock b)
{
    return !(a.high>b.high);
}

int main()
{
	string skip,high,low,average,date;
	double thehigh;
	int day,month,year;
	getline(fin,skip); //skipping the first row

	vector<Stock> mylist;
	int count =1;

	//storing stock data
	while(true)
	{
		if(store(day,month,year,thehigh))
		{
			Stock T(thehigh, month, day, year); //initializes T with stored values using constructor
			mylist.push_back(T);
			count++;
		}
		else
		{
			break;
		}
	}

	cout<<"---------------Displaying Average price per year---------------"<<endl;
    averageYear(mylist);

    cout<<endl<<"---------------Displaying Average price per month---------------"<<endl;
    averageMonth(mylist);

    cout<<endl<<"---------------Displaying Highest and Lowest price of each year---------------"<<endl;
    lowestandhighest(mylist);

    cout<<endl<<"---------------Creating Highest_to_Lowest.txt---------------"<<endl;
    cout<<"---------------Creating Lowest_to_Highest.txt---------------"<<endl;
    vector<Stock> htol = mylist;
    vector<Stock> ltoh = mylist;
    sort(htol.begin(),htol.end(),hightolow);
    sort(ltoh.begin(),ltoh.end(),lowtohigh);
    ofstream fhigh("Highest_to_Lowest.txt"); //creating text file for list of stock prices from highest to lowest
    ofstream flow("Lowest_to_Highest.txt"); //lowest to highest text file
    for(int i=0;i<htol.size();i++)
    {
        fhigh<<htol[i]<<endl;
    }
    for(int i=0;i<ltoh.size();i++)
    {
        flow<<ltoh[i]<<endl;
    }


	return 0;
}
