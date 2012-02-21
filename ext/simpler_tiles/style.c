#include "style.h"
#include "util.h"
#include <simple-tiles/style.h>

VALUE cSimplerTilesStyle;

static simplet_style_t *
get_style(VALUE self){
  simplet_style_t *style;
  Data_Get_Struct(self, simplet_style_t, style);
  return style;
}

static void
mark_style(void *style){
  simplet_style_t *stl = style;
  VALUE refs = (VALUE)simplet_style_get_user_data(stl);
  if(refs) rb_gc_mark(refs);
}

static void
style_free(void *style){
  simplet_style_t *stl = style;
  // test if we have been linked in ruby land
  VALUE refs = (VALUE)simplet_style_get_user_data(stl);
  // if not it is safe to free this style.
  if(!refs) simplet_style_free(stl);
}

static VALUE
alloc_style(VALUE klass){
  simplet_style_t *style;

  if(!(style = simplet_style_new(NULL, NULL)))
    rb_fatal("Could not allocate space for a new SimplerTiles::Style in memory.");

  return Data_Wrap_Struct(klass, mark_style, style_free, style);
}

/*
Set the arg for this Style.

@param (String)
@return (String)
*/
static VALUE
set_arg(VALUE self, VALUE arg){
  Check_Type(arg, T_STRING);
  simplet_style_t *style = get_style(self);
  simplet_style_set_arg(style, RSTRING_PTR(arg));
  return arg;
}


/*
Get the arg for this Style.

@return (String)
*/
static VALUE
get_arg(VALUE self){
  simplet_style_t *style = get_style(self);
  char *arg;
  simplet_style_get_arg(style, &arg);
  return rb_str_new2(arg);
}

/*
Set the key for this Style.

@param (String)
@return (String)
*/
static VALUE
set_key(VALUE self, VALUE key){
  Check_Type(key, T_STRING);
  simplet_style_t *style = get_style(self);
  simplet_style_set_key(style, RSTRING_PTR(key));
  return key;
}

/*
Get the key for this Style.

@param (String)
@return (String)
*/
static VALUE
get_key(VALUE self){
  simplet_style_t *style = get_style(self);
  char *key;
  simplet_style_get_key(style, &key);
  return rb_str_new2(key);
}

void
init_style(){
  VALUE rstyle = rb_define_class_under(mSimplerTiles, "Style", rb_cObject);
  rb_define_alloc_func(rstyle, alloc_style);
  rb_define_method(rstyle, "arg=", set_arg, 1);
  rb_define_method(rstyle, "arg", get_arg, 0);
  rb_define_method(rstyle, "key=", set_key, 1);
  rb_define_method(rstyle, "key", get_key, 0);

  cSimplerTilesStyle = rstyle;
}
