#include "cache.h"

class Student
{
    int id;
    int value;
    const char *data;

public:
    static const std::string class_name; // cada clase tiene un static llamado: class_name
    Student(int _id, int _value, const char *_data) : id(_id), value(_value), data(_data) {}
    void print()
    {
        cout << "Student Object: " << id << " " << value << " " << data << endl;
    }
    ~Student() {}

    int getId() { return id; }
    int getValue() { return value; }
    const char *getData() { return data; }
};

const string Student::class_name = "StudentClass";

int main()
{
    CacheManager<Student> student_cache(3);
    student_cache.insert("0", Student(0, 22, "student1"));
    student_cache.insert("1", Student(1, 23, "student2"));
    student_cache.insert("2", Student(2, 25, "student3"));
    student_cache.insert("3", Student(3, 29, "student4"));

    student_cache.show_cache();

    cout << "------------------ UPDATE ------------------" << endl;

    student_cache.insert("2", Student(22, 222, "EZE"));
    student_cache.show_cache();

    cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;

    Student return_obj = student_cache.get("0"); // not in cache but in filesystem

    cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;

    student_cache.insert("2", Student(2, 25, "EZE"));
    student_cache.show_cache();

    student_cache.insert("4", Student(4, 29, "student5"));
    student_cache.insert("5", Student(5, 29, "student6"));
    student_cache.insert("5", Student(5, 29, "student6"));
    student_cache.show_cache();

    return 0;
}