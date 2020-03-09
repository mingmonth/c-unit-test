// ���ͳݿ��� �������� �ܾ �м��ϴ� ���α׷��� ������ٰ� �����غ��ô�.
// �� ��� �������� �ܾ� ���� �����尡 �ٷ� �����ڰ� �ǰ�����.
// �Һ����� ���, ���� ���� ó���ϴ� �����带 �ǹ��մϴ�.
#include <chrono>	// std::chrono::miliseocnds
#include <iostream>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include <vector>

void producer(std::queue<std::string>* downloaded_pages, std::mutex* m, int index) {
	for(int i = 0; i < 5; i++)	 {
		// ������Ʈ�� �ٿ�ε� �ϴµ� �ɸ��� �ð��̶� �����ϸ� �ȴ�.
		// �� ������ ���� �ٿ�ε� �ϴµ� �ɸ��� �ð��� �ٸ���.
		std::this_thread::sleep_for(std::chrono::milliseconds(100 * index));
		std::string content = "������Ʈ: " + std::to_string(i) + " from thead(" + std::to_string(index) + ")\n";
		
		// data�� ������ ���̿��� �����ǹǷ� ciritical section �� �־�� �Ѵ�.
		m->lock();
		downloaded_pages->push(content);
		m->unlock(); 
	}
}

void consumer(std::queue<std::string>* downloaded_pages, std::mutex* m, int* num_processed) {
	// ��ü ó���ϴ� ������ ������ 5 * 5 = 25 ��
	while(*num_processed < 25) {
		m->lock();
		// ���� ���� �ٿ�ε��� �������� ���ٸ� �ٽ� ���.
		if(downloaded_pages->empty()) {
			m->unlock();
			
			// 10 �и��� �ڿ� �ٽ� Ȯ��
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
			continue;
		}
		
		// �� ���� �������� �а� ��� ��Ͽ��� ����.
		std::string content = downloaded_pages->front();
		downloaded_pages->pop();
		
		(*num_processed)++;
		m->unlock();
		
		// content �� ó��.
		std::cout << content;
		std::this_thread::sleep_for(std::chrono::milliseconds(80)) ;
	}
}
 
int main() {
	std::queue<std::string> downloaded_pages;
	std::mutex m;
	
	std::vector<std::thread> producers;
	for(int i = 0; i < 5; i++) {
		producers.push_back(std::thread(producer, &downloaded_pages, &m, i+ 1));
	}
	
	int num_processed = 0;
	std::vector<std::thread> consumers;
	for(int i = 0; i < 3; i++) {
		consumers.push_back(std::thread(consumer, &downloaded_pages, &m, &num_processed));
	}
	
	for(int i = 0; i < 5; i++) {
		producers[i].join();
	}
	
	for(int i = 0; i < 3; i++) {
		consumers[i].join();
	}
}
