#include <string>
#include <iostream>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>

struct vec2 {int x,y;};

class guiWindow
{
public:
    explicit guiWindow(const std::string& title = "Example", const vec2& size = {800, 600}, const vec2& pos = {0,0});
    ~guiWindow();
    vec2 getSize() noexcept {return size_;}
    vec2 getPos() noexcept {return pos_;}
    int draw();
    void setSize(const vec2& size);
    void setPos(const vec2& pos);
private:
    Display* display_;
    int screenNumber_;
    GC graphicContext_;
    XEvent event_;
    Window window_;

    std::string title_;
    vec2 size_;
    vec2 pos_;
};

guiWindow::guiWindow(const std::string& title, const vec2& pos, const vec2& size) :
title_(title), size_(size), pos_(pos)
{
    display_ = XOpenDisplay(nullptr);
    if ( display_ == nullptr ) throw "error";
    screenNumber_ = DefaultScreen(display_);
    window_ = XCreateSimpleWindow(display_, RootWindow(display_, screenNumber_), 100, 100, 800, 600, 0, BlackPixel(display_, screenNumber_), WhitePixel(display_, screenNumber_));
    XSelectInput(display_, window_, 
        ExposureMask | 
        KeyPressMask | 
        ButtonPressMask | 
        Button1Mask | 
        Button1MotionMask |
        DestroyNotify
    );
    XMapWindow(display_, window_);
}

guiWindow::~guiWindow()
{
    // XCloseDisplay (display_);
}

int guiWindow::draw()
{
    while (true)
    {
        XNextEvent(display_, &event_);
        switch (event_.type)
        {
        case ButtonPress:
            std::cout<<"BUTTON "<<event_.xbutton.button<<std::endl;
            // XCloseDisplay ( display_ );
            // return 0;
            break;

        case Button1:
            std::cout<<"BUTTON "<<std::endl;
            break;

        case Expose:
            std::cout<<"EXPOSE"<<std::endl;
            // if ( event_.xexpose.count != 0 ) break;
            // graphicContext_ = XCreateGC ( display_, window_, 0 , nullptr );
            // XSetForeground ( display_, graphicContext_, BlackPixel ( display_, 0) );
            // // XDrawString ( display_, window_, graphicContext_, 10, 10, textString.c_str(), textString.size() );
            // XFreeGC ( display_, graphicContext_ );
            // XFlush(display_);
            break;

        case KeyPress:
            std::cout<<"KEY PRESS"<<std::endl;
            // char buffer;
            // KeySym ks;
            // XLookupString(&event_.xkey, &buffer, 1, &ks, 0);
            // std::cout<<"KEY PRESS => "<< event_.xkey.keycode << " => "<<buffer<<std::endl;
            // send_redraw_request(display_, window_);
            break;

        case DestroyNotify:
            std::cout<<"DESTROY NOTIFY"<<std::endl;
            XCloseDisplay ( display_ );
            return 0;
            break;

        default:
            std::cout<<"MISSING"<<std::endl;
            break;
            
        }
    } 
    XCloseDisplay (display_);
}


