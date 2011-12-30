#include "layer.h"
#include <simple-tiles/layer.h>
#include <simple-tiles/filter.h>
#include <simple-tiles/list.h>

VALUE cSimplerTilesLayer;

static simplet_layer_t *
get_layer(VALUE self){
  simplet_layer_t *layer;
  Data_Get_Struct(self, simplet_layer_t, layer);
  return layer;
}

static void
mark_layer(void *layer){
  simplet_layer_t *lyr = layer;
  VALUE ref = (VALUE)simplet_layer_get_user_data(lyr);
  if(ref) rb_gc_mark(ref);
}

static void
layer_free(void *layer){
  simplet_layer_t *lyr = layer;
  // test if we have been linked in ruby land
  VALUE refs = (VALUE)simplet_layer_get_user_data(lyr);
  // if not it is safe to free this layer.
  if(!refs) simplet_layer_free(lyr);
}

static VALUE
set_source(VALUE self, VALUE source){
  Check_Type(source, T_STRING);
  simplet_layer_t *layer = get_layer(self);
  simplet_layer_set_source(layer, RSTRING_PTR(source));
  return source;
}

static VALUE
get_source(VALUE self) {
  simplet_layer_t *layer = get_layer(self);
  char *source;
  simplet_layer_get_source(layer, &source);
  return rb_str_new2(source);
}

static VALUE
add_filter(VALUE self, VALUE filter){
  simplet_layer_t *layer = get_layer(self);
  simplet_filter_t *fltr;
  Data_Get_Struct(filter, simplet_filter_t, fltr);
  simplet_layer_add_filter_directly(layer, fltr);
  VALUE circ_ref = rb_ary_new3(2, self, filter);
  simplet_filter_set_user_data(fltr, (void *)circ_ref);
  return filter;
}

// rb_define_alloc_func
VALUE
layer_alloc(VALUE klass){
  simplet_layer_t *layer;
  if(!(layer = simplet_layer_new("")))
    rb_fatal("Could not allocate space for a new SimplerTiles::Layer in memory.");

  return Data_Wrap_Struct(klass, mark_layer, layer_free, layer);
}

// use rb_define_alloc_func everywhere
void init_layer(){
  VALUE rlayer = rb_define_class_under(mSimplerTiles, "Layer", rb_cObject);
  rb_define_alloc_func(rlayer, layer_alloc);
  rb_define_method(rlayer, "source=", set_source, 1);
  rb_define_method(rlayer, "source", get_source, 0);
  rb_define_private_method(rlayer, "add_filter", add_filter, 1);

  cSimplerTilesLayer = rlayer;
}
