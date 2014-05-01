#include "raster_layer.h"
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

/*
Set the source attribute for the Layer.

@return (String)
@param (String)
*/
static VALUE
set_source(VALUE self, VALUE source){
  Check_Type(source, T_STRING);
  simplet_raster_layer_t *layer = get_layer(self);
  simplet_raster_layer_set_source(layer, RSTRING_PTR(source));
  return source;
}

/*
Get a copy of the Layer's source.

@return (String)
*/
static VALUE
get_source(VALUE self) {
  simplet_raster_layer_t *layer = get_layer(self);
  char *source;
  simplet_raster_layer_get_source(layer, &source);
  return rb_str_new2(source);
}

VALUE
raster_layer_alloc(VALUE klass){
  simplet_raster_layer_t *layer;
  if(!(layer = simplet_raster_layer_new("")))
    rb_fatal("Could not allocate space for a new SimplerTiles::Layer in memory.");

  return Data_Wrap_Struct(klass, mark_layer, layer_free, layer);
}

void init_raster_layer(){
  VALUE rLayer = rb_define_class_under(mSimplerTiles, "Layer", rb_cObject);
  VALUE rRasterLayer = rb_define_class_under(mSimplerTiles, "RasterLayer", rLayer);
  rb_define_alloc_func(rRasterLayer, raster_layer_alloc);
  rb_define_method(rRasterLayer, "source=", set_source, 1);
  rb_define_method(rRasterLayer, "source", get_source, 0);

  cSimplerTilesRasterLayer = rRasterLayer;
}
