#include <iostream>
#include <map>
#include <string>

using namespace std;

const int QUIZ_AMOUNT = 10;
const int PROJECT_AMOUNT = 3;

class Student {
	public:
		string name;
		string id;
		int quizScores[QUIZ_AMOUNT] = {};
		int projectScores[PROJECT_AMOUNT] = {};
		int finalScore;
		char finalGrade;
};

struct NewStudent {
  string studentID;
  Student student;

  NewStudent() : studentID(""), student() {}
  NewStudent(string studentID, Student student) {
    this->studentID = studentID;
    this->student = student;
  }
};

map<string, Student> studentMap;

NewStudent addStudent(bool modifying = false) {
    Student student;

    cout << "Enter student name: ";
    cin >>  student.name;

    string id;
    cout << "Enter student ID: ";
    cin >> id;

    while (studentMap.find(id) != studentMap.end()) {
    	cout << "Student ID already exists. Please enter a different one: ";
      cin >> id;
	  }

    student.id = id;

    cout << "Enter student Quiz Scores: " << endl;
    for(int i = 0; i < QUIZ_AMOUNT; i++) {
      int score;
      cout << "Score " << to_string(i + 1) << ": " ;
      cin >> score;
      student.quizScores[i] = score;
    }

    cout << "Enter student Project Scores: " << endl;
    for(int i = 0; i < PROJECT_AMOUNT; i++) {
      int score;
      cout << "Score " << to_string(i + 1) << ": " ;
      cin >> score;
      student.projectScores[i] = score;
    }

    int finalScore;
    cout << "Enter student Final Score: " << endl;
    cin >> finalScore;
    student.finalScore = finalScore;

    // Must find a way to make sure ID isn't changed during modification.
    NewStudent newbie(id, student);
    return newbie;
}

void modifyStudent() {
    system("cls");
    cout << "Enter ID of student to modify: ";
    string id;
    cin >> id;

    if(studentMap.find(id) == studentMap.end()) {
      cout << "Student with ID " << id << " does not exist." << endl;
      return;
    }

    const NewStudent changedStudent = addStudent();

    studentMap[id] = changedStudent.student;
}

void displayStudent(const Student& student) {
  string qScores;
  for(const int score : student.quizScores) {
    string stringScore = to_string(score);
    qScores += stringScore + ", ";
  }

  string pScores;
  for(const int score : student.projectScores) {
    string stringScore = to_string(score);
    pScores += stringScore + ", ";
  }
  cout << "Name: " << student.name << " | " << "ID: " << student.id << " | " << "Quiz Scores: " << qScores << " | " << "Project Scores: " << pScores << " | " << "Final Score: " << student.finalScore << endl;
}

void viewStudents() {
    if(studentMap.size() == 0) {
      cout << "No students to display." << endl;
      return;
    }
    for(const auto& student : studentMap) {
      displayStudent(student.second);
    }
}

void deleteStudent() {
  system("cls");
  cout << "Enter ID of student to delete: ";
  string id;
  cin >> id;

  if(studentMap.find(id) == studentMap.end()) {
    cout << "Student with ID " << id << " does not exist." << endl;
    return;
  }

  studentMap.erase(id);
}

void displayMenu() {
    int choice;
    while (true) {
        cout << "Choose:\n 1. Add Student \n 2. Modify Student \n 3. View Students \n 4. Delete Student \n 5. Exit\n";
        cin >> choice;
        NewStudent newStudent;

        switch (choice) {
            case 1:
                system("cls");
                newStudent = addStudent();
                studentMap.insert({newStudent.studentID, newStudent.student});
                break;
            case 2:
                modifyStudent();
                break;
            case 3:
                viewStudents();
                break;
            case 4:
                deleteStudent();
                break;
            case 5:
                cout << "Exiting...\n";
                return;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    }
}

int main() {
    displayMenu();
    return 0;
}
