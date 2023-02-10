#include <iostream>
#include <string>
#include <sstream>
#include <array>
using namespace std;
class slot {
    public:
    string status;
    string data;
    slot() {
        status = "never used";
        data = "";
    }
};

class hashT {    
    public:
    array<slot, 26> table;
    int search(string key);
    void insert(string key);
    void remove(string key);
    int hashF(string key);
    void print();
};

// returns (ASCII Decimal Value of the last letter of a string - 97)
int hashT::hashF(string key) {
    int L = key.back() - 97;
    return L;
}
/*
Searching works as follows:  
Step 1) given a key, take its last character as the hash value.  
Step 2) First try the corre-sponding table slot, if the objective key is there, then you have found it.  
Step 3) If the corresponding slot is neverused, terminate because we are certain that the objective is not in the table.  
Step 4) If the slot is occupied but it’s not the objective, or the slot is a “tombstone”, 
        then we move on to the next slot (may need to wrap aroundthe table if the current slot is the last one). 
        We keep trying until we either find the key or are certain that the key does not exist in the table.
*/

int hashT::search(string key) {
    // Step 1)
    int index = hashF(key);
    
    // Step 2) 
    if(table[index].data == key)
        return index;
    
    // Step 3)
    if(table[index].status == "never used")
        return -1;
        
    // Step 4)
    if(table[index].data != key || table[index].status == "tombstone") {
        if(index != 25) {
            for(int i=index+1; i<26; i++) {
                if(table[i].data == key)
                    return i;
            }
            for(int i=0; i<index; i++) {
                if(table[i].data == key)
                    return i;
            }
        } else {
            for(int i=0; i<index; i++) {
                if(table[i].data == key)
                    return i;
                else
                    return -1;           
            }
        }
    
    }
    return -1;
}
/*
Insertion works as follows:  
Step 1) First perform searching to ensure that the key does not exist.  
Step 2) If it already exists, then do nothing.  
Step 3) If it does not, take the last character of a key as the hash value.  
Step 4) If the correspondingtable slot is not occupied (either “never used” or “tombstone”), 
put the key there (the slot is now occupied).If the corresponding slot is already occupied, try the next slot.  
Repeat trying until you find an unoccupiedslot.
*/
void hashT::insert(string key) { 
    bool insertCompleted = false;
    // Step 1)
    // Step 2)
    if(search(key) != -1) {
        // Do Nothing
    }   
    // Step 3) 
    else {
        int hashIndex = hashF(key);
        if(table[hashIndex].status != "occupied") {
            table[hashIndex].data = key;
            table[hashIndex].status = "occupied";
            insertCompleted = true;
        } else { //if(table[hashIndex].status == "occupied")
            for(int i=hashIndex+1; i<26; i++) {
                if(table[i].status != "occupied") {
                    table[i].data = key;
                    table[i].status = "occupied";
                    insertCompleted = true;  
                    break;
                }
            } 
            if(insertCompleted == false) {
                for(int i=0; i<hashIndex; i++) {
                    if(table[i].status != "occupied") {
                        table[i].data = key;
                        table[i].status = "occupied";
                        insertCompleted = true;
                        break;
                    }
                }   
            }
        }
    }
}

/*
Deletion works as follows:  
Step 1) given a key, use the searching process to locate its slot.  
(If the key is not inthe table, then do nothing.)  
Step 2) Once you find the key, change the slot status to “tombstone”.
*/
void hashT::remove(string key) {
    int index = search(key);
    if(index == -1) {
        // Do Nothing
    } else {
        table[index].status = "tombstone";
    }
}
void hashT::print() {
    for(int i=0; i<26; i++) {
        if(table[i].status == "occupied") {
            cout << table[i].data << " ";
        }
    }
}

int main() {
    hashT myTab;

    string tempKey = "";                // temporary key for using at each iteration
    string inputStr = "";               // Whole line of inputs in one string
    string token;                       // Each (instruction+key) is a token
    getline(cin, inputStr);             // get a whole line of input and store in inputStr
    stringstream ss(inputStr);          
    
    while(getline(ss, token, ' ')) {    // Reads a line from ss until ' ' is reached and assignes it to token   
        tempKey.append( token.begin()+1, token.end() );

        if(token[0] == 'A') {
            // Insert
            myTab.insert(tempKey);
            
        } else {
            // if(tempInst == 'D')
            // Delete
            myTab.remove(tempKey);
        }
        tempKey = "";   // Reset tempKey
    }
    myTab.print();
return 0;
}