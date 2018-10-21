#ifndef AWQUE_H
#define AWQUE_H

#include <exception>

template <typename T>
class awqueIterator;

template <typename T>
class awque
{
	awqueIterator<T>* Beg;
	awqueIterator<T>* End;
	int quesize;
public:
	awque() : Beg(NULL), End(NULL), quesize(0) {};
	~awque() 
	{ 
		clear();
	};

	void push_at(const T& q, const int& param)
	{
		if (param == 0)
		{
			push_front(q);
			return;
		}
		if (param == quesize)
		{
			push_back(q);
			return;
		}
		if (param >= quesize)
			return;

		awqueIterator<T>* curr = Beg;
		for (int i = 0; i < param-1; i++)
			curr = curr->next;
		awqueIterator<T>* currnext = curr->next;
		curr->next = new awqueIterator<T>(q);
		curr->next->next = currnext;
		curr->next->previous = curr;
		quesize++;
	}

	void push_back(const T& q)
	{
		if (Beg == NULL)
		{
			Beg = new awqueIterator<T>(q);
			End = Beg;
		}
		else
		{
			End->next = new awqueIterator<T>(q);
			End->next->previous = End;
			End = End->next;
		}
		quesize++;
	}

	void push_front(const T& q)
	{
		if (Beg == NULL)
		{
			Beg = new awqueIterator<T>(q);
			End = Beg;
		}
		else
		{
			Beg->previous = new awqueIterator<T>(q);
			Beg->previous->next = Beg;
			Beg = Beg->previous;
		}
		quesize++;
	}

	void pop_at(const unsigned int& param)
	{
		if (param == 0)
		{
			pop_front();
			return;
		}
		if (param == quesize)
		{
			pop_back();
			return;
		}
		if (param > quesize)
			return;

		awqueIterator<T>* curr = Beg;
		for (int i = 0; i < param; i++)
			curr = curr->next;
		curr->previous->next = curr->next;
		if (curr->next != NULL)
			curr->next->previous = curr->previous;
		delete curr;
		quesize--;
	}

	void pop_back()
	{
		if (quesize == 0)
			return;
		if (quesize == 1)
		{
			delete Beg;
			End = NULL;
			Beg = NULL;
			quesize--;
			return;
		}
		End = End->previous;
		delete End->next;
		End->next = NULL;
		quesize--;
	}

	void pop_front()
	{
		if (quesize == 0)
			return;
		if (quesize == 1)
		{
			delete Beg;
			End = NULL;
			Beg = NULL;
			quesize--;
			return;
		}
		Beg = Beg->next;
		delete Beg->previous;
		Beg->previous = NULL;
		quesize--;
	}

	void clear()
	{
		if (quesize != 0)
		{
			End = Beg->next;
			while (End != NULL)
			{
				delete Beg;
				Beg = End;
				End = Beg->next;
			}
			delete Beg;
			Beg = NULL;
			quesize = 0;
		}
	}

	int size() { return quesize; }

	T& front() { return Beg->data; }

	T& back() { return End->data; }

	T& at(const int& param)
	{
		if (param >= quesize)
			throw -1;
			

		awqueIterator<T>* curr = Beg;
		for (int i = 0; i < param; i++)
			curr = curr->next;
		return curr->data;
	}
};

template <typename T>
class awqueIterator
{
	friend class awque<T>;
	awqueIterator<T>* next;
	awqueIterator<T>* previous;
	T data;
	awqueIterator(const T& q) : data(q), next(NULL), previous(NULL) {};
	~awqueIterator() {};
};

#endif