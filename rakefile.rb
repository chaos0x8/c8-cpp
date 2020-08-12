#!/usr/bin/ruby

gem 'rake-builder', '~> 2.0', '>= 2.0.8'

require 'rake-builder'

namespaces = Dir['rakelib/c8-*.rake'].collect { |x| File.basename(x).chomp('.rake') }

desc 'Builds all libs'
task(default: namespaces.collect { |x| "#{x}:default" })

desc 'Run all tests'
task(test: namespaces.collect { |x| "#{x}:test" })
