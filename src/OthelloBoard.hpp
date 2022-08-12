#ifndef OTHELLOBOARD_HPP
#define OTHELLOBOARD_HPP

#include "OthelloCell.hpp"

class OthelloBoard
{
public:
    virtual ~OthelloBoard() = default;
    virtual int width() const noexcept = 0;
    virtual int height() const noexcept = 0;
    virtual bool isValidCell(int x, int y) const noexcept = 0;
    virtual OthelloCell cellAt(int x, int y) const = 0;
    virtual void setCellAt(int x, int y, OthelloCell cell) = 0;
    virtual void placeTile(int x, int y, OthelloCell cell) = 0;
    virtual void flipTile(int x, int y) = 0;
};

#endif
