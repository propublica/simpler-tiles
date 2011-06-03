module SimplerTiles
  VERSION = '1.0.0'
  ROOT = File.expand_path File.dirname(__FILE__)
end

require "#{SimplerTiles::ROOT}/simpler_tiles/simpler_tiles"
require "#{SimplerTiles::ROOT}/simpler_tiles/mixins/pp"
require "#{SimplerTiles::ROOT}/simpler_tiles/map"
