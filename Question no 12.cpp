// Question no 12.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<windows.h>
using namespace std;
//definning person Type class
class personType {
	string firstName;
	string lastName;
public:
	personType(string first, string second) :firstName(first), lastName(second) {}
	personType() {
		firstName = "\0";
		lastName = "\0";
	}

	void setName();
	string getFirName();
	string getLasName();
};
void personType::setName() {
	cout << "first Name: " << endl;
	cin >> firstName;
	cout << "last Name: " << endl;
	cin >> lastName;
}
string personType::getFirName() {
	return firstName;
}
string personType::getLasName() {
	return lastName;
}

class doctorType :virtual public personType {
	string speciality;
public:
	doctorType(string fN,string lN,string special):personType(fN,lN),speciality(special){}
	doctorType() {
		personType();
		speciality = "\0";
	}
	void setInfo();
	string getDFirName();
	string getDLaName();
	string getDSpec();
};
string doctorType::getDSpec() {
	return speciality;
}
string doctorType::getDLaName() {
	return getLasName();
}
string doctorType::getDFirName() {
	return getFirName();
}
void doctorType::setInfo() {
	cout << "Doctor's Name" << endl;
	setName();
	cout << "Doctor's Speciality" << endl;
	cin >> speciality;
}

class billType {
	string patientId;
	float MedCharges;
	float DocCharges;
	float roomCharges;
public:
	billType(string id,float MC,float DC,float RC):patientId(id),MedCharges(MC),DocCharges(DC),
		roomCharges(RC){}
	billType() {
		patientId = "000";
		MedCharges = 0.0;
		DocCharges = 0.0;;
		roomCharges = 0.0;
	}
	void setData();
	string getId();
	float getMChar();
	float getDChar();
	float getRChar();
};
string billType::getId() {
	return patientId;
}
float billType::getMChar() {
	return MedCharges;
}
float billType::getDChar() {
	return DocCharges;
}
float billType::getRChar() {
	return roomCharges;
}
void billType::setData() {
	cout << "Enter patient's ID" << endl; cin >> patientId;
	cout << "Enter patient's MedCharges" << endl; cin >> MedCharges;
	cout << "Enter  patients's Doctor Fee" << endl; cin >> DocCharges;
	cout << "Enter patient's room charges" << endl; cin >> roomCharges;
}
class dateType {
	int day;
	int month;
	int year;
public:
	dateType(int dd, int mm, int yy) :day(dd), month(mm), year(yy) {}
	dateType() {
		day = 00;
		month = 00;
		year = 00;
	}
	void setDate();
	int getDay();
	int getMonth();
	int getYear();
};

void dateType::setDate() {
	SYSTEMTIME curr;
	GetSystemTime(&curr);
	cout << "year : ";
	cin >> year;
	while (year > curr.wYear) {
		cout << "enter enter the correct year" << endl;
		cin >> year;
	}

	cout << "month : ";
	cin >> month;
	while ((month < 1 || month >12) || ((year == curr.wYear && month > curr.wMonth))) {
		cout << "enter the correct month" << endl;
		cin >> month;
	}
	cout << "Day : ";
	cin >> day;
	while ((day < 1 || day >31) || ((year == curr.wYear && month <= curr.wMonth && day > curr.wDay))) {
		cout << "enter the correct day" << endl;
		cin >> day;
	}

}
int dateType::getDay() {
	return day;
}
int dateType::getMonth() {
	return month;
}
int dateType::getYear() {
	return year;
}

class patientType :virtual public personType, virtual public doctorType,virtual public billType {
	dateType* data;
	string patientsId;    
	string age; 
public: 
	patientType() {
		data = new dateType[3];
		personType();
		doctorType();
	}

	void setPatientInfo();
	void getPatientInfo();
};

void patientType::setPatientInfo() {
	SYSTEMTIME date;
	GetSystemTime(&date);
	cout << "                  Patient Name: " << endl;
	setName();
	cout << "                 Patient id: " << endl;
	cin >> patientsId;
	cout << "           Patient's Date Of Birth: " << endl;
	data[0].setDate();
	int year = date.wYear - data[0].getYear();
	int month = date.wMonth - data[0].getMonth();
	int day = date.wDay - data[0].getDay();
	age = year + '/' + month + '/' + day;
	cout << "            Patient's Admit Date: " << endl;
	data[1].setDate();
	cout << "          Patient's Discharge Date: " << endl;
	data[2].setDate();
	cout << "          physician’s information: " << endl;
	setInfo();
	cout << "            set billing information: " << endl;
	setData();
}
void patientType::getPatientInfo() {
	cout << "              PATIENT'S INFORMATION: " << endl;
	cout << "patient Name: " << getFirName() << " " << getLasName() << endl;
	cout << "patient ID: " << patientsId << endl;
	cout << "patient Age: " << age << endl;
	cout << "Patient's Admit Date: " << data[1].getMonth() << "/" << data[1].getDay() << "/" << data[1].getYear() << endl;
	cout<<"patient's discharge Date: "<< data[2].getMonth() << "/" << data[2].getDay() << "/" << data[2].getYear() << endl;
	cout << "medicine Charges:" << getMChar() << endl;
	cout << "Room charges" << getRChar();
	cout << "             PHYSICIAN'S INFORMATION: " << endl;
	cout <<"Name: " << getDFirName() << " " << getDLaName() << endl;
	cout << "Speciality: " << getDSpec() << endl;
	cout << "physician's Fee: " << getDChar() << endl ;
}

void menu() {
	cout << "1.to set patient information" << endl;
	cout << "2.to diplay the patint information" << endl;
	cout << "3.to display all the patients information" << endl;
	cout << "4.go back to main menu" << endl;
	cout << "5.to exit" << endl;
}
int main()
{
	int size;     //size of patients 
	patientType* p = NULL;
	p = new patientType[500];
	string name;        //name to diplay the information of after searching
	char option;
	do{
	cout << "chose the option" << endl;
	menu();
	cin >> option;
	switch (option) {
	case '1':
		cout << "how many patients data to store" << endl;
		cin >> size;
		for (int i = 0; i < size; i++) {
			cout << "enter the data of patient " << i + 1 << endl<<endl;
			p[i].setPatientInfo();
		}
		cout << endl;
		break;
	case '2':
		cout << "enter the person last Name to display the information of" << endl;
		cin >> name;
		for (int i = 0; i < size; i++) {
			if (name == p[i].getLasName()) {
				p[i].getPatientInfo();
				break;
			}
		}
		break;
	case '3':
		for (int i = 0; i < size; i++) {
			cout << "patient " << i + 1 << endl;
			p[i].getPatientInfo();
			cout << endl;
		}
		break;
	case '4':
		break;
	case '5':
		exit(0);
	default:
		cout << "chose the correct option" << endl;
	}
}
	while (true);

}

