require "#{File.join(File.dirname(__FILE__))}/helper"

describe SimplerTiles do
  it "should produce a png image" do
    map = SimplerTiles::Map.new do |m|
      m.bgcolor = "#000000"
      m.srs = "EPSG:32614"
      m.width = 256
      m.height = 256
      m.set_bounds(195585.000, 3472515.000, 427815.000, 3235485.000)

      layer = m.layer "#{File.dirname(__FILE__)}/../data/tl_2010_01_state10.shp" do |l|
        l.query "SELECT * from 'tl_2010_01_state10'" do |q|
          q.styles 'fill' => "#000dff",
              'line-join' => "round",
               'line-cap' => "square"
        end
      end

      m.raster_layer "#{File.dirname(__FILE__)}/../data/cea.tif"
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

  it "should not crash with memory errors" do
    GC.disable
    t = 10.times.map do
      Thread.new do
        map = SimplerTiles::Map.new do |m|
          m.slippy 3, 6, 4
          m.layer "#{File.dirname(__FILE__)}/../data/tl_2010_01_state10.shp" do |l|
            l.query "SELECT * from 'tl_2010_01_state10'" do |q|
              q.styles 'fill' => "#061F3799",
                  'line-join' => "round",
                   'line-cap' => "square",
                   'seamless' => "true"
            end
          end

          m.raster_layer "#{File.dirname(__FILE__)}/../data/cea.tif"
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
    t.map(&:join)
    GC.enable
    GC.start
  end
end
