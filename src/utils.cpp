#ifdef _WIN32
#include <io.h>
#else
#include <unistd.h>
#include <libgen.h>
#include <string.h>
#endif

#pragma warning(push, 0)
#include <FL/fl_draw.H>
#include <FL/filename.H>
#pragma warning(pop)

#include "utils.h"

const std::string whitespace(" \f\n\r\t\v");

bool starts_with(const std::string &s, const std::string &p) {
	return !s.compare(0, p.size(), p);
}

bool ends_with(const std::string &s, const std::string &p) {
	return s.size() >= p.size() && !s.compare(s.size() - p.size(), p.size(), p);
}

void trim(std::string &s, const std::string &t) {
	std::string::size_type p = s.find_first_not_of(t);
	s.erase(0, p);
	p = s.find_last_not_of(t);
	s.erase(p + 1);
}

void remove_comment(std::string &s, char c) {
	size_t p = s.find(c);
	if (p != std::string::npos) {
		s.erase(p);
	}
}

int text_width(const char *l, int pad) {
	int lw = 0, lh = 0;
	fl_measure(l, lw, lh, 0);
	return lw + 2 * pad;
}

bool file_exists(const char *f) {
#ifdef _WIN32
	return !_access_s(f, 4);
#else
	return !access(f, 4);
#endif
}

bool dir_name(const char *f, char *d) {
#ifdef _WIN32
	char e[FL_PATH_MAX] = {};
	if (_splitpath_s(f, d, FL_PATH_MAX, e, FL_PATH_MAX, NULL, 0, NULL, 0)) {
		return false;
	}
	strcat(d, e);
#else
	char *f2 = strdup(f);
	strcpy(d, dirname(f2));
	free(f2);
	strcat(d, DIR_SEP);
#endif
	return true;
}
