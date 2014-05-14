require 'spec_helper'

module DiffSet
  describe PairwiseRandomSet do
    it_behaves_like 'a set'
    
    def create_set(elements)
      PairwiseRandomSet.new.tap do |random_set|
        1.upto(elements).each{ |i| random_set.add i }
      end
    end
    
    let(:set){ create_set(5) }
    let(:other_set){ create_set(3) }
    
    it 'should sample pairs of elements' do
      set.sample(2).collect(&:length).should == [2, 2]
      set.sample(3).length.should == 2
    end
    
    it 'should not include removed elements in subtractions' do
      set.remove 5
      set.subtract(other_set, 5).flatten.should_not include 5
    end
    
    it 'should subtract another set' do
      set.subtract(other_set, 5).length.should == 1
      set.subtract(other_set, 5).first.should =~ [4, 5]
    end
    
    it 'should always return pairs' do
      6.upto(8).each{ |i| set.add i }
      set.subtract(other_set, 3).each{ |pair| pair.length.should == 2 }
    end
    
    it 'should mutate the order of the elements when sampling' do
      set_before = set.to_a
      set.sample 5
      set_before.should =~ set.to_a
      set_before.should_not == set.to_a
    end
    
    it 'should mutate the order of the elements on a subtraction' do
      set_before = set.to_a
      set.subtract other_set, 5
      set_before.should =~ set.to_a
      set_before.should_not == set.to_a
    end
  end
end
