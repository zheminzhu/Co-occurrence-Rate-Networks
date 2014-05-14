/*
 * Utils.cpp
 *
 *  Created on: Apr 3, 2014
 *      Author: zhemin
 */

#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "Utils.h"

using namespace std;

bool MyGlobal::isSpace(char ch){
	return (ch == ' ') || (ch == '\t')
			|| (ch == '\n') || (ch == '\r');
}

void MyGlobal::printError(const char* info){
	std::cout << info;
}

MyString* MyFile::readFile(const char* filePath){
	ifstream is (filePath, std::ifstream::binary);
	if(is){
		// get length of the file.
		is.seekg (0, is.end);
		int length = is.tellg();
		is.seekg (0, is.beg);

		// create buffer and read the whole file to the buffer at once.
		char* pBegin = new char [length + 1];
		is.read(pBegin,length);
		pBegin[length] = '\0';
		is.close();
		MyString* pMyStr = new MyString(pBegin, pBegin + length, false);
		return pMyStr;
	}else{
		cout << "Unable to open file: \n" << filePath;
		exit(1);
	}
}

void MyFile::writeFile(MyString* content, const char* filePath){
	ofstream outfile (filePath, ofstream::binary);
	outfile.write(content->getCString(), content->length());
    outfile.close();
}

void MyFile::writeFile(char* content, int size, const char* filePath){
	ofstream outfile (filePath, ofstream::binary);
	outfile.write(content, size);
    outfile.close();
}

void MyFile::copyFile(const char* source_file, const char* dest_file){
	size_t buf_size = 64 * 1024 * 1024;
	char* buf = new char[buf_size];
	size_t size;
	FILE* source = fopen(source_file, "rb");
	FILE* dest = fopen(dest_file, "wb");
	while (size = fread(buf, 1, buf_size, source))
		fwrite(buf, 1, size, dest);
	delete buf;
	fclose(source);
	fclose(dest);
}

void MyFile::makeDir(const char* dir){
	struct stat st = {0};
	if (stat(dir, &st) == -1)
	    mkdir(dir, 0700);
}

MyString::MyString(){
	m_pBegin = m_pEnd = new char[1];
	*m_pEnd = '\0';
}

MyString::MyString(string str):MyString(str.c_str()){

}

MyString::MyString(MyString* pMyStr){
	int size = pMyStr->length();
	if(size == 0){
		m_pBegin = m_pEnd = new char[1];
		*m_pEnd = '\0';
		return;
	}
	m_pBegin = new char[size + 1];
	strncpy(m_pBegin, pMyStr->getCString(), size);
	m_pEnd = m_pBegin + size;
	*m_pEnd = '\0';
}

MyString::MyString(int i){
	char buffer[32];
	int n = sprintf(buffer, "%d", i);
	m_pBegin = new char[n];
	strncpy(m_pBegin, buffer, n);
	m_pEnd = m_pBegin + n;
	*m_pEnd = '\0';
}

MyString::MyString(double d){
	char buffer[64];
	int n = sprintf(buffer, "%.4f", d);
	m_pBegin = new char[n];
	strncpy(m_pBegin, buffer, n);
	m_pEnd = m_pBegin + n;
	*m_pEnd = '\0';
}

MyString::MyString(const char* str){
	const char* pBegin = str;
	const char* pEnd = pBegin;
	while((*pEnd) != '\0')
		++ pEnd;
	int size = pEnd - pBegin;

	if(size == 0){
			m_pBegin = m_pEnd = new char[1];
			*m_pEnd = '\0';
			return;
	}
	m_pBegin = new char[size + 1];
	strncpy(m_pBegin, pBegin, size);
	m_pEnd = m_pBegin + size;
	*m_pEnd = '\0';
}

MyString::MyString(string* str){
	const char* p = str->c_str();
	int size = str->size();
	m_pBegin = new char[size + 1];
	strncpy(m_pBegin, p, size);
	m_pEnd = m_pBegin + size;
	*m_pEnd = '\0';
}

MyString::MyString(char* pBegin, char* pEnd, bool bCopy){
	if(!bCopy){
		m_pBegin = pBegin;
		m_pEnd = pEnd;
		trim();
		return;
	}
	int size = pEnd - pBegin;
	if(size < 0){
		MyGlobal::printError("Error in MyString::MyString(char* pBegin, char* pEnd), pEnd is smaller than pBegin!");
		exit(1);
	}

	if(size == 0){
		m_pBegin = m_pEnd = new char[1];
		*m_pEnd = '\0';
		return;
	}

	m_pBegin = new char[size + 1];
	strncpy(m_pBegin, pBegin, size);
	m_pEnd = m_pBegin + size;
	*m_pEnd = '\0';
}

MyString::~MyString(){
	delete[] m_pBegin;
}

int MyString::length(){
	return m_pEnd - m_pBegin;
}

void MyString::print(){
	string str(m_pBegin, length());
	cout << str << std::flush;
}

char MyString::getChar(int i){
	if(i< 0 || i > length()){
		MyGlobal::printError("Out the limits: char MyString::getChar(int i)");
		exit(1);
	}
	return m_pBegin[i];

}

string MyString::getString(){
	string str(getCString());
	return str;
}

void MyString::join(MyString* pStr){
	int str1Len = this->length();
	int str2Len = pStr->length();

	int size = str1Len + str2Len;
	char* pNewBegin = new char[size + 1];
	strncpy(pNewBegin, m_pBegin, length());
	strncpy(pNewBegin + length(), pStr->getCString(), pStr->length());
	m_pEnd = pNewBegin + size;
	*m_pEnd = '\0';
	delete m_pBegin;
	m_pBegin = pNewBegin;
}

void MyString::join(char* pStr){
	MyString myStr(pStr);
	this->join(&myStr);
}

void MyString::println(){
	string str(m_pBegin, length());
	cout << str << std::flush << endl;
}

void MyString::trim(){
	if(length() == 0)
		return;
	char* pBegin = m_pBegin;

	while( (pBegin <= m_pEnd)
			&& MyGlobal::isSpace(*pBegin) )
		++ pBegin;

	if(pBegin == m_pEnd){ //all are spaces.
		delete[] m_pBegin;
		m_pBegin = m_pEnd = 0;
		return;
	}

	char* pEnd;

	if(pBegin == (m_pEnd - 1)){ //only the last ch is not space
		pEnd = m_pEnd;
	}else{
		pEnd = m_pEnd;
		while( (pBegin < pEnd) && MyGlobal::isSpace(* (pEnd - 1)))
				-- pEnd;
	}

	if( (pBegin == m_pBegin) && (pEnd == m_pEnd))
		return;


	int newSize = pEnd - pBegin;

	char* pNewStr = new char[newSize + 1];
	strncpy(pNewStr, pBegin, newSize);
	delete[] m_pBegin;
	m_pBegin = pNewStr;
	m_pEnd = pNewStr + newSize;
	*m_pEnd = '\0';

}

MyVector<MyString>* MyString::splitBySpace(){
	MyVector<MyString>* pVecPStr = new MyVector<MyString>;
	vector<char* > pStrs;
	char* p = m_pBegin;
	pStrs.push_back(p);
	bool bPreSpace = false;
	++ p;
	while(p < m_pEnd){
		char ch = *p;
		bool bCurSpace = MyGlobal::isSpace(ch);
		if(bCurSpace){//current char is a space
			if(!bPreSpace)//previous char is not a space
				pStrs.push_back(p);
			bPreSpace = true;
		}else{// current char is not a space
			if(bPreSpace) //previous char is a space
				pStrs.push_back(p);
			bPreSpace = false;
		}

		++ p;
	}

	pStrs.push_back(p);
	for(int i = 0; i < pStrs.size() - 1; ++ i){
		char* begin = pStrs[i];
		char* end = pStrs[++ i];
		MyString* pStr = new MyString(begin, end, true);
		pVecPStr->push_back(pStr);
	}

	/* for debug
	for(int i = 0; i < pVecPStr->length(); ++ i){
		MyString* p = pVecPStr->getItem(i);
		cout << i << "\t" << std::flush;
		p->println();
	}*/
	return pVecPStr;
}

MyVector<MyString>* MyString::split(char ch){
	MyVector<MyString>* pVecTP = new MyVector<MyString>();
	vector<char* > pStrs;
	char* p = m_pBegin;
	pStrs.push_back(p);
	bool bCh = false;
	while(p < m_pEnd){
		if(*p == ch){
			if(!bCh){
				bCh = true;
				pStrs.push_back(p);
			}
		}else{
			if(bCh){
				pStrs.push_back(p);
				bCh = false;
			}
		}
		++ p;
	}
	pStrs.push_back(p);
	for(int i = 0; i < pStrs.size() - 1; ++ i){
		char* begin = pStrs[i];
		char* end = pStrs[++ i];
		MyString* pStr = new MyString(begin, end, true);
		pVecTP->push_back(pStr);
	}
	return pVecTP;
}

char* MyString::getCString(){
	return m_pBegin;
}

int MyString::findFirst(char* pStart, MyString* pattern){
	int patternLength = pattern->length();
	int state = 0;
	if(pStart < m_pBegin || pStart >= m_pEnd){
		MyGlobal::printError("Out of limits. MyString::findFirst");
		exit(1);
	}
	char* p = pStart;
	while(p <= m_pEnd){
		char curCh = *p;
		char curPattern = pattern->getChar(state);
		if(curCh == curPattern){
			if(state == (patternLength - 1)){
				return p - (patternLength - 1) - pStart;
			}else{
				++ state;
			}

		}else{
			state = 0;
		}
		++ p;
	}

	return -1;
}

vector<int> MyString::findAll(MyString* pattern){
	char* p = m_pBegin;
	int patternLength = pattern->length();
	vector<int> vec;
	while(p <= m_pEnd){
		int pos = findFirst(p, pattern);
		if(pos == -1){
			break;
		}else{
			vec.push_back(p + pos - m_pBegin);
			p += pos + patternLength;
		}

	}

	return vec;
}

MyVector<MyString>* MyString::split(MyString* pattern){
	vector<int> poses = findAll(pattern);
	int patternLength = pattern->length();
	MyVector<MyString>* pVecStrs = new MyVector<MyString>;
	if(poses.size() == 0){
		MyString* pStr = new MyString(this);
		pVecStrs->push_back(pStr);
	}else{
		char* pBegin = m_pBegin;
		for(int i = 0; i < poses.size(); ++ i){
			char* pEnd = m_pBegin + poses[i];
			MyString* pStr = new MyString(pBegin, pEnd, true);
			pStr->trim();
			pVecStrs->push_back(pStr);
			pBegin = pEnd + patternLength;
		}
		if(pBegin != m_pEnd){
			MyString* pStr = new MyString(pBegin, m_pEnd, true);
			pStr->trim();
			pVecStrs->push_back(pStr);
		}
	}

	/* for debug
	for(int i = 0; i < pVecStrs->length(); ++ i){
		MyString* pStr = pVecStrs->getItem(i);
		cout << i << endl << std::flush;
		pStr->println();
	}
	 */

	return pVecStrs;
}

MyTimer::MyTimer() {
	m_sumDuration = 0.0;
	m_state = 0;
}

MyTimer::~MyTimer() {}

double MyTimer::getSeconds(timespec diff){
	double sec = diff.tv_nsec * 1.0 / 1000000000;
	return sec;
}

void MyTimer::start(){
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &m_startTime);
	m_state = 1;
}

void MyTimer::end(){
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &m_endTime);
	m_state = 2;
}

timespec MyTimer::diff(){
	timespec temp;
	long dnano = m_endTime.tv_nsec - m_startTime.tv_nsec;
	int dsec =  m_endTime.tv_sec - m_startTime.tv_sec;
	if (dnano < 0) {
		temp.tv_sec = dsec - 1;
		temp.tv_nsec = 1000000000 + dnano;
	} else {
		temp.tv_sec = dsec;
		temp.tv_nsec = dnano;
	}

	return temp;

}

void MyTimer::addDuration(double duration){
	m_sumDuration += duration;
}

double MyTimer::duration(){
	if(m_state != 2){
		cout << "Wrong state in MyTimer!" << endl << std::flush;
		exit(1);
	}

	timespec dur = diff();
	return  getSeconds(dur);
}

void MyTimer::printDuration(const char* info){
	char buffer[1024];
	sprintf(buffer, "%s\t%lf Sec.", info, duration());
	MyString str(buffer);
	str.println();
}

void MyTimer::printSum(const char* info){
	char buffer[1024];
	sprintf(buffer, "%s\t%lf Sec.", info, m_sumDuration);
	MyString str(buffer);
	str.println();
}
