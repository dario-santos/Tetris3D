#include "PieceHolder.hpp"

#include "BoardObjects/BoardObject.hpp"

PieceHolder::PieceHolder() :
  _status(piece_Status_Not_Modified),
  _piece(nullptr)
{

}

bool PieceHolder::IsStatusNotModified()
{
  return _status == piece_Status_Not_Modified;
}

void PieceHolder::ChangePiece(unique_ptr<BoardObject>& piece)
{
  if (piece)
  {
    unique_ptr<BoardObject> tmpObject(piece.release());
    piece.reset(_piece.release());
    _piece.reset(tmpObject.release());
  }
  else // empty
    _piece.reset(piece.release()); // The release method sets the smart pointer piece to null

  _UpdateStatusToModified();
}

void PieceHolder::UpdateStatusToNotModified()
{
  _status = piece_Status_Not_Modified;
}


void PieceHolder::_UpdateStatusToModified()
{
  _status = piece_Status_Modified;
}
