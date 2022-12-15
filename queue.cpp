#include"queue.h"

Queue::~Queue() {
	while (lpar* current = head) {
		head = head->next;
		delete current;
	}
}
Queue::Queue(long capacity) { this->capacity = capacity; }

bool Queue::add(LPARAM st, bool type, WPARAM wt) {
	if (capacity > size) {
		size++;
		if (head) rear = rear->next = new lpar;
		else rear = head = new lpar;
		setflags(rear, type, st, wt);
		return true;
	} return false;
}
lpar Queue::pop() {
	if (size) {
		size--;
		lpar* curr = head;
		lpar ci = *curr;
		head = head->next;
		delete curr;
		return ci;
	}
}
long Queue::getSize() { return size; }
lpar* Queue::getHead() { return head; }
void Queue::calcTime() {
	lpar* r = head;
	while (r && r->next) {
		r->next->tim = r->next->ctim - r->ctim;
		if (!r->ty) {
			r->next->x = r->next->lc.mi.dx - r->lc.mi.dx;
			r->next->y = r->next->lc.mi.dy - r->lc.mi.dy;
		}
		r = r->next;
	}
	
}

void Queue::print() {
	lpar* r = head;
	while (r) {
		if (r->ty) cout << r->lc.ki.wScan << endl;
		else cout << r->lc.mi.dx << endl;
		r = r->next;
	}
}

Queue::Queue(const Queue& queue) {
	if (queue.head) {
		size = queue.size;
		capacity = queue.capacity;
		lpar* queueCurrent = queue.head, * current;
		head = current = queueCurrent->copy();
		while (queueCurrent = queueCurrent->next) current = current->next = queueCurrent->copy();
		rear = current;
	}
}

void spinLock(int milliseconds) {
	auto start = high_resolution_clock::now();
	while ((high_resolution_clock::now() - start).count() / 1e6 < milliseconds);
}
void KillablePlayer::playback(Queue* queue) {
		Queue q = *queue;
		do {
			lpar* current = q.getHead();
			while (!dead && current) {
				if (!current->ty) {
					if (MOUSE_ABSOLUTE) {
						current->lc.mi.dx = (current->ax + 1) * ABSX;
						current->lc.mi.dy = (current->ay + 1) * ABSY;
					}
					else {
						current->lc.mi.dx = current->x;
						current->lc.mi.dy = current->y;
					}
					//consoleText += to_string(current->lc.mi.dx) + ' ' + to_string(current->lc.mi.dx) + '\n';
				}
				if (!CONSTANT_TIME)spinLock(current->tim);
				else spinLock(CONSTANT_TIME_MSDELAY);
				SendInput(1, &current->lc, sizeof(INPUT));
				//consoleText += "Message Excuted!\n";
				current = current->next;
			}
		} while (REPEAT && !dead);
	}

void KillablePlayer::kill() {
	dead = true;
}

KillablePlayer::KillablePlayer(Queue* queue) {
	thread(&KillablePlayer::playback, this, queue).detach();
}

void setflags(lpar* gm, bool type, LPARAM st, WPARAM wt) {
	if (type) {
		KBDLLHOOKSTRUCT ckey = *((KBDLLHOOKSTRUCT*)st);
		gm->lc.ki.dwFlags = (ckey.flags >> 7) << 1 | KEYEVENTF_SCANCODE | (wt == 257) << 1;
		gm->lc.ki.dwExtraInfo = ckey.dwExtraInfo;
		gm->lc.ki.wScan = ckey.scanCode;
		gm->lc.type = type;
	}
	else {
		MSLLHOOKSTRUCT cbut = *((MSLLHOOKSTRUCT*)st);
		switch (wt) {
		case 512:
			gm->lc.mi.dwFlags = (MOUSE_ABSOLUTE * MOUSEEVENTF_ABSOLUTE) | MOUSEEVENTF_MOVE;
			break;
		case 513:
			gm->lc.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
			break;
		case 514:
			gm->lc.mi.dwFlags = MOUSEEVENTF_LEFTUP;
			break;
		case 516:
			gm->lc.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
			break;
		case 517:
			gm->lc.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
			break;
		case 519:
			gm->lc.mi.dwFlags = MOUSEEVENTF_MIDDLEDOWN;
			break;
		case 520:
			gm->lc.mi.dwFlags = MOUSEEVENTF_MIDDLEUP;
			break;
		case 523:
			gm->lc.mi.dwFlags = MOUSEEVENTF_MIDDLEDOWN;
			break;
		case 524:
			gm->lc.mi.dwFlags = MOUSEEVENTF_MIDDLEUP;
			break;
		case 522:
			gm->lc.mi.dwFlags = MOUSEEVENTF_WHEEL;
			break;
		}
		gm->lc.mi.mouseData = cbut.mouseData;
		gm->ax = cbut.pt.x;
		gm->ay = cbut.pt.y;
		gm->lc.type = type;
	}
	gm->ty = type;
	gm->ctim = GetTickCount64();
}