#include<iostream>
#include<string>
#include "course.hpp"

using namespace std ;

Course :: Course(const string& code, const string& title, const string& instructor, int credits)
    : code(code), title(title), instructor(instructor), credits(credits) {} ;

void Course::displayDetails() const {
    cout << "Code: " << code << endl;
    cout << "Title: " << title << endl;
    cout << "Instructor: " << instructor << endl;
    cout << "Credits: " << credits << endl;
}

const string& Course::getCode() const {
    return code ;
}

int Course::getCredits() const {
    return credits ;
}

LectureCourse::LectureCourse(const string& code, const string& title, const string& instructor, int credits)
            : Course(code, title, instructor, credits) {}

void LectureCourse::displayDetails() const {
    cout << "Lecture Course" << endl;
    Course::displayDetails();
}

char LectureCourse::calculateGrade() const {
    cout<<"for the course : "<<this->title;
    cout<<"Enter the percentage of attendance"<<endl ;
    int att ;
    cin>>att ;
    cout<<"Enter the percentage of mid-sem exams"<<endl ;
    int mid ;
    cin>>mid ;
    cout<<"Enter the percentage of end-sem exams "<<endl ;
    int end ;
    cin>>mid ;

    int score = att*25 + mid*25 + end*50 ;
    score = score/100 ;

    int grade = score/10 ;
    char Grade = 65 + (10-score);

    return Grade ;

}

LabCourse::LabCourse(const string& code, const string& title, const string& instructor, int credits)
    : Course(code, title, instructor, credits) {}

void LabCourse::displayDetails() const {
    cout << "Lab Course" << endl;
    Course::displayDetails();
}

char LabCourse::calculateGrade() const {
    cout<<"for the course : "<<this->title;
    cout<<"Enter the percentage of attendance"<<endl ;
    int att ;
    cin>>att ;
    cout<<"Enter the percentage of mid-sem exams"<<endl ;
    int mid ;
    cin>>mid ;
    cout<<"Enter the percentage of end-sem exams "<<endl ;
    int end ;
    cin>>mid ;

    int score = att*35 + mid*20 + end*45 ;
    score = score/100 ;

    int grade = score/10 ;
    char Grade = 65 + (10-score);

    return Grade ;
}

SeminarCourse::SeminarCourse(const string& code, const string& title, const string& instructor, int credits)
    : Course(code, title, instructor, credits) {}

void SeminarCourse::displayDetails() const {
    cout << "Seminar Course" << endl;
    Course::displayDetails();
}

char SeminarCourse::calculateGrade() const {
    cout<<"for the course"<<this->title;
    cout<<"Enter the percentage of attendance"<<endl ;
    int att ;
    cin>>att ;
    cout<<"Enter the percentage of mid-sem exams"<<endl ;
    int mid ;
    cin>>mid ;
    cout<<"Enter the percentage of end-sem exams "<<endl ;
    int end ;
    cin>>mid ;

    int score = att*15 + mid*30 + end*55 ;
    score = score/100 ;

    int grade = score/10 ;
    char Grade = 65 + (10-score);

    return Grade ;
}

