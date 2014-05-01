#include "vector_layer.h"
#include "layer.h"
#include <simple-tiles/layer.h>
#include <simple-tiles/vector_layer.h>
#include <simple-tiles/query.h>
#include <simple-tiles/list.h>
#include <simple-tiles/memory.h>

VALUE cSimplerTilesVectorLayer;

static simplet_vector_layer_t *
get_layer(VALUE self){
  simplet_vector_layer_t *layer;
  Data_Get_Struct(self, simplet_vector_layer_t, layer);
  return layer;
}

static void
mark_layer(void *layer){
  simplet_vector_layer_t *lyr = layer;
  VALUE ref = (VALUE)simplet_vector_layer_get_user_data(lyr);
  if(ref) rb_gc_mark(ref);
}

static void
layer_free(void *layer){
  simplet_vector_layer_t *lyr = layer;
  simplet_vector_layer_free(lyr);
}


/*
Add a query object to this Layer's list of queries.

@param (String)
@return (Query)
*/
static VALUE
add_query(VALUE self, VALUE query){
  simplet_vector_layer_t *layer = get_layer(self);
  simplet_query_t *qry;
  Data_Get_Struct(query, simplet_query_t, qry);
  simplet_vector_layer_add_query_directly(layer, qry);
  VALUE circ_ref = self;
  simplet_query_set_user_data(qry, (void *)circ_ref);
  simplet_retain((simplet_retainable_t*) qry);
  return query;
}

VALUE
vector_layer_alloc(VALUE klass){
  simplet_vector_layer_t *layer;
  if(!(layer = simplet_vector_layer_new("")))
    rb_fatal("Could not allocate space for a new SimplerTiles::Layer in memory.");

  return Data_Wrap_Struct(klass, mark_layer, layer_free, layer);
}

void init_vector_layer(){
  VALUE rVectorLayer = rb_define_class_under(mSimplerTiles, "VectorLayer", rb_cObject);
  rb_define_alloc_func(rVectorLayer, vector_layer_alloc);
  rb_define_method(rVectorLayer, "source=", set_source, 1);
  rb_define_method(rVectorLayer, "source", get_source, 0);
  rb_define_private_method(rVectorLayer, "add_query", add_query, 1);

  cSimplerTilesVectorLayer = rVectorLayer;
}
