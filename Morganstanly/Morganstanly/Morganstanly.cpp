// Morganstanly.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "std_lib_facilities.h"
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <sstream>
using namespace std;


class Trade_sample {
public:
	string sTrade_number;
	string Trade_status;
	string product;
	string sprice;
	string date;
	string squantity;
	int Trade_number;
	double price;
	int quantity;
	Trade_sample(string data){
		stringstream ss;
		ss << data;
		char n;
		int pose = 0;
		while (ss >> n) {
			if (pose == 0 && n != ',') {
				sTrade_number += n;
			}
			else if (pose == 1 && n != ',') {
				Trade_status += n;
			}
			else if (pose == 2 && n != ',') {
				product += n;
			}
			else if (pose == 3 && n != ',') {
				date += n;
			}
			else if (pose == 4 && n != ',') {
				sprice += n;
			}
			else if (pose == 5 && n != ',') {
				squantity += n;
			}
			else if (n == ',') {
				pose += 1;
			}
		}
		stringstream a;
		a << sTrade_number;
		a >> Trade_number;
		a.clear();
		a << sprice;
		a >> price;
		a.clear();
		a << squantity;
		a >> quantity;

	}

};

class Mark{
public:
	string As_of_day;
	string company;
	string type;
	string contractmonth;
	string date;
	string smark;
	double mark;
	const string unit = "USD/BBL";
	Mark(string data) {
		stringstream ss;
		ss << data;
		char n;
		int pose = 0;
		while (ss >> n) {
			if (pose == 0 && n != ',') {
				As_of_day += n;
			}
			else if (pose == 1 && n != ',') {
				company += n;
			}
			else if (pose == 2 && n != ',') {
				type += n;
			}
			else if (pose == 3 && n != ',') {
				contractmonth += n;
			}
			else if (pose == 4 && n != ',') {
				date += n;
			}
			else if (pose == 5 && n != ',') {
				smark += n;
			}
			else if (n == ',') {
				pose += 1;
			}
		}
		stringstream a;
		a << smark;
		a >> mark;
	}


};


int future_search(vector<Mark> v1) {
	string mdate;
	double pprice;

	cout << "Please input the price settled before: " << endl;
	cin >> pprice;

	double quantity;
	cout << "Please input the quantity in this trade: " << endl;
	cin >> quantity;

	int len_of_mark = sizeof(v1);
	string company_name;
	cout << "Please input the date you want to search:(input form should be like '20170501') " << endl;
	cin >> mdate;
	vector<Mark> vdate;
	for (int i = 0;i < len_of_mark;i++) {
		if (mdate == v1[i].As_of_day) {
			vdate.push_back(v1[i]);
		}
		else continue;
	}
	if (vdate.empty()) {
		cout << "Invalid date! Please input again!" << endl;
		cin >> mdate;
		for (int i = 0;i < len_of_mark;i++) {
			if (mdate == v1[i].As_of_day) {
				vdate.push_back(v1[i]);
			}
			else continue;
		}
	}


	cout << "Please input the name of company: " << endl;
	cin >> company_name;
	vector<Mark> vcom;
	for (int i = 0;i < sizeof(vdate);i++) {
		if (company_name == vdate[i].company) {
			vcom.push_back(vdate[i]);
		}
		else continue;
	}
	if (vcom.empty()) {
		cout << "Bad company name! Please retry!" << endl;

	}


	string pdate;
	double preprice;
	cout << "Please input the present date: " << endl;
	cin >> pdate;
	for (int i = 0;i < sizeof(v1);i++) {
		if (vcom[i].date == pdate) {
			preprice = vcom[i].mark;
			cout << "The profit of this trade is " << (preprice - pprice)* quantity << endl;
			return (preprice - pprice) * quantity;

		}
		if (i == sizeof(vcom) - 1 && vcom[i].date != pdate) {
			cout << "Date you search is out of range!" << endl;
			return 0;
		}
	}

}


int swap_search(vector<Mark> v2) {
	string mdate;
	double pprice;

	cout << "Please input the price settled before: " << endl;
	cin >> pprice;

	double quantity;
	cout << "Please input the quantity in this trade: " << endl;
	cin >> quantity;

	int len_of_mark = sizeof(v2);
	string company_name;
	cout << "Please input the date you want to search:(input form should be like '20170501') " << endl;
	cin >> mdate;

	vector<Mark> vdate;
	for (int i = 0;i < len_of_mark;i++) {
		if (mdate == v2[i].As_of_day) {
			vdate.push_back(v2[i]);
		}
		else continue;
	}
	if (vdate.empty()) {
		cout << "Invalid date! Please input again!" << endl;
		cin >> mdate;
		for (int i = 0;i < len_of_mark;i++) {
			if (mdate == v2[i].As_of_day) {
				vdate.push_back(v2[i]);
			}
			else continue;
		}
	}


	cout << "Please input the name of company: " << endl;
	cin >> company_name;
	vector<Mark> vcom;
	for (int i = 0;i < sizeof(vdate);i++) {
		if (company_name == vdate[i].company) {
			vcom.push_back(vdate[i]);
		}
		else continue;
	}
	if (vcom.empty()) {
		cout << "Bad company name! Please retry!" << endl;

	}


	cout << "Please input present date: " << endl;
	string predate;
	cin >> predate;


	int n;
	for (int i = 0;i < sizeof(vcom);i++) {
		if (predate == vcom[i].date) {
			n = 1;
		}
		if (i == sizeof(vcom) - 1 && vcom[i].date != predate) {
			cout << "Date you search is out of range!" << endl;
			return 0;
		}
	}
	double msum = (sizeof(vcom) - n + 1) * pprice;
	double sum = 0;
	for (int j = n;j < sizeof(vcom);j++) {
		sum += vcom[j].mark;
	}
	double pro = (sum - pprice) * quantity;
	cout << "The profit of this swap is : " << pro << endl;


	return pro;
}


int main()
{
	cout << "Dealing with Mark file, please wait......" << endl;
	ifstream markfile;
	vector<Mark> mark_list;
	markfile.open("D:\Morganstanley\Marks.xlsx",ios::in);
	if (!markfile.is_open())
		cout << "Marks file opening mistake!" << endl;
	else {
		string ml;
		getline(markfile, ml);
		ml.clear();
		while (getline(markfile, ml)) {
			if (ml.empty()) continue;
			else {
				Mark p = Mark(ml);
				mark_list.push_back(p);
				ml.clear();
			}
		}
	}
	cout << "Finished! Please start searching for trade!" << endl;


	cout << "input 0 to quit,1 for future trade, 2 for swap: " << endl;
	int n = 0;
	while (n = 0) {
		int input;
		cin >> input;
		if (input == 0) n++;
		else if (input == 1) future_search(mark_list);
		else if (input == 2) swap_search(mark_list);
		else {
			cout << "Invalid input! Please input again!" << endl;
			continue;
		}
	}
	
	return 0;
}

