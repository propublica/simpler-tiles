#include "bounds.h"
#include <simple-tiles/bounds.h>

VALUE cSimplerTilesBounds;

static simplet_bounds_t*
get_bounds(VALUE self){
  simplet_bounds_t *bounds;
  Data_Get_Struct(self, simplet_bounds_t, bounds);
  return bounds;
}

static VALUE
to_wkt(VALUE self){
  simplet_bounds_t *bounds = get_bounds(self);
  char *wkt = NULL;

  if(simplet_bounds_to_wkt(bounds, &wkt) != SIMPLET_OK)
    rb_raise(rb_eRuntimeError, "Error in creating wkt string.");

  return rb_str_new2(wkt);
}

static VALUE
extend(VALUE self, VALUE x, VALUE y){
  simplet_bounds_t *bounds = get_bounds(self);
  simplet_bounds_extend(bounds, NUM2DBL(x), NUM2DBL(y));
  return self;
}

static VALUE
reproject(VALUE self, VALUE from, VALUE to) {
  Check_Type(from, T_STRING);
  Check_Type(to, T_STRING);
  simplet_bounds_t *bounds;
  if(!(bounds = simplet_bounds_reproject(get_bounds(self), RSTRING_PTR(from), RSTRING_PTR(to))))
    rb_raise(rb_eRuntimeError, "Error in creating bounds.");

  VALUE id = rb_intern("new");

  VALUE rbounds = rb_funcall(cSimplerTilesBounds, id, 4,
                              rb_float_new(bounds->nw.x),
                              rb_float_new(bounds->nw.y),
                              rb_float_new(bounds->se.x),
                              rb_float_new(bounds->se.y));

  simplet_bounds_free(bounds);
  return rbounds;
}

static VALUE
alloc_bounds(VALUE self){
  simplet_bounds_t *bounds;
  VALUE args[4];
  if(!(bounds = simplet_bounds_new()))
    rb_raise(rb_eRuntimeError, "Error in creating bounds.");

  VALUE rbounds = Data_Wrap_Struct(self, NULL, simplet_bounds_free, bounds);
  return rbounds;
}

void
init_bounds(){
  VALUE rbounds = rb_define_class_under(mSimplerTiles, "Bounds", rb_cObject);
  rb_define_alloc_func(rbounds, alloc_bounds);
  rb_define_method(rbounds, "to_wkt", to_wkt, 0);
  rb_define_method(rbounds, "extend", extend, 0);
  rb_define_method(rbounds, "reproject", reproject, 2);
  cSimplerTilesBounds = rbounds;
}

