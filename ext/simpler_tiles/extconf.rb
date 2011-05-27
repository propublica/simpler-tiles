require 'mkmf'

RbConfig::MAKEFILE_CONFIG['CC'] = ENV['CC'] if ENV['CC']

ROOT = File.expand_path(File.join(File.dirname(__FILE__), '..', '..'))
LIBDIR = Config::CONFIG['libdir']
INCLUDEDIR = Config::CONFIG['includedir']

$CFLAGS << " #{ENV["CFLAGS"]}"
$LIBS << " #{ENV["LIBS"]}"

HEADER_DIRS = [
 '/usr/local/include',
 '/usr/X11/include',
 INCLUDEDIR,
 '/usr/include'
]

LIB_DIRS = [
 '/usr/local/lib',
 '/usr/X11/lib',
 LIBDIR,
 '/usr/lib',
]

dir_config('gdal', HEADER_DIRS, LIB_DIRS)
dir_config('cairo', HEADER_DIRS, LIB_DIRS)
dir_config('simple-tiles', HEADER_DIRS, LIB_DIRS)

def missing(lib)
  abort "Could not find #{lib}, you may have to change your load path."
end

missing "gdal"         unless find_library "gdal",         "OGROpen"
missing "cairo"        unless find_library "cairo",        "cairo_surface_write_to_png_stream"
missing "simple-tiles" unless find_library "simple-tiles", "simplet_map_render_to_stream"
missing "gdal"         unless find_header "gdal/ogr_api.h"
missing "gdal"         unless find_header "gdal/ogr_srs_api.h"
missing "cairo"        unless find_header "cairo/cairo.h"
missing "simple-tiles" unless find_header "simple-tiles/simple_tiles.h"

create_makefile('simpler-tiles/simpler_tiles')