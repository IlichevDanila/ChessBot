#include "Piece.hpp"

Piece *PieceSet::find(Piece piece)
{
    if(size == 0)
        return nullptr;

    //TODO: binary search
    for(int i = 0; i < size; ++i)
    {
        if(pieces[i] == piece)
        {
            return &pieces[i];
        }
    }

    return nullptr;
}

const Piece *PieceSet::find(Piece piece) const
{
    return const_cast<const Piece *>(find(piece));
}

Piece *PieceSet::find(Position pos)
{
    if(size == 0)
        return nullptr;

    //TODO: binary search
    for(int i = 0; i < size; ++i)
    {
        if(pieces[i].pos == pos)
        {
            return &pieces[i];
        }
    }

    return nullptr;
}

const Piece *PieceSet::find(Position pos) const
{
    return const_cast<const Piece *>(find(pos));
}

void PieceSet::push_back(Piece piece)
{
    //TODO: Do i need check?
    if(find(piece.pos) != nullptr)
        return;

    if(size == 16)
        return;

    //TODO: sorted insertion
    pieces[size] = piece;
    ++size;
}

void PieceSet::erase(Piece *piece)
{
    //TODO: do i need check?
    if(piece < pieces || piece >= (pieces + size))
        return;

    //TODO: sorted erase
    *piece = *(pieces + (size - 1));
    --size;
}