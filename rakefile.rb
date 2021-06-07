#!/usr/bin/ruby

gem 'rake-builder', '~> 3.2'

require 'rake-builder'

C8::Config.register :debug, default: false

task('debug', [:value]) { |t, args|
  value = args[:value] == 'true'
  C8::Config.debug = value
}

$flags = ['--std=c++17', '-Wall', '-Werror', '-Wsign-conversion']

if C8::Config.debug
  $flags += ['-g']
else
  $flags += ['-O3', '-s', '-DNDEBUG']
end

namespaces = Dir['rakelib/c8-*.rake'].collect { |x| File.basename(x).chomp('.rake') }

desc 'Builds all libs'
task(default: Names::All[namespaces.collect { |x| "#{x}:default" }])

desc 'Run all tests'
task(test: Names::All[namespaces.collect { |x| "#{x}:test" }])

desc 'Clean all build targets'
task(:clean) {
  Dir['.obj', 'lib', 'bin'].each { |fn|
    if File.directory? fn
      FileUtils.rm_rf fn, verbose: true
    else
      FileUtils.rm fn, verbose: true
    end
  }
}

desc 'Generates template for new library'
task(:new, [:name]) { |t, args|
  name = args[:name]

  unless File.exist?("rakelib/c8-#{name}.rake")
    IO.write("rakelib/c8-#{name}.rake", C8.erb(IO.read('templates/rakefile.rb.erb'), name: name))
  end

  FileUtils.mkdir_p "src/c8-#{name}"
  FileUtils.mkdir_p "test/c8-#{name}"

  unless File.exist?("src/c8-#{name}/#{name}.cpp")
    FileUtils.touch("src/c8-#{name}/#{name}.cpp")
  end
}

