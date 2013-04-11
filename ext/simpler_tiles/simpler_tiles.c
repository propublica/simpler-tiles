#include "simpler_tiles.h"

VALUE mSimplerTiles;

void
Init_simpler_tiles(){
  mSimplerTiles = rb_define_module("SimplerTiles");
  init_map();
  init_bounds();
  init_layer();
  init_query();
  init_style();
}
