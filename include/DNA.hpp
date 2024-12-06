#ifndef DNA_HPP
#define DNA_HPP

#include "Dugum.hpp"
#include "Kromozom.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

class DNA {
private:
    Dugum* head;
    int size;                    
    int capacity;

    Dugum* FindPrevByPosition(int position);
public:
    DNA();
    bool isEmpty() const;
    int count() const;
    Kromozom* first();
    Kromozom* last();
    void add(Kromozom* item);
    void insert(int index, Kromozom* item);
    void remove(Kromozom* item);
    void removeAt(int index);
    int indexOf(Kromozom* item);
    bool find(Kromozom* item);
	friend ostream& operator<<(ostream& screen,DNA& right);
    void clear();
    ~DNA();
    Kromozom* elementAt(int index);
    Dugum* getHead() const; // head döndüren fonksiyonun prototipi

    void mutate(int kromozomIndex, int genIndex, const char& mutasyon);
    void OtomatikIslemler() ;   
    bool isValidIndex(int index, int size);
    void caprazlama(int index1, int index2);
    void yazdirKucukGenler();
    
    Kromozom* birlestir(Kromozom* source1, int start1, int end1,Kromozom* source2, int start2, int end2);

};

#endif
