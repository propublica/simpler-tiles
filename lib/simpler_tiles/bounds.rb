module SimplerTiles
  class Bounds
    include SimplerTiles::PP

    def initialize(maxx, maxy, minx, miny)
      grow maxx, maxy
      grow minx, miny
    end

    private

    def inspect_attributes
      [:to_wkt]
    end
  end
end
