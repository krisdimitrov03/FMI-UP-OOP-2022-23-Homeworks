#pragma once
#include "Set.hpp"

template <typename T>
class UnionSet : public Set<T>
{
public:
	UnionSet() = default;
	UnionSet(const Set<T>** sets, size_t setsCount, bool& isError);
};

template<typename T>
inline UnionSet<T>::UnionSet(const Set<T>** sets, size_t setsCount, bool& isError)
{
	if (sets == nullptr) {
		isError = true;
		return;
	}

	if (setsCount == 0) {
		isError = true;
		return;
	}

	for (size_t i = 0; i < setsCount; i++)
		for (size_t j = 0; j < sets[i]->length(); j++)
			Set<T>::add((*sets[i])[j]);
}