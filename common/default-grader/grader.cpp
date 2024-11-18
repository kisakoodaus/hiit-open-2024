#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

vector<string> read(string name) {
    ifstream file;
    file.open(name);
    vector<string> data;
    string item;
    while (file >> item) data.push_back(item);
    return data;
}

int main(int argc, char **argv) {
    string input1 = argv[1];
    string input2 = argv[2];
    vector<string> data1 = read(input1);
    vector<string> data2 = read(input2);
    if (data1.size() != data2.size()) {
        cout << "0\n";
        return 0;
    }
    for (size_t i = 0; i < data1.size(); i++) {
        if (data1[i] != data2[i]) {
            cout << "0\n";
            return 0;
        }
    }
    cout << "1\n";
}
