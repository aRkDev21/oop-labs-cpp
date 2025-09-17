#include <iostream>
#include <string>
#include <vector>

class IEmployee {
public:
    virtual void work() const = 0;
    virtual double calculateSalary() const = 0;
    virtual void displayInfo() const = 0;
    virtual ~IEmployee() { }
};

class FullTimeEmployee : public IEmployee {
private:
    std::string name;
    double salary;
    double benefits;

public:
    FullTimeEmployee(const std::string& name, double salary, double benefits)
        : name(name), salary(salary), benefits(benefits) { }

    void work() const override {
        std::cout << name << " works all day." << std::endl;
    }

    double calculateSalary() const override {
        return salary + benefits;
    }

    void displayInfo() const override {
        std::cout << "Full-time employee " << name << std::endl
                  << "salary per month: " << calculateSalary() << std::endl;
    }

};

class PartTimeEmployee : public IEmployee {
private:
    std::string name;
    double hourlyRate;
    int hoursWorked;

public:
    PartTimeEmployee(const std::string& name, double hourlyRate, int hoursWorked)
        : name(name), hourlyRate(hourlyRate), hoursWorked(hoursWorked) { }

    void work() const override {
        std::cout << name << " works " << hoursWorked << " hours" << std::endl;
    }

    double calculateSalary() const override {
        return hourlyRate * hoursWorked;
    }

    void displayInfo() const override {
        std::cout << "Part-time employee " << name << std::endl
                  << "salary per month: " << calculateSalary() << std::endl;
    }
};

int main() {
    IEmployee* emp1 = new FullTimeEmployee("Petya", 2000, 500);
    IEmployee* emp2 = new PartTimeEmployee("Alexey", 15, 80);

    emp1->work();
    emp1->displayInfo();

    std::cout << std::endl;

    emp2->work();
    emp2->displayInfo();

    delete emp1;
    delete emp2;

    return 0;
}