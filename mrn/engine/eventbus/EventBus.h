//
// Created by Marian Cichy
//

#pragma once

#include "BusMember.h"
#include <vector>
namespace mrn {

    class EventBus {

    public:
        EventBus();
        ~EventBus();

 //       bool addMember(mrn::BusMember *)

    private:

    std::vector<BusMember*> members;

    };


}