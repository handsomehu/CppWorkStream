#include "screen.h"

inline // we can specify inline on the definition
Screen &Screen::move(pos r, pos c)
{
    pos row = r * width; // compute the row location
    cursor = row + c ; // move cursor to the column within that row
    return *this; // return this object as an lvalue
}
char Screen::get(pos r, pos c) const
// declared as inline in the class
{
    pos row = r * width; // compute row location
    return contents[row + c]; // return character at the given column
}

void Screen::some_member() const
{
    ++access_ctr; // keep a count of the calls to any member function
// whatever other work this member needs to do
}
inline Screen &Screen::set(char c)
{
    contents[cursor] = c; // set the new value at the current cursor location
    return *this; // return this object as an lvalue
}
inline Screen &Screen::set(pos r, pos col, char ch)
{
    contents[r*width + col] = ch; // set specified location to given value
    return *this; // return this object as an lvalue
}

void Window_mgr::clear(ScreenIndex i)
{
// s is a reference to the Screen we want to clear
Screen &s = screens[i];
// reset the contents of that Screen to all blanks
s.contents = std::string(s.height * s.width, ' ');
}

// return type is seen before we're in the scope of Window_mgr
Window_mgr::ScreenIndex Window_mgr::addScreen(const Screen &s)
{
    screens.push_back(s);
    return screens.size() - 1;
}
