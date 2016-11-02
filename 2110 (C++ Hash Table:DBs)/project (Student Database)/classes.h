// Author: scott visser
// CSCE 2110 
// program 3



// libraries
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <string>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

// grades class
class grade
{
	private:
	 string course;
	 char score;

	public:
	 grade();
	 void addgrade();
	 void display();

};
//grades constructor
grade::grade()
{
	course = "\0";
	score = 0;
};

// student class defined
class student
{
	private:
	 int id;
	 string fname;
	 string lname;
	 class grade *grades;
	 int gradecount;
	public: // student methods and constructor
	 student(); 
	 void addstudent();
	 void display();
	 int checkid(int option3);
	 void addgrade();
	 int checkForGrades();
	 void printgrades();
};
// constructor
student::student()
{
	int id = 0;
	fname = "\0";
	lname = "\0";
	grades = NULL;
	gradecount = 0;
};

// table class defined
class table
{
	private:
	 class student *students;
	 int studentcount;
	public:
	 table(void);
	 void loop1(void);
};
// constructor
table::table()
{
	students = NULL;
	studentcount = 0;
};
