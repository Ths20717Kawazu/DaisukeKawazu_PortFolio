#pragma once
#include "Actor.h"

//#include "InputComponent.h" Å©ó]åvÇ»Include

class Player :
    public Actor
{
public: 
      Player(Game* game);
      ~Player();
      void DrawPlayer(void);
      void UpdatePlayer(void) ;
      /*int playerState{0};*/
      //void ProcessInput(void);

  //  enum CharaState
  //  {
  //      STAND,
  //      FACE_RIGHT,
  //      FACE_LEFT,
  //      RUN_RIGHT,
  //      RUN_LEFT,
  //      JUMP,
  //      FALL,
  //      LAND,
  //};

private:

    

};

