# SimplerTiles contains all of the classes we'll want to define.
module SimplerTiles
  # The location of this file will define the root path for SimplerTiles
  ROOT = File.expand_path File.dirname(__FILE__)
end

require "#{SimplerTiles::ROOT}/simpler_tiles/simpler_tiles"
require "#{SimplerTiles::ROOT}/simpler_tiles/mixins/pp"
require "#{SimplerTiles::ROOT}/simpler_tiles/map"
require "#{SimplerTiles::ROOT}/simpler_tiles/layer"
require "#{SimplerTiles::ROOT}/simpler_tiles/query"
require "#{SimplerTiles::ROOT}/simpler_tiles/style"
require "#{SimplerTiles::ROOT}/simpler_tiles/bounds"
