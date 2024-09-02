savedcmd_/home/chydo/module_5/hello.mod := printf '%s\n'   hello.o | awk '!x[$$0]++ { print("/home/chydo/module_5/"$$0) }' > /home/chydo/module_5/hello.mod
