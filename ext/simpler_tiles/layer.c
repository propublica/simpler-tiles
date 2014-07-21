#include "layer.h"
#include <simple-tiles/layer.h>
#include <simple-tiles/list.h>

static simplet_layer_t *
get_layer(VALUE self){
  simplet_layer_t *layer;
  Data_Get_Struct(self, simplet_layer_t, layer);
  return layer;
}

/*
Set the source attribute for the Layer.

@return (String)
@param (String)
*/
VALUE
set_source(VALUE self, VALUE source){
  Check_Type(source, T_STRING);
  simplet_layer_t *layer = get_layer(self);
  simplet_layer_set_source(layer, RSTRING_PTR(source));
  return source;
}

/*
Get a copy of the Layer's source.

@return (String)
*/
VALUE
get_source(VALUE self) {
  simplet_layer_t *layer = get_layer(self);
  char *source;
  simplet_layer_get_source(layer, &source);
  return rb_str_new2(source);
}