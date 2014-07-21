#ifndef _SIMPLER_LAYER_H
#define _SIMPLER_LAYER_H

#include "simpler_tiles.h"

#ifdef __cplusplus
extern "C" {
#endif

VALUE
set_source(VALUE self, VALUE source);

VALUE
get_source(VALUE self);

#ifdef __cplusplus
}
#endif

#endif