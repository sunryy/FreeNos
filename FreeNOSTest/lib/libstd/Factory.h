#pragma once

//Abstract Factory design pattern.
template <class T>class Factory{
public:
	//Create an instance of T.
	static T *create(){
		return new T();
	}
};