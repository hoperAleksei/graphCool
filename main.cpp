#include <iostream>

#define UNMARK 0
#define MARKUNPASSED 1

#define PASSED 2
#define UNPASSED 3


/*
 *
 * 1	Конструктор
 * 2	Деструкор
 * 3	Добавление вершины
 * 4	Добавление дуги
 * 5	Удаление вершины
 * 6	Удаление дуги
 * 7	Поиск вершины
 * 8	Поиск дуги
 * 9	Печать графа
 *
 * 10	Обход
 *
 * 11	Алгоритм 3.4
 *
 * */

class vertex;
class edge{
private:
	vertex * ver;
	edge * next;
	edge * prev;
public:
//	int state;
//	vertex * link = nullptr;
	
	edge(vertex * ver, edge * next, edge * prev) {
		this->ver = ver;
		this->next = next;
		this->prev = prev;
	}
	
	~edge() {
		if (this->prev != nullptr) {
			prev->next = this->next;
		}
		if (this->next != nullptr) {
			this->next->prev = this->prev;
		}
		this->ver = nullptr;
		this->next = nullptr;
		this->prev = nullptr;
	}

	edge() = default;

	edge * getNext(){
		return next;
	}

	void setNext(edge * next){
		this->next = next;
	}

	edge * getPrev(){
		return this->prev;
	}

	void setPrev(edge * prev){
		this->prev = prev;
	}
	
	vertex * getVer(){
		return this->ver;
	}


};


class vertex{
private:
	vertex * next;
	vertex * prev;
	int index;
	int color = 0;
public:
	edge * ed;
	
//	int state;
//	vertex * link = nullptr;
	
	
	vertex(vertex * next, vertex * prev, int index){
		this->next = next;
		this->prev = prev;
		this->index = index;
		this->ed = nullptr;
	}
	
	int getInd() {
		int res = 0;
		vertex * c = this;
		while (c != nullptr){
			res += 1;
			c = c->prev;
		}
		
	}
	
	void setColor(int c) {
		this->color = c;
	}
	
	int getColor() {
		return this->color;
	}
	
	int getMinColor() {
		getMinColor(1);
	}
	
	int getMinColor(int c) {
		edge * cur = this->ed;
		
		if (cur == nullptr) {
			return 1;
		}
		int res = c;
		bool ind = true;
		while (ind) {
			cur = this->ed;
			while (cur != nullptr) {
				if (res == cur->getVer()->getColor()){
					break;
				}
				else if (cur->getNext() == nullptr) {
					ind = false;
					break;
				}
				cur = cur->getNext();
			}
			if (ind) {
				res += 1;
			}
		}
		
		return res;
		
	}
	
	bool testColor(int c) {
		edge * cur = this->ed;
		while (cur != nullptr) {
			if (cur->getVer()->getColor() == c){
				return false;
			}
			cur = cur->getNext();
		}
		return true;
	}
	
	
	
	~vertex() {
		if (this->ed != nullptr) {
			while (this->ed->getNext() != nullptr) {
				this->ed->getNext()->getVer()->removeEd(this->index);
				delete this->ed->getNext();
			}
			this->ed->getVer()->removeEd(this->index);
			delete this->ed;
			this-> ed = nullptr;
		}
		if (this->prev != nullptr) {
			this->prev->next = this->next;
			
		}
		if (this->next != nullptr) {
			this->next->prev = this->prev;
		}
		
		this->next = nullptr;
		this->prev = nullptr;
	}

	vertex * getNext(){
		return this->next;
	}

	void setNext(vertex * next){
		this->next = next;
	}
	vertex * getPrev(){
		return this->prev;
	}

	void setPrev(vertex * prev){
		this->next = prev;
	}

	int getIndex(){
		return this->index;
	}
	
	vertex * findEd(int ind){
		if (this->ed == nullptr) {
			return nullptr;
		}
		edge * cur = ed;
		while (cur != nullptr){
			if (cur->getVer()->getIndex() == ind){
				return cur->getVer();
			}
			cur = cur->getNext();
		}
		return nullptr;
	}

	void addToEd(vertex * ver){
		if (this->ed == nullptr){
			this->ed = new edge(ver, nullptr, nullptr);
		}
		else {
			if (findEd(ver->getIndex()) != nullptr)
			{
				std::cout << "ERROR: INDEX ALREADY IN EDGES" << std::endl;
				return;
			}
			edge * cur = this->ed;
			while (cur->getNext() != nullptr)
			{
				cur = cur->getNext();
			}

			cur->setNext(new edge(ver, nullptr, cur));
		}
	}
	
	void removeEd(int ind){
		if (findEd(ind) == nullptr){
			std::cout << "ERROR: INDEX NOT IN EDGES" << std::endl;
			return;
		}
		edge * cur = this->ed;
		while (cur != nullptr)
		{
			if (cur->getVer()->getIndex() == ind){
				if (cur->getPrev() == nullptr) {
					this->ed = this->ed->getNext();
				}
				delete cur;
				return;
			}
			cur = cur->getNext();
		}
		
	}

	void print(){
		std::cout << "(" << this->index << " [" <<this->color << "]) => ";
		edge * cur = this->ed;
		while (cur != nullptr) {
			std::cout << cur->getVer()->getIndex() << "[" << cur->getVer()->getColor() << "] ";
			cur = cur->getNext();
		}
		std::cout << std::endl;
	}


};




class graph {
private:
	vertex * head;
public:
	graph(){
		this->head = nullptr;
	}
	
	~graph() {
		while (this->head != nullptr) {
			removeVer(head->getIndex());
		}
		delete this->head;
		this->head = nullptr;
	}

	vertex * findVer(int ind){
		vertex * cur = head;
		while (cur != nullptr) {
			if (cur->getIndex() == ind){
				return cur;
			}
			cur = cur->getNext();
		}
		return nullptr;
	}

	void addVer(int ind) {
		if (this->head == nullptr) {
			this->head = new vertex(nullptr, nullptr, ind);
		}
		else {
			if (findVer(ind) != nullptr){
				std::cout << "ERROR: INDEX ALREADY IN GRAPH" << std::endl;
				return;
			}
			vertex * cur = head;
			while (cur->getNext() != nullptr){
				cur = cur->getNext();
			}

			cur->setNext(new vertex(nullptr, cur, ind));
		}
	}
	
	void removeVer(int ind) {
		if (this->head == nullptr) {
			std::cout << "ERROR: GRAPH IS EMPTY" << std::endl;
			return;
		}
		vertex * cur = findVer(ind);
		if (cur == nullptr){
			std::cout << "ERROR: INDEX NOT IN GRAPH" << std::endl;
			return;
		}
		if (cur->getPrev() == nullptr){
			this->head = cur->getNext();
		}
		delete cur;
	}
	
	void addEdge(int indOne, int indTwo) {
		vertex * one = findVer(indOne);
		vertex * two = findVer(indTwo);
		if (one == nullptr || two == nullptr) {
			std::cout << "ERROR: INDEX NOT IN GRAPH" << std::endl;
			return;
		}
		one->addToEd(two);
		two->addToEd(one);
	}
	
	void removeEdge(int indOne, int indTwo) {
		vertex * one = findVer(indOne);
		vertex * two = findVer(indTwo);
		if (one == nullptr || two == nullptr) {
			std::cout << "ERROR: INDEX NOT IN GRAPH" << std::endl;
			return;
		}
		if (one->findEd(indTwo) == nullptr) {
			std::cout << "ERROR: VERTEXES ARE NOT CONNECTED IN GRAPH" << std::endl;
			return;
		}
		one->removeEd(indTwo);
		two->removeEd(indOne);
	}
	
	bool findEdge(int indOne, int indTwo){
		vertex * one = findVer(indOne);
		vertex * two = findVer(indTwo);
		if (one == nullptr || two == nullptr) {
			std::cout << "ERROR: INDEX NOT IN GRAPH" << std::endl;
			return false;
		}
		if (one->findEd(indTwo) == nullptr) {
			return false;
		}
		return true;
	}
	
	void print(){
		vertex * cur = this->head;
		if (cur == nullptr) {
			std::cout << "NULLPTR" << std::endl;
			return;
		}
		while (cur != nullptr) {
			cur->print();
			cur = cur->getNext();
		}
	}
	/*
	void pass(vertex * v) {
		v->state = PASSED;
	}
	
	void mark(vertex * v) {
		std::cout << v->getIndex() << "->";
		v->state = MARKUNPASSED;
	}
	
	void pass(edge * e) {
		e->state = PASSED;
	}
	
	void traversal(int ind) {
		vertex *p0 = findVer(ind);
		if (p0 == nullptr) {
			std::cout << "ERROR: INDEX NOT IN GRAPH" << std::endl;
			return;
		}

//		начало говнокода
		;
		vertex *c = head;
		while (c != nullptr) {
			c->state = UNMARK;
			edge * cc = c->ed;
			while (cc != nullptr) {
				cc->state = UNPASSED;
				cc = cc->getNext();
			}
			c = c->getNext();
		}
		
		vertex * f = p0;
		vertex * v = p0;
		mark(p0);
		edge * ff;
		if (f != nullptr) {
			ff = f->ed;
			while (ff->getNext() != nullptr) {
				ff = ff->getNext();
			}
		}
		while (v != nullptr)
		{
			vertex * e = v;
			edge * ee;
			if (e->ed != nullptr) {
				ee = e->ed;
				pass(ee);
				vertex * q = ee->getVer();
				if (q->state == UNMARK) {
					ff->link = q;
					f = q;
					mark(q);
					if (f != nullptr) {
						ff = f->ed;
						while (ff->getNext() != nullptr){
							while (ff->getNext() != nullptr) {
								ff = ff->getNext();
							}
							if (ff->link != nullptr) {
								ff = ff->getNext();
							}
							
						}
					}
				}
				while (ee->getNext() != nullptr) {
					ee = ee->getNext();
					pass(ee);
					vertex * q = ee->getVer();
					if (q->state == UNMARK) {
						ff->link = q;
						f = q;
						mark(q);
						while (ff->getNext() != nullptr && ff->link != nullptr) {
							if (ff->getNext() == nullptr) {
								ff = ff->link->ed;
							}
							else {
								ff = ff->getNext();
							}
						}
					}
				}
				
			}
			pass(v);
			if (ee->getNext() == nullptr && ee->link == nullptr) {
				v = nullptr;
			}
			else if (ee->getNext() != nullptr) {
				v = ee->getNext()->getVer();
			}
			else if (ee->link != nullptr) {
				v = ee->link;
			}
			ee->link = nullptr;
		}

		std::cout << std::endl;
	
	
	
	}
*/
	
	void shag(vertex * cur, int maxC) {
		
		if (cur == head) {
			return;
		}
		/*edge * e = cur->ed;
		while (e != nullptr) {
			e = e->getNext();
		}*/
		
//		std::cout << cur->getIndex() << "=" << maxC << "==";
//		print();
//		std::cout << "\n";
		
		vertex * c = cur->getPrev();
		
		while (cur->findEd(c->getIndex()) == nullptr) {
			if (c->getPrev() != nullptr) {
				c = c->getPrev();
			} else {
				return;
			}
		}
		
		int col = c->getColor();
		
		
		
//		if (c->getMinColor(col+1) > maxC) {
//			shag(c, maxC);
//		} else
//		if (col+1 > maxC) {
//			shag(c, maxC);
//		}
		
//		col = c->getColor();
		
		c->setColor(c->getMinColor(col+1));
		if (c->getMinColor(col+1) < maxC) {
			vertex * cc = c->getNext();
			
			while (cc != nullptr) {
				int fc = cc->getMinColor();
				if (fc >= maxC) {
					cc->setColor(cc->getMinColor());
					shag(cc, maxC);
				}
				else {
					
					cc->setColor(fc);
					cc = cc->getNext();
				}
			}
		}
		else {
//			std::cout << col << "=" << c->getColor() << "==" << maxC << "\n\n";
			if (c->getMinColor(col+1) == maxC) {
				c->setColor(maxC);
				
			}
			shag(c, maxC);
			
		}
		
		
		
		
		
		
		
	}
	
	
	void colorize(){
		vertex * cur = head;
		int maxColor = 0;
		int c = 0;
		while (cur != nullptr) {
			c = cur->getMinColor();
			if (c > maxColor) {
				maxColor = c;
			}
			cur->setColor(c);
			cur = cur->getNext();
		}
		
		cur = head;
		
		
		print();
		std::cout << std::endl;
		
		/*int pmc = 0;
		int mc = 1;
		
		while (mc != pmc) {
			vertex * v = head;
			vertex * mv = head;

			while (v != nullptr) {
				if (v->getColor() > mc) {
					mc = v->getColor();
					mv = v;
				}
				v = v->getNext();
			}
			pmc = mc;

			shag(mv, mc);
			std::cout << "========";

			v = head;

			while (v != nullptr) {
				if (v->getColor() > mc) {
					mc = v->getColor();
					mv = v;
				}
				v = v->getNext();
			}



		}*/

		while (cur != nullptr) {
			if (cur->getColor() == maxColor) {
				break;
			}
			cur = cur->getNext();
		}

		
		shag(cur, maxColor);
		bool ind = false;
		cur = head;
		while (cur != nullptr) {
			if (cur->getColor() > maxColor) {
				ind = true;
				break;
			}
			cur = cur->getNext();
		}
		
		if (ind) {
			cur = head;
			maxColor = 0;
			while (cur != nullptr) {
				cur->setColor(cur->getMinColor());
				cur = cur->getNext();
			}
		}
		
	}
};


using namespace std;

#include <string>

int main() {
	std::cout << "Hello, World!" << std::endl;
	
	graph g;
/*
	for (int i=1;i<10;i++) {

		g.addVer(i);
		g.addVer(10-i);
	}

	for (int i=1;i<10;i++) {

		g.addEdge(i,i+1);
		g.addEdge(i,2*i);
	}

	g.print();
	cout<<endl<<endl;
	for (int i=1;i<11;i+=2) {

		g.removeVer(i);
	}
	g.print();
	
	for (int i=1;i<10;i++) {

		g.addVer(i);
		g.addVer(10-i);
	}
	cout<<endl<<endl;
	g.print();*/
	
	g.addVer(1);
	g.addVer(2);
	g.addVer(3);
	g.addVer(4);
	g.addVer(5);
	g.addVer(6);
	g.addVer(7);
	g.addVer(8);

	g.addEdge(1,8);
	g.addEdge(1,4);
	g.addEdge(1,6);
	g.addEdge(1,3);

	g.addEdge(2,8);
	g.addEdge(2,5);
	g.addEdge(2,7);
	g.addEdge(2,3);

	g.addEdge(3,1);
	g.addEdge(3,2);
	g.addEdge(3,6);
	g.addEdge(3,7);

	g.addEdge(4,1);
	g.addEdge(4,5);

	g.addEdge(5,4);
	g.addEdge(5,2);
	g.addEdge(5,7);
	g.addEdge(5,6);
	
	g.addEdge(6,5);
	g.addEdge(6,7);
	g.addEdge(6,1);
	g.addEdge(6,3);
	
	g.addEdge(7,5);
	g.addEdge(7,6);
	g.addEdge(7,3);
	g.addEdge(7,2);

	g.addEdge(8,1);
	g.addEdge(8,2);

/*	g.addVer(1);
	g.addVer(2);
	g.addVer(3);
	g.addVer(4);
	g.addVer(5);
	g.addVer(6);
	
	g.addEdge(1,3);
	g.addEdge(1,5);
	
	g.addEdge(2,4);
	g.addEdge(2,6);
	
	g.addEdge(3,6);
	
	g.addEdge(4,5);*/
	
//	g.print();
	
	cout << endl << endl;
	g.colorize();
	

	
//	g.traversal(1);
//	g.print();

	return 0;
}
