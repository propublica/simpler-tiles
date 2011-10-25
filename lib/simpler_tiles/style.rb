module SimplerTiles
  class Style
    include SimplerTiles::PP

    def initialize(key, arg)
      self.key = key
      self.arg = arg
    end

    private

    def inspect_attributes
      [:key, :arg]
    end
  end
end