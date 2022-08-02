#!/usr/bin/ruby

gem 'rake-builder', '~> 7.0', '>= 7.0.8'

require 'rake-builder'

require_relative 'rakelib/_common'

$config = {
  debug: false
}

desc 'Enables debug flags'
task('debug') do
  $config[:debug] = true
end

$flags = ['--std=c++17', '-Wall', '-Werror', '-Wsign-conversion']

$flags += if $config[:debug]
            ['-g']
          else
            ['-O3', '-s', '-DNDEBUG']
          end

namespaces = Dir['rakelib/c8-*.rake'].collect { |x| File.basename(x).chomp('.rake') }

namespaces.each do |namespace|
  path = Pathname.new("src/#{namespace}.hpp")
  include_directory self, path, path.dirname.glob("#{namespace}/*.hpp")
  Rake::Task[path.to_s].invoke
end

desc 'Builds all libs'
multitask(default: namespaces.collect { |x| "#{x}:main" })

desc 'Run all tests'
multitask(test: namespaces.collect { |x| "#{x}:all" }) do
  namespaces.collect { |x| "#{x}:test" }.each do |task|
    Rake::Task[task].invoke
  end
end

desc 'Clean all build targets'
task(clean: namespaces.collect { |x| "#{x}:clean" })

desc 'Generates template for new library'
task(:new, [:name]) do |_t, args|
  name = args[:name]

  unless File.exist?("rakelib/c8-#{name}.rake")
    code = C8.erb name: name do
      IO.read('templates/rakefile.rb.erb')
    end

    IO.write("rakelib/c8-#{name}.rake", code)
  end

  FileUtils.mkdir_p "src/c8-#{name}"
  FileUtils.mkdir_p "test/c8-#{name}"

  FileUtils.touch("src/c8-#{name}/#{name}.cpp") unless File.exist?("src/c8-#{name}/#{name}.cpp")

  unless File.exist?("test/c8-#{name}/main.cpp")
    code = C8.erb({}) do
      <<~INLINE
        #include <gtest/gtest.h>

        int main(int argc, char** argv) {
          testing::InitGoogleTest(&argc, argv);
          return RUN_ALL_TESTS();
        }
      INLINE
    end

    IO.write "test/c8-#{name}/main.cpp", code
  end
end
