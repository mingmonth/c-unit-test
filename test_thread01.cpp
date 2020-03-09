#include <iostream>
#include <thread>
#include <vector>

void worker(int& counter) {
	for(int i = 0; i < 10000; i++) {
		counter += 1;
	}
}

int main() {
	int counter = 0;
	
	std::vector<std::thread> workers;
	for(int i = 0; i < 100; i++) {
		workers.push_back(std::thread(worker, std::ref(counter)));
	}
	
	for(int i = 0; i < 100; i++) {
		workers[i].join();
	}
	
	std::cout << "Counter ���� ��: " << counter << std::endl; 
}
