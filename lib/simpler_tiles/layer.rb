module SimplerTiles
  class Layer
    include SimplerTiles::PP

    def initialize(source)
      self.source = source
      yield self if block_given?
    end

    def filter(sql, &blk)
      layer = SimplerTiles::Filter.new(sql, &blk)
      add_filter layer
    end

  private

    def inspect_attributes
      [:source]
    end
  end
end