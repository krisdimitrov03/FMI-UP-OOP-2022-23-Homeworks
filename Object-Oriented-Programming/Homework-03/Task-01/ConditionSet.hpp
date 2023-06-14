#pragma once
#include "Set.hpp"

template <typename T>
class ConditionSet : public Set<T> 
{
	bool(*condition)(const T&, const T*, size_t) = nullptr;
public:
	ConditionSet();
	ConditionSet(bool (*arg)(const T&, const T*, size_t));

	bool compare(const T& element) const;
};

template<typename T>
inline ConditionSet<T>::ConditionSet()
{
	condition = [](const T&, const T*, size_t) {
		return true;
	};
}

template<typename T>
inline ConditionSet<T>::ConditionSet(bool(*arg)(const T&, const T*, size_t))
	: condition(arg)
{
}

template<typename T>
inline bool ConditionSet<T>::compare(const T& element) const
{
	return condition(element, Set<T>::elements);
}
