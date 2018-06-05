class HanoiPiece {
public:

	class Color {
	public:
		Color();
		Color(float r, float g, float b);
		float getR();
		float getG();
		float getB();

	private:
		float r, g, b;
	};


	HanoiPiece(int n, float r, Color* c);
	~HanoiPiece();
	float getR();
	int getN();
	void Draw(GLuint texturID[NUM_MAX_TEXTURES]);
	static void DrawPiece(float radius, Color* color, GLuint texturID[NUM_MAX_TEXTURES]);

private:
	float r;
	Color* color;
	int n;
};