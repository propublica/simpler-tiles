require 'helper'

class TestMap < Test::Unit::TestCase
  context SimplerTiles::Map do
    setup do
      @map = SimplerTiles::Map.new
    end
    
    should "accept block parameters on initialization" do
      map = SimplerTiles::Map.new do |m|
        m.width = 500
        m.height = 500
      end
      
      assert_equal(map.width, 500)
      assert_equal(map.height, 500)
    end
    
    should "set projection" do
      srs = "+proj=longlat +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +no_defs ";
      @map.srs = srs
      assert_equal(@map.srs, srs)
    end
    
    should "test validity" do
      assert_equal @map.valid?, false
    end
  end
end