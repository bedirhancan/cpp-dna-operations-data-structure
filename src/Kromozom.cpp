#include "Kromozom.hpp"

Kromozom::Kromozom() {
    head = nullptr;
    tail = nullptr;
    size = 0;
}

int Kromozom::Count() const {
    return size;
}

bool Kromozom::isEmpty() const {
    return size == 0;
}

Gen* Kromozom::FindPreviousByPosition(int index) {
    if (index < 0 || index > size) throw NoSuchElement("No Such Element");
    Gen* prv = head;
    int i = 1;
    for (Gen* itr = head; itr->next != nullptr && i != index; itr = itr->next, i++) {
        prv = prv->next;
    }
    return prv;
}

void Kromozom::add(const char& item) {
    insert(size,item);
}

void Kromozom::insert(int index, const char& item) {
    if (index < 0 || index > size) throw "Index out of Range";

    Gen* newGen = nullptr;
    try {
        newGen = new Gen(item, nullptr, nullptr); // Yeni nesneyi oluştur.
        if (index == 0) {
            newGen->next = head;
            if (head != nullptr) head->prev = newGen;
            head = newGen;
        } else {
            Gen* prv = FindPreviousByPosition(index);
            newGen->next = prv->next;
            newGen->prev = prv;
            if (prv->next != nullptr) prv->next->prev = newGen;
            prv->next = newGen;
        }
        size++;
    } catch (...) {
        delete newGen; // Hata durumunda bellek sızıntısını önle.
        throw;
    }
}


Gen* Kromozom::first() throw(NoSuchElement) {
    if (isEmpty()) throw NoSuchElement("No Such Element");
    return head;
}

Gen* Kromozom::last() throw(NoSuchElement) {
    if (isEmpty()) throw NoSuchElement("No Such Element");
    return tail;
    //return FindPreviousByPosition(size)->item;
}

char const& Kromozom::lastChar() throw(NoSuchElement) {
    if (isEmpty()) throw NoSuchElement("No Such Element");
    return FindPreviousByPosition(size)->item;
}

int Kromozom::indexOf(const char& item) throw(NoSuchElement) {
    int index = 0;
    for (Gen* itr = head; itr != nullptr; itr = itr->next) {
        if (itr->item == item) return index;
        index++;
    }
    throw NoSuchElement("No Such Element");
}

void Kromozom::remove(const char& item) {
    int index = indexOf(item);
    removeAt(index);
}

void Kromozom::removeAt(int index) {
    if (index < 0 || index >= size) throw "Index out of Range";
    Gen* del;
    if (index == 0) {
        del = head;
        head = head->next;
        if (head != nullptr) head->prev = nullptr;
    } else {
        Gen* prv = FindPreviousByPosition(index);
        del = prv->next;
        prv->next = del->next;
        if (del->next != nullptr)
            del->next->prev = prv;
    }
    size--;
    delete del;
}

bool Kromozom::find(const char& item) {
    for (Gen* itr = head; itr != nullptr; itr = itr->next) {
        if (itr->item == item) return true;
    }
    return false;
}

void Kromozom::reverse() {
    for (Gen* itr = head; itr != nullptr;) {
        Gen* tmp = itr->next;
        itr->next = itr->prev;
        itr->prev = tmp;
        if (tmp == nullptr) {
            head = itr;
            break;
        }
        itr = tmp;
    }
}

const char& Kromozom::elementAt(int index) throw(NoSuchElement) {
    if (index < 0 || index >= size) throw NoSuchElement("No Such Element");
    if (index == 0) return head->item;
    return FindPreviousByPosition(index)->next->item;
}

void Kromozom::clear() {
    Gen* current = head;
    while (current != nullptr) {
        Gen* next = current->next; // Bir sonraki gen düğümünü sakla
        delete current;            // Gen düğümünü serbest bırak
        current = next;            // Sıradaki gen düğümüne geç
    }

    head = nullptr; // Listeyi sıfırla
    tail = nullptr; // Kuyruğu sıfırla
    size = 0;       // Eleman sayısını sıfırla
}


ostream& operator<<(ostream& screen, Kromozom& rgt) {
    for (Gen* itr = rgt.head; itr != nullptr; itr = itr->next) {
        screen << itr->item << " ";
    }
    screen << endl;
    return screen;
}


Gen* Kromozom::getGenAt(int index) {
        if (index < 0 || index >= size) {
            throw "Gen index out of range";
        }
        Gen* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current;
    }


Kromozom::~Kromozom() {
    Gen* current = head;
    while (current != nullptr) {
        Gen* toDelete = current;
        current = current->next;
        delete toDelete;
    }
}