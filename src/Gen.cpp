#include "Gen.hpp"
Gen::Gen(const char& item,Gen *next=NULL,Gen *prev=NULL){
	this->item = item;
	this->next = next;
	this->prev = prev;
}
void Gen::setItem(const char& newItem) {
        item = newItem;
    }