module SimplerTiles
  class Map
    include SimplerTiles::PP
    
    def styles(styles)
      styles.each do |k,v|
        add_style k, v
      end
    end
    
    def ar_layer
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
      add_layer "PG:#{params.map {|k,v| "#{k}='#{v}' "}}"
    end
        
    private
    def inspect_attributes
      [:srs, :width, :height]
    end
  end
end