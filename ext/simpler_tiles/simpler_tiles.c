#include "simpler_tiles.h"

VALUE mSimplerTiles;

void
Init_simpler_tiles(){
  mSimplerTiles = rb_define_module("SimplerTiles");
  rb_const_set(mSimplerTiles,
              rb_intern("SIMPLE_TILES_VERSION"),
              rb_str_new2(SIMPLE_TILES_VERSION));
  init_map();
  init_bounds();
}
