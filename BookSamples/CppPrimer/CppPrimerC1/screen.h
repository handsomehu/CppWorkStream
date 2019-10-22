#ifndef SCREEN_H
#define SCREEN_H
#include <string>
#include <vector>
class Screen {
public:
typedef std::string::size_type pos;
    Screen() = default; //
    Screen(pos ht, pos wd, char c): height(ht), width(wd),
    contents(ht * wd, c) { }
    char get() const // get the character at the cursor
    { return contents[cursor]; }
    inline char get(pos ht, pos wd) const;
    Screen &move(pos r, pos c);
    void some_member() const;
    Screen &set(char);
    Screen &set(pos, pos, char);
    Screen &display(std::ostream &os)
    { do_display(os); return *this; }
    const Screen &display(std::ostream &os) const
    { do_display(os); return *this; }
private:
    pos cursor = 0;
    pos height = 0, width = 0;
    std::string contents;
    mutable std::size_t access_ctr; // may change even in a const object
    // other members as before
    void do_display(std::ostream &os) const {os <<
    contents;}
};
class Window_mgr {
private:
// Screens this Window_mgr is tracking
// by default, a Window_mgr has one standard sized blank Screen
std::vector<Screen> screens{Screen(24, 80, ' ') };
};

#endif // SCREEN_H
