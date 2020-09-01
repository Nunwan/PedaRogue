//
// Created by nunwan on 30/08/2020.
//

#ifndef PEDAROGUE_BACKSYSTEM_HPP
#define PEDAROGUE_BACKSYSTEM_HPP


#include <core/ECSTypes.hpp>


class BackSystem : public System
{
public:
    /**
     * @brief           Treat all the back attempt in the game which enable the collision system to restablish reality
     */
    void update() override;
};


#endif //PEDAROGUE_BACKSYSTEM_HPP
