#pragma once
#include "Actor.h"

//#include "InputComponent.h" ���]�v��Include

class Player :
    public Actor
{
public: 
      Player(Game* game);
      ~Player();
      void DrawPlayer(void);
      //void ProcessInput(void);
      
 
    


private:
    
    

};

