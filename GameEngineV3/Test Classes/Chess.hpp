//
//  Chess.hpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 11/24/16.
//  Copyright © 2016 ARSC. All rights reserved.
//

#ifndef Chess_hpp
#define Chess_hpp

#include <stdio.h>
#include "Game.hpp"
#include "Animator.hpp"

#define BOARD_PATH  "/Volumes/HDD/C-C++/PROYECTOS/Juego_SDL/GameEngineV3/GameEngineV3/Resources/board.jpg"
#define PIECES_PATH "/Volumes/HDD/C-C++/PROYECTOS/Juego_SDL/GameEngineV3/GameEngineV3/Resources/pieces.png"

#define BSIZE  8
#define MAXMV  57

using namespace engine;

enum PieceType{
 OUT    = 0
,WPAWN  = 1
,BPAWN  = 2
,KNIGHT = 3
,BISHOP = 4
,ROOK   = 5
,QUEEN  = 6
,KING   = 7
};

#define BLACK 0
#define WHITE 1

#define PAWNV 1

const int8_t   lenghtMv[8]    = { 0, 6, 6,16, 8, 8,16,16};
const int8_t   pawnMvBlack[8] = { 0,-1, 1,-1,-1,-1, 0,-2};
const int8_t   pawnMvWhite[8] = { 0, 1, 1, 1,-1, 1, 0, 2};

const int8_t   bishopMv[8]    = { 1, 1, 1,-1,-1, 1,-1,-1};
const int8_t   rookMv[8]      = { 0, 1, 1, 0, 0,-1,-1, 0};
const int8_t   knightMv[16]   = { 2, 1, 2,-1,-2, 1,-2,-1, 1, 2, 1,-2,-1, 2,-1,-2};
const int8_t   queenMv[16]    = { 1, 1, 1,-1,-1, 1,-1,-1, 1, 0,-1, 0, 0, 1, 0,-1};
const int8_t   kingMv[16]     = { 1, 1, 1,-1,-1, 1,-1,-1, 1, 0,-1, 0, 0, 1, 0,-1};
const uint8_t  blockedPath[8] = { 0, 7,0x7,0xff,0xf,0xf,0xff,0xff};
const uint64_t bitPos[64] =
{ 0x1,               0x2,               0x4,               0x8,
  0x10,              0x20,              0x40,              0x80,
  0x100,             0x200,             0x400,             0x800,
  0x1000,            0x2000,            0x4000,            0x8000,
  0x10000,           0x20000,           0x40000,           0x80000,
  0x100000,          0x200000,          0x400000,          0x800000,
  0x1000000,         0x2000000,         0x4000000,         0x8000000,
  0x10000000,        0x20000000,        0x40000000,        0x80000000,
  0x100000000,       0x200000000,       0x400000000,       0x800000000,
  0x1000000000,      0x2000000000,      0x4000000000,      0x8000000000,
  0x10000000000,     0x20000000000,     0x40000000000,     0x80000000000,
  0x100000000000,    0x200000000000,    0x400000000000,    0x800000000000,
  0x1000000000000,   0x2000000000000,   0x4000000000000,   0x8000000000000,
  0x10000000000000,  0x20000000000000,  0x40000000000000,  0x80000000000000,
  0x100000000000000, 0x200000000000000, 0x400000000000000, 0x800000000000000,
  0x1000000000000000,0x2000000000000000,0x4000000000000000,0x8000000000000000};



class Board;

class Piece : public Object
{
  
public:
  friend class Board;
  PieceType type;
  
  
  inline Vector2 getBoardPosition(){
    return _boardPosition;
  }
  
  void setBoardPosition(Vector2 pos){
    if (pos.x >= 43 and pos.x < 43+8*68 and pos.y >= 43 and pos.y < 43+8*68){
      int nx = (pos.x - 43 + 34)/68;
      int ny = (pos.y - 43 + 34)/68;
      
      _boardPosition = Vector2(nx,ny);
      _previousPosition = _boardPosition*68+Vector2(43,43);
    }
    else {
      Debug::Log("Bad position for piece of type: " +
                  to_string(type) + " " +
                  pos.toStr());
    }
    setPosition(_previousPosition);
  }
  
  void Start(){
    
  }
  
  void Update();
  
private:
  static bool     _busyMouse;
  static Vector2 _size;
  
  bool     _grabed = false;
  Vector2 _boardPosition;
  Vector2 _previousPosition;
  
  
};


class Board : public Scene
{
  
public:
  
  static Piece* piecesBoard[8][8];
  
  Board();
  
  void Update() {
    if (not Piece::_busyMouse and Input::MouseButtonPressed(MOUSE_LEFT_BUTTON)){
      Vector2 click = Input::GetMouseClickPosition();
      int nx = (click.x - 43)/68;
      int ny = (click.y - 43)/68;
      Debug::Log(to_string(nx) + "  " + to_string(ny));
      if (piecesBoard[nx][ny] != NULL){
        piecesBoard[nx][ny]->_grabed = true;
        Piece::_busyMouse = true;
      }
    }
  }
  
private:
  vector<Piece*> _blackPieces;
  vector<Piece*> _whitePieces;
  long int _board;
  

  Sprite *pieces;
};

void loadChess();

#endif /* Chess_hpp */
