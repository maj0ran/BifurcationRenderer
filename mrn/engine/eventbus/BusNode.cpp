//
// Created by mrn on 19/05/23.
//

#include "BusNode.h"

mrn::BusNode::BusNode() {
  //  this->bus = bus;
  //  bus->addNode(this->getNotifyFunc());

}

mrn::BusNode::~BusNode() = default;

std::function<void(mrn::Event)> mrn::BusNode::getNotifyFunc() {
    std::function<void(mrn::Event)> eventListener = [=](Event e) -> void { this->onNotify(e); };
    return eventListener;
}

void mrn::BusNode::send(mrn::Event e) {
    bus->send(e);

}

void mrn::BusNode::attach(mrn::EventBus *bus) {
    this->bus = bus;
    this->bus->addNode(this->getNotifyFunc());
}
