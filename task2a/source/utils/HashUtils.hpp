#ifndef HASHUTILS_HPP
#define HASHUTILS_HPP

#include <utility>
#include <functional>

namespace std {
	template <typename T1, typename T2>
	struct hash<std::pair<T1, T2>> {
		std::size_t operator()(const std::pair<T1, T2>& pair) const {
			std::size_t h1 = std::hash<T1>{}(pair.first);
			std::size_t h2 = std::hash<T2>{}(pair.second);
			return h1 ^ (h2 << 1); // Простое комбинирование хэшей
		}
	};
}

#endif
