.. _tutorial_step2:

Creating your first window
===========================

Window Creation
------------------

Now that you understand how the main loop works in PanosUI, you're probably going to want to create some windows for your program.

To create your first window, replace the function from the previous step with the one below.

.. code-block:: c
   :linenos:

    void did_finish_launching(UIApplication *application)
    {
        UIRect window_frame = UIRectCreate(0, 0, 500, 500);
        UIWindow *window = UIWindowCreate(window_frame);

        UIWindowShow(window);
        UIWindowSetTitle(window, "First Window");
    }

This updated function should open a window with a width of 500px and a height of 500px. This is because we created a :code:`window_frame` variable of type :code:`UIRect` with an :code:`x` of 0, a :code:`y` of 0, and a :code:`width` and :code:`height` of 500px.

Window Controllers
------------------

Window controllers are similar to the UIApplicationDelegate from earlier. However, instead of controlling the applications lifecycle, it controls a UIWindow's lifecycle.

You can imagine how it would be useful to be able to customize a windows behavior and hook into the window's lifecycle.

To do this, replace the example code with the code below.

.. code-block:: c
   :linenos:

   void window_did_load(void *_, UIWindow *window)
    {
        UIView *view = UIWindowGetMainView(window);
        printf("Window did load! mainView: %p\n", window);
    }

    void did_finish_launching(UIApplication *application)
    {
        UIRect window_frame = UIRectCreate(0, 0, 500, 500);
        UIWindow *window = UIWindowCreate(window_frame);

        UIWindowController *my_window_controller = UIWindowControllerCreate();
        my_window_controller->windowDidLoad = &window_did_load;

        UIWindowSetController(window, my_window_controller);

        UIWindowShow(window);
        UIWindowSetTitle(window, "First Window");
    }