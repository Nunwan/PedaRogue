//
// Created by nunwan on 30/07/2020.
//

#ifndef PEDAROGUE_PICKSYSTEM_HPP
#define PEDAROGUE_PICKSYSTEM_HPP


#include <core/ECSTypes.hpp>


class PickSystem : public System
{
public:
    /**
     * @brief       Update the game with all the action of picking an object
     */
    void update() override;

};


#endif //PEDAROGUE_PICKSYSTEM_HPP
