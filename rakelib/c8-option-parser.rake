namespace('c8-option-parser') {
  flags = ['--std=c++17', '-Wall', '-Werror', '-O3', '-s', '-DNDEBUG']

  if ENV.has_key?('debug')
    flags -= ['-O3', '-s', '-DNDEBUG']
    flags += ['-g']
  end

  generated = [
    'src/c8-option-parser/errors.hpp',
  ].collect { |fn|
    if dir = fn.chomp(File.extname(fn)) and File.directory?(dir)
      Generate.includeDirectory(dir)
    end
  }

  library = Library.new { |t|
    t.name = 'lib/libc8-option-parser.a'
    t.requirements << generated
    t.sources << FileList['src/c8-option-parser/**/*.cpp']
    t.includes << ['src']
    t.flags << flags
  }

  ut = Executable.new { |t|
    t.name = 'bin/c8-option-parser-ut'
    t.requirements << generated
    t.sources << FileList['test/c8-option-parser/**/*.cpp']
    t.includes << ['src', 'test']
    t.libs << ['-pthread', '-lgtest', '-lgmock', library]
    t.flags << flags
  }

  desc 'Builds c8-option-parser'
  C8.multitask(default: Names['generated:default', library])

  desc 'Runs c8-option-parser tests'
  C8.multitask(test: Names['generated:default', library, ut]) {
    sh ut.name
  }
}
