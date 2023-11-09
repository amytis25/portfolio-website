#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <string>
using namespace std;

bool CheckInRange(int input, int max, int min);
int CheckIntegerIn(istream& datastream, int value, int maxValue, int minValue, string inputneeded);
string AccessClassData(double **gradeArraypp, int numStudents,
	int numActivities, int numActivitiesUsed,
	int unused1, int unused2);
void PrintMatrix(double** dataArraypp, int numStudents, int numActivities);
void PrintArrays(double** dataArraypp, double* percentageGrade,
	bool* IsFinal, int numStudents, int numActivities);
void SortData(double** gradeArray, int numStudents, int numActivities);
int CheckDoubleIn(istream& dataStream, double value,
	double maxValue, double minValue);
void CalcGradeForStudents(double** gradeArray,
	double* percentageGrade, bool* isFinal, int numStudents,
	int numActivities, int numActivitiesUsed);
void InsertionSort(double* inArray, int N);




// global constants
int MIN_STUDENTS = 0;
int MAX_STUDENTS = 5000;
int MIN_ACTIVITIES = 0;
int MAX_ACTIVITIES = 500;
int MIN_ACTIVITIES_USED = 0;
int MAX_ACTIVITIES_USED = 500;
float MIN_GRADE = -1000.0;
float MAX_GRADE = 1000.0;


int main()
{
	//VARIABLES AND CONSTANTS 
	string inputName;
	ifstream infile;
	ofstream outfile;
	string outputname;
	int studentnum = 0;
	int activitiesnum = 0; 
	int numActivitiesUsed = 0;
	int inputerror = 0;
	string gradestatus;
	double **scoreArraypp = NULL;
	float grade = 0;
	string inputneeded;
	int unused1 = 0;
	int unused2 = 0;
	double *percentageGradep = NULL;
	bool* isFinal = NULL;

	inputneeded = "Students";
	cout << "Enter the number of " << inputneeded << ": ";
	cin >> studentnum;
	

	inputneeded = "Activities";
	cout << "Enter the number of " << inputneeded << ": ";
	cin >> activitiesnum;
	
	
	inputneeded = "activities to be used to calculate the final grade";
	cout << "Enter the number of " << inputneeded << ": ";
	cin >> numActivitiesUsed;
	
	/* check function but it doesn't work	
	inputneeded = "Students";
	cout << "Enter the number of " << inputneeded << ": ";
	cin >> studentnum;
	for (int count = 0; count < 3; count++) {
		cout << "Enter the number of " << inputneeded << ": ";
		cin >> studentnum;

		if (CheckIntegerIn(cin, studentnum, MAX_STUDENTS, MIN_STUDENTS, inputneeded) == 1 || 2 ){
			inputerror = 1;

		}
		else {
			count = 3;
			inputerror = 0;

		}
	}	if (inputerror == 1) {
		cout << "ERROR: You exceeded maximum number of tries allowed while entering the number of " << inputneeded << endl;
		delete[] scoreArraypp;
		exit;
	}

	inputneeded = "Activities";
	cout << "Enter the number of " << inputneeded << ": ";
	cin >> activitiesnum;
	for (int count = 0; count < 3; count++) {
		cout << "Enter the number of " << inputneeded << ": ";
		cin >> activitiesnum;

		if (CheckIntegerIn(cin, activitiesnum, MAX_ACTIVITIES, MIN_ACTIVITIES, inputneeded) == 1 || 2 ) {
			inputerror = 1;
			delete[] scoreArraypp;
			exit;

		}
		else {
			count = 3;
			inputerror = 0;

		}
	}	if (inputerror == 1) {
		cout << "ERROR: You exceeded maximum number of tries allowed while entering the number of " << inputneeded << endl;
		delete[] scoreArraypp;
		exit;
	}
	
	inputneeded = "activities to be used to calculate the final grade";
	cout << "Enter the number of " << inputneeded << ": ";
	cin >> numActivitiesUsed;
	for (int count = 0; count < 3; count++) {
		cout << "Enter the number of " << inputneeded << ": ";
		cin >> numActivitiesUsed;

		if (CheckIntegerIn(cin, numActivitiesUsed, MAX_ACTIVITIES_USED, MIN_ACTIVITIES_USED, inputneeded) == 1 || 2 ) {
			inputerror = 1;


		}
		else {
			count = 3;
			inputerror = 0;

		}
	}	if (inputerror == 1) {
		cout << "ERROR: You exceeded maximum number of tries allowed while entering the number of " << inputneeded << endl;
		delete[] scoreArraypp;
		exit;
	}*/
	scoreArraypp = new double*[studentnum];
	for (int rows = 0; rows<studentnum ; rows++) {
		scoreArraypp [rows] = new double[activitiesnum];
	}
	percentageGradep = new double[studentnum];
	isFinal = new bool[studentnum];
	AccessClassData( scoreArraypp, studentnum,
		activitiesnum, numActivitiesUsed,
		unused1, unused2);

	/*SortData(scoreArraypp, studentnum, activitiesnum);

	CalcGradeForStudents(scoreArraypp,
		percentageGradep, isFinal, studentnum,
		activitiesnum, numActivitiesUsed);

	PrintMatrix(scoreArraypp, studentnum, activitiesnum);

	PrintArrays(scoreArraypp, percentageGradep,
		isFinal, studentnum, numActivitiesUsed);*/

	delete [] scoreArraypp;
	delete [] percentageGradep;
	delete [] isFinal;
}

int CheckIntegerIn(istream& datastream, int value, int maxValue, int minValue, string inputneeded) {

	if (datastream.fail())
	{
		cout << "Number of " << inputneeded << " could not be read" << endl;
		return 1;

	}
	else if (CheckInRange(value, maxValue, minValue) == false)
	{
		cout << "invalid number of " << inputneeded << endl << "The number of " << inputneeded << " has to be between " << minValue << " and " << maxValue << endl;
		return 2;

	}
	else {

		return 0;
	}
}

bool CheckInRange(int input, int max, int min) {
	if (input >= min && input <= max) {
		return true;
	}
	else {
		return false;
	}
}



string AccessClassData(double **gradeArraypp, int numStudents,
	int numActivities, int numActivitiesUsed,
	int unused1, int unused2){
	double *gradep = NULL;
	int inputerror = 0;
	double MIN_PERCENTAGE = -1000.0;
	string gradestatus;
	string returnstring;
	string inputname;
	ifstream infile;
	gradep = new double;
	
	for (int count = 0; count < 3; count++) {
		cout << endl << "Enter the name of the filename containing the grade data: ";
		cin >> inputname;

		infile.open(inputname);
		if (infile.fail())
		{
			cerr << "ERROR: " << inputname << " not opened correctly" << endl;
			infile.clear();
			inputerror = 1;

		}
		else {
			cout << "file opened" << endl;
			count = 3;
			inputerror = 0;
		}
	}

	if (inputerror == 1) {
		cout << "ERROR: You exceeded maximum number of tries allowed while entering the input file name" << endl;
		exit;
	}	
	for (int studentnumber = 0; studentnumber < numStudents; studentnumber++) {
		for (int activitynumber = 0; activitynumber < numActivitiesUsed; activitynumber++) {
			infile >> *gradep;
			if (*gradep < MIN_PERCENTAGE) {
				gradestatus = "missing";
				//cout << fixed << setw(12) << gradestatus;
			}
			else if (CheckInRange(*gradep, MAX_GRADE, MIN_GRADE) == false) {
				gradestatus = "invalid";
				//cout << fixed << setw(12) << gradestatus;
			}
			else {
				gradeArraypp[studentnumber][activitynumber] = gradep;
				cout << fixed << setw(12) << setprecision(2) << gradeArraypp[studentnumber][activitynumber];
				gradestatus = "recorded grade";

			}
		}
		cout << endl;
	}
	delete gradep;
	return returnstring;
}

void PrintMatrix(double** dataArraypp, int numStudents, int numActivities) {

	double MIN_PERCENTAGE = -1000.0;
	string gradestatus;
	//double* gradep = dataArraypp[numStudents][numActivities];
	for (int studentnumber = 0; studentnumber < numStudents; studentnumber++) {
		for (int activitynumber = 0; activitynumber < numActivities; activitynumber++) {

			if (dataArraypp[studentnumber][activitynumber] < MIN_PERCENTAGE) {
				gradestatus = "missing";
				cout << fixed << setw(12) << gradestatus;
			}
			else if (CheckInRange(dataArraypp[studentnumber][activitynumber], MAX_GRADE, MIN_GRADE) == false) {
				gradestatus = "invalid";
				cout << fixed << setw(12) << gradestatus;
			}
			else {
				//dataArraypp[studentnumber][activitynumber] = gradep;
				cout << fixed << setw(12) << setprecision(2) << dataArraypp[studentnumber][activitynumber];
				gradestatus = "recorded grade";
			}
		}
		cout << endl;
	}

	return;
}


void PrintArrays(double** dataArraypp, double* percentageGrade,
	bool* IsFinal, int numStudents, int numActivities) {
	double MIN_PERCENTAGE = -1000.0;
	string gradestatus;
	double* gradep = NULL;
	gradep = new double; 

	for (int studentnumber = 0; studentnumber < numStudents; studentnumber++) {
		for (int activitynumber = 0; activitynumber < numActivities; activitynumber++) {
			dataArraypp[studentnumber][numActivities] = *gradep;
			if (*gradep < MIN_PERCENTAGE) {
				gradestatus = "missing";
				cout << fixed << setw(12) << gradestatus;
			}
			else if (CheckInRange(*gradep, MAX_GRADE, MIN_GRADE) == false) {
				gradestatus = "invalid";
				cout << fixed << setw(12) << gradestatus;
			}
			else {
				dataArraypp[studentnumber][activitynumber] = *gradep;
				cout << fixed << setw(12) << setprecision(2) << dataArraypp[studentnumber][activitynumber];
				gradestatus = "recorded grade";
			}
		}
		cout << percentageGrade[studentnumber] << " " << IsFinal[studentnumber] << endl;

	}

	return;
}

void SortData(double** gradeArray, int numStudents, int numActivities) {


	for (int row = 0; row < numStudents; row++) {
		for (int col = 0; col < numActivities; col++) {

			InsertionSort(&gradeArray[row][col], numActivities);

		}
	}

	return;
}

int CheckDoubleIn(istream& dataStream, double value,
	double maxValue, double minValue) {

	if (dataStream.eof()) {
		//no more data
		dataStream.clear();
		return 1;
	}
	else if (dataStream.fail()) {
		//data is corrupt
		dataStream.clear();
		return 2;
	}
	else if (value < minValue || value > maxValue) {
		// data out of range
		return 3;
	}
	else 
	{
		return 0;
	}
}

void CalcGradeForStudents(double** gradeArray,
	double* percentageGrade, bool* isFinal, int numStudents,
	int numActivities, int numActivitiesUsed) {

	double sum = 0;
	int count = 0;

	for (int studentnumber = 0; studentnumber < numStudents; studentnumber++) {
		for (int activitynumber = 0; activitynumber < numActivities; activitynumber++) {
			if (gradeArray[studentnumber][activitynumber] > MIN_GRADE) {
				sum = gradeArray[studentnumber][activitynumber] + sum;
				count++; 
			}
		} 
		if (count < numActivitiesUsed) {
			isFinal [studentnumber] = false;
		}
		percentageGrade[studentnumber] = sum / count; 
		count = 0; 
	}

	return;
}

void InsertionSort(double* inArray, int N) {

		for (int i = 1; i < N; i++)
		{
			double* placeholderp = NULL;
			placeholderp = &inArray[i];
			int x = i;

			while (*placeholderp < inArray [x-1]&& x > 0)
			{
				inArray[x] = inArray[x - 1];
				inArray[x - 1] = *placeholderp;
				x--;

			}
		}

	return;
}