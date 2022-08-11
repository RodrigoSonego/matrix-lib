#include <iostream>
#include <math.h>

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

#define SIZE 4

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

    dist = sqrt(pow(vec.x, 2) + pow(vec.y, 2));

	return dist;
}

void imprimeMatriz(const int (&mat)[SIZE][SIZE])
{
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            std::cout << mat[i][j] << " ";
        }
        std::cout << "\n";
    }
}

void mul(const int (&matA)[SIZE][SIZE], const int (&matB)[SIZE][SIZE], int (&matOut)[SIZE][SIZE])
{
    int x, y, z;
    for (y = 0; y < SIZE; ++y) 
    {
        for (x = 0; x < SIZE; ++x) 
        {
            matOut[y][x] = 0;

            for (z = 0; z < SIZE; ++z)
            {
                matOut[y][x] += matA[y][z] * matB[z][x];
            }    
        }
    }
}

int main(int, char**)
{
	Vector2 vec;
	vec.x = 10.0f;
	vec.y = 10.0f;

	Vector2 vec2;

	vec2.x = 12.0f;
	vec2.y = 12.0f;

	std::cout << "Distancia dos vetao: \n";
	//render(vec, vec2);

	const float distancia = dist(vec, vec2);
    
    std::cout << "Distancia: " << distancia;

    std::cout << "\n\n --------Multiplicacao de matriz-------- \n\n";

    int A[4][4] = {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };
 
    int B[4][4] = {
        1,   2,  3,  4,
        5,   6,  7,  8,
        9,  10, 11, 12,
        13, 14, 15, 16
    };
 
    int C[4][4];

    mul(A,B,C);

    imprimeMatriz(C);
}


