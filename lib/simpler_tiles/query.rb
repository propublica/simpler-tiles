module SimplerTiles
  # A Query represents an OGR SQL query against a layer's datasource. Queries
  # contain styles that are applied to each returned object from the datastore.
  class Query
    include SimplerTiles::PP

    # Initialize a query with a string containing OGR SQL.
    def initialize(query)
      self.query = query
      yield self if block_given?
    end

    # Styles will take a hash of style declarations and adds them to the internal
    # c list.
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
