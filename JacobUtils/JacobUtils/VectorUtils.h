#include <vector>
#include <algorithm>

namespace VectorUtils
{
	template<typename T>
	int removeOverlap(std::vector<T>& eraseFrom, std::vector<T>& toErase)
	{
		typename std::vector<T>::iterator itr = toErase.begin();
		typename std::vector<T>::iterator itrLast = toErase.end();
		for(; itr != itrLast; ++itr)
		{
		  eraseFrom.erase(std::remove(eraseFrom.begin(),
		  							  eraseFrom.end(), 
		  							  *itr),
		  							  eraseFrom.end());
		};

		return (1);
	}; // End removeOverlap
}; // End namespace VectorUtils
