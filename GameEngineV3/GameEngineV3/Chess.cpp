//
//  Chess.cpp
//  GameEngineV3
//
//  Created by Carlos Spaggiari Roa on 11/24/16.
//  Copyright © 2016 ARSC. All rights reserved.
//

#include "Chess.hpp"

bool     Piece::_busyMouse = false;
Vector2D Piece::_size      = Vector2D(68,68);

Piece*   Board::piecesBoard[8][8];

void loadChess(){
  shared_ptr<Board> board = shared_ptr<Board>(new Board());
  
  Game::Application->currentScene = board;
  
}


void Piece::Update(){
  if (hidden) return;
  if (_grabed){
    setPosition(Input::GetMouseClickPosition() - _size/2);
    if (Input:: MouseButtonReleased(MOUSE_LEFT_BUTTON)){
      _grabed    = false;
      _busyMouse = false;
      
      Vector2D oldPos = _boardPosition;
      
      
      setBoardPosition(transform.position);
      Board::piecesBoard[(int)oldPos.x][(int)oldPos.y] = NULL;
      Vector2D newPos = _boardPosition;
      Piece   *piece  = Board::piecesBoard[(int)newPos.x][(int)newPos.y];
      
      if (not (oldPos == newPos or piece == NULL)){
        
        piece->hide(true);
      }
      
      Board::piecesBoard[(int)newPos.x][(int)newPos.y] = this;
    }
  }
}




Board::Board() : Scene("Chess_Board", Rect(0,0,628,628))
{
  background = new Texture("ChessBoard" , BOARD_PATH);
  pieces     = new Sprite("ChessPieces", PIECES_PATH, 6, 2);
  name = "Chess";
  this->_blackPieces.reserve(16);
  this->_blackPieces.resize(16);
  this->_whitePieces.reserve(16);
  this->_whitePieces.resize(16);
  
  for (int i = 0; i < 16; ++i) {
    _whitePieces[i] = new Piece();
    _blackPieces[i] = new Piece();
  }
  
  for (int i = 0; i < 8; ++i) {
    _whitePieces[i]->type = WPAWN;
    _blackPieces[i]->type = BPAWN;
    
    _whitePieces[i]->setBoardPosition(Vector2D(43+68*i, 43+68));
    _blackPieces[i]->setBoardPosition(Vector2D(43+68*i, 43+68*6));
    
    _whitePieces[i]->texture = pieces->sheet[11];
    _blackPieces[i]->texture = pieces->sheet[5];
    
    addObject(_whitePieces[i]);
    addObject(_blackPieces[i]);
  }
  _whitePieces[8]->type  = ROOK;
  _blackPieces[8]->type  = ROOK;
  _whitePieces[9]->type  = KNIGHT;
  _blackPieces[9]->type  = KNIGHT;
  _whitePieces[10]->type = BISHOP;
  _blackPieces[10]->type = BISHOP;
  _whitePieces[11]->type = QUEEN;
  _blackPieces[11]->type = QUEEN;
  _whitePieces[12]->type = KING;
  _blackPieces[12]->type = KING;
  _whitePieces[13]->type = BISHOP;
  _blackPieces[13]->type = BISHOP;
  _whitePieces[14]->type = KNIGHT;
  _blackPieces[14]->type = KNIGHT;
  _whitePieces[15]->type = ROOK;
  _blackPieces[15]->type = ROOK;
  
  _whitePieces[8]->texture  = pieces->sheet[8];
  _blackPieces[8]->texture  = pieces->sheet[2];
  _whitePieces[9]->texture  = pieces->sheet[10];
  _blackPieces[9]->texture  = pieces->sheet[4];
  _whitePieces[10]->texture = pieces->sheet[9];
  _blackPieces[10]->texture = pieces->sheet[3];
  _whitePieces[11]->texture = pieces->sheet[7];
  _blackPieces[11]->texture = pieces->sheet[1];
  _whitePieces[12]->texture = pieces->sheet[6];
  _blackPieces[12]->texture = pieces->sheet[0];
  _whitePieces[13]->texture = pieces->sheet[9];
  _blackPieces[13]->texture = pieces->sheet[3];
  _whitePieces[14]->texture = pieces->sheet[10];
  _blackPieces[14]->texture = pieces->sheet[4];
  _whitePieces[15]->texture = pieces->sheet[8];
  _blackPieces[15]->texture = pieces->sheet[2];
  
  _whitePieces[8]->setBoardPosition (Vector2D(     43, 43));
  _blackPieces[8]->setBoardPosition (Vector2D(     43, 43+68*7));
  _whitePieces[9]->setBoardPosition (Vector2D(  43+68, 43));
  _blackPieces[9]->setBoardPosition (Vector2D(  43+68, 43+68*7));
  _whitePieces[10]->setBoardPosition(Vector2D(43+68*2, 43));
  _blackPieces[10]->setBoardPosition(Vector2D(43+68*2, 43+68*7));
  _whitePieces[11]->setBoardPosition(Vector2D(43+68*3, 43));
  _blackPieces[11]->setBoardPosition(Vector2D(43+68*3, 43+68*7));
  _whitePieces[12]->setBoardPosition(Vector2D(43+68*4, 43));
  _blackPieces[12]->setBoardPosition(Vector2D(43+68*4, 43+68*7));
  _whitePieces[13]->setBoardPosition(Vector2D(43+68*5, 43));
  _blackPieces[13]->setBoardPosition(Vector2D(43+68*5, 43+68*7));
  _whitePieces[14]->setBoardPosition(Vector2D(43+68*6, 43));
  _blackPieces[14]->setBoardPosition(Vector2D(43+68*6, 43+68*7));
  _whitePieces[15]->setBoardPosition(Vector2D(43+68*7, 43));
  _blackPieces[15]->setBoardPosition(Vector2D(43+68*7, 43+68*7));
  
  addObject(_whitePieces[8]);
  addObject(_blackPieces[8]);
  addObject(_whitePieces[9]);
  addObject(_blackPieces[9]);
  addObject(_whitePieces[10]);
  addObject(_blackPieces[10]);
  addObject(_whitePieces[11]);
  addObject(_blackPieces[11]);
  addObject(_whitePieces[12]);
  addObject(_blackPieces[12]);
  addObject(_whitePieces[13]);
  addObject(_blackPieces[13]);
  addObject(_whitePieces[14]);
  addObject(_blackPieces[14]);
  addObject(_whitePieces[15]);
  addObject(_blackPieces[15]);
  
  for (int i = 0; i < 16; ++i) {
    SDL_Point wv = _whitePieces[i]->getBoardPosition().to_SDL_Point();
    SDL_Point bv = _blackPieces[i]->getBoardPosition().to_SDL_Point();
    piecesBoard[wv.x][wv.y] = _whitePieces[i];
    piecesBoard[bv.x][bv.y] = _blackPieces[i];
  }
  
}
