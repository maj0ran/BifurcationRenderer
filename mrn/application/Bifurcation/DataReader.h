//
// Created by mrn on 19/06/06.
//

#pragma once
#include <vector>

using namespace std;
class DataReader {
public:
    DataReader() = default;
    ~DataReader() = default;

    vector<vector<vector<double>>> read(vector<const char*>& filenames);
};


