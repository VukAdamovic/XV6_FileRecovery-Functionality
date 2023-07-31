#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"     //ovaj ti uvek treba
#include "kernel/fs.h"


int
main(int argc, char *argv[])
{
	hello(3);
	exit(); // ovo ti uvek treba na kraju
}
