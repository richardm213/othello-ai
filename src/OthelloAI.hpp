#ifndef OTHELLOAI_HPP
#define OTHELLOAI_HPP

#include <utility>
#include "OthelloGameState.hpp"

class OthelloAI
{
public:
    virtual ~OthelloAI() = default;
    virtual std::pair<int, int> chooseMove(const OthelloGameState &state) = 0;
};

#endif
