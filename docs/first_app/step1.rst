.. _tutorial_step1:

Making a window
===============

To make a window, 

.. code-block:: c
   :linenos:

    void did_finish_launching(UIApplication *application)
    {
        printf("Hello World!\n");
    }
    
    static UIApplicationDelegate my_delegate = {.didFinishLaunching = &didFinishLaunching};

    int main()
    {
        UIApplicationMain(&my_delegate);
    }
