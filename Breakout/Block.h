#ifndef __BLOCK_H
#define __BLOCK_H

class Block
{
private:
	int x, y;	// x and y coordinate of the block
	int width, height;	// width and height of the block
	// TODO: texture

public:
	// constructors/desctructor
	Block();
	Block(int x, int y, int width, int height);
	~Block();

	// getter methods
	int getX();
	int getY();
	int getWidth();
	int getHeight();
	
	// setter methods
	void setX(int x);
	void setY(int y);
	void setWidth(int width);
	void setHeight(int height);
};

#endif