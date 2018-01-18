// ast_move.h
// Horacio Lopez and Yifan Yu
// This is the header file that contains the classes for the movement of asteroids.

class Asteroid {
	public:
		Asteroid(int xcoord, int ycoord, int radius, int deltat);
		~Asteroid();
		void display();
		void travel(int wd, int ht);
		void didHit(int x1, int y1);
		bool didHitShip(int x1, int y1);
		void split();
		void destroy();
		int countAst(int number);
		double getXC();
		double getYC();
		int getR();
	private:
		int red, green, blue;
		int dt;
		double xc;
		double yc;
		int r;
		int angle;
		double dx;
		double dy;
};
