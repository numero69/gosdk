#include "dependencies/global.hpp"
#include "utilities/global.hpp"
#include "csgo/valve/global.hpp"

#include "config/global.hpp"

LPVOID InitializeHack(HMODULE Instance)
{
	utilities::globals::this_module = Instance;
	try {
		utilities::console::initialize_console(
			STR("gosdk"), STR("welcome, initialized"));

		// run config before everything
		config::run_config();

		csgo::valve::interfaces::run_interfaces();
		utilities::hooking::run_hooks();
	} catch (const std::exception &e) {
		utilities::console::log<std::string>(e.what());
	}

	while (!utilities::globals::should_unload) {
		using namespace std::chrono_literals;
		std::this_thread::sleep_for(15ms);
	}

	// just in case
	try {
		utilities::console::destroy_console();
		utilities::hooking::release_hooks();
		csgo::valve::interfaces::release_interfaces();

		// release config after everything
		config::release_config();
	} catch (const std::exception &e) {
		utilities::console::log<std::string>(e.what());
	}
	FreeLibraryAndExitThread(Instance, NULL);
}

std::uint8_t WINAPI DllMain(HINSTANCE Instance, DWORD CallReason,
			    LPVOID Reserved [[maybe_unused]])
{
	if (CallReason != DLL_PROCESS_ATTACH)
		return false;

	const auto ThreadHandle = CreateThread(
		nullptr, NULL,
		reinterpret_cast<LPTHREAD_START_ROUTINE>(InitializeHack),
		reinterpret_cast<LPVOID>(Instance), NULL, nullptr);

	if (ThreadHandle == nullptr || ThreadHandle == INVALID_HANDLE_VALUE) {
		MessageBoxA(nullptr,
			    STR("failed to create initialization thread."),
			    STR("error"), MB_OKCANCEL);
		return false;
	}

	CloseHandle(ThreadHandle);
	return true;
}