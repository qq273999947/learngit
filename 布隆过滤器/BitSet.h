#pragma once
#include <vector>

class BitMap
{
public:
	BitMap()
		:_size(0)
	{}
	BitMap(size_t n)
		:_size(0)
	{
		_array.resize((n>>5) + 1);
	}
	void resize(size_t n)
	{
		_array.resize((n>>5) + 1);
	}
	bool Test(size_t num)//�鿴�����Ƿ����
	{
		size_t index = num>>5;
		size_t n = num % 32;

		return _array[index]&(1<<n);
	}
	bool Set(size_t num)
	{
		size_t index = num>>5;
		size_t n = num % 32;
		if(_array[index] & (1<<n))//������Ѿ�������
		{
			return false;
		}
		_array[index] |= 1<<n;//ע���������ʱ�������λ�ƶ�����������������ƶ���
		_size++;
		return true;
	}
	bool Reset(size_t num)
	{
		size_t index = num>>5;
		size_t n = num % 32;
		if(!_array[index] & (1<<n))//�����������
		{
			return false;
		}
		_array[index] &= ~(1<<n);
		_size--;
		return true;
	}

	void Clear()
	{
		_array.assign(_array.size(),0);
	}
protected:
	vector<size_t> _array;
	size_t _size;
};