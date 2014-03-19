require "#{File.join(File.dirname(__FILE__))}/helper"

class TestSimplerTiles < Test::Unit::TestCase
  should "produce a png image" do
    map = SimplerTiles::Map.new do |m|
      m.slippy 3, 6, 4
      m.layer "#{File.dirname(__FILE__)}/../data/tl_2010_us_state10.shp" do |l|
        l.query "SELECT * from 'tl_2010_us_state10'" do |q|
          q.styles 'fill' => "#061F3799",
              'line-join' => "round",
               'line-cap' => "square",
               'seamless' => "true"
        end
      end
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


  should "not crash with memory errors" do
    GC.disable
    t = 100.times.map do
      Thread.new do
        map = SimplerTiles::Map.new do |m|
          m.slippy 3, 6, 4
          m.layer "#{File.dirname(__FILE__)}/../data/tl_2010_us_state10.shp" do |l|
            l.query "SELECT * from 'tl_2010_us_state10'" do |q|
              q.styles 'fill' => "#061F3799",
                  'line-join' => "round",
                   'line-cap' => "square",
                   'seamless' => "true"
            end
          end
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
  end
  GC.enable
  GC.start
end
