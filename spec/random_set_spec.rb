require 'spec_helper'

module DiffSet
  describe RandomSet do
    it_behaves_like 'a set'
    
    def create_set(elements)
      RandomSet.new.tap do |random_set|
        1.upto(elements).each{ |i| random_set.add i }
      end
    end
    
    let(:set){ create_set(5) }
    let(:other_set){ create_set(3) }
    
    it 'should subtract another set' do
      set.subtract(other_set, 5).should =~ [4, 5]
      [4, 5].should include set.subtract(other_set, 1).first
    end
    
    it 'should not include removed elements in subtractions' do
      set.remove 5
      set.subtract(other_set, 5).should == [4]
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
