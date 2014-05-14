/*
 * Utils.h
 *
 *  Created on: Apr 3, 2014
 *      Author: zhemin
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <ctime>
#include <vector>
#include <string>

using namespace std;

class MyGlobal;
class MyFile;
class MyString;
class MyTimer;
template <typename T> class MyVector;

struct MyGlobal{
public:
	const static bool g_bDebug = true;
	const static int g_numThreads = 2;
	const static bool g_bStartEnd = false;
	constexpr static char* g_trainFileName = "train.corpus";
	constexpr static char* g_templateFileName = "template";
	static bool isSpace(char ch);
	static void printError(const char* errInfo);
	static void dummy(){};
};

class MyFile {
public:
	static MyString* readFile(const char* filePath);
	static void writeFile(MyString* content, const char* filePath);
	static void writeFile(char* content, int size, const char* filePath);
	static void copyFile(const char* source_file, const char* dest_file);
	static void makeDir(const char* dir);
};

class MyString {
public:
	MyString();
	MyString(string str);
	MyString(MyString* pMyStr);
	MyString(const char* str);
	MyString(string* str);
	MyString(char* pBegin, char* pEnd, bool bCopy);
	~MyString();
	MyString(int i);
	MyString(double d);
public:
	void trim();
	MyVector<MyString>* splitBySpace();
	MyVector<MyString>* split(char ch);
	int findFirst(char* pStart, MyString* pattern);
	vector<int> findAll(MyString* pattern);
	MyVector<MyString>* split(MyString* pattern);
	int length();
	void print();
	void println();
	char* getCString();
	char getChar(int i);
	void join(MyString* pMyStr);
	void join(char* pStr);
	string getString();
private:
	char* m_pBegin;
	char* m_pEnd;
};

class MyTimer {
public:
	MyTimer();
	virtual ~MyTimer();
	void start();
	void end();
	double duration();
	void addDuration(double duration);
	void printDuration(const char* info);
	void printSum(const char* info);
private:
	double m_sumDuration;  //total duration in sum;
	timespec m_startTime;
	timespec m_endTime;
	int m_state;  //0: not started   //1: started, not end  //2: started and ended.
	double getSeconds(timespec diff);
	timespec diff();
};

template <typename T> class MyVector{
public:
	~MyVector(){
		int size = length();
		for(int i = 0; i < size; ++ i)
			delete getItem(i);
	}

	int length(){
		return m_vecTP.size();
	}

	void push_back(T* tp){
		m_vecTP.push_back(tp);
	}

	T* getItem(int i){
		return m_vecTP[i];
	}

	T* getFirst(){
		return m_vecTP[0];
	}

	T* getLast(){
		int lastIndex = m_vecTP.size() - 1;
		return m_vecTP[lastIndex];
	}
private:
	vector<T*> m_vecTP;
};

#endif /* UTILS_H_ */
