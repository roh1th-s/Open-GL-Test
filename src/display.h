#ifndef DISPLAY_H
#define DISPLAY_H

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <string>

class Display
{
public:
    Display(int width, int height, const std::string &title);

    void Clear(float r, float g, float b, float a);
    bool IsClosed();
    void Update();

    virtual ~Display();

protected:
private:
    Display(const Display &other) {}
    void operator=(const Display &rhs) {}

    SDL_Window *m_window;
    SDL_GLContext m_glContext;
    bool m_isClosed;
};

#endif // DISPLAY_H
