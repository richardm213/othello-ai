#include "BasicAI.hpp"

std::pair<int, int> BasicAI::chooseMove(const OthelloGameState &state)
{
    int max = std::numeric_limits<int>::min();
    int score;
    std::pair<int, int> move;
    OthelloCell current_player;
    if (state.isWhiteTurn())
        current_player = OthelloCell::white;
    else
        current_player = OthelloCell::black;
    for (int i = 0; i < state.board().width(); ++i)
    {
        for (int j = 0; j < state.board().height(); ++j)
        {
            if (state.isValidMove(i, j))
            {
                std::unique_ptr state_copy = state.clone();
                state_copy->makeMove(i, j);
                score = search(*state_copy, 2, current_player);
                if (score > max)
                {
                    max = score;
                    move = {i, j};
                }
            }
        }
    }
    return move;
}

int BasicAI::search(const OthelloGameState &state, int depth, OthelloCell player)
{
    if (depth == 0 || state.isGameOver())
        return getEvaluation(state, player);
    else if ((player == OthelloCell::white && state.isWhiteTurn()) || (player == OthelloCell::black && state.isBlackTurn()))
    {
        int max = std::numeric_limits<int>::min();
        int score;
        for (int i = 0; i < state.board().width(); ++i)
        {
            for (int j = 0; j < state.board().height(); ++j)
            {
                if (state.isValidMove(i, j))
                {
                    std::unique_ptr s = state.clone();
                    s->makeMove(i, j);
                    score = search(*s, depth - 1, player);
                    if (score > max)
                        max = score;
                }
            }
        }
        return max;
    }
    else
    {
        int min = std::numeric_limits<int>::max();
        int score;
        for (int i = 0; i < state.board().width(); ++i)
        {
            for (int j = 0; j < state.board().height(); ++j)
            {
                if (state.isValidMove(i, j))
                {
                    std::unique_ptr s = state.clone();
                    s->makeMove(i, j);
                    score = search(*s, depth - 1, player);
                    if (score < min)
                        min = score;
                }
            }
        }
        return min;
    }
}

int BasicAI::getEvaluation(const OthelloGameState &state, OthelloCell player)
{
    return scoreDifference(state, player);
}

int BasicAI::scoreDifference(const OthelloGameState &state, OthelloCell player)
{
    if (player == OthelloCell::white)
        return state.whiteScore() - state.blackScore();
    return state.blackScore() - state.whiteScore();
}
