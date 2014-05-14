# DiffSet

DiffSet contains a collection of data structures optimized to perform partial set subtractions.

- `DiffSet::RandomSet` Produces a randomized set difference

- `DiffSet::PrioritySet` Produces an ordered set difference

- `DiffSet::PairwiseRandomSet` Presents a random set difference as a list of pairs

- `DiffSet::PairwisePrioritySet` Presents an ordered set difference as a list of pairs

## Installation

1. Install [Boost](http://www.boost.org/):

  - OS X: `brew update && brew install boost`
  
  - Ubuntu: `sudo apt-get update && sudo apt-get install libboost-all-dev`

3. Add this line to your application's Gemfile: `gem 'diff_set'`

4. And then execute: `bundle`

To install rice **Ruby must be compiled with shared libraries enabled**

  - rvm:   `rvm reinstall [version] -- --enable-shared`

  - rbenv: `CONFIGURE_OPTS="--enable-shared" rbenv install [version]`


## Usage

The API is pretty straightforward, and [the specs](https://github.com/parrish/diff_set/tree/master/spec) have examples.

## Testing

Run the specs with `rake`

## Contributing

1. Fork it ( http://github.com/parrish/diff_set/fork )
2. Create your feature branch (`git checkout -b my-new-feature`)
3. Commit your changes (`git commit -am 'Add some feature'`)
4. Push to the branch (`git push origin my-new-feature`)
5. Create new Pull Request
