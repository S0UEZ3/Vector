#pragma once
#include <cstddef>
#include <algorithm>
using std::size_t;

const double R_COEF = 2.0;

template <class T>
class Vector {
public:
	class Iter {
	public:
		friend Vector<T>;
		Iter(T* uk);

	public:
		Iter& operator++();
		Iter operator++(int);
		Iter& operator--();
		Iter operator--(int);
		T& operator*();

		bool operator==(const Iter& other);
		bool operator!=(const Iter& other);

	private:
		T* uk;
	};

public:
	Vector();
	Vector(size_t size);
	Vector(size_t size, const T& default_value);
	Vector(const Vector<T>& other);
	~Vector();

	Vector<T>& operator=(const Vector<T>& other);
	Vector<T>& operator+=(const Vector<T>& other);
	T& operator[](const size_t i);

	Iter begin() const;
	Iter end() const;
	size_t capacity() const;
	size_t size() const;
	
	void clear();
	void pop_back();
	void push_back(const T&);
	void reserve(size_t capacity);
	void resize(size_t size);
	void resize(size_t size, const T& default_value);

private:
	size_t _size;
	size_t _capacity;
	T* arr;
};

// -------------------------------------------------------------- //

template <class T>
Vector<T>::Iter::Iter(T* uk) : uk(uk){};

template <class T>
typename Vector<T>::Iter& Vector<T>::Iter::operator++() {
	uk++;
	return *this;
};

template <class T>
typename Vector<T>::Iter Vector<T>::Iter::operator++(int) {
	Iter temp = *this;
	++(uk);
	return temp;
};

template <class T>
typename Vector<T>::Iter& Vector<T>::Iter:: operator--() {
	uk--;
	return *this;
};

template <class T>
typename Vector<T>::Iter Vector<T>::Iter:: operator--(int) {
	Iter temp = *this;
	--uk;
	return temp;
};

template <class T>
	T& Vector<T>::Iter::operator*() {
	return *uk;
};

template <class T>
bool Vector<T>::Iter::operator==(const Iter& other) {
	return uk == other.uk;
};

template <class T>
bool Vector<T>::Iter::operator!=(const Iter& other) {
	return !(*this == other);
};

template <class T>
Vector<T>::Vector() : _size(0), _capacity(0), arr(nullptr) {};

template <class T>
Vector<T>::Vector(size_t size) : _size(size), _capacity(size) {
	arr = new T[size];
};

template <class T>
Vector<T>::Vector(size_t size, const T& default_value) : _size(size), _capacity(size){
	arr = new T[size];
	std::fill(arr, arr + size, default_value);
};

template <class T>
Vector<T>::Vector(const Vector<T>& other) : _size(other.size()), _capacity(other.capacity()) {
	arr = new T[other.capacity()];
	std::copy(other.arr, other.arr + other.size(), arr);
};

template <class T>
Vector<T>:: ~Vector() {
	delete[] arr;
};

template <class T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other) {
	delete[] arr;
	_size = other.size();
	_capacity = other.capacity();
	arr = new T[other.capacity()];
	std::copy(other.arr, other.arr + other.size(), arr);
	return *this;
};

template <class T>
Vector<T>& Vector<T>::operator+=(const Vector<T>& other) {
	size_t temp = _size;
	resize(_size + other.size());
	std::copy(other.arr, other.arr + other.size(), arr + temp);
	return *this;
};

template <class T>
T& Vector<T>::operator[](const size_t i) {
	return *(arr + i);
};

template <class T>
typename Vector<T>::Iter Vector<T>::begin() const {
	return Iter(arr);
};

template <class T>
typename Vector<T>::Iter Vector<T>::end() const {
	return Iter(arr + _size);
};

template <class T>
size_t Vector<T>::capacity() const {
	return _capacity;
};

template <class T>
size_t Vector<T>::size() const {
	return _size;
};

template <class T>
void Vector<T>::clear() {
	delete[] arr;
	_size = 0;
	_capacity = 0;
};

template <class T>
void Vector<T>::pop_back() {
	--_size;
};

template <class T>
void Vector<T>::push_back(const T& new_data) {
	if (_size == _capacity) {
		reserve(1 + R_COEF * _size);
	}
	arr[_size] = new_data;
	_size++;
};

template<class T>
void Vector<T>::reserve(size_t new_capacity) {
	if (_capacity >= new_capacity) {
		return;
	}
	_capacity = new_capacity;
	T* temp = new T[_capacity];
	std::copy(arr, arr + _size, temp);
	delete[] arr;
	arr = temp;
};

template<class T>
void Vector<T>::resize(size_t new_size) {
	if(new_size > _capacity) {
		reserve(new_size);
	}
	_size = new_size;

};

template<class T>
void Vector<T>::resize(size_t new_size, const T& default_value) {
	size_t temp = _size;
	arr.resize(new_size);
	if (temp < new_size) {
		fill(arr + temp, arr + new_size, default_value);
	}
};
