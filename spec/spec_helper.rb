root = File.expand_path File.join(File.dirname(__FILE__), '../')
%w(lib ext).each do |name|
  dir = File.join root, name
  $LOAD_PATH.unshift dir unless $LOAD_PATH.include? dir
end

require 'pry'
require 'diff_set'

Dir["./spec/support/**/*.rb"].sort.each{ |f| require f }

RSpec.configure do |config|
  config.treat_symbols_as_metadata_keys_with_true_values = true
  config.run_all_when_everything_filtered = true
  config.filter_run :focus
  config.order = 'random'
end
