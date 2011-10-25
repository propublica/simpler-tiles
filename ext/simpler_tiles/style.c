#include "style.h"
#include <simple-tiles/style.h>


static simplet_style_t *
get_style(VALUE self){
  simplet_style_t *style;
  Data_Get_Struct(self, simplet_style_t, style);
  return style;
}

static VALUE
alloc_style(VALUE klass){
  simplet_style_t *style;
  if(!(style = simplet_style_new(NULL, NULL)))
    rb_fatal("Could not allocate space for a new SimplerTiles::Style in memory.");
  return Data_Wrap_Struct(klass, NULL, simplet_style_free, style);
}

static VALUE
set_arg(VALUE self, VALUE arg){
  Check_Type(arg, T_STRING);
  simplet_style_t *style = get_style(self);
  simplet_style_set_arg(style, RSTRING_PTR(arg));
  return arg;
}

static VALUE
get_arg(VALUE self){
  simplet_style_t *style = get_style(self);
  char *arg;
  simplet_style_get_arg(style, &arg);
  return rb_str_new2(arg);
}

static VALUE
set_key(VALUE self, VALUE key){
  Check_Type(key, T_STRING);
  simplet_style_t *style = get_style(self);
  simplet_style_set_key(style, RSTRING_PTR(key));
  return key;
}

static VALUE
get_key(VALUE self){
  simplet_style_t *style = get_style(self);
  char *key;
  simplet_style_get_key(style, &key);
  return Qnil;
}

void
init_style(){
  VALUE rstyle = rb_define_class_under(mSimplerTiles, "Style", rb_cObject);
  rb_define_alloc_func(rstyle, alloc_style);
  rb_define_method(rstyle, "arg=", set_arg, 1);
  rb_define_method(rstyle, "arg", get_arg, 0);
  rb_define_method(rstyle, "key=", set_key, 1);
  rb_define_method(rstyle, "key", get_key, 0);

  cSimplerTilesFilter = rstyle;
}