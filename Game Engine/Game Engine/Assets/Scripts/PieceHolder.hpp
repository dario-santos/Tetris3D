#pragma once

#include <memory>

// Forward Declaration
class BoardObject;

class PieceHolder
{

public:

  PieceHolder();

  ~PieceHolder() = default;

  bool IsStatusNotModified();
  void ChangePiece(std::unique_ptr<BoardObject>& piece);
  void UpdateStatusToNotModified();

private:

  enum pieceStatus
  {
    piece_Status_Not_Modified = 0,
    piece_Status_Modified
  };

  pieceStatus _status;
  std::unique_ptr<BoardObject> _piece;

  void _UpdateStatusToModified();

};
