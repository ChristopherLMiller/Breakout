#include "Block.h"

Block::Block() {
	x = 10;
	y = 10;
	width = 10;
	height = 10;
}

Block::Block(int x, int y, int width, int height) {
	x = x;
	y = y;
	width = width;
}

Block::~Block() {
	// TODO: release the texture resource
}

int Block::getX() {
	return x;
}

int Block::getY() {
	return y;
}

int Block::getWidth() {
	return width;
}

int Block::getHeight() {
	return height;
}

void Block::setX(int x) {
	x = x;
}

void Block::setY(int y) {
	y = y;
}

void Block::setWidth(int width) {
	width = width;
}

void Block::setHeight(int height) {
	height = height;
}