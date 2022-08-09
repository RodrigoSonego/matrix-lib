#include <iostream>

struct Vector2
{
	float x;
	float y;
	Vector2() {}
	Vector2(float x, float y) {}
	Vector2(int _x, int _y) {
		this->x = (float) _x;
		this->y = (float) _y;
	}
};

struct Vector3
{
	float x;
	float y;
};

struct Mat2x2
{
	int xs[2];
	int ys[2];
};

struct Mat3x3
{
	int xs[3];
	int ys[3];
	int zs[3];
};

struct Mat4x4
{
	int xs[4];
	int ys[4];
	int zs[4];
	int ws[4];
};

#define COLS  90
#define LINES 30

void render(Vector2 p0, Vector2 p1)
{
	for (int y = 0; y < LINES; ++y) {
		int p0y = (int) p0.y;
		int p1y = (int) p1.y;

		for (int x = 0; x < COLS; ++x) {
			int p0x = (int) p0.x;
			int p1x = (int) p1.x;
			
			if (p0y == y && p0x == x) {
				std::cout << "0";
			} else if (p1y == y && p1x == x) {
				std::cout << "1";
			} else {
				std::cout << ".";
			}

		}
		std::cout << "\n";
	}

}

void printvec2(Vector2 vec) {
	std::cout << "X: " << vec.x << " Y:" << vec.y << "\n";
}

float dist(Vector2 p0, Vector2 p1)
{
	float dist;
	Vector2 vec;
	vec.x = p1.x - p0.x;
	vec.y = p1.y - p0.y;

	printvec2(p0);
	printvec2(p1);
	printvec2(vec);

	return dist;
}

int main(int, char**)
{
	Vector2 vec;
	vec.x = 10.0f;
	vec.y = 10.0f;

	Vector2 vec2;

	vec2.x = 12.0f;
	vec2.y = 10.0f;

	// std::cout << "vetao: x: " << vec.x << " y: " << vec.y << "\n";
	render(vec, vec2);

	dist(vec, vec2);
}


