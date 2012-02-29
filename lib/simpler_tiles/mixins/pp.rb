module SimplerTiles
  # PP contains a pretty print routine for SimplerTiles objects.
  module PP
    # A simple Nokogiri inspired inspection routine.
    def inspect
      attributes = inspect_attributes.map do |attribute|
        "#{attribute.to_s}=#{send(attribute).inspect}"
      end.join ' '

      "#<#{self.class.name}:#{sprintf("0x%x", object_id)} #{attributes}>"
    end
  end
end
