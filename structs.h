#ifndef UNTITLED_STRUCTS_H
#define UNTITLED_STRUCTS_H
#endif //UNTITLED_STRUCTS_H

#include <vector>

using  std::vector;

struct point
{
    int x;
    int y;
    static point getPoint(int, int);
};

struct buffer
{
    char** data;
    buffer();
    void plot(int, int, char) const;
    void line(point, point) const;
    void triangle(point, point, point) const;
    void render() const;
    void clear() const;
    void drawLines(vector<vector<int>>) const;
    void clear_till(int) const;
    void result(int);
    ~buffer();
};