.. _tutorial_step1:

Understanding the main loop
===========================

The application loop wraps around the platform's event loop converts them to PanosUI UIEvents.

To start the event loop you will need an application delegate. A UIApplicationDelegate contains a callback that the UIApplication singleton instance will call when the process is ready for you to create GUI elements.

.. code-block:: c
   :linenos:

    void did_finish_launching(UIApplication *application)
    {
        printf("Hello World!\n");
    }
    
    /* The user defined delegate which specifies that we should call the above function
     * when the app has finished launching */
    static UIApplicationDelegate my_delegate = {.didFinishLaunching = &did_finish_launching};

    int main()
    {
        // Runs the main event loop with the above delegate
        UIApplicationMain(&my_delegate);
    }
