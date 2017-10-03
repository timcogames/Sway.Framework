#include "size.h"

NAMESPACE_BEGIN(std)

template <typename type>
inline ostream &operator<<(ostream &str, const sway::math::TSize<type> &size)
{
	return str << '(' << size.getW() << ' ' << size.getH() << ')';
}

template <typename type>
inline string to_string(const sway::math::TSize<type>& size)
{
	stringstream stream;
	stream << size;
	return stream.str();
}

NAMESPACE_END(std)