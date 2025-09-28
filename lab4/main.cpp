#include <iostream>
#include <string>

class Entity {
protected:
    int entityID;
public:
    virtual ~Entity() {}
};

class Course : public Entity {
private:
    inline static int courseCount = 0; // inline

    std::string* students;
    int capacity;
    int size;
    std::string name;

public:
    Course(const std::string& name, int countStudents = 3) : name(name), capacity(countStudents) {
        students = new std::string[capacity];
        entityID = ++courseCount;
        size = 0;
    }

    void addStudent(const std::string& StudentName) {
        if (size < capacity) {
            students[size++] = StudentName; 
        } else {
            capacity *= 2;
            std::string* newStudents = new std::string[capacity];

            for (int i = 0; i < capacity; i++) 
                newStudents[i] = students[i];
            newStudents[size++] = StudentName;

            delete[] students;
            students = newStudents;
        }
    }

    int getCountOfStudents() { return size; } // or sum(size) for each course
    int getCountOfCourses() { return courseCount; }
    void printInfo() {
        std::cout << "Info about \"" << name << "\"" << std::endl 
                  << "count of students: " << getCountOfStudents() << std::endl; 
    }

    ~Course() {
        delete[] students;
    }
};

int main() {
    Course c1("learn C++");
    Course c2("learn R");
    Course c3("learn Rust");
    
    c1.addStudent("gera");
    c1.addStudent("knowyourlegs");

    
    c1.printInfo();
    c2.printInfo();
    c3.printInfo();
}