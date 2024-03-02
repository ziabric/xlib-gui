#include <iostream>
#include <string>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>

void send_redraw_request(Display *display, Window window) 
{
    XWindowAttributes attributes;
    XGetWindowAttributes(display, window, &attributes);
    XExposeEvent ee;
    ee.type = Expose;
    ee.display = display;
    ee.window = window;
    ee.x = attributes.x;
    ee.y = attributes.y;
    ee.width = attributes.width;
    ee.height = attributes.height;
    ee.count = 0;

    XSendEvent(display, window, False, ExposureMask, (XEvent *)&ee);
    XFlush(display);
}

int main(int argc, char** argv)
{
    std::string title = "Title";

    Display* display;
    int screenNumber;
    GC graphicContext;
    XEvent event;
    Window window;

    std::string textString = "";

    display = XOpenDisplay(nullptr);
    if ( display == nullptr ) return 1;
    screenNumber = DefaultScreen(display);
    window = XCreateSimpleWindow(display, RootWindow(display, screenNumber), 100, 100, 800, 600, 0, BlackPixel(display, screenNumber), WhitePixel(display, screenNumber));
    XSelectInput(display, window, ExposureMask | KeyPressMask | ButtonPressMask | Button1Mask | Button1MotionMask);
    XMapWindow(display, window);

    Atom wmDeleteMessage = XInternAtom(display, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(display, window, &wmDeleteMessage, 1);

    int tmp;

    while (true)
    {
        XNextEvent(display, &event);
        switch (event.type)
        {
        case ClientMessage:
            if ( event.xclient.data.l[0] == wmDeleteMessage )
            {
                XCloseDisplay ( display );
                return 0;   
            }
            break;

        case ButtonPress:
            std::cout<<"BUTTON "<<event.xbutton.button<<std::endl;
            XCloseDisplay ( display );
            return 0;
            break;

        case Button1:
            std::cout<<"BUTTON "<<std::endl;
            break;

        case Expose:
            std::cout<<"EXPOSE"<<std::endl;
            if ( event.xexpose.count != 0 ) break;
            graphicContext = XCreateGC ( display, window, 0 , NULL );
            XSetForeground ( display, graphicContext, BlackPixel ( display, 0) );
            XDrawString ( display, window, graphicContext, 10, 10, textString.c_str(), textString.size() );
            tmp = XDrawLine(display, window, graphicContext, 100, 100, 400, 400);
            std::cout<<tmp<<std::endl;
            XDrawRectangle(display, window, graphicContext, 400, 400, 100, 100);
            XFreeGC ( display, graphicContext );
            XFlush(display);
            break;

        case KeyPress:
            char buffer;
            KeySym ks;
            XLookupString(&event.xkey, &buffer, 1, &ks, 0);
            std::cout<<"KEY PRESS => "<< event.xkey.keycode << " => "<<buffer<<std::endl;
            textString += buffer;
            send_redraw_request(display, window);
            break;

        case DestroyNotify:
            std::cout<<"DESTROY NOTIFY"<<std::endl;
            XCloseDisplay ( display );
            return 0;
            break;

        default:
            std::cout<<"MISSING"<<std::endl;
            break;
        }
    } 
    XCloseDisplay ( display );
}

// #include <guiWindow.hpp>

// int main(int argc, char const *argv[])
// {
//     guiWindow window("Example 1", {800, 600}, {100, 100});
//     return window.draw();
// }
