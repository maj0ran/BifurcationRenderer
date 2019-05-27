//
// Created by mrn on 19/05/23.
//

#pragma once

#include <vector>
#include <cstdint>
#include "../common.h"
#include "EventTypes.h"

namespace mrn {
    class Event {
    public:
        Event(EventType type);
        ~Event();

        const EventType getType() const;

        template <typename T>
        void addData(T* data) {
            auto bytedata = toBytes(data);
            this->_data.insert(this->_data.end(),  bytedata, bytedata + sizeof(T));
        }

        template <typename T>
        T readData() {
            T result = fromBytes<T>(&_data[_data.size() - sizeof(T)]);
            _data.erase(_data.end() - sizeof(T), _data.end());
            return result;
        }
    private:
        std::vector<unsigned char> _data;
        EventType type;
    };

}


