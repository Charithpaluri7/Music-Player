#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ofstream out;
    out.open("hey.txt");  // Open file for writing

    out << "this is not me!";  // Write to file

    out.close();  // Always close the file when done

    ifstream hey;
    string s;
    hey.open("hey.txt");
    while(hey.eof()==0){
        getline(hey,s);
    }
    return 0;
}
