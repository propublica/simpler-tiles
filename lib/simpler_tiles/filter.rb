module SimplerTiles
  class Filter
    include SimplerTiles::PP

    def initialize(query)
      self.query = query
      yield self if block_given?
    end

  private

    def inspect_attributes
      [:query]
    end
  end
end