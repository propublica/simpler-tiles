module SimplerTiles
  class Layer
    include SimplerTiles::PP

    def initialize(source)
      self.source = source
      yield self if block_given?
    end

    def query(sql, &blk)
      layer = SimplerTiles::Query.new(sql, &blk)
      add_query layer
    end

  private

    def inspect_attributes
      [:source]
    end
  end
end
