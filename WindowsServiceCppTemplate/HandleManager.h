#pragma once
#include <functional>
#include <utility>

template<typename Handle>
class HandleManager {
private:
	Handle handle;
	std::function<void(Handle&)> Close;
public:
	HandleManager(Handle&& h, const std::function<void(Handle&)>& CloseFunc) : handle(std::move(h)), Close(CloseFunc) { h = nullptr; }
	HandleManager(std::nullptr_t) : handle(nullptr), Close(nullptr) {}
	~HandleManager() {
		if (this->handle != nullptr) {
			this->Close(this->handle);
			this->handle = nullptr;
		}
	}
	HandleManager(const HandleManager&) = delete;
	HandleManager(HandleManager&& h) : handle(std::move(h.handle)) { h.handle = nullptr; }
	HandleManager& operator = (const HandleManager&) = delete;
	HandleManager& operator = (HandleManager&& h) {
		this->handle = std::move(h.handle);
		h.handle = nullptr;
		return *this;
	}
	operator const Handle& () const noexcept { return this->handle; }
	operator Handle& () noexcept { return this->handle; }
};
