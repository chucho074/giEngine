#pragma once
#include <giPrerequisitesUtilities.h>
#include <giBaseInput.h>
#include <gainput/gainput.h>

namespace giEngineSDK {
  class InputManager : BaseInput
  {
   public:
    //Default Constructor
  	InputManager();

    //Destructor
  	~InputManager();

    void
    createInputDevice();

    void 
    update();
   protected:
  	
   private:
    gainput::InputManager Input;
  };
}