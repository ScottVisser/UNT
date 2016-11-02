// Author: scott visser
// CSCE 2110 
// program 3

// add student fucntion  called table method under loop menu
void student::addstudent()
{
	cin >> id;
	cin >> fname;
	cin >> lname;
};

// display student information
void student::display()
{
	cout << "(" << id << "," << fname << "," << lname << ") ";
};

// checks particular student if id matches input
int student::checkid(int option3)
{
	if (option3 == id)
	 return 0;
	else 
	 return 1;
};

// add grade function called by table loop menu
void student::addgrade()
{
	if (gradecount == 0) // initial case (no grades entered for student)
	{
		grades = new grade [1];
		grades[0].addgrade();
	} 
	else	// else: re allocate size of grades* and add new input
	{
		class grade temp[gradecount];
		int i;
		for (i=0;i<gradecount;i++)
		 temp[i] = grades[i]; 
		grades = new grade [gradecount+1];
		for (i=0;i<gradecount;i++)
		 grades[i] = temp[i];
		grades[gradecount].addgrade();
	}
	gradecount++; // increment grade count member of particular student
};

// checks particular student for if they have any grades entered
int student::checkForGrades()
{
	if (gradecount == 0)
	 return 0;
	else if (gradecount > 0)
	 return 1;
};

// loop displaying grades for each student
void student::printgrades()
{
	int i;
	for (i=0;i<gradecount;i++)
	{
		cout << "(" << id << ",";
		grades[i].display();
	}
};