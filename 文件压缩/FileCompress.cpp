#include <iostream>
using namespace std;
#include "FileCompress.hpp"

void test()
{
	FileCompress<CharInfo> f;
	f.Compress("haha.txt");
	f.UnCompress("haha.txt");
}
int main()
{
	test();
	return 0;
}