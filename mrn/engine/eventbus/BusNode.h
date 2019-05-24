//
// Created by mrn on 19/05/23.
//

#pragma once

#include <iostream>
#include "EventBus.h"

namespace mrn {
    class BusNode {
    public:
        explicit BusNode();
        ~BusNode();
        void attach(EventBus* bus);

    protected:
        EventBus* bus;
        std::function<void (Event)> getNotifyFunc();
        void send(Event& e);

        virtual void onNotify(Event &e) { std::cout << "Event Received" << std::endl; };
    };


}