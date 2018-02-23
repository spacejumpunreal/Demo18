#pragma once
#include "Demo18.h"
#include "Utils.h"

namespace Demo18
{
	template<typename T>
	using IRef = std::shared_ptr<T>;

	using ByteBlob = std::vector<uint8_t>;
	using SharedBytes = IRef<ByteBlob>;

	inline SharedBytes CreateSharedBytes(size_t sz, void* initData = nullptr)
	{
		auto blob = new ByteBlob(sz);
		Copy(initData, blob->data(), sz);
		return IRef<ByteBlob>(blob);
	}
}