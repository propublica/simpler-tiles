module SimplerTiles
  class Map
    include SimplerTiles::PP
    
    def styles(styles)
      styles.each do |k,v|
        add_style k, v
      end
    end
    
    private
    def inspect_attributes
      [:srs, :width, :height]
    end
  end
end