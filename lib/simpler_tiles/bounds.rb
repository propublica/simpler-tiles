module SimplerTiles
  # Each Bounds represents a rectangular box, for {Map} objects they define
  # the boundary of the data to return from each {Layer}.
  class Bounds
    include SimplerTiles::PP

    # Initialize a bounds from max and min coordinates
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
