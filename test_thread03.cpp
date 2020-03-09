// 인터넷에서 페이지를 긁어서 분석하는 프로그램을 만들었다고 생각해봅시다.
// 이 경우 페이지를 긁어 오는 쓰레드가 바로 생산자가 되겠지요.
// 소비자의 경우, 받은 일을 처리하는 스레드를 의미합니다.
#include <chrono>	// std::chrono::miliseocnds
#include <condition_variable>	// std::condition_variable
#include <iostream>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include <vector>

void producer(std::queue<std::string>* downloaded_pages, std::mutex* m, int index, std::condition_variable* cv) {
	for(int i = 0; i < 5; i++)	 {
		// 웹사이트를 다운로드 하는데 걸리는 시간이라 생각하면 된다.
		// 각 스레드 별로 다운로드 하는데 걸리는 시간은 다르다.
		std::this_thread::sleep_for(std::chrono::milliseconds(100 * index));
		std::string content = "웹사이트: " + std::to_string(i) + " from thead(" + std::to_string(index) + ")\n";
		
		// data는 스레드 사이에서 공유되므로 ciritical section 에 넣어야 한다.
		m->lock();
		downloaded_pages->push(content);
		m->unlock(); 
		
		// consumere 에게 content 가 준비되었음을 알림.
		cv->notify_one() ;
	}
}

void consumer(std::queue<std::string>* downloaded_pages, std::mutex* m, int* num_processed, std::condition_variable* cv) {
	// 전체 처리하는 페이지 개수가 5 * 5 = 25 개
	while(*num_processed < 25) {
		std::unique_lock<std::mutex> lk(*m);
		
		// 조건이 참일때까지 기다린다. 
		cv->wait(lk, [&] { return !downloaded_pages->empty() || *num_processed == 25; });
		
		if(*num_processed == 25) {
			lk.unlock();
			return;
		}
		
//		m->lock();
//		// 만일 현재 다운로드한 페이지가 없다면 다시 대기.
//		if(downloaded_pages->empty()) {
//			m->unlock();
//			
//			// 10 밀리초 뒤에 다시 확인
//			std::this_thread::sleep_for(std::chrono::milliseconds(10));
//			continue;
//		}
		
		// 맨 앞의 페이지를 읽고 대기 목록에서 제거.
		std::string content = downloaded_pages->front();
		downloaded_pages->pop();
		
		(*num_processed)++;
		m->unlock();
		
		// content 를 처리.
		std::cout << content;
		std::this_thread::sleep_for(std::chrono::milliseconds(80)) ;
	}
}
 
int main() {
	std::queue<std::string> downloaded_pages;
	std::mutex m;
	std::condition_variable cv;
	
	std::vector<std::thread> producers;
	for(int i = 0; i < 5; i++) {
		producers.push_back(std::thread(producer, &downloaded_pages, &m, i + 1, &cv));
	}
	
	int num_processed = 0;
	std::vector<std::thread> consumers;
	for(int i = 0; i < 3; i++) {
		consumers.push_back(std::thread(consumer, &downloaded_pages, &m, &num_processed, &cv));
	}
	
	for(int i = 0; i < 5; i++) {
		producers[i].join();
	}
	
	// 나머지 자고 있는 스레드들을 모두 깨운다. 
	cv.notify_all();
	
	for(int i = 0; i < 3; i++) {
		consumers[i].join();
	}
}
