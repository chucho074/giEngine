/**
 * @file    giModule.h
 * @author  Jes�s Alberto Del Moral Cupil
 * @e       idv18c.jmoral@uartesdigitales.edu.mx
 * @date    26/03/2021
 * @brief   A basic description of the what do the doc.
 * @bug     No known Bugs.
 */
 
/**
 * @include
 */
#pragma once


namespace giEngineSDK {
  /**
   * @brief  Represents one engine module. Essentially it is a specialized type
   *        of singleton. Module must be manually started up and shut down
   *        before and after use.
   */
  template<class T>
  class Module
  {
   public:
    /**
     * @brief Returns a reference to the module instance. Module has to have
     *        been started up first otherwise an exception will be thrown.
     */
    static T&
    instance() {
      if (!isStartedUp()) {
        //GI_EXCEPT(InternalErrorException,
        //          "Trying to access a module but it hasn't been started.");
      }

      if (isDestroyed()) {
        //GE_EXCEPT(InternalErrorException,
        //          "Trying to access a destroyed module.");
      }

      return *_instance();
    }

    /**
     * @brief  Returns a pointer to the module instance. Module has to have been
     *        started up first otherwise an exception will be thrown.
     */
    static T*
    instancePtr() {
      if (!isStartedUp()) {
        //GE_EXCEPT(InternalErrorException,
        //          "Trying to access a module but it hasn't been started.");
      }

      if (isDestroyed()) {
        //GE_EXCEPT(InternalErrorException,
        //          "Trying to access a destroyed module.");
      }

      return _instance();
    }

    /**
     * @brief Constructs and starts the module using the specified parameters.
     */
    template<class... Args>
    static void
    startUp(Args&& ...args) {
      if (isStartedUp()) {
        //GE_EXCEPT(InternalErrorException,
        //          "Trying to start an already started module.");
      }

      _instance() = new T(std::forward<Args>(args)...);
      isStartedUp() = true;

      static_cast<Module*>(_instance())->onStartUp();
    }

    /**
     * @brief Constructs and starts a specialized type of the module.
     *        Provided type must derive from type the Module is initialized with.
     */
    template<class SubType, class... Args>
    static void
    startUp(Args&& ...args) {
      static_assert(std::is_base_of<T, SubType>::value,
                    "Provided type isn't derived from type the Module is initialized with.");

      if (isStartedUp()) {
        //Except  "Trying to start an already started module."
      }

      _instance() = new SubType (std::forward<Args>(args)...);
      isStartedUp() = true;

      static_cast<Module*>(_instance())->onStartUp();
    }

    /**
     * @brief Shuts down this module and frees any resources it is using.
     */
    static void
    shutDown() {
      if (isDestroyed()) {
        //Except "Trying to shut down an already shut down module."
      }

      if (!isStartedUp()) {
        //Except "Trying to shut down a module which was never started."
      }

      static_cast<Module*>(_instance())->onShutDown();

      delete(_instance());
      isDestroyed() = true;
    }

    /**
     * @brief Query if the module has been started.
     */
    static bool
    isStarted() {
      return isStartedUp() && !isDestroyed();
    }

   protected:
    Module() = default;

    virtual
    ~Module() = default;

    Module(Module&&) = delete;

    Module(const Module&) = delete;

    Module&
    operator=(Module&&) = delete;

    Module&
    operator=(const Module&) = delete;

    /**
     * @brief  Override if you want your module to be notified once it has been
     *        constructed and started.
     * @note Useful when your module is polymorphic and you cannot perform some
     *       implementation specific initialization in constructor itself.
     */
    virtual void
    onStartUp() {}

    /**
     * @brief Override if you want your module to be notified just before it is deleted.
     * @note  Useful when your module is polymorphic and you might want to perform
     *        some kind of clean up perhaps overriding that of a base class.
     */
    virtual void
    onShutDown() {}

    /**
     * @brief Returns a singleton instance of this module. Throws an exception
     *        if module is not yet initialized.
     */
    static T*&
    _instance() {
      static T* inst = nullptr;
      return inst;
    }

    /**
     * @brief Checks has the Module been shut down.
     * @note  If module was never even started, this will return false.
     */
    static bool&
    isDestroyed() {
      static bool inst = false;
      return inst;
    }

    /**
     * @brief Checks has the Module been started up.
     */
    static bool&
    isStartedUp() {
      static bool inst = false;
      return inst;
    }

   public:
    /**
     * @brief    Set the object of the Graphics API.
     * @param    inAPI   The api to set.
     */
    template<typename T>
    void
    setObject(T * inObject) {
      T::_instance() = inObject;
    }
  };
}

