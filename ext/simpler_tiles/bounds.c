#include "bounds.h"
#include <simple-tiles/bounds.h>

VALUE cSimplerTilesBounds;

static simplet_bounds_t*
get_bounds(VALUE self){
  simplet_bounds_t *bounds;
  Data_Get_Struct(self, simplet_bounds_t, bounds);

  return bounds;
}

static void
mark_bounds(simplet_bounds_t *bounds){ (void) bounds; }

static VALUE
to_wkt(VALUE self){
  simplet_bounds_t *bounds = get_bounds(self);
  char *wkt = NULL;

  if(simplet_bounds_to_wkt(bounds, &wkt) != SIMPLET_OK)
    rb_raise(rb_eRuntimeError, "Error in creating wkt string.");

  return rb_str_new2(wkt);
}

static VALUE
new(VALUE self, VALUE maxx, VALUE maxy, VALUE minx, VALUE miny){
  simplet_bounds_t *bounds;
  VALUE args[4];
  if(!(bounds = simplet_bounds_new()))
    rb_raise(rb_eRuntimeError, "Error in creating bounds.");

  args[0] = maxx;
  args[1] = maxy;
  args[2] = minx;
  args[3] = miny;


  simplet_bounds_extend(bounds, NUM2DBL(maxx), NUM2DBL(maxy));
  simplet_bounds_extend(bounds, NUM2DBL(minx), NUM2DBL(miny));

  VALUE rbounds = Data_Wrap_Struct(self, mark_bounds, simplet_bounds_free, bounds);
  rb_obj_call_init(rbounds, 4, args);
  return rbounds;
}

static VALUE
init(VALUE self, VALUE maxx, VALUE maxy, VALUE minx, VALUE miny){
  return self;
}

void
init_bounds(){
  VALUE rbounds = rb_define_class_under(mSimplerTiles, "Bounds", rb_cObject);
  rb_define_singleton_method(rbounds, "new", new, 4);
  rb_define_method(rbounds, "initialize", init, 4);
  rb_define_method(rbounds, "to_wkt", to_wkt, 0);
  cSimplerTilesBounds = rbounds;
}

