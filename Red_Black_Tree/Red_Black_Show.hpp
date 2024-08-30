#include <queue>
#include <vector>
#include <string>
#include <cstring>
#include <sstream>
#include <iostream>

class Canvas
{
public:
    static const int HEIGHT = 20;
    static const int WIDTH = 90;
    static char buffer[HEIGHT][WIDTH + 1];

    static void draw()
    {
        std::cout << std::endl;
        for (int i = 0; i < HEIGHT; i++)
        {
            buffer[i][WIDTH] = '\0';
            std::cout << buffer[i] << std::endl;
        }
        std::cout << std::endl;
    }

    static void put(int r, int c, const std::string &s)
    {
        int len = s.length();
        int idx = 0;
        for (int i = c; (i < WIDTH) && (idx < len); i++)
            buffer[r][i] = s[idx++];
    }
    static void put(int r, int c, char ch, int num)
    {
        while (num > 0 && c < WIDTH)
            buffer[r][c++] = ch, num--;
    }

    static void resetBuffer()
    {
        for (int i = 0; i < HEIGHT; i++)
            memset(buffer[i], ' ', WIDTH);
    }
};