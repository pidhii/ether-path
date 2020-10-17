#include <ether/ether.h>

#include <libgen.h>
#include <string.h>


static eth_t
_dirname(void)
{
  eth_args args = eth_start(2);
  eth_t path = eth_arg2(args, eth_string_type);
  char buf[PATH_MAX];
  memcpy(buf, eth_str_cstr(path), eth_str_len(path) + 1);
  eth_return(args, eth_str(dirname(buf)));
}

static eth_t
_basename(void)
{
  eth_args args = eth_start(2);
  eth_t path = eth_arg2(args, eth_string_type);
  char buf[PATH_MAX];
  memcpy(buf, eth_str_cstr(path), eth_str_len(path) + 1);
  eth_return(args, eth_str(basename(buf)));
}


int
ether_module(eth_module *mod, eth_env *topenv)
{
  eth_define(mod, "dirname", eth_proc(_dirname, 1));
  eth_define(mod, "basename", eth_proc(_basename, 1));

  if (not eth_add_module_script(mod, "./lib.eth", topenv))
    return -1;

  return 0;
}
