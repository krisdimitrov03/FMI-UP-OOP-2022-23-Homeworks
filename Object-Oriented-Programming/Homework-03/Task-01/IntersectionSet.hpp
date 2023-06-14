#pragma once
#include "Set.hpp"

template <typename T>
class IntersectionSet : public Set<T>
{
public:
	IntersectionSet() = default;
	IntersectionSet(const Set<T>** sets, size_t setsCount, bool& isError);
};

template<typename T>
inline IntersectionSet<T>::IntersectionSet(const Set<T>** sets, size_t setsCount, bool& isError) : Set<T>()
{
	if (sets == nullptr) {
		isError = true;
		return;
	}

	if (setsCount == 0) {
		isError = true;
		return;
	}

	for (size_t i = 0; i < sets[0]->length(); i++)
	{
		const T& elementToSearch = (*sets[0])[i];
		bool isInAll = true;

		for (size_t j = 1; j < setsCount; j++)
		{
			if (!sets[j]->contains(elementToSearch)) {
				isInAll = false;
				break;
			}
		}

		if (isInAll)
			Set<T>::add(elementToSearch);
	}
}