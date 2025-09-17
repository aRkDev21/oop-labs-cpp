#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

class Animal {
protected:
    int age;
    std::string name;

public:
    
    Animal(const std::string &name, int age) : name(name), age(age) {
        if (age < 0) throw std::invalid_argument("Age cannot be negative.");
        std::cout << "Animal created: " << name << ", Age: " << age << std::endl;
    }

    virtual void makeSound() const {
        std::cout << "Animal sound!" << std::endl;
    }

    void displayInfo() const {
        std::cout << "Name: " << name << ", Age: " << age << std::endl;
    }

    virtual ~Animal() {}
};

class Dog : public Animal {
private:
    std::string breed;

public:
    Dog(const std::string& name, int age, const std::string &breed)
        : Animal(name, age), breed(breed) { }

    void makeSound() const override {
        std::cout << "Bark!" << std::endl;
    }

    void displayInfo() const {
        Animal::displayInfo();
        std::cout << "Breed: " << breed << std::endl;
    }
};

class Cat : public Animal {
private:
    std::string color;

public:
    Cat(const std::string& name, int age, const std::string &color)
        : Animal(name, age), color(color) { }

    void makeSound() const override {
        std::cout << "Meow!" << std::endl;
    }

    void displayInfo() const {
        Animal::displayInfo();
        std::cout << "Color: " << color << std::endl;
    }
};

class Bird : public Animal {
private:
    std::string species;

public:
    Bird(const std::string& name, int age, const std::string &species)
        : Animal(name, age), species(species) { }

    void makeSound() const override {
        std::cout << "Chirp!" << std::endl;
    }

    void displayInfo() const {
        Animal::displayInfo();
        std::cout << "Species: " << species << std::endl;
    }
};

class Zoo {
private:
    std::vector<Animal*> animals;

public:
    ~Zoo() {
        for (Animal* animal : animals) {
            delete animal;
        }
    }

    void addAnimal(Animal* animal) {
        animals.push_back(animal);
    }

    void displayAllAnimals() const {
        for (const Animal* animal : animals) {
            animal->displayInfo();
            std::cout << std::endl;
        }
    }

    void makeAllSounds() const {
        for (const Animal* animal : animals) {
            animal->makeSound();
            std::cout << std::endl;
        }
    }
};

int main () {
    Zoo zoo;

    try {
        zoo.addAnimal(new Dog("Buddy", 3, "Pug"));
        zoo.addAnimal(new Cat("Bebra", 2, "White"));
        zoo.addAnimal(new Bird("Petro", -1, "Sova"));

        zoo.displayAllAnimals();
        zoo.makeAllSounds();

    } catch (const std::invalid_argument &e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    system("pause");

    return 0;
}