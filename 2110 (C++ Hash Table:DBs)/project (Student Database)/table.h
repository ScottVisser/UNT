// Author: scott visser
// CSCE 2110 
// program 3

//menu loop
void table::loop1(void)
{
	string option1 = "\0";
	string option2 = "\0";
	while(1)
	{
		cout << "table> ";
		cin >> option1;
		if (option1 == "quit")
		 exit(1);
		cin >> option2;
		
		if ((option1 == "students") && (option2 == "add"))
		{
			if (studentcount == 0)
			{
				students = new student [1];
				students[0].addstudent();
			} 
			else
			{
				class student temp[studentcount];
				int i;
				for (i=0;i<studentcount;i++)
				 temp[i] = students[i]; 
				students = new student [studentcount+1];
				for (i=0;i<studentcount;i++)
				 students[i] = temp[i];
				students[studentcount].addstudent();
			}
			studentcount++;
		}

		else if ((option1 == "students") && (option2 == "delete"))
		{
			if (studentcount == 0)
			 cout << "ERROR: NO STUDENTS ENTERED" << endl;

			else
			{
				int i;
				int option3;
				cin >> option3;
				for (i=0;i<studentcount;i++)
				{
					if (students[i].checkid(option3) == 0)
					{
						int j;
						class student temp1[i];
						class student temp2[studentcount-i-1];
						for (j=0;j<i;j++)
						 temp1[j] = students[j];
						for (j=0;j<studentcount-i-1;j++)
						 temp2[j] = students[j+i+1];
						studentcount--;
						if (studentcount == 0)
						{
							students = NULL;
							break;
						}
						students = new student[studentcount];
						if (i == 0)
						{
							for (j=0;j<studentcount;j++)
							 students[j]=temp2[j];
						} 
						else
						{
							for (j=0;j<i;j++)
							 students[j] = temp1[j];
							for (j=i;j<studentcount-i+1;j++)
							 students[j] = temp2[j-i];
						}
		
					}
				}
			}	
		}
		
		

		else if ((option1 == "students") && (option2 == "display"))
		{
			int i;
			for (i=0;i<studentcount;i++)
			 students[i].display();
			cout << endl;
		}

		else if ((option1 == "grades") && (option2 == "add"))
		{
			int i;
			int option3;
			cin >> option3;
			for (i=0;i<=studentcount;i++)
			{
				if (i == studentcount)
				{
					cout << "STUDENT NOT FOUND" << endl;
					break;
				}
				else if (students[i].checkid(option3) == 0)
				{
					students[i].addgrade();
					break;
				}
			}

		}

		else if ((option1 == "grades") && (option2 == "delete"))
		{
			cout << "OPTION NOT AVAILABLE";
		}

		else if ((option1 == "grades") && (option2 == "display"))
		{
			int i;
			if (studentcount == 0)
			{
				cout << "ERROR: NO RECORDS" << endl;
			}
			else
			{
				for (i=0;i<studentcount;i++)
				{
					if (students[i].checkForGrades() == 1)
					 students[i].printgrades();
				}
				cout << endl;
			}
		}
		else
		 cout << "INVALID INPUT" << endl;
	}
};
