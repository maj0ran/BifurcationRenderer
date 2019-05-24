//
// Created by mrn on 19/05/23.
//

#pragma once

#include <functional>
#include <queue>
#include "Event.h"
namespace mrn {
    class EventBus {
    public:
        EventBus();

        ~EventBus();

        void addNode(std::function<void (Event)> node);
        void send(Event e);
        void notify();
    private:
        std::vector<std::function<void (Event)>> nodes;
        std::queue<Event> events;

    };


}