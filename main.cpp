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

NewStudent addStudent(bool modifying = false, string originalID = "") {
  Student student;

  cout << "Enter student name: ";
  cin >> student.name;

  if (modifying) {
    student.id = originalID; // Retain the original ID during modification
  } else {
    string id;
    cout << "Enter student ID: ";
    cin >> id;

    while (studentMap.find(id) != studentMap.end()) {
      cout << "Student ID already exists. Please enter a different one: ";
      cin >> id;
    }

    student.id = id;
  }

  cout << "Enter student Quiz Scores: " << endl;
  for (int i = 0; i < QUIZ_AMOUNT; i++) {
    int score;
    cout << "Score " << to_string(i + 1) << ": ";
    cin >> score;
    student.quizScores[i] = score;
  }

  cout << "Enter student Project Scores: " << endl;
  for (int i = 0; i < PROJECT_AMOUNT; i++) {
    int score;
    cout << "Score " << to_string(i + 1) << ": ";
    cin >> score;
    student.projectScores[i] = score;
  }

  int finalScore;
  cout << "Enter student Final Score: " << endl;
  cin >> finalScore;
  student.finalScore = finalScore;

  return NewStudent(student.id, student);
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

    const NewStudent changedStudent = addStudent(true, id);

    studentMap[id] = changedStudent.student;
}

void displayStudent(const Student& student) {
  string qScores;
  for(int i = 0; i < QUIZ_AMOUNT; i++) {
    int score = student.quizScores[i];
    string stringScore = to_string(score);
    if(i == QUIZ_AMOUNT - 1) {
      qScores += stringScore;
    } else {
      qScores += stringScore + ", ";
    };
  }

  string pScores;
  for(int i = 0; i < PROJECT_AMOUNT; i++) {
    int score = student.projectScores[i];
    string stringScore = to_string(score);
    if(i == PROJECT_AMOUNT - 1) {
      pScores += stringScore;
    } else {
      pScores += stringScore + ", ";
    };
  }
  cout << "Name: " << student.name << " | " << "ID: " << student.id << " | " << "Quiz Scores: " << qScores << " | " << "Project Scores: " << pScores << " | " << "Final Score: " << student.finalScore << endl;
}

void viewStudents() {
    if(studentMap.empty()) {
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

string getFinalGrade(Student student) {
  int quizTotal = 0;
  for(const int score: student.quizScores) {
    quizTotal += score;
  }
  const int quizAverage = quizTotal / QUIZ_AMOUNT;

  int projectTotal = 0;
  for(const int score: student.projectScores) {
    projectTotal += score;
  }
  const int projectAverage = projectTotal / PROJECT_AMOUNT;

  const float quizWeight = 0.4;
  const float projectWeight = 0.3;
  const float finalWeight = 0.3;

  const float finalScore = (quizAverage * quizWeight) + (projectAverage * projectWeight) + (student.finalScore * finalWeight);
  const int roundScore = finalScore;

  if(roundScore >= 97 && roundScore < 100) {
    return "A+";
  } else if(roundScore >= 93 && roundScore < 97) {
    return "A";
  } else if(roundScore >= 90 && roundScore < 93) {
    return "A-";
  } else if(roundScore >= 87 && roundScore < 90) {
    return "B+";
  } else if(roundScore >= 83 && roundScore < 87) {
    return "B";
  } else if(roundScore >= 80 && roundScore < 83) {
    return "B-";
  } else if(roundScore >= 77 && roundScore < 80) {
    return "C+";
  } else if(roundScore >= 73 && roundScore < 77) {
    return "C";
  } else if(roundScore >= 70 && roundScore < 73) {
    return "C-";
  } else if(roundScore >= 67 && roundScore < 70) {
    return "D+";
  } else if(roundScore >= 65 && roundScore < 67) {
    return "D";
  } else if(roundScore < 65) {
    return "F";
  }
}

void displayFinalGrades() {
  if(studentMap.empty()) {
    cout << "There are no students." << endl;
    return;
  }
  for(const auto& student : studentMap) {
    const string finalGrade = getFinalGrade(student.second);
    cout << student.second.name << "'s Grade: " << finalGrade << endl;
  }
}

void displayMenu() {
    int choice;
    while (true) {
        cout << "Choose:\n 1. Add Student \n 2. Modify Student \n 3. View Students \n 4. Delete Student \n 5. Show Final Grades \n 6. Exit\n";
        cin >> choice;
        NewStudent newStudent;

        switch (choice) {
            case 1:
                system("cls");
                newStudent = addStudent(false);
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
                displayFinalGrades();
                break;
            case 6:
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
