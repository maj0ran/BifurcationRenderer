//
// Created by mrn on 19/05/23.
//

#pragma once

#include <vector>
#include <cstdint>
#include "../common.h"

namespace mrn {
    class Event {
    public:
        Event();
        ~Event();

        template <typename T>
        void addData(T data) {
            auto bytedata = toBytes(data);
            this->_data.insert(this->_data.end(),  bytedata.begin(), bytedata.end());
        }

        template <typename T>
        T readData() {
            std::vector<unsigned char> data = std::vector<unsigned char>(_data.end() - sizeof(T), _data.end());
            _data.erase(_data.end() - sizeof(T), _data.end());
            return fromBytes<T>(data);
        }

        std::vector<unsigned char> _data;
    };

}


