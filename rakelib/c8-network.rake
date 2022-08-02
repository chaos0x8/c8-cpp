namespace 'c8-network' do
  p = project do |p|
    p.flags << $flags
    p.flags << %w[-Isrc]
    p.link 'lib/libc8-common.a'

    p.generated_file 'src/c8-network/generated/BufferSize.hpp' do |t|
      size = 1024 * 1024

      t.depend __FILE__
      t.erb = proc do
        <<~INLINE
          #pragma once

          #include <cstddef>

          namespace C8::Network {
            constexpr size_t BUFFER_SIZE = <%= size %>;
          }
        INLINE
      end
    end

    p.library 'lib/libc8-network.a' do |t|
      t.sources << Dir['src/c8-network/**/*.cpp']
    end

    p.executable 'bin/c8-network-ut' do |t|
      t.flags << %w[-Itest]
      t.link_flags << %w[-pthread -lgtest -lgmock]
      t.sources << Dir['test/c8-network/**/*.cpp']
    end
  end

  multitask 'all' => [*p.requirements]
  multitask 'main' => [*p.requirements('lib/libc8-network.a')]

  multitask 'test' => [*p.requirements('bin/c8-network-ut')] do
    sh 'bin/c8-network-ut'
  end

  task 'clean' do
    p.clean
  end
end
