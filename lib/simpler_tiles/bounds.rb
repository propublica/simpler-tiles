module SimplerTiles
  class Bounds
    include SimplerTiles::PP

    private
    def inspect_attributes
      [:to_wkt]
    end
  end
end
