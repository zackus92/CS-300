// CS-300 Project Two
// Ryan Zackus
// 2-22-2024

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

class Course {                    //  Class to hold course info
public:
	string courseNumber;
	string courseTitle;
	vector<string> prerequisites;
	  
	Course() = default;         //Constructor set to default         
	Course(string number, string title, vector<string> prereq)     //Constructor initializes a Course using a vector for the prerequisites
		: courseNumber(number), courseTitle(title), prerequisites(prereq) {
	}
};

map<string, Course> courses;   // Using a map I can store the courses and use the course numbers as keys!  
                               // Map also keeps the keys sorted
void LoadCourseFromFile(string& fileName) {
	string line;                                  // This loads the course info from the file from user input
	ifstream file(fileName);                      // and counts how many courses are loaded. 
	int counter = 0;

	if (!file.is_open()) {
		cout << "Unable to locate file." << endl;

		return;
	}

	while (getline(file, line)) {         //Reads every line in the file and stores course info.
		stringstream sStream(line);
		string part, courseNumber, courseTitle;
		vector<string>prerequisites;

		getline(sStream, courseNumber, ',') ; //Parses the CSV line into course details.
		
		getline(sStream, courseTitle, ',');

		while (getline(sStream, part, ',')) {   //Grabs any prerequisites that come after the course
			prerequisites.push_back(part);
		}
		courses[courseNumber] = Course(courseNumber, courseTitle, prerequisites);
		counter++;                                         // Stores the course in map
	}
	cout << "Courses loaded " << counter << endl;
}
void PrintCourseInfo(string& courseNumber) {             //Prints info for the course relating to the course number that user inputs
	if (courses.find(courseNumber) != courses.end()) {

		Course& course = courses[courseNumber];         // Finds the course using the coursenumber

		cout << "Course number:" << course.courseNumber << endl;
		cout << "Course title:" << course.courseTitle << endl;
		cout << "Prerequisites:";

		for (string& prereq : course.prerequisites) {
			cout << prereq << " ";
		}
		cout << endl;
	}
	else {
		cout << "Course Not found" << endl ;
	}

}

void PrintAllCourses() {                          // Courses already sorted by course number using map, 
	for (auto& pair : courses) {                  // Iterates through and prints the course number then the course title                       
		cout << pair.first << " " << pair.second.courseTitle << endl;
	}
}


void Menu() {                 // creates the menu that the user will interface wit
	string input;
	int choice;
	string fileName, courseNumber;

	while (true) {                               //creates a loop, the menu will keep going until the user inputs 9
		cout << "1. Load Course Data " << endl;
		cout << "2. Print Course Info " << endl;
		cout << "3. Print all courses " << endl;
		cout << "9. Exit" << endl;
		cout << "Make a selection: " << endl;

		getline(cin, input);                           // Reads the user input and turns it into an int
		stringstream(input) >> choice; 
		
		switch (choice) {                               
		case 1:                                                 // This handles what the user inputs. They can load courses from a file
			cout << "Enter the full path and file name: ";     // with the path and file name 
			getline(cin, fileName);
			LoadCourseFromFile(fileName);
			break;
		case 2:
			cout << "Input Course Number; ";
			getline(cin, courseNumber);                     // Takes the users specific course number and shows info about that course.
			PrintCourseInfo(courseNumber);
			break;
		case 3:                                             // Prints information for all courses
			PrintAllCourses();
			break;
		case 9:
			cout << "Goodbye!" << endl;                    //Close the program
			return ;
		default:

			cout << "Choose a displayed option" << endl;

		}
	}
}
int main() {
	Menu();              // main calls menu and starts the program
	return 0;
}





