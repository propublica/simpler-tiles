module SimplerTiles
  class Map
    include SimplerTiles::PP
    
    private
    def inspect_attributes
      [:srs, :width, :height]
    end
  end
end