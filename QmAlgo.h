#ifndef QMALGO
#define QMALGO

#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
#include "Implicant.cpp"

using namespace std;

/*
Naming Convention:
 - Maps are capitalized
 - Vectors are camelCased
*/

struct comparatorImp {
    bool operator()(const Implicant &a, const Implicant &b) const {
        return a.binary < b.binary;
    }
};

struct pairimp {
    Implicant implicant;
    int frequency;
};

class QmAlgo {
    int variables; // no of variables

    string fileName; // input file 
    fstream inputFile;

    // to be done: map to list all minterms and dont cares' numbers to retrieve them easily
    map<int, bool> Terms; // storing minterms and dont cares, such that false means dontcare
    map<Implicant, bool, comparatorImp> Implicants; // map to store the minImplicants (bool: istaken or not)

    vector<Implicant> primeImplicants;
    vector<Implicant> essentialPrimeImplicants;
    vector<Implicant> reducedExpression;
    map<int, vector<Implicant>> coversOverMinterms;
    map<int, bool> isMinTermCovered;
    vector<int> mintermsnotcovered; //not covered by EPIs

    void reduce(); // Main Algorithm

public:
    QmAlgo(int variables, vector<int>& minterms, vector<int>& dontcares); // populate the map from values validated in the validation method
    
    void populatePrimeImplicants();
    void populateEssentialPrimeImplicants();

    void printPIs(); // print all prime Implicants
    void printEPIs(); // print all essential prime Implicants

    void PITable(); // print the prime Implicants table/chart
    void generateMinmizedLogicExpression(); // get the very minimized logic expression of the function according to the PI table
    void runAlgo(); 
};

#endif