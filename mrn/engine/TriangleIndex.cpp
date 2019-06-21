//
// Created by mrn on 19/06/12.
//

#include "TriangleIndex.h"

mrn::TriangleIndex::TriangleIndex() {

}

mrn::TriangleIndex::~TriangleIndex() {

}


void mrn::TriangleIndex::setVertices(uint32_t p0, uint32_t p1, uint32_t p2) {
    this->p0 = p0;
    this->p1 = p1;
    this->p2 = p2;

}



uint32_t mrn::TriangleIndex::getP0() {
    return p0;
}

uint32_t mrn::TriangleIndex::getP1() {
    return p1;
}

uint32_t mrn::TriangleIndex::getP2() {
    return p2;
}
