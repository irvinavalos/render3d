#define DOCTEST_CONFIG_IMPLEMENT
#include <doctest.h>

int main(int argc, char **argv) {
  doctest::Context ctx;

  ctx.setOption("abort-after", 5);
  ctx.applyCommandLine(argc, argv);
  ctx.setOption("no-breaks", true);

  int res = ctx.run();

  if (ctx.shouldExit())
    return res;

  return res;
}
