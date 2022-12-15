#include "GlobalVars.h"

struct lpar {
	INPUT lc = { 0 };
	lpar* next = nullptr;
	DWORD tim = 0;
	DWORD ctim = 0;
	bool ty = 0;
	int x=0, y=0, ax=0, ay=0;
	lpar operator= (lpar& other) {
		lc = other.lc;
		next = other.next;
		tim = other.tim;
		ctim = other.ctim;
		ty = other.ty;
		x = other.x;
		y = other.y;
		ax = other.ax;
		ay = other.ay;
		return *this;
	}
	lpar operator= (lpar *other) {
		lc = other->lc;
		next = other->next;
		tim = other->tim;
		ctim = other->ctim;
		ty = other->ty;
		x = other->x;
		y = other->y;
		ax = other->ax;
		ay = other->ay;
		return *this;
	}
	lpar* copy() {
		lpar* result = new lpar;
		result->lc = lc;
		result->next = next;
		result->tim = tim;
		result->ctim = ctim;
		result->ty = ty;
		result->x = x;
		result->y = y;
		result->ax = ax;
		result->ay = ay;
		return result;
	}
};

class Queue
{
private:
	lpar* head = nullptr;
	lpar* rear = nullptr;
	long size = 0;
	long capacity = 0;
public:
	Queue(long);
	~Queue();
	bool add(LPARAM, bool, WPARAM=0);
	lpar pop();
	long getSize();
	lpar* getHead();
	void calcTime();
	void print();
	Queue(const Queue&);
};

void setflags(lpar*, bool, LPARAM, WPARAM);
class KillablePlayer {
	bool dead=false;
public:
	void kill();
	KillablePlayer(Queue*);
	void playback(Queue* queue);
};