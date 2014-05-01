module SimplerTiles
  class VectorLayer < Layer
    # Add a query to this Layer's c list.
    def query(sql, &blk)
      layer = SimplerTiles::Query.new(sql, &blk)
      add_query layer
    end
  end
end