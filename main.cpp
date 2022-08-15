#include <iostream>
#include <memory>
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
private:
	int mat[4][4] = {
		{ 1, 0, 0, 0, },
		{ 0, 1, 0, 0, },
		{ 0, 0, 1, 0, },
		{ 0, 0, 0, 1  }
	};

public:
	void setRow(int xInd, int row0, int row1, int row2, int row3) {
		mat[xInd][0] = row0;
		mat[xInd][1] = row1;
		mat[xInd][2] = row2;
		mat[xInd][3] = row3;
	}

	void set(int xInd, int yInd, int value) {
		mat[xInd][yInd] = value;
	}

	int get(int xInd, int yInd) const {
		return mat[xInd][yInd];
	}

	void print() const {
		for (int x = 0; x < 4; ++x)
		{
			for (int y = 0; y < 4; ++y)
			{
				int curr = mat[x][y];
				if (curr < 10) std::cout << "0";
				std::cout << mat[x][y] << " ";
			}
			std::cout << "\n";
		}
	}
};

#define COLS  90
#define LINES 30

#define SIZE 4

void render(const Vector2 &p0, const Vector2 &p1, const Vector2 &q0, const Vector2 &q1)
{
	std::cout << "segmento de reta A: vai de 'a' ate 'A', segmento de reta B: vai de 'b' ate 'B' \n";
	for (int y = 0; y < LINES; ++y) {
		int p0y = (int) p0.y;
		int p1y = (int) p1.y;

		int q0y = (int) q0.y;
		int q1y = (int) q1.y;

		for (int x = 0; x < COLS; ++x) {
			int p0x = (int) p0.x;
			int p1x = (int) p1.x;
			
			int q0x = (int) q0.x;
			int q1x = (int) q1.x;

			if (p0y == y && p0x == x) {
				std::cout << "a";
			} else if (p1y == y && p1x == x) {
				std::cout << "A";
			} else if (q0y == y && q0x == x) {
				std::cout << "b";
			} else if (q1y == y && q1x == x) {
				std::cout << "B";
			} else {
				std::cout << ".";
			}

		}
		std::cout << "\n";
	}

}

void printvec(const Vector2 vec) {
	std::cout << "X: " << vec.x << " Y:" << vec.y << "\n";
}

float dist(const Vector2 p0, const Vector2 p1)
{
	float dist;
	Vector2 vec;
	vec.x = p1.x - p0.x;
	vec.y = p1.y - p0.y;

	std::cout << "a: ";
	printvec(p0);
	std::cout << "b: ";
	printvec(p1);

	dist = sqrt(pow(vec.x, 2) + pow(vec.y, 2));

	return dist;
}


// Mat4x4& mul()
std::unique_ptr<Mat4x4> mul(const Mat4x4 &matA, const Mat4x4 &matB)
{
	std::unique_ptr<Mat4x4> output = std::make_unique<Mat4x4>();
	int x, y, z;
	
	for (y = 0; y < SIZE; ++y) 
	{
		for (x = 0; x < SIZE; ++x) 
		{
			output->set(y, x, 0);

			for (z = 0; z < SIZE; ++z)
			{
				int current = output->get(y, x);
				output->set(y, x, current + matA.get(y, z) * matB.get(z, x));
			}
		}
	}

	return output;
}




// 0 --> Collinear
// 1 --> Clockwise
// 2 --> Counterclockwise
int isClockwise(Vector2 p1, Vector2 p2, Vector2 pr)
{
	int val = (p2.y - p1.y) * (pr.x - p2.x) -
			  (p2.x - p1.x) * (pr.y - p2.y);

	if (val == 0) return 0;  // collinear

	return (val > 0)? 1 : 2;
}

bool isOnSegment(Vector2 p1, Vector2 p2, Vector2 pr)
{
		if (p2.x <= std::max(p1.x, pr.x) && p2.x >= std::min(p1.x, pr.x) &&
			p2.y <= std::max(p1.y, pr.y) && p2.y >= std::min(p1.y, pr.y))
		return true;
  
	return false;
}

bool hasIntersection(const Vector2 p1, const Vector2 q1, const Vector2 p2, const Vector2 q2)
{
	int o1 = isClockwise(p1, q1, p2);
	int o2 = isClockwise(p1, q1, q2);
	int o3 = isClockwise(p2, q2, p1);
	int o4 = isClockwise(p2, q2, q1);

	if (o1 != o2 && o3 != o4) { 
		return true;
	}

	// Collinear Cases
	if (o1 == 0 && isOnSegment(p1, q1, p2)) { return true; }
  
	if (o2 == 0 && isOnSegment(p1, q2, p2)) { return true; }
  
	if (o3 == 0 && isOnSegment(q1, p1, q2)) { return true; }
  
	if (o4 == 0 && isOnSegment(q1, p2, q2)) { return true; }
  
	return false; // Doesn't fall in any of the above cases
}

int main(void)
{
	std::cout << "\n\n ----------------Vetores----------------- \n\n";
	Vector2 vec1;
	vec1.x = 10.0f;
	vec1.y = 10.0f;

	Vector2 vec2;
	vec2.x = 12.0f;
	vec2.y = 12.0f;

	Vector2 vec3;
	vec3.x = 9.0f;
	vec3.y = 13.0f;

	Vector2 vec4;
	vec4.x = 13.0f;
	vec4.y = 15.0f;

	render(vec1, vec2, vec3, vec4);

	const float distancia = dist(vec1, vec2);
	std::cout << "Distancia entre 'a' e 'b': " << distancia;
	   
    std::cout << "\n\n";
    
    bool intersect = hasIntersection(vec1, vec2, vec3, vec4);
    std::cout << "Retas a->A b->B " << (intersect ? "se intersectam" : "nao se intersectam");



	std::cout << "\n\n --------Multiplicacao de matriz-------- \n\n";

	Mat4x4 A;
	A.setRow(0,      1, 2, 3, 4);
	A.setRow(1,      5, 6, 7, 8);
	A.setRow(2,      9, 10, 11, 12);
	A.setRow(3,      13, 14, 15, 16);
	
	Mat4x4 B; // matriz padrão é a matriz de identidade

	std::unique_ptr<Mat4x4> C = mul(A, B);

	A.print();
	std::cout << "x\n";
	B.print();
	std::cout << "=\n";
	C->print();
}