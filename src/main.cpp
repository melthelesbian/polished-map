#include <iostream>

#pragma warning(push, 0)
#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Window.H>
#pragma warning(pop)

#include "version.h"
#include "preferences.h"
#include "themes.h"
#include "main-window.h"

#ifdef _WIN32

#include <shlobj.h>
#include <tchar.h>

#define MAKE_WSTR_HELPER(x) L ## x
#define MAKE_WSTR(x) MAKE_WSTR_HELPER(x)

#endif

static void use_theme(OS::Theme theme) {
	OS::use_native_font();
	switch (theme) {
	case OS::Theme::AERO:
		OS::use_aero_theme();
		return;
	case OS::Theme::METRO:
		OS::use_metro_theme();
		return;
	case OS::Theme::GREYBIRD:
		OS::use_greybird_theme();
		return;
	case OS::Theme::BLUE:
		OS::use_blue_theme();
		return;
	case OS::Theme::DARK:
		OS::use_dark_theme();
	}
}

int main(int argc, char **argv) {
	std::ios::sync_with_stdio(false);
#ifdef _WIN32
	SetCurrentProcessExplicitAppUserModelID(MAKE_WSTR(PROGRAM_AUTHOR) L"." MAKE_WSTR(PROGRAM_NAME));
#endif
	Fl::visual(FL_DOUBLE | FL_RGB);

#ifdef _WIN32
	OS::Theme theme = (OS::Theme)Preferences::get("theme", (int)OS::Theme::BLUE);
#else
	OS::Theme theme = (OS::Theme)Preferences::get("theme", (int)OS::Theme::GREYBIRD);
#endif
	use_theme(theme);

#ifdef _WIN32
	int x = Preferences::get("x", 48), y = Preferences::get("y", 48 + GetSystemMetrics(SM_CYCAPTION));
#else
	int x = Preferences::get("x", 48), y = Preferences::get("y", 48);
#endif
	int w = Preferences::get("w", 640), h = Preferences::get("h", 480);
	Main_Window window(x, y, w, h);
	window.show();

	if (argc > 1) {
		window.open_map(argv[1]);
	}

	return Fl::run();
}
