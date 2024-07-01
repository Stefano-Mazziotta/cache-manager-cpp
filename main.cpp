#include "cache.h"

class Student
{
    int id;
    string name;
    int age;

public:
    static const std::string class_name; // cada clase tiene un static llamado: class_name
    Student() = default;
    Student(int _id, string _name, int _age) : id(_id), name(_name), age(_age) {}
    void print()
    {
        cout << "Student: " << id << " " << name << " " << age << " years old" << endl;
    }

    ~Student() {}

    int getId() { return id; }
    int getAge() { return age; }
    string getName() { return name; }

    friend std::ostream &operator<<(std::ostream &os, const Student &student)
    {
        os << student.id << " " << student.name << " " << student.age;
        return os;
    }

    friend std::istream &operator>>(std::istream &is, Student &student)
    {
        // Assuming id is an int, name is a string that doesn't contain spaces, and age is an int
        std::string name;
        is >> student.id >> student.name >> student.age;
        return is;
    }
};

const string Student::class_name = "StudentClass";

int main()
{
    CacheManager<Student> student_cache(3);
    student_cache.insert("1", Student(1, "Pepe", 22));
    student_cache.insert("2", Student(2, "María", 25));
    student_cache.insert("3", Student(3, "Stefanito", 23));
    student_cache.insert("4", Student(4, "Gorka", 36));

    student_cache.show_cache();

    cout << "------------------ UPDATE ------------------" << endl;

    student_cache.insert("3", Student(3, "Stefano", 23));
    student_cache.show_cache();

    cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;

    Student return_obj = student_cache.get("1"); // not in cache but in filesystem
    return_obj.print();

    cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;

    student_cache.insert("2", Student(2, "Ana María", 25));
    student_cache.show_cache();

    cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;

    student_cache.insert("4", Student(4, "Gorka", 37));
    student_cache.insert("5", Student(5, "Gino Mazziotta", 29));
    student_cache.insert("6", Student(6, "Giuliano Mazziotta", 32));
    student_cache.show_cache();

    return 0;
}