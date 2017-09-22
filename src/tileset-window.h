#ifndef TILESET_WINDOW_H
#define TILESET_WINDOW_H

#include <string>

#pragma warning(push, 0)
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>
#pragma warning(pop)

#include "tileset.h"
#include "map-buttons.h"
#include "palette-map.h"
#include "metatile.h"
#include "widgets.h"

#define TILES_PER_ROW 16
#define TILES_PER_COL (MAX_NUM_TILES / TILES_PER_ROW)
#define TILE_PX_SIZE (TILE_SIZE * 2)
#define CHIP_PX_SIZE (TILE_SIZE * 3)

class Tileset_Window {
private:
	int _dx, _dy;
	uint8_t _metatile_id;
	const Tileset *_tileset;
	bool _canceled;
	Fl_Double_Window *_window;
	Label *_tileset_heading, *_metatile_heading;
	Fl_Group *_tileset_group, *_metatile_group;
	Tile_Button *_tile_buttons[MAX_NUM_TILES], *_selected;
	Chip *_chips[METATILE_SIZE * METATILE_SIZE];
	Default_Button *_ok_button;
	OS_Button *_cancel_button;
public:
	Tileset_Window(int x, int y);
	~Tileset_Window();
private:
	void initialize(void);
	void refresh(void);
public:
	void tileset(const Tileset *t);
	void metatile(const Metatile *mt);
	inline uint8_t tile_id(int x, int y) { return _chips[y * METATILE_SIZE + x]->id(); }
	inline bool canceled(void) const { return _canceled; }
	inline void canceled(bool c) { _canceled = c; }
	void show(const Fl_Widget *p);
	void draw_tile(int x, int y, uint8_t id, bool z = false);
private:
	static void close_cb(Fl_Widget *w, Tileset_Window *tw);
	static void cancel_cb(Fl_Widget *w, Tileset_Window *tw);
	static void select_tile_cb(Tile_Button *tb, Tileset_Window *tw);
	static void change_chip_cb(Chip *c, Tileset_Window *tw);
};

#endif