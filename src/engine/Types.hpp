#pragma once
#include <memory>

typedef unsigned int uint;
typedef unsigned char byte;

template<typename T> using Ref = std::shared_ptr<T>;


//CreateRef
template<typename T, typename... Args>
constexpr Ref<T> CreateRef(Args&&... args) {
    return std::make_shared<T>(std::forward<Args>(args)...);
}