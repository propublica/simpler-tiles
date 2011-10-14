require 'helper'

class TestSimplerTiles < Test::Unit::TestCase
  should "produce a png image" do
    map = SimplerTiles::Map.new do |m|


      m.slippy 13, 27, 6

      m.add_layer "/Users/jlarson/dev/redistricting-lobbying/db/static/shapes/10m_land.shp"
      m.add_filter "SELECT * from '10m_land'"
      m.styles 'fill' => "#061F3799",
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
