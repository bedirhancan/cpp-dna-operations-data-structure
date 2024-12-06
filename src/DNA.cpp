#include "DNA.hpp"
#include<iomanip>
#include <sstream>

    ostream& operator<<(ostream& screen,DNA& right){
			if(right.isEmpty()) screen << "Empty Kromozom"<<endl;
			else {
				for(Dugum* itr=right.getHead();itr!=NULL;itr=itr->next){ // dugum yerine Kromozom oluşturmamaız lazım gibi duruyor ya da dugum yapısını inceleleyerek Kromozom ya ulaşmaya çalış
				screen << *(itr->item)<<" ";
				}
			}
			
			return screen;
		};
    Dugum* DNA::FindPrevByPosition(int position) {
        if (position < 0 || position > size) throw "Index out of range";
        int index = 1;
        for (Dugum* itr = head; itr != NULL; itr = itr->next, index++) {
            if (position == index) return itr;	
        }
        return NULL;
    }
    
    // Head döndüren fonksiyonun tanımı
    Dugum* DNA::DNA::getHead() const {
        return head;
    }
	DNA::DNA(){
		head = NULL;
		size =0;
	}
	bool DNA::isEmpty()const{
		return size == 0;
	}
	int DNA::count()const{
		return size;
	}
	Kromozom* DNA::first(){
		if(isEmpty()) throw "Empty List";
		return head->item;
	}
	Kromozom* DNA::last(){
		if(isEmpty()) throw "Empty List";
		return FindPrevByPosition(size)->item;	
	}
	void DNA::add(Kromozom* item){
		insert(size,item);
	}
	void DNA::insert(int index,Kromozom* item){
		if(index==0) head = new Dugum(item,head);
		else{
			Dugum* prev = FindPrevByPosition(index);
			prev->next = new Dugum(item,prev->next);
		}
		size++;			
	}	
	void DNA::remove(Kromozom* item){
		removeAt(indexOf(item));
	}		
	void DNA::removeAt(int index) {
    if (isEmpty()) throw "Empty List";
    Dugum* del; 
    if (index == 0) {
        del = head;
        head = head->next;
    } else {
        Dugum* prev = FindPrevByPosition(index);
        del = prev->next;
        prev->next = del->next;
    }
    delete del->item; // Kromozom'u serbest bırak
    delete del;       // Düğümü serbest bırak
    size--;
}
	
	int DNA::indexOf(Kromozom* item){
		int index=0;
		for(Dugum* itr=head;itr!=NULL;itr=itr->next,index++){
			if(itr->item==item) return index;				
		}
		throw "Index out of range";
	}
	bool DNA::find(Kromozom* item){		
		for(Dugum* itr=head;itr!=NULL;itr=itr->next){
			if(itr->item==item) return true;				
		}
		return false;			
	}
	void DNA::clear() {
    Dugum* current = head;
    while (current != nullptr) {
        Dugum* next = current->next; // Bir sonraki düğümü sakla

        // Kromozom'u temizle
        if (current->item != nullptr) {
            current->item->clear(); // Kromozom sınıfındaki clear metodunu çağır
            delete current->item;   // Kromozom nesnesini serbest bırak
        }

        delete current;             // Düğümün kendisini serbest bırak
        current = next;             // Sıradaki düğüme geç
    }

    head = nullptr; // Listeyi sıfırla
    size = 0;       // Eleman sayısını sıfırla
}


	DNA::~DNA(){
		clear();	
	}			
	
	Kromozom* DNA::elementAt(int index) {
    if (index < 0 || index >= size) throw "Index out of range";
    Dugum* itr = head;
    for (int i = 0; i < index; i++) {
        itr = itr->next;
    }
    return itr->item;
	};
	
	void DNA::mutate(int kromozomIndex, int genIndex, const char& mutasyon) {
    if (kromozomIndex < 0 || kromozomIndex >= count()) {
        throw "Kromozom index out of range";
    }

    Kromozom* targetKromozom = elementAt(kromozomIndex); // İlgili kromozomu al
    if (genIndex < 0 || genIndex >= targetKromozom->Count()) {
        throw "Gen index out of range";
    }

    Gen* targetGen = targetKromozom->getGenAt(genIndex); // İlgili geni al (Kromozom sınıfında `getGenAt` eklemeliyiz)
    targetGen->setItem(mutasyon); // Gen değerini "X" olarak değiştir
}

    bool DNA::isValidIndex(int index, int size) {
    return index >= 0 && index < size;
}

    void DNA::OtomatikIslemler() {
    // Islemler.txt dosyasını açıyoruz
    ifstream file("Islemler.txt");
    if (!file.is_open()) {
        cerr << "Islemler.txt dosyasi acilamadi!" << endl;
        return;
    }

    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        char islem;
        int kromozomIndex1 = -1, kromozomIndex2 = -1, genIndex = -1;

        ss >> islem;  // İşlem türünü alıyoruz

        switch (toupper(islem)) {
            case 'M': { // Mutasyon işlemi
                ss >> kromozomIndex1 >> genIndex;
                if (isValidIndex(kromozomIndex1, count()) && isValidIndex(genIndex, elementAt(kromozomIndex1)->Count())) {
                    cout << "Mutasyon: Kromozom " << kromozomIndex1 << ", Gen " << genIndex << endl;
                    this->mutate(kromozomIndex1, genIndex, 'X');
                } else {
                    cout << "Gecersiz mutasyon indeksleri: " <<"Kromozom "<< kromozomIndex1 << " veya  " <<"Gen "<< genIndex << " yok."<< endl;                }
                break;
            }
            case 'C': { // Çaprazlama işlemi
                ss >> kromozomIndex1 >> kromozomIndex2;
                if (isValidIndex(kromozomIndex1, count()) && isValidIndex(kromozomIndex2, count())) {
                    cout << "Caprazlama: Kromozom " << kromozomIndex1 << ", Kromozom " << kromozomIndex2 << endl;
                    this->caprazlama(kromozomIndex1, kromozomIndex2);
                } else {
                    cout << "Gecersiz caprazlama indeksleri: " <<"Kromozom "<< kromozomIndex1 << " veya  " <<"Kromozom "<< kromozomIndex2 << " yok."<< endl;                }
                break;
            }
            default:
                cout << "Gecersiz islem türü: " << islem << endl;
                break;
        }
    }

    file.close();
}

    void DNA::caprazlama(int index1, int index2) {
    // İndekslerin geçerliliğini kontrol et
    if (index1 < 0 || index1 >= count() || index2 < 0 || index2 >= count()) {
        throw "Kromozom indeksi gecersiz";
    }

    Kromozom* kromozom1 = elementAt(index1);
    Kromozom* kromozom2 = elementAt(index2);

    // Orta noktaları hesapla
    int mid1 = kromozom1->Count() / 2;
    int mid2 = kromozom2->Count() / 2;

    Kromozom *newKromozom1 = new Kromozom();
    Kromozom *newKromozom2 = new Kromozom();
    // Yeni kromozomlar için parçaları hazırla
    newKromozom1 = birlestir(kromozom1, 0, mid1, kromozom2, mid2 + (kromozom2->Count() % 2), kromozom2->Count());
    newKromozom2 = birlestir(kromozom1, mid1 + (kromozom1->Count() % 2), kromozom1->Count(), kromozom2, 0, mid2);

    // Yeni kromozomları listeye ekle
    this->add(newKromozom1);
    this->add(newKromozom2);
}

    Kromozom* DNA::birlestir(Kromozom* source1, int start1, int end1, Kromozom* source2, int start2, int end2) {
    Kromozom* yeni = new Kromozom();

    // İlk kaynaktan eleman ekle
    for (int i = start1; i < end1; i++) {
        yeni->add(source1->elementAt(i));
    }

    // İkinci kaynaktan eleman ekle
    for (int i = start2; i < end2; i++) {
        yeni->add(source2->elementAt(i));
    }

    return yeni;
}


    void DNA::yazdirKucukGenler() {
    if (isEmpty()) {
        cout << "Kromozom listesi bos." << endl;
        return;
    }

    int kromozomIndex = 0;

    for (Dugum* itr = head; itr != nullptr; itr = itr->next, kromozomIndex++) {
        Kromozom* currentKromozom = itr->item;

        if (currentKromozom->isEmpty()) {
            cout << "Kromozom " << kromozomIndex << ": Bos kromozom." << endl;
            continue;
        }

        // İlk gen
        Gen* firstGen = currentKromozom->getGenAt(0);
        if (firstGen == nullptr) {
            cout << "Kromozom " << kromozomIndex << ": Bos kromozom." << endl;
            continue;
        }

        char firstGenAscii = firstGen->item; // İlk genin ASCII değeri
        Gen* selectedGen = firstGen;        // Varsayılan olarak ilk gen seçiliyor

        // Sağdan sola dolaşarak en küçük gen bulma
        for (int i = currentKromozom->Count() - 1; i >= 0; i--) {
            Gen* currentGen = currentKromozom->getGenAt(i); // İlgili geni al
            if (currentGen->item < firstGenAscii) {
                selectedGen = currentGen;
                break; // Daha küçük bir gen bulundu, işlem tamam
            }
        }

        // Seçilen gen ekrana yazdırılır
        cout << selectedGen->item<<" " ;
    }
}
