//
// Created by mrn on 19/05/23.
//

#include "EventBus.h"

mrn::EventBus::EventBus() {

}

mrn::EventBus::~EventBus() {

}

void mrn::EventBus::addNode(std::function<void (mrn::Event)> node) {
    nodes.push_back(node);
}

void mrn::EventBus::send(mrn::Event& e) {
    events.push(e);
}

void mrn::EventBus::notify() {
    while(!events.empty()) {
        for(const auto &n : nodes) {
            (n)(events.front());
        }
        events.pop();
    }
}
