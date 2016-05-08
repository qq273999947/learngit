#pragma once
#include "BitSet.h"
#include <string>

//����������
static size_t _GetNextPrime(size_t size)
{
	static const int _PrimeSize = 28;
	static const unsigned long _PrimeList [_PrimeSize] =
	{
		53ul,         97ul,         193ul,       389ul,       769ul,
		1543ul,       3079ul,       6151ul,      12289ul,     24593ul,
		49157ul,      98317ul,      196613ul,    393241ul,    786433ul,
		1572869ul,    3145739ul,    6291469ul,   12582917ul,  25165843ul,
		50331653ul,   100663319ul,  201326611ul, 402653189ul, 805306457ul,
		1610612741ul, 3221225473ul, 4294967291ul
	};

	for (size_t i = 0; i < _PrimeSize; ++i)
	{
		if (_PrimeList[i] > size)
		{
			return _PrimeList[i];
		}
	}

	return _PrimeList[_PrimeSize-1];
}

//�����ַ�����������
static size_t BKDRHash(const char * str)
{
	unsigned int seed = 131; // 31 131 1313 13131 131313
	unsigned int hash = 0;
	while (*str )
	{
		hash = hash * seed + (* str++);
	}
	return (hash & 0x7FFFFFFF);
}
static size_t SDBMHash(const char *str)  
{  
	register size_t hash = 0;  
	while (size_t ch = (size_t)*str++)  
	{  
		hash = 65599 * hash + ch;         
	}  
	return hash;  
}  
static size_t RSHash(const char *str)  
{  
	register size_t hash = 0;  
	size_t magic = 63689;     
	while (size_t ch = (size_t)*str++)  
	{  
		hash = hash * magic + ch;  
		magic *= 378551;  
	}  
	return hash;  
} 
static size_t APHash(const char *str)  
{  
	register size_t hash = 0;  
	size_t ch;  
	for (long i = 0; ch = (size_t)*str++; i++)  
	{  
		if ((i & 1) == 0)  
		{  
			hash ^= ((hash << 7) ^ ch ^ (hash >> 3));  
		}  
		else  
		{  
			hash ^= (~((hash << 11) ^ ch ^ (hash >> 5)));  
		}  
	}  
	return hash;  
}  
static size_t JSHash(const char *str)  
{  
	if(!*str)        
		return 0;  
	register size_t hash = 1315423911;  
	while (size_t ch = (size_t)*str++)  
	{  
		hash ^= ((hash << 5) + ch + (hash >> 2));  
	}  
	return hash;  
} 
template<class K>
struct HashFunc
{
	size_t operator() (const K& key)
	{
		return key;
	}
};
template<class string>
struct HashFunc1
{
	size_t operator() (const string& key)
	{
		return BKDRHash(key.c_str());
	}
};
template<class string>
struct HashFunc2
{
	size_t operator() (const string& key)
	{
		return SDBMHash(key.c_str());
	}
};
template<class string>
struct HashFunc3
{
	size_t operator() (const string& key)
	{
		return RSHash(key.c_str());
	}
};
template<class string>
struct HashFunc4
{
	size_t operator() (const string& key)
	{
		return APHash(key.c_str());
	}
};
template<class string>
struct HashFunc5
{
	size_t operator() (const string& key)
	{
		return JSHash(key.c_str());
	}
};
template<class K = string,
class HashFunc1 = HashFunc1<K>,
class HashFunc2 = HashFunc2<K>,
class HashFunc3 = HashFunc3<K>,
class HashFunc4 = HashFunc4<K>,
class HashFunc5 = HashFunc5<K>>
class BloomFilter
{
public:
	BloomFilter(size_t size)
	{
		_capacity = _GetNextPrime(size);
		_bitmap.resize(_capacity);
	}
	void Set(const K&key)
	{
		size_t index1 = HashFunc1()(key);
		size_t index2 = HashFunc2()(key);
		size_t index3 = HashFunc3()(key);
		size_t index4 = HashFunc4()(key);
		size_t index5 = HashFunc5()(key);

		_bitmap.Set(index1%_capacity);
		_bitmap.Set(index2%_capacity);
		_bitmap.Set(index3%_capacity);
		_bitmap.Set(index4%_capacity);
		_bitmap.Set(index5%_capacity);
	}
	bool IsIn(const K&key)
	{
		size_t index1 = HashFunc1()(key);
		if(!_bitmap.Test(index1%_capacity))
		{
			return false;
		}

		size_t index2 = HashFunc2()(key);
		if(!_bitmap.Test(index2%_capacity))
		{
			return false;
		}

		size_t index3 = HashFunc3()(key);
		if(!_bitmap.Test(index3%_capacity))
		{
			return false;
		}

		size_t index4 = HashFunc4()(key);
		if(!_bitmap.Test(index4%_capacity))
		{
			return false;
		}

		size_t index5 = HashFunc5()(key);
		if(!_bitmap.Test(index5%_capacity))
		{
			return false;
		}
		return true;
	}
protected:
	BitMap _bitmap;
	size_t _capacity;
};