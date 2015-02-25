#include "raster_layer.h"
#include "layer.h"
#include <simple-tiles/layer.h>
#include <simple-tiles/raster_layer.h>
#include <simple-tiles/list.h>

VALUE cSimplerTilesRasterLayer;

static simplet_raster_layer_t *
get_layer(VALUE self){
  simplet_raster_layer_t *layer;
  Data_Get_Struct(self, simplet_raster_layer_t, layer);
  return layer;
}

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

static VALUE
lanczos(VALUE self, VALUE boolean){
  simplet_raster_layer_t *layer = get_layer(self);
  simplet_raster_layer_set_resample(layer, SIMPLET_LANCZOS);
  return Qnil;
}

static VALUE
bilinear(VALUE self, VALUE boolean){
  simplet_raster_layer_t *layer = get_layer(self);
  simplet_raster_layer_set_resample(layer, SIMPLET_BILINEAR);
  return Qnil;
}

static VALUE
nearest(VALUE self, VALUE boolean){
  simplet_raster_layer_t *layer = get_layer(self);
  simplet_raster_layer_set_resample(layer, SIMPLET_NEAREST);
  return Qnil;
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

  rb_define_method(rRasterLayer, "bilinear!", bilinear, 0);
  rb_define_method(rRasterLayer, "lanczos!", lanczos, 0);
  rb_define_method(rRasterLayer, "nearest!", nearest, 0);

  cSimplerTilesRasterLayer = rRasterLayer;
}
