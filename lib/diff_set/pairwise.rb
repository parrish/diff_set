module DiffSet
  module Pairwise
    def subtract(set, limit)
      _in_pairs super(set, 2 * limit)
    end
    
    def sample(limit)
      _in_pairs super(2 * limit)
    end
    
    protected
    
    def _in_pairs(list)
      list.each_slice(2).to_a.reject{ |pair| pair.length != 2 }
    end
  end
end
