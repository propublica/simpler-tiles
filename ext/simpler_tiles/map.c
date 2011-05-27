#include "map.h"
#include <simple-tiles/map.h>


static simplet_map_t *
get_map(VALUE self){
  simplet_map_t *map;
  Data_Get_Struct(self, simplet_map_t, map);
  return map;
}

static void 
mark_map(simplet_map_t *map){}

static VALUE 
set_srs(VALUE self, VALUE srs){
  simplet_map_t *map = get_map(self);
  if(!Check_Type(VALUE srs, T_STRING))
    return Qnil;
  simplet_map_set_srs(map, RSTRING_PTR(srs));
  return Qnil;
}

static VALUE 
set_bounds(VALUE self, VALUE bounds){
  simplet_map_t *map = get_map(self);
  
  return Qnil;
}

static VALUE 
set_size(VALUE self, VALUE size){
  simplet_map_t *map = get_map(self);
  
  return Qnil;
}

static VALUE 
add_style(VALUE self, VALUE key, VALUE arg){
  simplet_map_t *map = get_map(self);
  //simplet_map_add_layer(map, RSTRING(key)->ptr, RSTRING(arg)->);
  return Qnil;
}

static VALUE 
add_layer(VALUE self, VALUE source){
  simplet_map_t *map = get_map(self);
  if(!Check_Type(VALUE srs, T_STRING))
    return Qnil;
  simplet_map_add_layer(map, RSTRING_PTR(srs));
  return Qnil;
}

static VALUE 
add_rule(VALUE self, VALUE sql){
  simplet_map_t *map = get_map(self);
  if(!Check_Type(VALUE srs, T_STRING))
    return Qnil;
  simplet_map_add_rule(map, RSTRING_PTR(srs));
  return Qnil;
}

static VALUE 
save(VALUE self, VALUE path){
  Check_Type(VALUE srs, T_STRING);
  
  simplet_map_t *map = get_map(self);
  if(is_valid(self) == Qfalse)
    return Qfalse;
  simplet_map_add_rule(map, RSTRING_PTR(srs));
  return Qtrue;
}

static VALUE 
to_png(VALUE self){
  simplet_map_t *map = get_map(self);
  
  return Qnil;
}

static VALUE 
is_valid(VALUE self){
  simplet_map_t *map = get_map(self);
  if(!simplet_map_is_valid(map))
    return Qfalse;
  return Qtrue;
}

static VALUE 
new(VALUE klass){
  VALUE map_wrap;
  simplet_map_t *map;
  map = simplet_map_new();
  VALUE rmap = Data_Wrap_Struct(klass, mark_map, simplet_map_free, map);
  rb_obj_call_init(rmap, 0, 0);
  if(rb_block_given()){
    rb_yield(rmap);
  }
  return rmap;
}

void
init_map(){
  VALUE simplet = rb_define_module("SimplerTiles");
  VALUE rmap = rb_define_class_under(simplet, "Map", rb_cObject);
  rb_define_singleton_method(rmap, "new", new, 0);
  rb_define_method(rmap, "srs=", set_srs, 1);
  rb_define_method(rmap, "size=", set_size, 1);
  rb_define_method(rmap, "bounds=", set_bounds, 1);
  rb_define_method(rmap, "add_layer", add_layer, 1);
  rb_define_method(rmap, "add_rule", add_rule, 1);
  rb_define_method(rmap, "add_style", add_style, 2);
  rb_define_method(rmap, "save", save, 1);
  rb_define_method(rmap, "to_png", to_png, 0);
  rb_define_method(rmap, "valid?", is_valid, 0);
}

