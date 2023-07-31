#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"     //ovaj ti uvek treba
#include "kernel/fs.h"


int
main(int argc, char *argv[])
{	
	int i;
	int sizeFile;
	


	int fd,wf;

	if(argc  != 3 ){ // nisi uneo dobro
		fprintf(2, "Unesi ime fajla i velicinu!\n");
		exit();
	}else{
		sizeFile = atoi(argv[2]);  // odvajamo velicinu


		fd = open(argv[1],0x201); //kreiras

		char buf[sizeFile];
		char karakter = 'a';
		buf[0] = karakter;
		for( i = 1 ; i < sizeFile; i++){
			if(i % 512 == 0){
				karakter++;
			}
			
			buf[i] = karakter; // punis buffer	
		}

		write(fd,buf,sizeFile); // upisujes citas


		close(fd);
		exit(); // ovo ti uvek treba na kraju
	}
	
}
