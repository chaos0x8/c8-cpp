#include "c8-embeded-ruby/Init.hpp"
#include <memory>
#include <ruby.h>

namespace C8::EmbededRuby {
  namespace Detail {
    class RubyInit {
    public:
      RubyInit() {
        ruby_init();
        ruby_init_loadpath();
      }

      ~RubyInit() {
        ruby_cleanup(0);
      }
    };

    std::unique_ptr<RubyInit> rubyInit = nullptr;

  } // namespace Detail

  void init() {
    if (Detail::rubyInit == nullptr)
      Detail::rubyInit = std::make_unique<Detail::RubyInit>();
  }
} // namespace C8::EmbededRuby
