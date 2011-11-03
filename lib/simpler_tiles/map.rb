module SimplerTiles
  class Map
    include SimplerTiles::PP

    def initialize
      yield self if block_given?
    end

    def layer(source, &blk)
      layer = SimplerTiles::Layer.new(source, &blk)
      add_layer layer
    end


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
      layer "PG:#{params.map {|k,v| "#{k}='#{v}' "}}", &blk
    end

  private

    def inspect_attributes
      [:srs, :width, :height]
    end
  end
end