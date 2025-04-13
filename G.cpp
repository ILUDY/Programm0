#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

struct Person {
    string name;
    int generation;
    Person* parent;
    vector<Person*> children;

    Person(const string& name_, Person* parent_ = nullptr)
        : name(name_), generation(-1), parent(parent_) {
    }
};

class FamilyTree {
    map<string, Person*> people;

    void calculate_generation(Person* person) {
        if (person == nullptr || person->generation != -1) return;

        if (person->parent == nullptr) {
            person->generation = 0;
        }
        else {
            calculate_generation(person->parent);
            person->generation = person->parent->generation + 1;
        }

        for (Person* child : person->children) {
            calculate_generation(child);
        }
    }

public:
    ~FamilyTree() {
        for (auto& pair : people) {
            delete pair.second;
        }
    }

    void add_relationship(const string& child_name, const string& parent_name) {
        // Добавляем родителя, если его нет
        if (people.find(parent_name) == people.end()) {
            people[parent_name] = new Person(parent_name);
        }

        // Добавляем ребенка
        if (people.find(child_name) == people.end()) {
            people[child_name] = new Person(child_name, people[parent_name]);
        }
        else {
            // Если ребенок уже существует, обновляем его родителя
            people[child_name]->parent = people[parent_name];
        }

        // Добавляем связь родитель-ребенок
        people[parent_name]->children.push_back(people[child_name]);
    }

    void calculate_all_generations() {
        // Находим всех, у кого нет родителя (корни)
        for (auto& pair : people) {
            if (pair.second->parent == nullptr) {
                calculate_generation(pair.second);
            }
        }
    }

    void print_sorted_results() {
        vector<string> names;
        for (auto& pair : people) {
            names.push_back(pair.first);
        }
        sort(names.begin(), names.end());

        for (const string& name : names) {
            cout << name << " " << people[name]->generation << endl;
        }
    }
};

int main() {
    int n;
    cin >> n;

    FamilyTree tree;

    for (int i = 0; i < n - 1; ++i) {
        string child, parent;
        cin >> child >> parent;
        tree.add_relationship(child, parent);
    }

    tree.calculate_all_generations();
    tree.print_sorted_results();

}