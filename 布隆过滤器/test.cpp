#include <iostream>
using namespace std;
#include "BloomFilter.hpp"


void test()
{
	BloomFilter<> bm(100);
	bm.Set("http://blog.chinaunix.net/uid/30154485.html");
	bm.Set("±äÊİ");
	bm.Set("±äÊİ°¡°¡°¡");
	bm.Set("ÕÒ¹¤×÷");
	bm.Set("ÕÒÄĞÆ±");
	bm.Set("¹ş¹ş");

	cout<<bm.IsIn("http://blog.chinaunix.net/uid/30154485.html")<<endl;
	cout<<bm.IsIn("±äÊİ")<<endl;
	cout<<bm.IsIn("±äÊİ°¡°¡°¡")<<endl;
	cout<<bm.IsIn("ÕÒ¹¤×÷")<<endl;
	cout<<bm.IsIn("¹ş¹ş")<<endl;

	cout<<bm.IsIn("Äã³òÉ¶")<<endl;
}
int main()
{
	test();
	return 0;
}