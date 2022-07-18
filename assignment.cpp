#include<iostream>
#include<cstring>
#include<fstream>
#include<iomanip>
using namespace std;

string inputFile  = "Stud.txt";
string outputFile = "ReportsOut.txt";

struct Course{
	string code;
	int credit;
	char grade;
};

struct Student{
	string id;
	string lastname;
	string firstname;
	char middleInitial;
	string phone;
	char sex;
	char classLevel[2];
	int totalCreditsFall;
	double CGPAFall;
	int noOfCourses;
	Course *courses;
	
	int springCredits;
	int totalCredits;
	double CGPA;
	
	void display(){
		cout<<"Student ID number: "<<id<<endl;
		cout<<"Name: "<<lastname<<", "<<firstname<<", "<<middleInitial<<endl;
		cout<<"Tel.: "<<phone<<endl;
		cout<<"Gender: ";
		if(sex == 'M'){
			cout<<"Male"<<endl;
		}else{
			cout<<"Female"<<endl;
		}
		
		cout<<"Class Level: ";
		if(strcmp(classLevel, "FR") == 0){
			cout<<"Freshman"<<endl;
		}else if(strcmp(classLevel, "JR") == 0){
			cout<<"Junior"<<endl;
		}else if(strcmp(classLevel, "SR") == 0){
			cout<<"Senior"<<endl;
		}else{
			cout<<"Sophomore"<<endl;
		}
		
		if(noOfCourses > 0){
			cout<<"Registration of Spring 2017: Yes"<<endl;
			cout<<endl<<endl;
			
			cout<<setw(44)<<"Unofficial Report Card\n";
			cout<<setw(13)<<"COURSE"<<setw(22)<<"CREDITS"<<setw(22)<<"GRADE"<<endl;
			cout<<"====================  ";
			cout<<"====================  ";
			cout<<"====================\n";
			
			for(int i=0; i<noOfCourses; i++)
			{
				cout<<setw(14)<<courses[i].code<<setw(18)<<courses[i].credit<<setw(23)<<courses[i].grade<<endl;
			}
			calculateCGPA();
			cout<<endl<<endl;
			cout<<"Credits for Spring 2017: "<<springCredits<<endl;
			cout<<"Fall 16 Semester GPA: "<<CGPAFall<<endl;
			cout<<"Total Credits: "<<totalCredits<<endl;
			cout<<"New Cumulative GPA: "<<CGPA<<endl;
		}
		cout<<"======================================================================"<<endl;
		cout<<endl<<endl;
	}
	
	void calculateCGPA()
	{
		int semesterCredits = 0;
		double semesterPoints = 0;
		double semesterGPA = 0;
		for(int i=0; i < noOfCourses; i++)
		{
			if(courses[i].grade == 'W')
				continue;
			
			switch(courses[i].grade){
				case 'A':
					semesterPoints += 4*courses[i].credit;
					break;
					
				case 'B':
					semesterPoints += 3*courses[i].credit;
					break;
					
				case 'C':
					semesterPoints += 2*courses[i].credit;
					break;
					
				case 'D':
					semesterPoints += 1*courses[i].credit;
					break;
					
				case 'F':
					semesterPoints += 0*courses[i].credit;
					break;
			}
			semesterCredits += courses[i].credit;
		}
		springCredits = semesterCredits;
		totalCredits  = totalCreditsFall + springCredits;
		
		double oldPoints  = totalCreditsFall*CGPAFall;
		double totalPoints= oldPoints + semesterPoints;
		CGPA = totalPoints/totalCredits;
	}
	
	
};

void getDataFromFile(ifstream &myfile, Student &student);
void writeDataInFile(ofstream &outFile, Student &student);

int main()
{
	ifstream myfile;
	myfile.open(inputFile.c_str());
	
	ofstream outFile;
	outputFile.clear();
	outFile.open(outputFile.c_str(), ios::app);
	
	Student student;
	
	if(myfile.is_open())
	{
		do{
			getDataFromFile(myfile, student);
			student.display();
			writeDataInFile(outFile, student);
		}while(!myfile.eof());
		myfile.close();
		outFile.close();
	}
	return 0;
}

void getDataFromFile(ifstream &myfile, Student &student){	
	myfile>>student.id;
	myfile>>student.lastname;
	myfile>>student.firstname;
	myfile>>student.middleInitial;
	myfile>>student.phone;
	myfile>>student.sex;
	myfile>>student.classLevel;
	myfile>>student.totalCreditsFall;
	myfile>>student.CGPAFall;
	myfile>>student.noOfCourses;
	student.courses = new Course[student.noOfCourses];
	
	for(int i=0; i < student.noOfCourses; i++)
	{
		myfile>>student.courses[i].code;
		myfile>>student.courses[i].credit;
		myfile>>student.courses[i].grade;
	}
}

void writeDataInFile(ofstream &outFile, Student &student){
	outFile<<"Student ID number: "<<student.id<<endl;
	outFile<<"Name: "<<student.lastname<<", "<<student.firstname<<", "<<student.middleInitial<<endl;
	outFile<<"Tel.: "<<student.phone<<endl;
	outFile<<"Gender: ";
	if(student.sex == 'M'){
		outFile<<"Male"<<endl;
	}else{
		outFile<<"Female"<<endl;
	}
	
	outFile<<"Class Level: ";
	if(strcmp(student.classLevel, "FR") == 0){
		outFile<<"Freshman"<<endl;
	}else if(strcmp(student.classLevel, "JR") == 0){
		outFile<<"Junior"<<endl;
	}else if(strcmp(student.classLevel, "SR") == 0){
		outFile<<"Senior"<<endl;
	}else{
		outFile<<"Sophomore"<<endl;
	}
	
	if(student.noOfCourses > 0){
		outFile<<"Registration of Spring 2017: Yes"<<endl;
		outFile<<endl<<endl;
		
		outFile<<setw(44)<<"Unofficial Report Card\n";
		outFile<<setw(13)<<"COURSE"<<setw(22)<<"CREDITS"<<setw(22)<<"GRADE"<<endl;
		outFile<<"====================  ";
		outFile<<"====================  ";
		outFile<<"====================\n";
		
		for(int i=0; i<student.noOfCourses; i++)
		{
			outFile<<setw(14)<<student.courses[i].code<<setw(18)<<student.courses[i].credit<<setw(23)<<student.courses[i].grade<<endl;
		}
		student.calculateCGPA();
		outFile<<endl<<endl;
		outFile<<"Credits for Spring 2017: "<<student.springCredits<<endl;
		outFile<<"Fall 16 Semester GPA: "<<student.CGPAFall<<endl;
		outFile<<"Total Credits: "<<student.totalCredits<<endl;
		outFile<<"New Cumulative GPA: "<<student.CGPA<<endl;
	}
	outFile<<"======================================================================"<<endl;
	outFile<<endl<<endl;
}
