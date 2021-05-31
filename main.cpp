#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Person {
  string name;
  int salary;

  Person(string name, int salary) {
    this->name = name;
    this->salary = salary;
  }

  friend ostream &operator<<(ostream &output, const Person &p) {
    output << "name: " << p.name << endl << "salary: " << p.salary << endl;
    return output;
  }
};

void printPersons(vector<Person> p) {
  for (int i = 0; i < p.size(); i++) {
    cout << p[i];
  }
}

void printSalaries(vector<int> s) {
  for (int i = 0; i < s.size(); i++) {
    cout << s[i] << endl;
  }
}

int main() {
  cout << "\n##### Data:\n";
  vector<Person> persons;
  persons.push_back(Person("Bob", 5000000));
  persons.push_back(Person("Bill", 1000000));
  persons.push_back(Person("Joe", 2000000));
  persons.push_back(Person("Cathy", 3000000));
  printPersons(persons);

  cout << "\n##### Iterative get salaries >3M" << endl;
  vector<int> high_salaries;
  auto start = std::chrono::steady_clock::now();
  for (int i = 0; i < persons.size(); i++) {
    if (persons[i].salary >= 3000000) {
      high_salaries.push_back(persons[i].salary);
    }
  }
  auto end = std::chrono::steady_clock::now();
  std::chrono::duration<double> elapsed_seconds = end - start;

  cout << "result:\n";
  printSalaries(high_salaries);
  std::cout << "elapsed time:\n" << elapsed_seconds.count() << "s\n\n";

  cout << "##### Functional get salaries >3M" << endl;
  vector<int> high_salaries2;
  auto start2 = std::chrono::steady_clock::now();
  transform(persons.begin(), persons.end(), back_inserter(high_salaries2),
            [](Person p) { return p.salary; });
  high_salaries2.erase(remove_if(high_salaries2.begin(), high_salaries2.end(),
                                 [](int s) { return s < 3000000; }),
                       high_salaries2.end());
  auto end2 = std::chrono::steady_clock::now();
  std::chrono::duration<double> elapsed_seconds2 = end2 - start2;

  cout << "result:\n";
  printSalaries(high_salaries2);
  std::cout << "elapsed time:\n" << elapsed_seconds2.count() << "s\n\n";
}
