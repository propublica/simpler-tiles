require 'mkmf'

RbConfig::MAKEFILE_CONFIG['CC'] = ENV['CC'] if ENV['CC']

ROOT = File.expand_path(File.join(File.dirname(__FILE__), '..', '..'))
LIBDIR = RbConfig::CONFIG['libdir']
INCLUDEDIR = RbConfig::CONFIG['includedir']

$CFLAGS << " #{ENV["CFLAGS"]}" << `pkg-config --cflags simple-tiles pangocairo`.chomp << `gdal-config --cflags`.chomp
$LIBS << " #{ENV["LIBS"]}" << `pkg-config --libs simple-tiles pangocairo`.chomp << `gdal-config --libs`

HEADER_DIRS = [
 '/usr/local/include',
 '/usr/X11/include',
 '/usr/local/opt/gettext/include',
 INCLUDEDIR,
 '/usr/include'
]

LIB_DIRS = [
 '/usr/local/lib',
 '/usr/X11/lib',
 '/usr/local/opt/gettext/lib',
 LIBDIR,
 '/usr/lib',
]

dir_config('cairo', HEADER_DIRS, LIB_DIRS)
dir_config('pango', HEADER_DIRS, LIB_DIRS)
dir_config('simple-tiles', HEADER_DIRS, LIB_DIRS)

def missing(lib)
  abort "Could not find #{lib}, you may have to change your load path."
end

missing "cairo"        unless find_library "cairo",        "cairo_surface_write_to_png_stream"
missing "simple-tiles" unless find_library "simple-tiles", "simplet_map_render_to_stream"
missing "gdal"         unless find_header "ogr_api.h"
missing "gdal"         unless find_header "ogr_srs_api.h"
missing "cairo"        unless find_header "cairo.h"
missing "pango"        unless find_header "pango/pangocairo.h"
missing "simple-tiles" unless find_header "simple-tiles/simple_tiles.h"

create_makefile('simpler_tiles/simpler_tiles')
