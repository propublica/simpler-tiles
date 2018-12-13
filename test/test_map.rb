require "#{File.join(File.dirname(__FILE__))}/helper"

describe SimplerTiles::Map do
  before do
    @map = SimplerTiles::Map.new
  end

  it "should accept block parameters on initialization" do
    map = SimplerTiles::Map.new do |m|
      m.width = 500
      m.height = 500
    end

    assert_equal(map.width, 500)
    assert_equal(map.height, 500)
  end

  it "should set projection" do
    srs = "+proj=longlat +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +no_defs ";
    @map.srs = srs
    assert_equal(@map.srs, srs)
  end

  it "should test validity" do
    assert_equal @map.valid?, false
  end

  it "should set slippy" do
    @map.slippy(0, 0, 1)
    assert_equal @map.width, 256
  end

  it "should raise error when invalid" do
    map = SimplerTiles::Map.new do |m|
      m.srs = "+proj=longlat +ellps=GRS80 +datum=NAD83 +no_defs"
      m.set_bounds -179.231086, 17.831509, -100.859681, 71.441059
      m.set_size 256, 256
      m.layer "#{File.dirname(__FILE__)}/../data/tl_2010_01_state10.shp" do |l|
        l.query "SELECT * from tl_2010_01_state10_error_error" do |q|
          q.styles 'fill' => "#061F3799",
              'line-join' => "round",
               'line-cap' => "square",
               'seamless' => "true"
        end
      end
    end
    assert_raises RuntimeError do
      map.to_png
    end
  end

  #TODO: transform to real test
  it "should return bounds" do
    map = SimplerTiles::Map.new do |m|
      m.slippy 0, 0, 1
    end
    map.buffer = 1000
  end

  it "should set and get bgcolor" do
    color = "#cc0000"
    @map.bgcolor = color
    assert_equal @map.bgcolor, color
  end
end
