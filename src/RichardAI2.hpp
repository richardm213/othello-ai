#ifndef RICHARDOAI2_HPP
#define RICHARDOAI2_HPP
#include "OthelloAI.hpp"
#include "OthelloCell.hpp"
#include <limits>

class RichardAI2 : public OthelloAI
{
public:
    std::pair<int, int> chooseMove(const OthelloGameState &state) override;
    int search(const OthelloGameState &state, int depth, int alpha, int beta, OthelloCell player);
    int getEvaluation(const OthelloGameState &state, OthelloCell player);
    int numCorners(const OthelloGameState &state, OthelloCell player);
    int position(const OthelloGameState &state, OthelloCell player);
    int scoreDifference(const OthelloGameState &state, OthelloCell player);
    int mobility(const OthelloGameState &state, OthelloCell player);
    int parity(const OthelloGameState &state, OthelloCell player);
    int xSquares(const OthelloGameState &state, OthelloCell player);
    int cSquares(const OthelloGameState &state, OthelloCell player);
    OthelloCell oppositePlayer(OthelloCell player);
};

#endif
