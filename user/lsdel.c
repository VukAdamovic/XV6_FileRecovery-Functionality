#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"
#include "kernel/fs.h"

char*
fmtname(char *path)
{
	static char buf[DIRSIZ+1];
	char *p;

	// Find first character after last slash.
	for(p=path+strlen(path); p >= path && *p != '/'; p--)
		;
	p++;

	// Return blank-padded name.
	if(strlen(p) >= DIRSIZ)
		return p;
	memmove(buf, p, strlen(p));
	memset(buf+strlen(p), ' ', DIRSIZ-strlen(p));
	return buf;
}

void
test(char *path)
{
	char buf[512], *p;
	int fd;
	struct dirent de;
	struct stat st;
	int broj = 0;
	char result[896]; //(64* (DIRSIZ+ 1) = 896
	
	for(int i = 0; i < 896 ; i++){
		result[i] =' ';
	
	}
	

	if((fd = open(path, 0)) < 0){
		fprintf(2, "ls: cannot open %s\n", path);
		return;
	}

	if(fstat(fd, &st) < 0){
		fprintf(2, "ls: cannot stat %s\n", path);
		close(fd);
		return;
	}

		switch(st.type){
		case T_FILE:	
			printf("%s %d %d %d\n", fmtname(path), st.type, st.ino, st.size);
			break;

		case T_DIR:
			if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
				printf("ls: path too long\n");
				break;
			}

			broj = lsdel(fd,result);

			if(broj == 0){
				fprintf(2,"Nema obrisanih fajla u datom folderu.\n");
			}else{
				for(int i = 0; i < 896; i++){	
					if(result[i] != ' ')
						printf("%c",result[i]);

				}
			}
			break;
		}

		close(fd);
}

int
main(int argc, char *argv[])
{
	int i;

	if(argc < 2){
		test(".");
		exit();
	}
	for(i=1; i<argc; i++)
		test(argv[i]);
	exit();
}
