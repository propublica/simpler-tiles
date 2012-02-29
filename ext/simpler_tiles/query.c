#include "query.h"
#include <simple-tiles/query.h>
#include <simple-tiles/style.h>

VALUE cSimplerTilesQuery;

static simplet_query_t *
get_query(VALUE self){
  simplet_query_t *query;
  Data_Get_Struct(self, simplet_query_t, query);
  return query;
}

static void
mark_query(void *query){
  simplet_query_t *fltr = query;
  VALUE ref = (VALUE)simplet_query_get_user_data(fltr);
  if(ref) rb_gc_mark(ref);
}


static void
query_free(void *query){
  simplet_query_t *fltr = query;
  // test if we have been linked in ruby land
  VALUE refs = (VALUE)simplet_query_get_user_data(fltr);
  // if not it is safe to free this query.
  if(!refs) simplet_query_free(fltr);
}

/*
Set the OGR SQL for this Query.

@return (String)
*/
static VALUE
set_sql(VALUE self, VALUE query){
  Check_Type(query, T_STRING);
  simplet_query_t *qry = get_query(self);
  simplet_query_set(qry, RSTRING_PTR(query));
  return query;
}

/*
Get the OGR SQL for this Query.

@return (String)
*/
static VALUE
get_sql(VALUE self){
  simplet_query_t *query = get_query(self);
  char *str;
  simplet_query_get(query, &str);
  return rb_str_new2(str);
}

static VALUE
add_style(VALUE self, VALUE style){
  simplet_query_t *query = get_query(self);
  simplet_style_t *style_s;
  Data_Get_Struct(style, simplet_style_t, style_s);
  simplet_query_add_style_directly(query, style_s);
  VALUE circ_ref = rb_ary_new3(2, self, style);
  simplet_style_set_user_data(style_s, (void *)circ_ref);
  return style;
}

static VALUE
query_alloc(VALUE klass){
  simplet_query_t *query;

  if(!(query = simplet_query_new(NULL)))
    rb_fatal("Could not allocate space for a new SimplerTiles::Query in memory.");

  return Data_Wrap_Struct(klass, mark_query, query_free, query);
};


void init_query(){
  VALUE rquery = rb_define_class_under(mSimplerTiles, "Query", rb_cObject);
  rb_define_alloc_func(rquery, query_alloc);
  rb_define_method(rquery, "query=", set_sql, 1);
  rb_define_method(rquery, "query", get_sql, 0);
  rb_define_private_method(rquery, "add_style", add_style, 1);

  cSimplerTilesQuery = rquery;
}
