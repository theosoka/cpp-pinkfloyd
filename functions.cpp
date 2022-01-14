#include <iostream>
#include <windows.h>
#include <unordered_map>
#include "structs.h"

#define HEIGHT 30
#define WIDTH  110



// min X and max X for every horizontal line within the triangle
int end = 1, start = 0;

char randChar()
{
    int val = rand() % 93 + 33;
    return val;
}

buffer::buffer()
{
    this->data = new char *[HEIGHT];
    for (int i = 0; i < HEIGHT; ++i)
    {
        this->data[i] = new char[WIDTH];
        for (int j = 0; j < WIDTH; ++j)
            data[i][j] = ' ';
    }
    clear();
}

void buffer::plot(const int x, const int y, const char c) const
{
    if ((x < 0) || (x >= WIDTH) || (y < 0) || (y >= HEIGHT)) return; //  invalid arguments
    data[y][x] = c;
}

void buffer::render() const
{
    std::unordered_map<int, int> COLOURS = { {17, 4}, {18, 12},{19, 14},{20, 6},{21, 10},
                                             {22, 2},{23, 3},{24, 11},{25, 9} };
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    char **p = data;

    for (int y = 0; y < HEIGHT; y++)
    {
        SetConsoleTextAttribute(hConsole, 15);
        for (int x = 0; x < WIDTH; x++)
        {
                printf("%c", *(*(p + y) + x));
                if (x > 58 && x - y > 48) 
                {
                    SetConsoleTextAttribute(hConsole, COLOURS[y]);
                }
            
        }
                std::cout << std::endl;
    }
}

void buffer::line(const point p1, const point p2) const
{
    int sx, sy, dx1, dy1, dx2, dy2, x, y, m, n, k, cnt;
    sx = p2.x - p1.x;
    sy = p2.y - p1.y;
    dy1 = (sy > 0) ? 1 : (sy < 0) ? -1 : 0;
    dx1 = (sx > 0) ? 1 : (sx < 0) ? -1 : 0;
    m = abs(sx);
    n = abs(sy);
    dx2 = dx1;
    dy2 = 0;

    if (m < n)
    {
        m = abs(sy);
        n = abs(sx);
        dx2 = 0;
        dy2 = dy1;
    }

    x = p1.x;
    y = p1.y;
    cnt = m + 1;
    k = n / 2;

    while (cnt--)
    {
        plot(x, y, randChar());
        k += n;
        if (k < m)
        {
            x += dx2;
            y += dy2;
        } else
        {
            k -= m;
            x += dx1;
            y += dy1;
        }
    }
}

void buffer::triangle(const point p1, const point p2, const point p3) const
{
    int y;
    line(p1, p2);
    line(p2, p3);
    line(p3, p1);
}

buffer::~buffer()
{
    for (int i = 0; i < HEIGHT; ++i)
        delete[] this->data[i];
    delete[] this->data;
}

void buffer::clear() const
{
    for (int i = 0; i < HEIGHT; ++i)
    {
        for (int j = 0; j < WIDTH; ++j)
        {
            this->data[i][j] = ' ';
        }
    }
}

void buffer::clear_till(int x) const
{
   if (x > WIDTH)
   {
       end = 1;
       start = 0;
   }

    for (int i = start; i < end; i ++)
    {
        for (int j = 0; j < HEIGHT; j++)
            this->data[j][i] = ' ';
    }
    end += 3;
    start += end < 50 ? 0 : 5;
}

void buffer::drawLines(vector<vector<int>> args) const
{
    for (auto & arg : args)
    {
        point p1 = {arg[0],arg[1]}, p2={arg[2],arg[3]};
        line(p1, p2);
    }
}

void buffer::result(int i) {
    vector<vector<int>> LINES{ {1,  23, 46,  17},
                             {1,  23, 46,  18},
                             {66, 17, 110, 25},
                             {66, 18, 110, 24},
                             {66, 18, 110, 22},
                             {66, 18, 110, 23},
                             {64, 17, 110, 22},
                             {64, 17, 110, 21},
                             {64, 18, 110, 26},
    };
    vector<vector<int>> IN_LINES{ {48, 17, 64, 17},
                                 {48, 18, 64, 18} };
    drawLines(LINES);
    drawLines(IN_LINES);
    clear_till(i);
    triangle(point::getPoint(40, 25), point::getPoint(74, 25), point::getPoint(56, 11));
    render();
}

point point::getPoint(int x, int y)
{
    point p = {x, y};
    return p;
}
