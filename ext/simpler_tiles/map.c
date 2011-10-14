#include "map.h"
#include <simple-tiles/map.h>


VALUE cSimplerTilesMap;

static simplet_map_t *
get_map(VALUE self){
  simplet_map_t *map;
  Data_Get_Struct(self, simplet_map_t, map);
  return map;
}

static void
mark_map(simplet_map_t *map){ (void) map; }

static VALUE
set_bgcolor(VALUE self, VALUE bgcolor){
  Check_Type(bgcolor, T_STRING);
  simplet_map_t *map = get_map(self);
  simplet_map_set_bgcolor(map, RSTRING_PTR(bgcolor));
  return Qnil;
}

static VALUE
get_bgcolor(VALUE self){
  simplet_map_t *map = get_map(self);
  char *color;
  simplet_map_get_bgcolor(map, &color);
  return rb_str_new2(color);
}

static VALUE
set_srs(VALUE self, VALUE srs){
  Check_Type(srs, T_STRING);
  simplet_map_t *map = get_map(self);
  simplet_map_set_srs(map, RSTRING_PTR(srs));
  return Qnil;
}

static VALUE
get_srs(VALUE self){
  simplet_map_t *map = get_map(self);
  char *srs;
  simplet_map_get_srs(map, &srs);
  return rb_str_new2(srs);
}

static VALUE
set_bounds(VALUE self, VALUE maxx, VALUE maxy, VALUE minx, VALUE miny){
  simplet_map_t *map = get_map(self);
  simplet_map_set_bounds(map, NUM2DBL(maxx), NUM2DBL(maxy), NUM2DBL(minx), NUM2DBL(miny));
  return Qnil;
}

static VALUE
bounds(VALUE self){
  simplet_map_t *map = get_map(self);
  VALUE args[4];
  args[0] = rb_float_new(map->bounds->nw.x);
  args[1] = rb_float_new(map->bounds->nw.y);
  args[2] = rb_float_new(map->bounds->se.x);
  args[3] = rb_float_new(map->bounds->se.y);
  return rb_funcall2(cSimplerTilesBounds, rb_intern("new"), 4, args);
}

static VALUE
set_size(VALUE self, VALUE width, VALUE height){
  simplet_map_t *map = get_map(self);
  simplet_map_set_size(map, NUM2INT(width), NUM2INT(height));
  return Qnil;
}

static VALUE
set_width(VALUE self, VALUE width){
  simplet_map_t *map = get_map(self);
  map->width = NUM2INT(width);
  return INT2NUM(map->width);
}

static VALUE
set_height(VALUE self, VALUE height){
  simplet_map_t *map = get_map(self);
  map->height = NUM2INT(height);
  return INT2NUM(map->height);
}

static VALUE
get_width(VALUE self){
  simplet_map_t *map = get_map(self);
  return INT2NUM(map->width);
}

static VALUE
get_height(VALUE self){
  simplet_map_t *map = get_map(self);
  return INT2NUM(map->height);
}

// TODO: return newly created layer
static VALUE
add_layer(VALUE self, VALUE source){
  Check_Type(source, T_STRING);
  simplet_map_t *map = get_map(self);
  simplet_map_add_layer(map, RSTRING_PTR(source));
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
save(VALUE self, VALUE path){
  Check_Type(path, T_STRING);
  if(!is_valid(self)) return Qfalse;
  simplet_map_t *map = get_map(self);
  simplet_map_render_to_png(map, RSTRING_PTR(path));
  if(simplet_map_get_status(map) == SIMPLET_OK) {
    return Qtrue;
  } else {
    rb_raise(rb_eRuntimeError, simplet_map_status_to_string(map));
    return Qfalse;
  }
}

static cairo_status_t
stream(void* stream, const unsigned char *data, unsigned int length){
  Check_Type((VALUE)stream, T_STRING);
  rb_str_cat((VALUE)stream, (const char *)data, (long)length);
  return CAIRO_STATUS_SUCCESS;
}


static VALUE
to_png(VALUE self){
  simplet_map_t *map = get_map(self);
  VALUE data;
  char *cdata = "";
  data = rb_str_new2(cdata);
  simplet_map_render_to_stream(map, (void *)data, stream);
  if(simplet_map_get_status(map) != SIMPLET_OK)
    rb_raise(rb_eRuntimeError, simplet_map_status_to_string(map));

  if(rb_block_given_p()) rb_yield(data);
  return data;
}

static VALUE
slippy(VALUE self, VALUE x, VALUE y, VALUE z){
  simplet_map_t *map = get_map(self);
  if(simplet_map_set_slippy(map, NUM2INT(x), NUM2INT(y), NUM2INT(z)))
    return Qtrue;
  return Qfalse;
}

static VALUE
new(VALUE klass){
  simplet_map_t *map;
  if(!(map = simplet_map_new()))
    rb_fatal("Could not allocate space for a new SimplerTiles::Map in memory.");
  VALUE rmap = Data_Wrap_Struct(klass, mark_map, simplet_map_free, map);
  rb_obj_call_init(rmap, 0, 0);
  if(rb_block_given_p()) rb_yield(rmap);
  return rmap;
}

void
init_map(){
  VALUE rmap = rb_define_class_under(mSimplerTiles, "Map", rb_cObject);
  rb_define_singleton_method(rmap, "new", new, 0);
  rb_define_method(rmap, "bgcolor=", set_bgcolor, 1);
  rb_define_method(rmap, "bgcolor", get_bgcolor, 0);
  rb_define_method(rmap, "srs=", set_srs, 1);
  rb_define_method(rmap, "srs", get_srs, 0);
  rb_define_method(rmap, "set_size", set_size, 2);
  rb_define_method(rmap, "width", get_width, 0);
  rb_define_method(rmap, "height", get_height, 0);
  rb_define_method(rmap, "width=", set_width, 1);
  rb_define_method(rmap, "height=", set_height, 1);
  rb_define_method(rmap, "set_bounds", set_bounds, 4);
  rb_define_method(rmap, "bounds", bounds, 0);
  rb_define_method(rmap, "add_layer", add_layer, 2);
  rb_define_method(rmap, "save", save, 1);
  rb_define_method(rmap, "slippy", slippy, 3);
  rb_define_method(rmap, "to_png", to_png, 0);
  rb_define_method(rmap, "valid?", is_valid, 0);
  cSimplerTilesMap = rmap;
}
