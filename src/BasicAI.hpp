#ifndef BASICAI_HPP
#define BASICAI_HPP
#include "OthelloAI.hpp"
#include "OthelloCell.hpp"
#include <limits>

class BasicAI : public OthelloAI
{
public:
    // Returns the move with the best evaluation.
    std::pair<int, int> chooseMove(const OthelloGameState &state) override;
    // Minimax search algorithm.
    int search(const OthelloGameState &state, int depth, OthelloCell player);
    // Returns the evaluation of a given state.
    int getEvaluation(const OthelloGameState &state, OthelloCell player);
    // Returns the score difference during a given state.
    int scoreDifference(const OthelloGameState &state, OthelloCell player);
};

#endif
