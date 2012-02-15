module SimplerTiles
  class Query
    include SimplerTiles::PP

    def initialize(query)
      self.query = query
      yield self if block_given?
    end

    def styles(styles)
      styles.each do |k,v|
        style = SimplerTiles::Style.new k, v
        add_style style
      end
    end

  private

    def inspect_attributes
      [:query]
    end
  end
end
