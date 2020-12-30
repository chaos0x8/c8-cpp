namespace('c8-option-parser') {
  flags = $flags

  generated = [
    'src/c8-option-parser/errors.hpp',
  ].collect { |fn|
    if dir = fn.chomp(File.extname(fn)) and File.directory?(dir)
      Generate.includeDirectory(dir)
    end
  }

  library = Library.new { |t|
    t.name = 'lib/libc8-option-parser.a'
    t.requirements << generated << C8::Config
    t.sources << FileList['src/c8-option-parser/**/*.cpp']
    t.includes << ['src']
    t.flags << flags
  }

  ut = Executable.new { |t|
    t.name = 'bin/c8-option-parser-ut'
    t.requirements << generated << C8::Config
    t.sources << FileList['test/c8-option-parser/**/*.cpp']
    t.includes << ['src', 'test']
    t.libs << ['-pthread', '-lgtest', '-lgmock', library]
    t.libs << '-lgmock_main' unless t.sources.find { |x| File.basename(x.name) == 'main.cpp' }
    t.flags << flags
  }

  desc 'Builds c8-option-parser'
  C8.multitask(default: Names::All['generated:default', library])

  desc 'Runs c8-option-parser tests'
  C8.multitask(test: Names::All['generated:default', library, ut]) {
    sh ut.name
  }
}
