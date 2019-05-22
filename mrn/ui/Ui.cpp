//
// Created by Marian Cichy
//

#include "Ui.h"

mrn::ui::Ui::Ui() {

}

mrn::ui::Ui::~Ui() {

}

void mrn::ui::Ui::addWidget(mrn::ui::Widget *w) {
    this->widgets.push_back(w);
}

void mrn::ui::Ui::render() {
    for(Widget* w : widgets) {

    }
}


