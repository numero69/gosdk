#include "dependencies/global.hpp"
#include "utilities/global.hpp"
#include "csgo/valve/global.hpp"
#include "config/global.hpp"

LPVOID initialize_hack(HMODULE instance)
{
	utilities::globals::this_module = instance;
	try {
		utilities::console::initialize_console(
			STR("gosdk"), STR("welcome, initialized"));

		// run config before everything
		config::run_config();
		csgo::valve::interfaces::run_interfaces();
		utilities::render::run_render();
		utilities::hooking::run_hooks();
		csgo::valve::netvar::init();
	} catch (const std::exception &e) {
		utilities::console::log<std::string>(e.what());
	}

	while (!utilities::globals::should_unload) {
		using namespace std::chrono_literals;
		std::this_thread::sleep_for(15ms);
	}

	utilities::console::destroy_console();
	utilities::hooking::release_hooks();
	utilities::render::release_render();
	csgo::valve::interfaces::release_interfaces();

	// release config after everything
	config::release_config();

	FreeLibraryAndExitThread(instance, NULL);
}

std::uint8_t WINAPI DllMain(HINSTANCE instance, DWORD call_reason,
			    LPVOID reserved [[maybe_unused]])
{
	if (call_reason != DLL_PROCESS_ATTACH)
		return false;

	const auto thread_handle = CreateThread(
		nullptr, NULL,
		reinterpret_cast<LPTHREAD_START_ROUTINE>(initialize_hack),
		reinterpret_cast<LPVOID>(instance), NULL, nullptr);

	if (thread_handle == nullptr || thread_handle == INVALID_HANDLE_VALUE) {
		MessageBoxA(nullptr,
			    STR("failed to create initialization thread."),
			    STR("error"), MB_OKCANCEL);
		return false;
	}

	CloseHandle(thread_handle);
	return true;
}
