#include <iostream>
#include <chrono>
using namespace std;

struct element {
	int key;
	element *prev, *next;
};

void menu() {
	cout << "Dvojno povezan seznam - izbira: " << endl;
	cout << endl;
	cout << "1) Iskanje podatka" << endl;
	cout << "2) Vnos podatka v glavo" << endl;
	cout << "3) Vnos podatka za elementom" << endl;
	cout << "4) Vnos podatka za repom" << endl;
	cout << "5) Brisanje podatka" << endl;
	cout << "6) Izpisi od glave proti repu" << endl;
	cout << "7) Izpisi od repa proti glavi" << endl;
	cout << "8) Testiraj hitrost" << endl;
	cout << "9) Konec" << endl;
	cout << endl;
	cout << "Izbira: ";
}

element* head;
element* tail;


element* search(int stevilo) {
	element *temp = head;

	while (temp != nullptr && temp->key != stevilo) {
		temp = temp->next;
	}

	return temp;
}


void insertHead(int stevilo) {

	element* new_element = new element;
	new_element->key = stevilo;

	new_element->next = head;			//kazalec *next novega elementa nastavimo da kaže na glavo (tako ga vrinemo pred prvi element)
	new_element->prev = nullptr;		//kazalec *prev novega elementa pa je null

	if (head != nullptr) {				//če že obstaja prvi element ...
		head->prev = new_element;		//... nastavimo da kazalec *prev prvega elementa kaže na nov element
	}
	else {
		tail = new_element;				//... drugače kaže rep na nov element 
	}

	head = new_element;					//glavo nastavimo na prvi element 
}


void vstaviZa(element* elem, element* new_element) {
	new_element->prev = elem;
	new_element->next = elem->next;
	elem->next = new_element;

	if (new_element->next != nullptr) {
		new_element->next->prev = new_element;
	}
	else {
		tail = new_element;
	}
}

void insertAfterX(int x, int stevilo) {
	element* elem = new element;
	elem = search(x);

	element* new_element = new element;
	new_element->key = stevilo;

	vstaviZa(elem, new_element);
}


void insertTail(int stevilo) {
	element* new_element = new element;
	new_element->key = stevilo;

	new_element->prev = tail;
	new_element->next = nullptr;

	tail->next = new_element;
	tail = new_element;

}


void deleteElement(int stevilo) {

	element* temp = search(stevilo);

	if (temp->prev == nullptr && temp->next == nullptr) {		//če je število, ki ga brišemo edini element seznama, zbiršemo glavo in tail (torej ta edini element)
		head = nullptr;							
		tail = nullptr;
	}
	else {
		if (temp->prev != nullptr) {						//če element ni na prvem mestu (head)...
			temp->prev->next = temp->next;					// ... nastavimo, da prejšni element od števila, ki ga brišemo, kaže na naslednjega
		}
		else {
			head = temp->next;								// ... sicer postane naslednji element prvi (head)
			head->prev = nullptr;							// ... in "izbrišemo" število (prvi element seznama)
		}

		if (temp->next != nullptr) {						//če element ni na zadnjem mestu	
			temp->next->prev = temp->prev;					// ... nastavimo, da naslednji element kaže na prejšnega
		}
		else {
			tail = temp->prev;								// ... sicer postane prejšni element zadnji (tail)
			tail->next = nullptr;							// ... in izbrišemo število (zadnji element seznama)
		}
	}

}


void printHeadToTail() {
	element* temp = head;			//začasni kazalec *temp ki se bo premikal od glave proti repu

	while (temp != nullptr) {
		cout << temp->key << " ";
		temp = temp->next;
	}
	cout << endl;
	delete temp;
}


void printTailToHead() {
	element* temp = tail;

	while (temp != nullptr) {
		cout << temp->key << " ";
		temp = temp->prev;
	}
	cout << endl;
	delete temp;
}

void insertNinHead(int N) {
	head = nullptr;		//počistimo seznam
	tail = nullptr;

	auto start = std::chrono::steady_clock::now();

	for (unsigned long i = 1; i < N; i++) {		//v seznam vstavimo N elementov
		insertHead(i);
	}

	auto end = std::chrono::steady_clock::now();
	std::cout << "Skupen cas vstavljanja " << N << " elementov v glavo seznama: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "μs." << std::endl;
}

void vsotaKljucev(int N) {
	element* temp = head;
	long long vsota = 0.0;

	auto start = std::chrono::steady_clock::now();

	while (temp != nullptr) {
		vsota += temp->key;
		temp = temp->next;
	}

	//cout << "Vsota - seznam: " << vsota << endl;

	auto end = std::chrono::steady_clock::now();
	std::cout << "Skupen cas izracuna vsote " << N << " elementov iz seznama: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "μs." << std::endl;

}

void premakniVdesno(int* table, int N){
	for (int i = (N - 1); i >= 0; i--) {
		table[i] = table[i - 1];
	}
}

int* polje(int N) {
	int* table = new int[N];
	for (unsigned int j = 0; j < N; j++) {
		table[j] = NULL;
	}

	auto start = std::chrono::steady_clock::now();

	for (unsigned int i = 1; i < N; i++) {
		premakniVdesno(table, N);
		table[0] = i;				//vstavljamo na prvo mesto v tabeli
	}
	
	auto end = std::chrono::steady_clock::now();
	std::cout << "Skupen cas vstavljanja " << N << " vrednosti na prvo mesto v polje : " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "μs." << std::endl;

	return table;
}

void vsotaKljucevPolje(int* table, int N) {
	long long vsota = 0.0;

	auto start = std::chrono::steady_clock::now();

	for (int i = 0; i < N; i++){
		vsota += table[i];
	}
	
	//cout << "Vsota - polje: " << vsota << endl;

	auto end = std::chrono::steady_clock::now();
	std::cout << "Skupen cas izracuna vsote " << N << " vrednosti iz polja: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "μs." << std::endl;

}

void polje2(int N) {
	int* table2 = new int[N];

	auto start = std::chrono::steady_clock::now();

	for (int i = 0; i < N; i++) {
		table2[i] = i + 1;
	}

	auto end = std::chrono::steady_clock::now();
	std::cout << "Skupen cas vstavljanja " << N << " vrednosti na konec polja: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "μs." << std::endl;

}

void testHitrost(int N) {
	insertNinHead(N);					//napolnimo povezan seznam z N elementi
	vsotaKljucev(N);						//vsota vseh vrednosti v seznamu
	vsotaKljucevPolje(polje(N), N);		//napolnimo polje z N elementi (od zadnjega do prvega) & vsota vseh vrednosti v polju
	polje2(N);							//napolnimo polje z N elementi (od prvega do zadnjega)
}

int main(){
	bool running = true;
	int izbira;

	int stevilo;
	int element;
	int N;

	do {
		cout << endl;
		menu();
		cin >> izbira;
		switch (izbira) {
		case 1:
			cout << "Katero stevilo v seznamu isces: ";
			cin >> stevilo;
			if (search(stevilo)!=nullptr)
				cout << "Element ze obstaja" << endl;
			else
				cout << "Element se ne obstaja" << endl;
			break;
		case 2:
			cout << "Katero stevilo zelite vstaviti v glavo: ";
			cin >> stevilo;
			insertHead(stevilo);
			system("cls");
			break;
		case 3:
			cout << "Vnos podatka za katerim stevilom: ";
			cin >> element;
			while (search(element) == nullptr) {
				cout << "Stevilo ne obstaja. Vnesi novo: ";
				cin >> element;
			}
			cout << endl;
			cout << "Podatek(stevilo), ki ga vnasate: ";
			cin >> stevilo;
			insertAfterX(element, stevilo);
			break;
		case 4:
			cout << "Katero stevilo zelite vstaviti za repom: ";
			cin >> stevilo;
			insertTail(stevilo);
			system("cls");
			break;
		case 5:
			cout << "Podatek za brisanje (brisanje prve pojavitve): ";
			cin >> stevilo;
			while (search(stevilo) == nullptr) {
				cout << "Stevilo ne obstaja. Vnesi novo: ";
				cin >> stevilo;
			}
			deleteElement(stevilo);
			break;
		case 6:
			printHeadToTail();
			break;
		case 7:
			printTailToHead();
			break;
		case 8:
			cout << "Stevilo elementov: ";
			cin >> N;
			testHitrost(N);
			break;
		case 9:
			running = false;
			break;
		default:
			cout << "Narobe izbira!" << endl;
			break;
		}
	} while (running);
	return 0;
}

