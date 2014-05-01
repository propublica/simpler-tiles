#include "map.h"
#include "util.h"
#include <simple-tiles/map.h>
#include <simple-tiles/vector_layer.h>
#include <simple-tiles/raster_layer.h>
#include <simple-tiles/bounds.h>
#include <simple-tiles/list.h>

VALUE cSimplerTilesMap;

static simplet_map_t *
get_map(VALUE self){
  simplet_map_t *map;
  Data_Get_Struct(self, simplet_map_t, map);
  return map;
}

/*
Set the background color of the map.

@param (String)
@return (nil)
*/
static VALUE
set_bgcolor(VALUE self, VALUE bgcolor){
  Check_Type(bgcolor, T_STRING);
  simplet_map_t *map = get_map(self);
  simplet_map_set_bgcolor(map, RSTRING_PTR(bgcolor));
  return Qnil;
}

/*
Return a copy of the background color of the map.

@return (String)
*/
static VALUE
get_bgcolor(VALUE self){
  simplet_map_t *map = get_map(self);
  char *color;
  simplet_map_get_bgcolor(map, &color);
  return rb_str_new2(color);
}

/*
Set the projection from an Proj.4 readable string.

@param (String)
@return (String)
*/
static VALUE
set_srs(VALUE self, VALUE srs){
  Check_Type(srs, T_STRING);
  simplet_map_t *map = get_map(self);
  simplet_map_set_srs(map, RSTRING_PTR(srs));
  return Qnil;
}

/*
Return the projection for the map in string representation.

@return (String)
*/
static VALUE
get_srs(VALUE self){
  simplet_map_t *map = get_map(self);
  char *srs;
  simplet_map_get_srs(map, &srs);
  return rb_str_new2(srs);
}

/*
Set the bounds on the map.

@param (Number, Number, Number, Number)
@return (nil)
*/
static VALUE
set_bounds(VALUE self, VALUE maxx, VALUE maxy, VALUE minx, VALUE miny){
  simplet_map_t *map = get_map(self);
  simplet_map_set_bounds(map, NUM2DBL(maxx), NUM2DBL(maxy), NUM2DBL(minx), NUM2DBL(miny));
  return Qnil;
}

static VALUE
new_bounds(simplet_bounds_t *bounds){
  VALUE args[4];
  args[0] = rb_float_new(bounds->nw.x);
  args[1] = rb_float_new(bounds->nw.y);
  args[2] = rb_float_new(bounds->se.x);
  args[3] = rb_float_new(bounds->se.y);
  return rb_funcall2(cSimplerTilesBounds, rb_intern("new"), 4, args);
}

/*
Return the bounds of this map.

@return (Bounds)
*/
static VALUE
bounds(VALUE self){
  simplet_map_t *map = get_map(self);
  return new_bounds(map->bounds);
}
/*
Return the bounds of this map sized according to it's buffer attribute.

@return (Bounds)
*/
static VALUE
buffered_bounds(VALUE self){
  simplet_map_t *map = get_map(self);
  cairo_matrix_t mat;
  simplet_map_init_matrix(map, &mat);
  cairo_matrix_invert(&mat);

  double dx, dy;
  dx = dy = simplet_map_get_buffer(map);
  cairo_matrix_transform_distance(&mat, &dx, &dy);

  simplet_bounds_t *bbounds = simplet_bounds_buffer(map->bounds, dx);
  if(!bbounds)
    rb_raise(rb_eRuntimeError, "Could not allocate space for a new SimplerTiles::Bounds in memory.");

  return new_bounds(bbounds);
}

/*
Set the size in pixels of the final map.

@param (Number, Number)
@return (nil)
*/
static VALUE
set_size(VALUE self, VALUE width, VALUE height){
  simplet_map_t *map = get_map(self);
  simplet_map_set_size(map, NUM2INT(width), NUM2INT(height));
  return Qnil;
}

/*
Set the buffer on the Map.

@param (Number)
@return (Number)
*/
static VALUE
set_buffer(VALUE self, VALUE buffer){
  simplet_map_t *map = get_map(self);
  simplet_map_set_buffer(map, NUM2DBL(buffer));
  return rb_float_new(map->buffer);
}

/*
Get the Map's buffer.

@return (Number)
*/
static VALUE
get_buffer(VALUE self){
  simplet_map_t *map = get_map(self);
  return rb_float_new(simplet_map_get_buffer(map));
}


/*
Get the width of the map.

@return (Number)
*/
static VALUE
get_width(VALUE self){
  simplet_map_t *map = get_map(self);
  return INT2NUM(simplet_map_get_width(map));
}

/*
Get the height of the map.

@return (Number)
*/
static VALUE
get_height(VALUE self){
  simplet_map_t *map = get_map(self);
  return INT2NUM(simplet_map_get_height(map));
}

/*
Set the width of the Map.

@return (Number)
*/
static VALUE
set_width(VALUE self, VALUE width){
  simplet_map_t *map = get_map(self);
  simplet_map_set_width(map, NUM2INT(width));
  return get_width(self);
}

/*
Set the height of the Map.

@return (Number)
*/
static VALUE
set_height(VALUE self, VALUE height){
  simplet_map_t *map = get_map(self);
  simplet_map_set_height(map, NUM2INT(height));
  return get_height(self);
}



/*
Create and return a {VectorLayer} based on the passed in string.

@param (String)
@return (Layer)
*/
static VALUE
add_vector_layer(VALUE self, VALUE layer){
  simplet_map_t *map = get_map(self);
  simplet_vector_layer_t *lyr;
  Data_Get_Struct(layer, simplet_vector_layer_t, lyr);
  simplet_map_add_layer_directly(map, lyr);
  VALUE circ_ref = self;
  simplet_layer_set_user_data(lyr, (void *)circ_ref);
  simplet_retain((simplet_retainable_t*) lyr);
  return layer;
}

/*
Create and return a {RasterLayer} based on the passed in string.

@param (String)
@return (Layer)
*/
static VALUE
add_raster_layer(VALUE self, VALUE layer){
  simplet_map_t *map = get_map(self);
  simplet_raster_layer_t *lyr;
  Data_Get_Struct(layer, simplet_raster_layer_t, lyr);
  simplet_map_add_layer_directly(map, lyr);
  VALUE circ_ref = self;
  simplet_layer_set_user_data(lyr, (void *)circ_ref);
  simplet_retain((simplet_retainable_t*) lyr);
  return layer;
}


/*
Test to see if the Map has fulfilled the requirements for rendering

@return (Boolean)
*/
static VALUE
is_valid(VALUE self){
  simplet_map_t *map = get_map(self);
  if(!simplet_map_is_valid(map))
    return Qfalse;
  return Qtrue;
}

/*
Render the Map to the filesystem.

@param (String)
@return (Boolean)
*/
static VALUE
save(VALUE self, VALUE path){
  Check_Type(path, T_STRING);
  if(!is_valid(self)) return Qfalse;
  simplet_map_t *map = get_map(self);
  simplet_map_render_to_png(map, RSTRING_PTR(path));
  if(simplet_map_get_status(map) == SIMPLET_OK) {
    return Qtrue;
  } else {
    rb_raise(rb_eRuntimeError, "%s", simplet_map_status_to_string(map));
    return Qfalse;
  }
}


static cairo_status_t
stream(void* block, const unsigned char *data, unsigned int length){
  ID call = rb_intern("call");
  VALUE rdata = rb_str_new((const char *)data, (long)length);
  rb_funcall((VALUE)block, call, 1, rdata);
  return CAIRO_STATUS_SUCCESS;
}

/*
Render the map to a png stream and yield values to the passed in block.

@yield [chunk] Block that takes chunks of data
@return (nil)
*/
static VALUE
to_png_stream(VALUE self, VALUE block){
  simplet_map_t *map = get_map(self);

  simplet_map_render_to_stream(map, (void *)block, stream);
  if(simplet_map_get_status(map) != SIMPLET_OK)
    rb_raise(rb_eRuntimeError, "%s", simplet_map_status_to_string(map));

  return Qnil;
}

/*
Set the map to be slippy via passed in parameters.

@param (Number, Number, Number)
@return (nil)
*/
static VALUE
slippy(VALUE self, VALUE x, VALUE y, VALUE z){
  simplet_map_t *map = get_map(self);
  if(simplet_map_set_slippy(map, NUM2INT(x), NUM2INT(y), NUM2INT(z)) != SIMPLET_OK)
    rb_raise(rb_eRuntimeError, "%s", simplet_map_status_to_string(map));
  return Qnil;
}

static VALUE
map_alloc(VALUE klass){
  simplet_map_t *map;

  if(!(map = simplet_map_new()))
    rb_fatal("Could not allocate space for a new SimplerTiles::Map in memory.");

  return Data_Wrap_Struct(klass, NULL, simplet_map_free, map);
}

void
init_map(){
  VALUE rmap = rb_define_class_under(mSimplerTiles, "Map", rb_cObject);
  rb_define_alloc_func(rmap, map_alloc);
  rb_define_method(rmap, "bgcolor=", set_bgcolor, 1);
  rb_define_method(rmap, "bgcolor", get_bgcolor, 0);
  rb_define_method(rmap, "srs=", set_srs, 1);
  rb_define_method(rmap, "srs", get_srs, 0);
  rb_define_method(rmap, "set_size", set_size, 2);
  rb_define_method(rmap, "width", get_width, 0);
  rb_define_method(rmap, "height", get_height, 0);
  rb_define_method(rmap, "width=", set_width, 1);
  rb_define_method(rmap, "height=", set_height, 1);
  rb_define_method(rmap, "buffer", get_buffer, 0);
  rb_define_method(rmap, "buffer=", set_buffer, 1);
  rb_define_method(rmap, "set_bounds", set_bounds, 4);
  rb_define_method(rmap, "bounds", bounds, 0);
  rb_define_method(rmap, "buffered_bounds", buffered_bounds, 0);
  rb_define_method(rmap, "save", save, 1);
  rb_define_method(rmap, "slippy", slippy, 3);
  rb_define_method(rmap, "valid?", is_valid, 0);
  rb_define_private_method(rmap, "to_png_stream", to_png_stream, 1);
  rb_define_private_method(rmap, "add_vector_layer", add_vector_layer, 1);
  rb_define_private_method(rmap, "add_raster_layer", add_raster_layer, 1);

  cSimplerTilesMap = rmap;
}
