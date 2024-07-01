#include "cache.h"

class Student
{
    int id;
    const char *name;
    int age;

public:
    static const std::string class_name; // cada clase tiene un static llamado: class_name
    Student() = default;
    Student(int _id, const char *_name, int _age) : id(_id), name(_name), age(_age) {}
    void print()
    {
        cout << "Student: " << id << " " << name << " " << age << "years old" << endl;
    }

    ~Student() {}

    int getId() { return id; }
    int getAge() { return age; }
    const char *getName() { return name; }

    friend std::ostream &operator<<(std::ostream &os, const Student &student)
    {
        os << student.id << " " << student.name << " " << student.age;
        return os;
    }
};

const string Student::class_name = "StudentClass";

int main()
{
    CacheManager<Student> student_cache(3);
    student_cache.insert("1", Student(1, "Pepito", 22));
    // student_cache.insert("2", Student(2, 23, "María"));

    // student_cache.show_cache();

    cout << "------------------ UPDATE ------------------" << endl;

    // student_cache.insert("2", Student(22, 222, "EZE"));
    // student_cache.show_cache();

    cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;

    // Student return_obj = student_cache.get("0"); // not in cache but in filesystem

    cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;

    // student_cache.insert("2", Student(2, 25, "EZE"));
    // student_cache.show_cache();

    // student_cache.insert("4", Student(4, 29, "student5"));
    // student_cache.insert("5", Student(5, 29, "student6"));
    // student_cache.insert("5", Student(5, 29, "student6"));
    // student_cache.show_cache();

    return 0;
}