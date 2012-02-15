module SimplerTiles
  ROOT = File.expand_path File.dirname(__FILE__)
end

require "#{SimplerTiles::ROOT}/simpler_tiles/simpler_tiles"
require "#{SimplerTiles::ROOT}/simpler_tiles/mixins/pp"
require "#{SimplerTiles::ROOT}/simpler_tiles/map"
require "#{SimplerTiles::ROOT}/simpler_tiles/layer"
require "#{SimplerTiles::ROOT}/simpler_tiles/query"
require "#{SimplerTiles::ROOT}/simpler_tiles/style"
require "#{SimplerTiles::ROOT}/simpler_tiles/bounds"
