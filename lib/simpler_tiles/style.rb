module SimplerTiles
  # Each style defines a particular directive for styling the map. For a list
  # of keys and arguments refer to the simple-tiles documentation.
  class Style
    include SimplerTiles::PP

    # Construct a new style
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
