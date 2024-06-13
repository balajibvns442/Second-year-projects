// main.cpp
#include <iostream>
#include <string>
#include <vector>
#include "course.hpp"

using namespace std;

class CourseManager {
private:
    vector<Course*> courses;
    string student ;
    int student_id ;
    double cum_grade ;

public:

    CourseManager(string name , int id ){
        student = name ;
        student_id = id ;
        cum_grade = 0 ;
    }

    ~CourseManager() {
        for (auto course : courses) {
            delete course;
        }
        courses.clear();
    }

    void addCourse(Course* course) {
        courses.push_back(course);
    }

    void removeCourse(const string& code) {
        for (auto it = courses.begin(); it != courses.end();) {
            if ((*it)->getCode() == code) {
                delete *it;
                it = courses.erase(it);
            } else {
                ++it;
            }
        }
    }

    double calculateCGPA() {
        int cred = 0 ;
        double sum = 0 ;

        for (const auto& course : courses) {
            char g = course->calculateGrade() ;
            int grade =  75 - g ;
            sum = sum + ( grade*course->getCredits() );
            cred = cred + course->getCredits();
        }

    cum_grade = sum/cred ;
    return cum_grade ;

    }

    void displayAllCourses() const {
        cout<<"Student name :"<<student<<endl ;
        cout<<"student ID "<<student_id<<endl ;
        cout<<"Student CGPA :"<<cum_grade<<endl ;

        for (const auto& course : courses) {
            course->displayDetails();
            cout << endl;
        }
    }
};

int main() {
    CourseManager manager("Balaji", 29405);

    LectureCourse* lectureCourse = new LectureCourse("CS101", "Introduction to Programming", "Dr. Smith", 3);
    LabCourse* labCourse = new LabCourse("CS101L", "Programming Lab", "Dr. Johnson", 1);
    SeminarCourse* seminarCourse = new SeminarCourse("CS102S", "Software Engineering Seminar", "Dr. Brown", 2);

    manager.addCourse(lectureCourse);
    manager.addCourse(labCourse);
    manager.addCourse(seminarCourse);
    int cumu = manager.calculateCGPA();

    cout << "Before removal:" << endl;
    manager.displayAllCourses();

    manager.removeCourse("CS101");

    cout << "After removal:" << endl;
    manager.displayAllCourses();

    // Cleanup
    manager.removeCourse("CS101L");
    manager.removeCourse("CS102S");

    return 0;
}
