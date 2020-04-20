#pragma once
#include <Windows.h>
#include <functional>
#include <utility>

namespace windows {
	namespace impl {
		template<typename Handle>
		class HandleManager {
		private:
			Handle handle;
			std::function<void(Handle&)> Close;
		public:
			HandleManager(Handle&& h, std::function<void(Handle&)>&& CloseFunc) : handle(std::move(h)), Close(std::move(CloseFunc)) { h = nullptr; }
			HandleManager(std::nullptr_t) : handle(nullptr), Close(nullptr) {}
			~HandleManager() {
				if (this->handle != nullptr) {
					this->Close(this->handle);
					this->handle = nullptr;
				}
			}
			HandleManager(const HandleManager&) = delete;
			HandleManager(HandleManager&& h) : handle(std::move(h.handle)), Close(std::move(h.Close)) { h.handle = nullptr; }
			HandleManager& operator = (const HandleManager&) = delete;
			HandleManager& operator = (HandleManager&& h) {
				this->handle = std::move(h.handle);
				this->Close = std::move(h.Close);
				h.handle = nullptr;
				h.Close = nullptr;
				return *this;
			}
			operator const Handle& () const noexcept { return this->handle; }
			operator Handle& () noexcept { return this->handle; }
			const Handle* operator & () const noexcept { return &this->handle; }
			Handle* operator & () noexcept { return &this->handle; }
		};
		inline void CloseNormalHandle(HANDLE& h) {
			if (h != nullptr) {
				CloseHandle(h);
				h = nullptr;
			}
		}

		inline void CloseWinServiceHandle(SC_HANDLE& h) {
			if (h != nullptr) {
				CloseServiceHandle(h);
				h = nullptr;
			}
		}
	}

	class Handle : public impl::HandleManager<HANDLE> {
	public:
		Handle(HANDLE&& h) : impl::HandleManager<HANDLE>(std::move(h), [](HANDLE& h) { CloseHandle(h); }) {}
	};

	class ServiceHandle : public impl::HandleManager<SC_HANDLE> {
	public:
		ServiceHandle(SC_HANDLE&& h) : impl::HandleManager<SC_HANDLE>(std::move(h), [](SC_HANDLE& h) { CloseServiceHandle(h); }) {}
	};
}
