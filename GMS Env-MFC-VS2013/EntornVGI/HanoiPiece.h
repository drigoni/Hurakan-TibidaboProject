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
	void Draw();
	static void DrawPiece(float radius, Color* color);

private:
	float r;
	Color* color;
	int n;
};