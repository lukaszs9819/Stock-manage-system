#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
#include <iterator>
using namespace std;



class Article{
private:
    string m_name;
    int m_amount{};
    float m_price{};
    double m_barcode{};
public:
    Article(const string& name, int amount, float price, double barcode): m_name{name},m_amount{amount},m_barcode{barcode},m_price{price}
    {}
    Article()= default;
    string get_name(){return m_name;}
    int get_amount() const{return m_amount;}
    float get_price() const{return m_price;}
    double get_barcode() const{return m_barcode;}
    void set_name(string name){m_name=name;}
    void set_amount(int amount){m_amount=amount;}
    void set_price(float price){m_price=price;}
    void set_barcode(double barcode){m_barcode=barcode;}

    void supply(int amount_supply){m_amount+=amount_supply;}
    void sell(int amount_sold){
        m_amount-=amount_sold;
        cout << "Cena towaru: "<< m_price*amount_sold << endl;
    }
};

Article modify(Article product){
    cout << "Wybrany produkt \nNazwa: "<< product.get_name() <<"\nIlosc: " << product.get_amount() <<
         "\nCena: "<< product.get_price() << "\nKod kreskowy: "<< product.get_barcode()<<endl;
    bool modeOn=true;
    while(modeOn){
        cin.clear();
        cout << "Wybierz ktora czesc chcesz zmienic:\nNazwe(n)\nIlosc(i)\nCene(c)\nKod kreskowy(k)\nWszystkie zmienne(w)\nPorzuc modyfikowanie(x)"<<endl;
        char menu;
        cin >> menu;
        switch (menu) {
            case 'n':{
                cout << "Podaj nowa nazwe: ";
                string name;
                cin >> name;
                product.set_name(name);
                break;
            }case 'i':{
                cout << "Podaj nowa ilosc: ";
                int amount;
                cin >> amount;
                product.set_amount(amount);
                break;
            }case 'c':{
                cout << "Podaj nowa cene: ";
                float price;
                cin >> price;
                product.set_price(price);
                break;
            }case 'k':{
                cout << "Podaj nowy kod kreskowy: ";
                double code;
                cin >> code;
                product.set_barcode(code);
                break;
            }case 'w':{
                cout << "Podaj nową nazwe: ";
                string name;
                cin >> name;
                product.set_name(name);
                cout << "Podaj nową ilość: ";
                int amount;
                cin >> amount;
                product.set_amount(amount);
                cout << "Podaj nową cenę: ";
                float price;
                cin >> price;
                product.set_price(price);
                cout << "Podaj nowy kod kreskowy: ";
                double code;
                cin >> code;
                product.set_barcode(code);
                break;
            }case 'x':{
                modeOn=false;
                break;
            }
            default:
                cout << "Podano bledna zmienna, sprobuj ponownie"<<endl;
        }

    }
    return product;
}

int main() {
    const string file = "C:\\Users\\Lukasz\\CLionProjects\\Stock Manage System\\base.txt";
    vector<Article> products;
    fstream base (file);
    try {

        if (!base.is_open()) throw "Nie udalo sie otworzyc pliku z baza danych";
        else{
            while (!base.eof()) {
                string name;
                int amount;
                float price;
                double barcode;
                base >> name;
                base >> amount;
                base >> price;
                base >> barcode;
                products.push_back(Article(name, amount, price, barcode));
            }
        }//tworzenie wektora z wszystkimi artykułami
    }
    catch (const char *ex) // przechwyć wyjątek typu const char*
    {
        cerr << ex << endl;
        return -1;
    }
    base.close();
    string pom;
    char iter;
    bool firstMenu = true, secondMenu;
    while (firstMenu){ //Nieskończona pętla aby program działał aż do wybrania opcji wyjścia
        cin.clear();
        cout << "Wybierz funkcje poprzez wpisanie do terminala odpowiedniej frazy, po frazie nacisnij enter"
        << "\nDostawa towarow(d)"
        << "\nSprzedaz towarow(s)\nModyfikacja towarow(m)\n"
        << "Wyswietlanie listy towarow(l)\nWyswietlanie towarow brakujacych i konczacych sie(b)\n"
        << "Wyjdz z programu(x)\n" << endl; //menu główne
        cin >> pom;
        secondMenu=true;

        if(pom.length()!=1)
            iter='0';
        else
            iter=pom[0]; //sprawdzenie czy wpisano literę czy stringa oraz przypisanie tego do naszego wyboru

        switch (iter) {
            case 'd': {
                while(secondMenu) {
                    cin.clear();
                    cout << "Wybierz opcje: \nDostawa towaru(dt)\nDodanie nowego towaru(dnt)\nWroc do poprzedniego menu(x)" << endl;
                    string type;
                    cin >> type;
                    if (type == "dt"){
                        double barcode;
                        int amount;
                        cout << "Wpisz kod kreskowy dostarczonego towaru (10 cyfr)" << endl;
                        cin >> barcode;
                        cout << "Wpisz ilosc dostarczona (liczba calkowita)" << endl;
                        cin >> amount;
                        for(auto & product : products){
                            if(product.get_barcode()==barcode){
                                if(amount>0)
                                product.supply(amount);
                                else
                                    cout << "Nie mozna dostarczyc ujemnej liczby towarow" << endl;
                                break;
                            }
                        }
                    }
                    else if (type== "dnt"){
                        string name;
                        int amount;
                        float price;
                        double barcode;
                        bool checkBase=true;
                        cout << "Wpisz nazwe dodawanego towaru (ciąg znaków alfanumerycznych)" << endl;
                        cin >> name;
                        cout << "Wpisz ilosc dodawanego towaru (liczba calkowita)" << endl;
                        cin >> amount;
                        cout << "Wpisz cene dodawanego towaru (liczba zmiennoprzecinkowa)" << endl;
                        cin >> price;
                        cout << "Wpisz kod kreskowy dodawanego towaru (10 cyfr)" << endl;
                        cin >> barcode;
                        for(auto product:products) {
                            if (product.get_name() == name) {
                                cout << "Produkt o podanej nazwie jest juz w bazie";
                                checkBase = false;
                            }
                            else if (product.get_barcode() == barcode) {
                                cout << "Produkt o podanym kodzie kreskowym jest juz w bazie";
                                checkBase = false;
                            }
                        }
                        if(amount<0){
                            cout << "Nie mozna dodac towaru z ujemna iloscia" << endl;
                            checkBase = false;
                        }
                        if(checkBase)
                        products.push_back(Article(name,amount,price,barcode));
                    }
                    else if (type== "x")
                        secondMenu=false;
                    else
                        cout << "Wpisano bledna informacje, sprobuj ponownie" << endl;
                    }
                break;
            }
            case 's': {
                double barcode;
                int amount;
                bool barcodeExist=true;
                cin.clear();
                while (barcodeExist) {
                    cout << "Wpisz barcode sprzedanego towaru (10 cyfr)" << endl;
                    cin >> barcode;
                    bool checkAmount = false;
                    while (!checkAmount) {
                        cout << "Wpisz sprzedana ilosc (liczba calkowita)" << endl;
                        cin >> amount;
                        for (auto &product : products) {
                            if (product.get_barcode() == barcode) {
                                barcodeExist= false;
                                if (product.get_amount() > amount) {
                                    if(amount>0) {
                                        checkAmount = true;
                                        product.sell(amount);
                                    }
                                    else
                                        cout << "Nie da sie sprzedac ujemnej ilosci\nPodaj na nowo ile chcesz sprzedac" << endl;
                                } else
                                    cout << "Nie ma tyle towaru w magazynie, stan magazynu:" << product.get_amount()
                                         << "\nPodaj na nowo ile chcesz sprzedac" << endl;
                                break;
                            }
                        }
                        if(barcodeExist)
                            cout << "Nie ma takiego kodu kreskowego w bazie, spróbuj ponownie" << endl;
                    }
                }
                break;
            }
            case 'm':{
                bool searching=true;
                while(searching){
                    cin.clear();
                cout << "Wybierz za pomoca czego chcesz wyszukac towar do modyfikacji" << endl << "Za pomoca kodu kreskowego (kod) lub za pomoca nazwy(nazwa)"<< endl;
                string searchBy;
                cin >> searchBy;
                if(searchBy=="kod"){
                    bool barcodeExist=false;
                    while (!barcodeExist) {
                        cout << "Podaj kod towaru ktory chcesz modyfikowac (10 cyfr)"<<endl;
                        double barcode;
                        cin >> barcode;
                        for (auto &product : products) {
                            if (product.get_barcode() == barcode) {
                                barcodeExist= true;
                                product=modify(product);
                                break;
                            }
                        }
                        if(!barcodeExist)
                            cout << "Podano bledny kod kreskowy" << endl;
                    }
                    searching=false;
                }
                else if(searchBy=="nazwa") {
                    bool nameExist = false;
                    while (!nameExist) {
                        cin.clear();
                        cout << "Podaj nazwe towaru ktory chcesz modyfikowac (ciag alfanumeryczny)"<<endl;
                        string name;
                        cin >> name;
                        for (auto &product : products) {
                            if (product.get_name() == name) {
                                nameExist= true;
                                product=modify(product);
                                break;
                            }
                        }
                        if(!nameExist)
                            cout << "Podano bledna nazwe" << endl;
                        searching = false;
                    }
                }
                else
                    cout << "Wpisano bledna opcje, sprobuj ponownie" <<endl;
                }
                break;
            }
            case 'l':{
                bool searchMenu=true;
                while(searchMenu) {
                    cin.clear();
                    cout<< "Wybierz opcje wyszukiwania:\nNieposotrowana lista(l)\nLista posortowana po nazwie(n)\nLista posortowana po ilosci(i)\nLista posortowana po cenie(c)\nPowrot do poprzedniego menu(x)"<< endl;
                    char sortLetter;
                    cin >> sortLetter;

                    switch (sortLetter) {
                        case 'l': {
                            cout << "\nNieposortowana lista towarow: \nnazwa/ilosc/cena/kod kreskowy" << endl;
                            for (auto product:products)
                                cout << product.get_name() << " " << product.get_amount() << " " << product.get_price()
                                     << " " << product.get_barcode() << endl;
                            cout << endl;
                            break;
                        }
                        case 'n': {
                        map<string, Article> sortingList;
                        string sortedTab[products.size()];
                        for(int i=0;i<products.size();i++) {
                            sortedTab[i] = products[i].get_name();
                            sortingList[products[i].get_name()]=products[i];
                        }
                        int sizeOfArray = sizeof(sortedTab) / sizeof(sortedTab[0]);
                        sort(sortedTab, sortedTab + sizeOfArray);
                        vector<Article> temp;
                        for(auto item:sortedTab)
                            temp.push_back(sortingList[item]);
                        cout << "\nLista posortowana po nazwie: \nnazwa/ilosc/cena/kod kreskowy" << endl;
                        for(auto item:sortedTab)
                            cout << sortingList[item].get_name() << " " << sortingList[item].get_amount() << " " << sortingList[item].get_price() << " " << sortingList[item].get_barcode() << endl;
                        cout << endl;
                           /*string sortedTab[products.size()];
                            for (int i = 0; i < products.size(); i++)
                                sortedTab[i] = products[i].get_name();
                            int sizeOfArray = sizeof(sortedTab) / sizeof(sortedTab[0]);
                            sort(sortedTab, sortedTab + sizeOfArray);
                            vector<Article> temp;
                            for (auto sortedName:sortedTab)
                                for (auto product :products)
                                    if (sortedName == product.get_name()) {
                                        temp.push_back(product);
                                        break;
                                    }
                            cout << "\nLista posortowana po nazwie: " << endl;
                            for (auto product:temp)
                                cout << product.get_name() << " " << product.get_amount() << " " << product.get_price()
                                     << " " << product.get_barcode() << endl << endl;*/
                            break;
                        }
                        case 'i': {/*
                            int sortedTab[products.size()];
                            for (int i = 0; i < products.size(); i++)
                                sortedTab[i] = products[i].get_amount();
                            int sizeOfArray = sizeof(sortedTab) / sizeof(sortedTab[0]);
                            sort(sortedTab, sortedTab + sizeOfArray);
                            vector<Article> temp;
                            for (auto sortedName:sortedTab)
                                for (auto product :products)
                                    if (sortedName == product.get_amount()) {
                                        temp.push_back(product);
                                        break;
                                    }
                            cout << "\nLista posortowana po ilosci: " << endl;
                            for (auto product:temp)
                                cout << product.get_name() << " " << product.get_amount() << " " << product.get_price()
                                     << " " << product.get_barcode() << endl << endl;
*/
                            int sortedTab[products.size()];
                            for (int i = 0; i < products.size(); i++)
                                sortedTab[i] = products[i].get_amount();
                            int sizeOfArray = sizeof(sortedTab) / sizeof(sortedTab[0]);
                            sort(sortedTab, sortedTab + sizeOfArray);
                            vector<Article> temp;
                            vector<Article>::iterator iteration;
                            for(auto tab:sortedTab)
                                for(iteration=products.begin();iteration!=products.end();iteration++)
                                    if(tab==iteration->get_amount()){
                                        temp.push_back(*iteration);
                                        products.erase(iteration);
                                        break;
                                    }
                            cout << "\nLista posortowana po ilosci\nnazwa/ilosc/cena/kod kreskowy"<<endl;
                            for (auto product:temp)
                                cout << product.get_name() << " " << product.get_amount() << " " << product.get_price()
                                     << " " << product.get_barcode() << endl;
                            cout << endl;
                            products=temp;
                            break;
                        }
                        case 'c': {float sortedTab[products.size()];
                            for (int i = 0; i < products.size(); i++)
                                sortedTab[i] = products[i].get_price();
                            int sizeOfArray = sizeof(sortedTab) / sizeof(sortedTab[0]);
                            sort(sortedTab, sortedTab + sizeOfArray);
                            vector<Article> temp;
                            vector<Article>::iterator iteration;
                            for(auto tab:sortedTab)
                                for(iteration=products.begin();iteration!=products.end();iteration++)
                                    if(tab==iteration->get_price()){
                                        temp.push_back(*iteration);
                                        products.erase(iteration);
                                        break;
                                    }
                            cout << "\nLista posortowana po cenie\nnazwa/ilosc/cena/kod kreskowy"<<endl;
                            for (auto product:temp)
                                cout << product.get_name() << " " << product.get_amount() << " " << product.get_price()
                                     << " " << product.get_barcode() << endl;
                            cout << endl;
                            products=temp;
                            break;
                        }
                        case 'x': {
                            searchMenu =false;
                            break;
                        }
                        default: {
                            cout << "Wpisano bledna informacje, sprobuj ponownie" << endl;
                            break;
                        }

                    }
                }
                break;

            }
            case 'b':{
                cout << "\nLista brakujacych towarow lub towarow ktorych ilosc jest mniejsza niz 10:\nnazwa/ilosc/cena/kod kreskowy"<< endl;
                for(auto product:products)
                    if(product.get_amount()<10)
                        cout << product.get_name() << " " << product.get_amount() << " " << product.get_price() << " " << product.get_barcode() << endl << endl;
                break;
            }
            case 'x':{
                firstMenu=false;
                break;
            }
            default:{
                cout << "Wpisano bledna informacje, sprobuj ponownie" << endl;
                break;
            }
        }
    }
    bool first=true;
    base.open(file,ios::out | ios::trunc); //otwieram plik do zapisu danych jednocześnie go czyszcząc
    for(Article p: products){
        if(!first)
            base<<"\n";
        base<<p.get_name()+"\n";
        base<<p.get_amount();
        base<<"\n";
        base<<p.get_price();
        base<<"\n";
        base<<p.get_barcode();
        first=false;
    }
    base.close();
    return 0;
}
