#include <iostream>
#include <chrono>
#include <thread>

struct point
{
	int x;
	int y;
};

struct buffer
{
private:
	char** data;
	int width;
	int height;
public:
	buffer(const int, const int);
	void plot(const int, const int, const char);
	void line(const point, const point);
	void render();
	void clear();
	void out_of_bond();
	~buffer();
};

buffer::buffer(const int W, const int H)
{
	this->width = W;
	this->height = H;

	this->data = new char* [H];
	for (int i = 0; i < H; ++i)
		this->data[i] = new char[W];

	clear();
}

void buffer::plot(const int x, const int y, const char c)
{
	data[y][x] = c;
}

void buffer::line(const point start, const point end)
{
	int deltax = end.x - start.x;
	int deltay = end.y - start.y;
	double delta_error = end.y;
	if (delta_error < 0) delta_error = -delta_error;
	double error = 0;
	int y = start.y;
	if (deltax != 0) {
		delta_error = (double)deltay / deltax;
		for (int x = start.x; x <= end.x; ++x)
		{
			plot(x, y, '#');
			error += delta_error;
			if (error >= 0.5)
			{
				if (deltay > 0) ++y;
				else --y;
				--error;
			}
		}
	}
	else {
		for (int y1 = start.y; y1 < end.y; ++y1)
			plot(start.x, y1, '#');
	}
	
}

void buffer::render()
{
	for (int i = 0; i < this->height; ++i)
	{
		for (int j = 0; j < this->width; ++j)
		{
			std::cout << this->data[i][j];
		}
		std::cout << std::endl;
	}
}

buffer::~buffer()
{
	for (int i = 0; i < this->height; ++i)
		delete[] this->data[i];
	delete[] this->data;
}

void buffer::clear()
{
	for (int i = 0; i < this->height; ++i)
	{
		for (int j = 0; j < this->width; ++j)
		{
			this->data[i][j] = ' ';
		}
	}
}

void buffer::out_of_bond() {
	//
}

int main()
{
	buffer screen(20, 20);
	screen.line({ 0, 0 }, { 0, 3 });
	screen.render();
	
	/*bool right = false;
	while (true)
	{
		screen.clear();
		if (right)
		{
			screen.line({ 0,0 }, { 15,15 });
			right = false;
		}
		else
		{
			screen.line({ 0,0 }, { 15,0 });
			right = true;
		}
		screen.render();
		using namespace std::this_thread;
		using namespace std::chrono_literals;
		using std::chrono::system_clock;
		sleep_for(1s);
		system("cls");
	}*/
}