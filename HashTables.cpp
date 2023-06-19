#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

class Person
{
protected:
    string _firstName;
    string _secondName;
    int _id;
public:
    Person(string fn, string sn, int id):_firstName(fn), _secondName(sn), _id(id){}
    Person(){}
    string getFullName() const { return _firstName + " " + _secondName; }
    int getID(){ return _id; }
    // ostale metode po zelji napravite sami
};


int main() {
    Person Kate("Kate,", "Gregory", 123);
    Person Someone("Someone", "Else", 456);
    Person Jason("Jason", "Smith", 145);
    pair<int, Person> mojpar(123, Kate);

    cout << mojpar.first << endl;
    unordered_map<int, Person> people;

    // one way of adding elements to unordered_map
    people.insert(pair<int, Person> (Kate.getID(), Kate));

    // or using square brackets
    people[Someone.getID()] = Someone;
    people[Jason.getID()] = Jason;

    // we can easily access elements, given that we know its keys
    cout << endl << people[123].getFullName() << endl;
    cout << people.find(123)->second.getFullName() << endl << endl;

    // we can iterate over unordered_map pairs, same as we did for map (both are just STL containers)
    for (auto i=people.begin(); i != people.end(); i++)
    {
        cout << i->first << "  " << i->second.getFullName() << endl;
    }
    cout << endl;

    // or using modern C++, we can iterate even easier
    for (const auto &p : people)
        cout << p.first << "  " << p.second.getFullName() << endl;

    // note that this time output was not ordered by key values ;-)


    return 0;
}