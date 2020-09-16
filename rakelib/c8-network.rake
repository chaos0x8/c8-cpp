namespace('c8-network') {
  flags = ['--std=c++17', '-Wall', '-Werror']

  if $argv[:debug]
    flags += ['-g']
  else
    flags += ['-O3', '-s', '-DNDEBUG']
  end

  generated = []
  generated << GeneratedFile.new(format: true) { |t|
    t.name = 'src/c8-network/generated/BufferSize.hpp'
    t.code = proc {
      d = []
      d << "#pragma once"
      d << ""
      d << "#include <cstddef>"
      d << ""
      d << "namespace C8::Network {"
      d << "  constexpr size_t BUFFER_SIZE = #{1024*1024}u;"
      d << "}"
    }
  }

  library = Library.new { |t|
    t.name = 'lib/libc8-network.a'
    t.requirements << generated << 'c8-common:default'
    t.sources << FileList['src/c8-network/**/*.cpp']
    t.includes << ['src']
    t.flags << flags
  }

  ut = Executable.new { |t|
    t.name = 'bin/c8-network-ut'
    t.requirements << generated << 'c8-common:default'
    t.sources << FileList['test/c8-network/**/*.cpp']
    t.includes << ['src', 'test']
    t.libs << ['-pthread', '-lgtest', '-lgmock', library, 'lib/libc8-common.a']
    t.flags << flags
  }

  desc 'Builds c8-network'
  C8.multitask(default: Names['generated:default', library])

  desc 'Runs c8-network tests'
  C8.multitask(test: Names['generated:default', library, ut]) {
    sh ut.name
  }
}
