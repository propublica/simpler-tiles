require 'helper'

class TestSimplerTiles < Test::Unit::TestCase
  should "produce a png image" do
    map = SimplerTiles::Map.new do |m|
      m.srs = "+proj=longlat +ellps=GRS80 +datum=NAD83 +no_defs"
      m.set_bounds -179.231086, 17.831509, -100.859681, 71.441059
      m.set_size 256, 256
      m.add_layer "#{File.dirname(__FILE__)}/../data/tl_2010_us_state10.shp"
      m.add_filter "SELECT * from tl_2010_us_state10"
      m.styles 'fill' => "#061F37ff",
          'line-join' => "round",
           'line-cap' => "square",
           'seamless' => "true"
    end
    
    assert map.valid?

    map.to_png do |data|
      assert data
      File.open "#{File.dirname(__FILE__)}/out.png", "wb" do |f| 
        f.write data
      end
      assert data.length
    end
  end
end
