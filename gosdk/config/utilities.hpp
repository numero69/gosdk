#pragma once
#include "config.hpp"

namespace config
{
inline void run_config()
{
	configs = std::make_unique<config::settings>();
}

inline void release_config()
{
	configs.reset();
}
inline void to_clipboard(const std::string &s)
{
	OpenClipboard(0);
	EmptyClipboard();
	HGLOBAL hg = GlobalAlloc(GMEM_MOVEABLE, s.size());
	if (!hg) {
		CloseClipboard();
		return;
	}
	memcpy(GlobalLock(hg), s.c_str(), s.size());
	GlobalUnlock(hg);
	SetClipboardData(CF_TEXT, hg);
	CloseClipboard();
	GlobalFree(hg);
}
} // namespace config