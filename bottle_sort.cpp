#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <string>
using namespace std;

int main()
{
	//DEFINE AND INITIALIZE VARIABLES AND CONSTANTS HERE
	string inputName;
	ifstream inFile;

	//ADD YOUR CONSTANTS AND VARIABLE INITIALIZATIONS AND DECLARATIONS HERE
	int numLinesData = 0;
	int MIN_LINESDATA = 0;
	double spring = 0;
	double weight = 0;
	double colour = 0;
	int linenum = 1;
	string use; 
	string usable = "usable";
	string broken = "broken";
	double factor = (5.0/255.0);
	//factor = factor / 255;
	int totalA = 0; 
	int totalB = 0;
	int totalC = 0;
	int totalother = 0; 
	double wasteweight = 0;
	double totalwaste = 0;
	double gtokg = (1.0/1000.0);

	// request input filename
	// open the file and check it was opened correctly
	cout << "Type the name of the input file containing sensor readings: " << endl;
	cin >> inputName;

	inFile.open(inputName);
	if (inFile.fail())
	{
		cerr << "ERROR: File " << inputName
			<< " could not be opened for input" << endl;
		inFile.clear();
	}

	//To read from input file use inFile instead of cin  for example
	inFile >> numLinesData;   //Reads first line of file (number of fragments)

	//ADD CODE HERE
	//TEST IF numLInesData IS IN RANGE
	//TERMINATE IF NOT
	if (numLinesData > MIN_LINESDATA)
	{
		cout << "There are " << numLinesData << " bottles or fragments to be processed" << endl;
	}
	else
	{
		cout << "invalid number of bottles or fragments" << endl;
		exit;
	}
	ifstream infile;
	infile.open(inputName);
	infile >> numLinesData;
	for (int count = 0; count < numLinesData; count++)
	{
		//INSERT CODE HERE
		//MAIN PROGRAM

			infile >> spring >> colour >> use;
			//cout << spring << endl; 
			weight = (20 * spring * factor);

			if (weight <= 0 || weight >= 255)
			{
				cout << "weight sensor reading out of range, ignoring line " << linenum << " in the input file" << endl;
			}
			else if (colour <= 0 || colour > 255)
			{
				cout << "Colour Sensor reading out of range, ignoring line " << linenum << " in the input file" << endl;
			}
			// its classifying everything as broken 
			else if (use != usable) {
				cout << "The robot has rotated 270 degrees to face the waste container" << endl;
				wasteweight = wasteweight + weight;
				totalwaste = totalwaste + weight;
				cout << fixed << setprecision(3) << "The waste container now contains " << setw(8) << wasteweight << " grams of glass" << endl;

				if (wasteweight > 750.0) {
					cout << "A new waste container is needed" << endl;
					cout << "Stop the incoming conveyor belt" << endl;
					cout << "A new waste container is ready for use" << endl;
					cout << "Start the incoming conveyor belt" << endl;
					wasteweight = 0;
				}
				cout << "The robot rotates -270 degrees" << endl;
			}
			else if (weight > 74.0 && weight < 90.0 && colour > 170.0 && colour < 195.0) // type A
			{
				totalA++;
				cout << "The robot has rotated 90 degrees to face the TYPE A bottles conveyor belt" << endl;
				cout << "The robot has placed " << totalA << " TYPE A bottles on the conveyor belt" << endl;
				cout << "The robot rotates -90 degrees" << endl;

			}
			else if (weight > 50.0 && weight < 60.0 && colour > 55.0 && colour < 95.0) // type B
			{
				totalB++;
				cout << "The robot has rotated 150 degrees to face the TYPE B bottles conveyor belt" << endl;
				cout << "The robot has placed " << totalB << " TYPE B bottles on the conveyor belt" << endl;
				cout << "The robot rotates -150 degrees" << endl;
			}
			else if (weight > 35.0 && weight < 41.0 && colour > 235.0 && colour <= 255.0) //type C
			{
				totalC++;
				cout << "The robot has rotated 210 degrees to face the TYPE C bottles conveyor belt" << endl;
				cout << "The robot has placed " << totalC << " TYPE C bottles on the conveyor belt" << endl;
				cout << "The robot rotates -210 degrees" << endl;
			}
			else {
				totalother++;
				cout << "The robot has rotated 45 degrees to face the OTHER bottles conveyor belt" << endl;
				cout << "The robot has placed " << totalother << " OTHER bottles on the conveyor belt" << endl;
				cout << "The robot rotates -45 degrees" << endl;
			}
			linenum++;
	}
	inFile.close();


	//ADD CODE HERE
	//PRINT SUMMARY OUTPUT HERE
	totalwaste = totalwaste * gtokg;
	/* SUMMARY
	The robot processed 3 TYPE C bottles
	The robot processed 3 TYPE B bottles
	The robot processed 3 TYPE A bottles
	The robot processed 14 OTHER bottles
	The robot processed 0.7914 kg of waste glass */
	cout << "\n \n \nSUMMARY" << endl;
	cout << "The robot processed " << totalC << " TYPE C bottles" << endl;
	cout << "The robot processed " << totalB << " TYPE B bottles" << endl;
	cout << "The robot processed " << totalA << " TYPE A bottles" << endl;
	cout << "The robot processed " << totalother << " OTHER bottles" << endl;
	cout << "The robot processed " << fixed << setprecision(4) << setw(12) << totalwaste << " kg of waste glass" << endl; 


	return 0;
}
