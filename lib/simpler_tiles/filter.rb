module SimplerTiles
  class Filter
    include SimplerTiles::PP

    def initialize(query)
      self.query = query
      yield self if block_given?
    end

    def styles(styles)
      styles.each do |k,v|
        add_style k, v
      end
    end

  private

    def inspect_attributes
      [:query]
    end
  end
end