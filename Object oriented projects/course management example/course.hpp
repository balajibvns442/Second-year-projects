#include<iostream>
#include<string>
#include<vector>

using namespace std ;

class Course{
    protected:
        string code ;
        string title ;
        string instructor ;
        int credits;

    public:
        Course(const string& code, const string& title, const string& instructor, int credits) ;
        virtual void displayDetails() const ;
        virtual char calculateGrade() const = 0 ;
        const string& getCode() const ; 
        int getCredits() const ;
};

class LectureCourse : public Course {
    public:
        LectureCourse(const string& code, const string& title, const string& instructor, int credits) ;
        void displayDetails() const override ;
        char calculateGrade() const override ;
};

class LabCourse : public Course {
    public:
        LabCourse(const string& code, const string& title, const string& instructor, int credits) ;
        void displayDetails() const override ;
        char calculateGrade() const override ;
};

class SeminarCourse : public Course {
    public:
        SeminarCourse(const string& code, const string& title, const string& instructor, int credits) ;
        void displayDetails() const override ;
        char calculateGrade() const override ;
};