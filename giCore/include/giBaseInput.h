/**
 * @file    giBaseInput.h
 * @author  Jesús Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    21/09/2021
 * @brief   A basic description of the what do the doc.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#pragma once
#include <giPrerequisitesCore.h>
#include <giModule.h>
#include <windows.h>

namespace giEngineSDK {
  class BaseInput : public Module<BaseInput>
  {
   public:
    //Desfault Constructor
    BaseInput() = default;
    //Destructor
    ~BaseInput() = default;

    virtual void 
    init() {}

    virtual void
    createInputDevice() {}

    virtual void
    update() {}

    virtual void
    updateSize(int inWidth, int inHeight) {}

    virtual void
    sendEvent(MSG inMessage) {}
    
    virtual void 
    runEvents() {}
  };
  GI_CORE_EXPORT BaseInput& 
  g_inputManager();

  //For load the DLL
  using funCreateInputManager = BaseInput * (*)();
}