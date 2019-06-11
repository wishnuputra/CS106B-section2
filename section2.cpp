#include <iostream>
#include <cmath>
#include <cctype>
#include <sstream>
#include <fstream>
#include "console.h"
#include "hashset.h"
#include "set.h"
#include "vector.h"
#include "map.h"
#include "simpio.h"
#include "filelib.h"
using namespace std;

void twiceTest();
Set<int> twice(Vector<int> &v);
Set<int> twiceBonuse(Vector<int> &v);
Vector<int> twice2(Vector<int> &v);

void unionSetsTest();
Set<int> unionSets(Set<Set<int>> &sets);

void rarestTest();
string rarest(Map<string, string> &map);

void friendListTest();
Map<string, Vector<string>> friendList(string &filename);

void reverseMapTest();
Map<string, int> reverseMap(Map<int, string> &m);

void sumOfSquaresTest();
int sumOfSquares(int n);

void reverseStringTest();
string reverseString(string s);

void starStringTest();
string starString(int n);


int main() {
    twiceTest();
    unionSetsTest();
    rarestTest();
    friendListTest();
    reverseMapTest();
    sumOfSquaresTest();
    reverseStringTest();
    starStringTest();
    return 0;
}

void twiceTest() {
    Vector<int> v {1, 3, 1, 4, 3, 7, -2, 0, 7, -2, -2, 1};
    cout << "TwiceMap: " <<twice(v) << endl;;
    cout << "TwiceVector: " << twice2(v) << endl;
    cout << "TwiceBonus: " << twiceBonuse(v) << endl;
}

Set<int> twice(Vector<int> &v) {
    Map<int, int> count;
    for (int i : v) {
        count[i]++;
    }

    Set<int> set;
    for (int i : count) {
        if (count[i] == 2)
            set += i;
    }
    return set;
}

Set<int> twiceBonuse(Vector<int> &v) {
    Set<int> once;
    Set<int> twice;
    Set<int> more;
    for (int i : v) {
        if (once.contains(i)) {
            once.remove(i);
            twice.add(i);
        } else if (twice.contains(i)) {
            twice.remove(i);
            more.add(i);
        } else if (!more.contains(i)) {
            once.add(i);
        }
    }
    return twice;
}

Vector<int> twice2(Vector<int> &v) {
    v.sort();
    Vector<int> result;
    int counter = 1;
    int index = -1;
    for (int i = 0; i < v.size() - 1; i++) {
        if (v[i] == v[i + 1]) {
            counter++;
            if (!result.contains(v[i])) {
                result.add(v[i]);
                index++;
            }
        }
        if (v[i] != v[i + 1]) {
            counter = 1;
        }
        if (counter > 2) {
            result.remove(result.indexOf(v[i]));
        }
    }
    return result;
}

void unionSetsTest() {
    Set<int> one, two, three;
    one += 1, 3;
    two += 2, 3, 4, 5;
    three += 3, 5, 6, 7;

    Set<Set<int>> sets {one, two, three};
    cout << "unionSets(sets): " << unionSets(sets) << endl;
}

Set<int> unionSets(Set<Set<int>> &sets) {
    Set<int> result;
    for (Set<int> i : sets) {
        result += i;
    }
    return result;
}

void rarestTest() {
    Map<string, string> map;
    map.put("Alyssa", "Harding");
    map.put("Char", "Smith");
    map.put("Dan", "Smith");
    map.put("Jeff", "Jones");
    map.put("Kasey", "Jones");
    map.put("Kim", "Smith");
    map.put("Morgan", "Jones");
    map.put("Ryan", "Smith");
    map.put("Stef", "Harding");

    cout << "rarest(map): " << rarest(map) << endl;
}

string rarest(Map<string, string> &map) {
    Map<string, int> count;
    for (string name : map) {
        string lastName = map[name];
        count[lastName]++;
    }

    string result = "";
    for (string lastName : count) {
        if (result == "" || count.get(lastName) < count.get(result)) {
            result = lastName;
        }
    }
    return result;
}

void friendListTest() {
    string filename = "friends.txt";
    cout << "friendlist: " << friendList(filename) << endl;
}

Map<string, Vector<string>> friendList(string &filename) {
    ifstream input;
    input.open(filename);
    Map<string, Vector<string>> friends;
    string s1, s2;
    while (input >> s1 >> s2) {
        friends[s1] += s2;
        friends[s2] += s1;
    }

    return friends;
}

void reverseMapTest() {
    Map<int, string> map;
    map[1] = "a";
    map[2] = "b";
    map[3] = "c";
    cout << "reverseMap: " << reverseMap(map) << endl;;

}

Map<string, int> reverseMap(Map<int, string> &m) {
    Map<string, int> reverse;
    for (int i : m) {
        reverse[m[i]] = i;
    }
    return reverse;
}

void sumOfSquaresTest() {
    int n = 3;
    cout << "sumOfSquares(" << n << "): " << sumOfSquares(n) << endl;
}

int sumOfSquares(int n) {
    if (n == 1) {
        return 1;
    } else {
        return (n * n) + sumOfSquares(n - 1);
    }
}

void reverseStringTest() {
    string s = "Hi, you!";
    cout << "reverseString(\"" << s << "\"): " << reverseString(s) << endl;
}

string reverseString(string s) {
    string result;
    int sLength = s.length();
    if (sLength <= 1) {
        return s;
    } else {
        char first = s[0];
        char last = s[sLength - 1];
        string middle = s.substr(1, sLength - 2);
        result = last + reverseString(middle) + first;
    }
    return result;
}

void starStringTest() {
    int n = 4;
    cout << "startString(" << n << "): " << starString(n) << endl;
}
string starString(int n) {
    if (n == 0) {
        return "*";
    } else {
        return starString(n - 1) + starString(n - 1);
    }
}
