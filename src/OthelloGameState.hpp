#ifndef OTHELLOGAMESTATE_HPP
#define OTHELLOGAMESTATE_HPP

#include <memory>
#include "OthelloBoard.hpp"

class OthelloGameState
{
public:
    virtual ~OthelloGameState() = default;
    virtual const OthelloBoard &board() const noexcept = 0;
    virtual int blackScore() const noexcept = 0;
    virtual int whiteScore() const noexcept = 0;
    virtual bool isGameOver() const noexcept = 0;
    virtual bool isBlackTurn() const noexcept = 0;
    virtual bool isWhiteTurn() const noexcept = 0;
    virtual bool isValidMove(int x, int y) const = 0;
    virtual void makeMove(int x, int y) = 0;
    virtual std::unique_ptr<OthelloGameState> clone() const = 0;
};

#endif
