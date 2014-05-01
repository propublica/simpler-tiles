module SimplerTiles
  # The Layer object contains connection info for a particular datasource and
  # tracks a list of {Query}s.
  class Layer
    include SimplerTiles::PP

    def initialize(source)
      self.source = source
      yield self if block_given?
    end

  private

    def inspect_attributes
      [:source]
    end
  end
end
