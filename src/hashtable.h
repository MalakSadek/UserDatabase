#ifndef HASHTABLE
#define HASHTABLE

#include <iostream>
#include<QtCore/QFile>
#include<QtCore/QTextStream>

using namespace std;

// Specification of the class
template <class keyType, class dataType>
class hashTable{
public:

    // Member Functions
    hashTable(int nelements = 11);		// Constructor
    ~hashTable();						// Destructor

    // Functions Prototype Definitions
    void emptyTable(const keyType &);
    bool tableIsEmpty() const;
    bool tableIsFull() const;
    bool insert(const keyType &, const dataType &, const bool &);
    int search(const keyType & );
    dataType getPassword(int);
    bool getAccess(int);
    void readFile(QString);

private:

    // Slot Class
    class slot{
       public:
           keyType key; 		// key
           dataType password;  // Data
           bool hasAccess;
       }; // end of class slot declaration

    slot *T;							// Pointer to Storage Array
    int h;								// Index to a slot
    int MaxSize, csize;					// Maximum and Current Sizes
    keyType Empty;						// empty symbol

    // Private Member function
    int hash(const keyType & );
    long pow(int, int);
};

// Constructor with argument, size is nelements, default is 11
template <class keyType, class dataType>
hashTable<keyType, dataType>::hashTable(int nelements){
    MaxSize = nelements;
    T = new slot[MaxSize];
    csize = 0;
    h = -1;
}


// Destructor
template <class keyType, class dataType>
hashTable<keyType, dataType>::~hashTable(){
    delete[]T;
}


// Empty all slots
template <class keyType, class dataType>
void hashTable<keyType, dataType>::emptyTable(const keyType &k)
{
    //Set the empty value
    Empty = k;
    for (int i = 0; i<MaxSize; i++)
        T[i].key = Empty;
    h = -1;
    csize = 0;
}

// return True if table is empty
template <class keyType, class dataType>
bool hashTable<keyType, dataType>::tableIsEmpty() const
{
    //Test current size if = 0
    return csize == 0;
}

// return True if table is full
template <class keyType, class dataType>
bool hashTable<keyType, dataType>::tableIsFull() const{

    //Test current size if = Maximum size
    return csize == MaxSize;
}

// insert key and data at a hashed slot
template <class keyType, class dataType>
bool hashTable<keyType, dataType>::insert(const keyType &k, const dataType &d, const bool &b){
    if (!tableIsFull()) {
        h = hash(k);
        while (T[h].key != Empty) {
            h = (h+1) % MaxSize;
        }
        if (T[h].key == Empty) {
            T[h].key = k;
            T[h].password = d;
            T[h].hasAccess = b;
            csize++;
            return true;
        }
    }
    return false;
}

// Search the table for the slot that matches key.
// If found, return True, set current position to slot
template <class keyType, class dataType>
int hashTable<keyType, dataType>::search(const keyType &k )
{
    if(!tableIsEmpty()){
        h = hash(k); int start = h;
        for ( ; ; ){
            if (T[h].key == Empty) return -1;
            if (T[h].key == k) return h;
            h = (h+1) % MaxSize;
            if (h == start) return -1;
        }
     }
     else
         return -1;
}

// Private Hashing Function
template <class keyType, class dataType>
int hashTable<keyType, dataType>::hash(const keyType &k ){
    int total = 0;
    for (int i = 0; i < k.length(); i++)
               total = total + (pow(2, i) * int(k.toStdString().at(i)));

    total = total % MaxSize;
    return (total);
}

template <class keyType, class dataType>
dataType hashTable<keyType, dataType>::getPassword(int i){
    return T[i].password;
}

template <class keyType, class dataType>
bool hashTable<keyType, dataType>::getAccess(int i){
    return T[i].hasAccess;
}

template <class keyType, class dataType>
long hashTable<keyType, dataType>::pow(int a, int b){
    while(b--)
        a*=a;
    return a;
}

template <class keyType, class dataType>
void hashTable<keyType, dataType>::readFile(QString read){
    QFile file(read);
    if(file.open(QIODevice::ReadOnly) == false){
        cout<<"Could not open file, please specify correct file path in loginform.cpp"<<endl;
    }
    QTextStream textStream(&file);
    QString x,y,z;

    while (!textStream.atEnd()){
        textStream >> x;
        textStream >> y;
        textStream >> z;
        bool flag = z == "true" ? true:false;
        insert(x, y, flag);
    }

    file.close();
}


#endif // HASHTABLE

