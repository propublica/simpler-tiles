#include "layer.h"
#include <simple-tiles/layer.h>

static simplet_layer_t *
get_layer(VALUE self){
  simplet_layer_t *layer;
  Data_Get_Struct(self, simplet_layer_t, layer);
  return layer;
}


static VALUE
set_source(VALUE self, VALUE source){
  Check_Type(source, T_STRING);
  simplet_layer_t *layer = get_layer(self);
  simplet_layer_set_source(layer, RESTRING_PTR(source));
  return source;
}

static VALUE
get_source(VALUE self) {
  simplet_layer_t *layer = get_layer(self);
  char *source;
  simplet_layer_get_source(layer, &source);
  return rb_string_new2(source);
}

static VALUE
add_filter(VALUE self, VALUE sql){
  Check_Type(sql, T_STRING);
  simplet_layer_t *layer = get_layer(self);
  simplet_layer_add_filter(layer, RSTRING_PTR(sql));
  return Qnil;
}

// rb_define_alloc_func
VALUE
layer_alloc(VALUE klass){
  simplet_layer_t *layer;
  if(!(layer = simplet_layer_new("")))
    rb_fatal("Could not allocate space for a new SimplerTiles::Layer in memory.");

  return Data_Wrap_Struct(klass, NULL, simplet_layer_free, filter);
}

// use rb_define_alloc_func everywhere
void init_layer(){
  VALUE rlayer = rb_define_class_under(mSimplerTiles, "Layer", rb_cObject);
  rb_define_alloc_func(rlayer, layer_alloc);
  rb_define_method(rlayer, "source=", set_source, 1);
  rb_define_method(rlayer, "source", get_source, 0);
  rb_define_method(rlayer, "add_filter", add_filter, 1);

  cSimplerTilesLayer = rlayer;
}