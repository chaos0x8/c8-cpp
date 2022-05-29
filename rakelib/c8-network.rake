C8::Config.register :networkBufferSize, default: 1024 * 1024

C8.project 'c8-network' do
  flags << $flags
  flags << %w[-Isrc]

  link 'lib/libc8-common.a'

  file_generated 'src/c8-network/generated/BufferSize.hpp' => __FILE__ do
    C8.erb size: C8::Config.networkBufferSize do
      <<~INLINE
        #pragma once

        #include <cstddef>

        namespace C8::Network {
          constexpr size_t BUFFER_SIZE = <%= size %>;
        }
      INLINE
    end
  end

  library 'lib/libc8-network.a' do
    sources << Dir['src/c8-network/**/*.cpp']
  end

  test 'bin/c8-network-ut' do
    flags << %w[-Itest]
    link_flags << %w[-pthread -lgtest -lgmock]
    sources << Dir['test/c8-network/**/*.cpp']
  end
end
