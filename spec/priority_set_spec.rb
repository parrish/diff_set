require 'spec_helper'

module DiffSet
  describe PrioritySet do
    it_behaves_like 'a set'
    
    let(:set) do
      ids = (1..5).to_a
      priorities = ids.reverse
      
      PrioritySet.new.tap do |priority_set|
        ids.zip(priorities).each{ |id, priority| priority_set.add id, priority }
      end
    end
    
    let(:other_set) do
      RandomSet.new.tap do |random_set|
        1.upto(3).each{ |i| random_set.add i }
      end
    end
    
    it 'should sample elements in order' do
      set.sample(5).should == (1..5).to_a
    end
    
    it 'should subtract another set' do
      set.subtract(other_set, 5).should == [4, 5]
      set.subtract(other_set, 1).first.should == 4
    end
    
    it 'should not include removed elements in subtractions' do
      set.remove 5
      set.subtract(other_set, 5).should == [4]
    end
    
    it 'should update the priority' do
      set.to_a.first.should == 1
      set.to_h[1].should be_within(0.1).of(5)
      set.add 1, 0
      set.to_a.first.should == 2
      set.to_a.last.should == 1
      set.to_h[1].should be_within(0.1).of(0)
    end
  end
end
