#include <iostream>
using namespace std;
#include "BloomFilter.hpp"


void test()
{
	BloomFilter<> bm(100);
	bm.Set("http://blog.chinaunix.net/uid/30154485.html");
	bm.Set("����");
	bm.Set("���ݰ�����");
	bm.Set("�ҹ���");
	bm.Set("����Ʊ");
	bm.Set("����");

	cout<<bm.IsIn("http://blog.chinaunix.net/uid/30154485.html")<<endl;
	cout<<bm.IsIn("����")<<endl;
	cout<<bm.IsIn("���ݰ�����")<<endl;
	cout<<bm.IsIn("�ҹ���")<<endl;
	cout<<bm.IsIn("����")<<endl;

	cout<<bm.IsIn("���ɶ")<<endl;
}
int main()
{
	test();
	return 0;
}