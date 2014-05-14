require 'pairwise'

module DiffSet
  class PairwisePrioritySet < PrioritySet
    include Pairwise
  end
end
