/* John Ko
 * HW4
 *
 */
#ifndef _STACKS_H_
#define _STACKS_H_

#include <iostream>
#include <vector>

template <class T>
class Stacks
{
	public:
		Stacks();
		Stacks(int);
		~Stacks();
		void push(T);
		T pop();
		void print();
		bool empty();
		T peek();
		bool isFlagSet();
		void setFlag(bool);
	private:
		T* arr;
		int top;
		bool flag;
		

};

template <class T>
Stacks<T>::Stacks()
{
	//hardcoded the number if 
	//the number is not given
	arr = new T[10];
	top = 0;
	flag = false;
}

template <class T>
Stacks<T>::Stacks(int s)
{
	arr = new T[s];
	top = 0;
	flag = false;
}

template <class T>
Stacks<T>::~Stacks()
{}

template <class T>
void Stacks<T>::push(T var)
{
	arr[top++] = var;
}

template <class T>
T Stacks<T>::pop()
{
	if(top >= 0 )
		return arr[--top];
	top--;
	return (T)0;
}

template <class T>
void Stacks<T>::print()
{
	for(int i=0; i<top; i++)
	{
		cout <<  i << ":" << arr[i] << endl;
	}
}

template <class T>
bool Stacks<T>::empty()
{
	if(top <= 0)
		return true;
	return false;
}

template <class T>
void Stacks<T>::setFlag(bool f)
{
	flag = f;
}

template <class T>
T Stacks<T>::peek()
{
	return arr[top-1];
}

template <class T>
bool Stacks<T>::isFlagSet()
{
	return flag;
}
#endif