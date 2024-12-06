#ifndef KROMOZOM_HPP
#define KROMOZOM_HPP

#include "Gen.hpp"
#include <string>
#include <iostream>

using namespace std;

// Exception sınıfı
class Exception {
private:
    string message;
public:
    Exception(const string& msg) : message(msg) {}
    string Message() const { return message; }
};

// NoSuchElement sınıfı (Exception'dan türetilmiş)
class NoSuchElement : public Exception {
public:
    NoSuchElement(const string& msg) : Exception(msg) {}
};

// Kromozom sınıfı
class Kromozom {
private:
    Gen* head;
    Gen* tail;
    int size;

    Gen* FindPreviousByPosition(int index);

public:
    Kromozom();
    int Count() const;
    bool isEmpty() const;
    void add(const char& item);
    void insert(int index, const char& item);
    Gen* first() throw(NoSuchElement);
    Gen* last() throw(NoSuchElement);
    char const& lastChar() throw(NoSuchElement);
    int indexOf(const char& item) throw(NoSuchElement);
    void remove(const char& item);
    void removeAt(int index);
    bool find(const char& item);
    void reverse();
    const char& elementAt(int index) throw(NoSuchElement);
    void clear();
    friend ostream& operator<<(ostream& screen, Kromozom& rgt);
    ~Kromozom();
    Gen* getGenAt(int index);
};

#endif
