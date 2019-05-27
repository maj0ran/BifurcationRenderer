//
// Created by mrn on 19/05/23.
//

#include "Event.h"

mrn::Event::Event(EventType type) {
    this->type = type;
}

mrn::Event::~Event() {

}

const EventType mrn::Event::getType() const {
    return this->type;
}
