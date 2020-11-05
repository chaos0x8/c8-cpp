C8::Config.register :networkBufferSize, default: 1024*1024

namespace('c8-network') {
  flags = ['--std=c++17', '-Wall', '-Werror']

  if C8::Config.debug
    flags += ['-g']
  else
    flags += ['-O3', '-s', '-DNDEBUG']
  end

  generated = Invoke.new { |t|
    t.name = 'generated'
    t.requirements << GeneratedFile.new(format: true) { |t|
      t.name = 'src/c8-network/generated/BufferSize.hpp'
      t.requirements << 'rakelib/c8-network.rake' << C8::Config
      t.code = proc {
        C8.erb(C8.data(__FILE__).bufferSize, size: C8::Config.networkBufferSize)
      }
    }
  }

  library = Library.new { |t|
    t.name = 'lib/libc8-network.a'
    t.requirements << generated << 'c8-common:default' << C8::Config
    t.sources << FileList['src/c8-network/**/*.cpp']
    t.includes << ['src']
    t.flags << flags
  }

  ut = Executable.new { |t|
    t.name = 'bin/c8-network-ut'
    t.requirements << generated << 'c8-common:default' << C8::Config
    t.sources << FileList['test/c8-network/**/*.cpp']
    t.includes << ['src', 'test']
    t.libs << ['-pthread', '-lgtest', '-lgmock', library, 'lib/libc8-common.a']
    t.libs << '-lgmock_main' unless t.sources.find { |x| File.basename(x.name) == 'main.cpp' }
    t.flags << flags
  }

  desc 'Builds c8-network'
  C8.multitask(default: Names::All['generated:default', library])

  desc 'Runs c8-network tests'
  C8.multitask(test: Names::All['generated:default', library, ut]) {
    sh ut.name
  }
}

__END__
@@bufferSize=
#pragma once

#include <cstddef>

namespace C8::Network {
  constexpr size_t BUFFER_SIZE = <%= @size %>u;
}
