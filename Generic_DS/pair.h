#pragma once

template<typename T, typename L>
class pair
{
public:
	pair(T f, L s);
	pair();
	T first;
	L second;
	void make_pair(T f, L s);
	~pair();

private:

};

template<typename T, typename L>
inline pair<T,L>::pair(T f, L s)
{
	first = f;
	second = s;
}

template<typename T, typename L>
inline pair<T, L>::pair()
{
	first = NULL;
	second = NULL;
}

template<typename T, typename L>
inline void pair<T,L>::make_pair(T f, L s)
{
	first = f;
	second = s;
	return;
}

template<typename T, typename L>
inline pair<T,L>::~pair()
{
}
