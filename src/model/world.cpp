#include "world.h"
#include "../common/common.h"

World::World(const World &world) {
	this->board = world.board;
	this->player = world.player;
}

World::World(std::shared_ptr<Observer> observer, int length_board) {
	observers.insert(observer);
	board = Matrix(length_board, length_board);
	player = Player(0, 0);
	board(length_board - 1, length_board - 1);
}

void World::movePlayer(Direction direction) {
	(*player).move(board, direction);
}

void World::moveEntities() {
	for (Matrix::iterator1 it = board.begin1(); it != board.end1(); ++it) {
		(*it).get()->move(board);
	}
}

bool World::gameOver() {
	return board((*player).getX(), (*player).getY()) != nullptr;
}

void World::notifyAll() {
	for (std::shared_ptr<Observer> o: observers) {
		(*o).update(player, board);
	}
}

void World::addObserver(std::shared_ptr<Observer> observer) {
	observers.insert(observer);
}
