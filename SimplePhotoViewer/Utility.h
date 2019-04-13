#pragma once

namespace winrt::SimplePhotoViewer
{
	/*find_if for winrt vector collections,searching [first,end) in the collection.*/
	template<class InputIt, class UnaryPredicate>
	constexpr InputIt find_if(InputIt first, UnaryPredicate p)
	{
		for (; first.HasCurrent(); first.MoveNext())
		{
			if (p(first.Current()))
			{
				return first;
			}
		}
		return first;
	}

	template<class InputIt, class UnaryPredicate>
	auto find_index(InputIt first, UnaryPredicate p)
	{
		uint32_t resultIndex = 0;
		for (; first.HasCurrent(); first.MoveNext(), ++resultIndex)
		{
			if (p(first.Current()))
			{
				return resultIndex;
			}
		}
		return resultIndex;
	}

	template<class InputIt, class UnaryPredicate, class Vector>
	auto find_all(InputIt first, UnaryPredicate p, Vector &resultVector)
	{
		for (; first.HasCurrent(); first.MoveNext())
		{
			if (p(first.Current()))
			{
				resultVector.Append(first.Current());
			}
		}
	}

}