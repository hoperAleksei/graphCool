#include <iostream>

/*
 *
 * 1	Конструктор
 * 2	Деструкор           TODO
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
 * 11	Алгоритм
 *
 * */

class vertex;
class edge{
private:
	vertex * ver;
	edge * next;
	edge * prev;
public:
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
	edge * ed;
public:
	vertex(vertex * next, vertex * prev, int index){
		this->next = next;
		this->prev = prev;
		this->index = index;
		this->ed = nullptr;
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
		std::cout << "(" << this->index << ") => ";
		edge * cur = this->ed;
		while (cur != nullptr) {
			std::cout << cur->getVer()->getIndex() << " ";
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

	

};


using namespace std;

int main() {
	std::cout << "Hello, World!" << std::endl;
	
	graph g;
	
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
		//g.addVer(10-i);
	}
	g.print();
	
	for (int i=1;i<10;i++) {
		
		g.addVer(i);
		g.addVer(10-i);
	}
	cout<<endl<<endl;
	g.print();
	
	/*g.addVer(1);
	g.addVer(2);
	g.addVer(3);
	
	g.print();
	
	g.addEdge(1,2);
	g.addEdge(1,3);
	g.addEdge(2,3);
	
	g.print();
	
	cout << g.findEdge(3,2);
	g.removeEdge(2,3);
	cout << g.findEdge(3,2) << endl;
	g.removeEdge(1,2);
	g.removeEdge(3,1);
	
	g.print();
	
	g.addEdge(1,2);
	g.addEdge(1,3);
	g.addEdge(2,3);
	
	g.removeVer(1);
	g.removeVer(3);
	g.removeVer(2);
	
	g.print();
	
	graph * gg = new graph;
	
	gg->addVer(1);
	gg->addVer(2);
	gg->addVer(3);
	
	gg->addEdge(1,2);
	gg->addEdge(1,3);
	gg->addEdge(2,3);
	
	delete gg;
	
	std::cout << "Hello, World!" << std::endl;*/
	
	return 0;
}
