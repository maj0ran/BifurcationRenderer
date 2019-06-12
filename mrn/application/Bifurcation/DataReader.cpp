//
// Created by mrn on 19/06/06.
//

#include "DataReader.h"
#include <fstream>
#include <iostream>

// vector<vector<double>> DataReader::read(const char *filename) {

//    // open file
//    ifstream file(filename, ios::in);
//    if (!file.is_open()) {
//        cerr << "Error opening file " << filename << endl;
//        exit(1);
//    }
//
//    vector<vector<double>> data(1, vector<double>(0));
//    double num = 0.0;
//    int row = 0;
//    while(file >> num) {
//        data[row].push_back(num);
//        if(file.peek() == '\n') {
//            data.push_back(vector<double>(0));
//            row++;
//        }
//    }
//    file.close();
//    return data;
//}

vector<vector<vector<double>>> DataReader::read(vector<const char *>& filenames) {
 //   vector<vector<vector<double>>> data(1, vector<vector<double>>(1, vector<double>(0)));
    vector<vector<vector<double>>> data;
    int k_row = 0;
    for(auto filename : filenames) {
        data.push_back((vector<vector<double>>(0)));
        data[k_row].push_back(vector<double>(0));
        ifstream file(filename, ios::in);
        if (!file.is_open()) {
            cerr << "Error opening file " << filename << endl;
            exit(1);
        }

        double val = 0.0;
        int row = 0;

        while(file >> val) {
            data[k_row][row].push_back(val);
            if(file.peek() == '\n') {
                data[k_row].push_back(vector<double>(0));
                row++;
            }
        }
        file.close();
        k_row++;

    }
    return data;
}
