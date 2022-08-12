#include "RichardAI2.hpp"

std::pair<int, int> RichardAI2::chooseMove(const OthelloGameState &state)
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
                score = search(*state_copy, 3, std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), current_player);
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

int RichardAI2::search(const OthelloGameState &state, int depth, int alpha, int beta, OthelloCell player)
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
                    score = search(*s, depth - 1, alpha, beta, player);
                    if (score > max)
                        max = score;
                    if (score > alpha)
                        alpha = score;
                    if (beta <= alpha)
                        break;
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
                    score = search(*s, depth - 1, alpha, beta, player);
                    if (score < min)
                        min = score;
                    if (score < beta)
                        beta = score;
                    if (beta <= alpha)
                        break;
                }
            }
        }
        return min;
    }
}

int RichardAI2::getEvaluation(const OthelloGameState &state, OthelloCell player)
{
    if (state.isGameOver())
        return 10000 * scoreDifference(state, player);
    float board_percent_filled = (state.blackScore() + state.whiteScore()) / (state.board().width() * state.board().height());
    if (board_percent_filled < 0.3)
        return 1000 * numCorners(state, player) + 40 * position(state, player) + 40 * mobility(state, player);
    else if (board_percent_filled < 0.9)
        return 1000 * numCorners(state, player) + 20 * position(state, player) + 10 * mobility(state, player);
    else
        return 1000 * scoreDifference(state, player) + 1000 * numCorners(state, player) + 1000 * parity(state, player);
}

int RichardAI2::numCorners(const OthelloGameState &state, OthelloCell player)
{
    int corners = 0;
    OthelloCell opposite_player = oppositePlayer(player);
    if (state.board().cellAt(0, 0) == player)
        corners++;
    else if (state.board().cellAt(0, 0) == opposite_player)
        corners--;
    if (state.board().cellAt(0, state.board().height() - 1) == player)
        corners++;
    else if (state.board().cellAt(0, state.board().height() - 1) == opposite_player)
        corners--;
    if (state.board().cellAt(state.board().width() - 1, 0) == player)
        corners++;
    else if (state.board().cellAt(state.board().width() - 1, 0) == opposite_player)
        corners--;
    if (state.board().cellAt(state.board().width() - 1, state.board().height() - 1) == player)
        corners++;
    else if (state.board().cellAt(state.board().width() - 1, state.board().height() - 1) == opposite_player)
        corners--;
    return corners;
}

int RichardAI2::position(const OthelloGameState &state, OthelloCell player)
{
    int score = 0;
    OthelloCell opposite_player = oppositePlayer(player);
    score -= 5 * xSquares(state, player);
    score += 5 * xSquares(state, opposite_player);
    score -= 1 * cSquares(state, player);
    score += 1 * cSquares(state, opposite_player);
    return score;
}

int RichardAI2::scoreDifference(const OthelloGameState &state, OthelloCell player)
{
    if (player == OthelloCell::white)
        return state.whiteScore() - state.blackScore();
    return state.blackScore() - state.whiteScore();
}

int RichardAI2::mobility(const OthelloGameState &state, OthelloCell player)
{
    int count = 0;
    for (int i = 0; i < state.board().width(); ++i)
    {
        for (int j = 0; j < state.board().height(); ++j)
        {
            if (state.isValidMove(i, j))
                count++;
        }
    }
    return count;
}

int RichardAI2::parity(const OthelloGameState &state, OthelloCell player)
{
    if ((player == OthelloCell::white && state.isWhiteTurn()) || (player == OthelloCell::black && state.isBlackTurn()))
    {
        if ((state.whiteScore() + state.blackScore() % 2) == 1)
            return 1;
        else
            return -1;
    }
    else
    {
        if ((state.whiteScore() + state.blackScore()) % 2 == 0)
            return 1;
        else
            return -1;
    }
}

int RichardAI2::xSquares(const OthelloGameState &state, OthelloCell player)
{
    int count = 0;
    if (state.board().cellAt(0, 0) != player && state.board().cellAt(1, 1) == player)
        count += 1;
    if (state.board().cellAt(state.board().width() - 1, 0) != player && state.board().cellAt(state.board().width() - 2, 1) == player)
        count += 1;
    if (state.board().cellAt(0, state.board().height() - 1) != player && state.board().cellAt(1, state.board().height() - 2) == player)
        count += 1;
    if (state.board().cellAt(state.board().width() - 1, state.board().height() - 1) != player && state.board().cellAt(state.board().width() - 2, state.board().height() - 2) == player)
        count += 1;
    return count;
}

int RichardAI2::cSquares(const OthelloGameState &state, OthelloCell player)
{
    int count = 0;
    if (state.board().cellAt(0, 0) != player)
    {
        if (state.board().cellAt(1, 0) == player)
            count += 1;
        if (state.board().cellAt(0, 1) == player)
            count += 1;
    }
    if (state.board().cellAt(state.board().width() - 1, 0) != player)
    {
        if (state.board().cellAt(state.board().width() - 2, 0) == player)
            count += 1;
        if (state.board().cellAt(state.board().width() - 1, 1) == player)
            count += 1;
    }
    if (state.board().cellAt(0, state.board().height() - 1) != player)
    {
        if (state.board().cellAt(0, state.board().height() - 2) == player)
            count += 1;
        if (state.board().cellAt(1, state.board().height() - 1) == player)
            count += 1;
    }
    if (state.board().cellAt(state.board().width() - 1, state.board().height() - 1) != player)
    {
        if (state.board().cellAt(state.board().width() - 2, state.board().height() - 1) == player)
            count += 1;
        if (state.board().cellAt(state.board().width() - 1, state.board().height() - 2) == player)
            count += 1;
    }
    return count;
}

OthelloCell RichardAI2::oppositePlayer(OthelloCell player)
{
    if (player == OthelloCell::white)
        return OthelloCell::black;
    else
        return OthelloCell::white;
}
