#include "raster_layer.h"
#include "layer.h"
#include <simple-tiles/layer.h>
#include <simple-tiles/raster_layer.h>
#include <simple-tiles/list.h>

VALUE cSimplerTilesRasterLayer;

static void
mark_layer(void *layer){
  simplet_raster_layer_t *lyr = layer;
  VALUE ref = (VALUE)simplet_raster_layer_get_user_data(lyr);
  if(ref) rb_gc_mark(ref);
}

static void
layer_free(void *layer){
  simplet_raster_layer_t *lyr = layer;
  simplet_raster_layer_free(lyr);
}

VALUE
raster_layer_alloc(VALUE klass){
  simplet_raster_layer_t *layer;
  if(!(layer = simplet_raster_layer_new("")))
    rb_fatal("Could not allocate space for a new SimplerTiles::Layer in memory.");

  return Data_Wrap_Struct(klass, mark_layer, layer_free, layer);
}

void init_raster_layer(){
  VALUE rRasterLayer = rb_define_class_under(mSimplerTiles, "RasterLayer", rb_cObject);
  rb_define_alloc_func(rRasterLayer, raster_layer_alloc);

  rb_define_method(rRasterLayer, "source=", set_source, 1);
  rb_define_method(rRasterLayer, "source", get_source, 0);

  cSimplerTilesRasterLayer = rRasterLayer;
}
