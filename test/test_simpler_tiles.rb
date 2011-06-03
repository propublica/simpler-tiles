require 'helper'

class TestSimplerTiles < Test::Unit::TestCase
  should "produce a png image" do
    map = SimplerTiles::Map.new do |m|
      m.srs = "+proj=longlat +ellps=GRS80 +datum=NAD83 +no_defs"
      m.bounds -179.231086, 17.831509, -100.859681, 71.441059
      m.size 256, 256
      m.layer "../data/tl_2010_us_cd108.shp"
      m.add_filter "SELECT * from tl_2010_us_cd108"
      m.styles 'fill' => "#061F37ff",
          'line-join' => "round",
           'line-cap' => "square"
    end
    
    assert map.valid?

    map.data do |data|
      p data
      p data.length
    end
    
    p map.to_png
    
    p png.length
  end
end
