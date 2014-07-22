module SimplerTiles
  # The Map object is the root of the style declaration for SimplerTiles.
  # It wraps the methods in Simple Tiles and tracks projection, width, height
  # and contains a list of Layer objects.
  class Map
    include SimplerTiles::PP

    def initialize
      yield self if block_given?
    end

    # Add a layer to the c list of layers and yield the new layer.
    def layer(source, &blk)
      layer = SimplerTiles::VectorLayer.new(source, &blk)
      add_vector_layer layer
    end

    # Add a raster layer
    def raster_layer(source)
      layer = SimplerTiles::RasterLayer.new(source)
      add_raster_layer layer
    end

    # A convienence method to use Active Record configuration and add a new
    # layer.
    def ar_layer(&blk)
      if !defined?(ActiveRecord)
        raise "ActiveRecord not available"
      end

      config = ActiveRecord::Base.connection.instance_variable_get("@config")
      params = {
        :dbname   => config[:database],
        :user     => config[:username],
        :host     => config[:host],
        :port     => config[:port],
        :password => config[:password]
      }

      conn = "PG:" + params.reject {|k,v| v.nil? }.map {|k,v| "#{k}=#{v}"}.join(' ')

      layer conn, &blk
    end

    # Render the data to a blob of png data.
    def to_png
      data = ""
      to_png_stream Proc.new { |chunk| data += chunk }
      yield data if block_given?
      data
    end

  private

    def inspect_attributes
      [:srs, :width, :height]
    end
  end
end
