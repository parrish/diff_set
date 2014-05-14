module DiffSet
  module Pairwise
    def self.included(klass)
      klass.class_eval do
        alias_method :_c_subtract, :subtract
        def subtract(set, limit)
          _in_pairs _c_subtract(set, 2 * limit)
        end
        
        alias_method :_c_sample, :sample
        def sample(limit)
          _in_pairs _c_sample(2 * limit)
        end
      end
    end
    
    protected
    
    def _in_pairs(list)
      list.each_slice(2).to_a.reject{ |pair| pair.length != 2 }
    end
  end
end
