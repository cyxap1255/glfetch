#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/utsname.h>
#include <sys/sysinfo.h>

#define DEFAULT_TEXT "\x1b[35m"
#define KEY "\x1b[36m"

int main(int argc, char *argv[]) {
	char *distro = "Gentoo Linux";
    	char *term = getenv("TERM");
    	char *shell = getenv("SHELL");
    	char *user = getenv("USER");
		char hostname[256];
    	gethostname(hostname, sizeof(hostname));
    	struct utsname kernel;
    	uname(&kernel);
    	struct sysinfo sys_info;
    	sysinfo(&sys_info);
    	long uptime_seconds = sys_info.uptime;
    	long hours = (uptime_seconds % 86400) / 3600;
    	long minutes = (uptime_seconds % 3600) / 60;
    	long total_ram = 0, free_ram = 0;
    	FILE *f = fopen("/proc/meminfo", "r");
        if (f) {
        	char line[256];
            	while (fgets(line, sizeof(line), f)) {
                	sscanf(line, "MemTotal: %ld kB", &total_ram);
                	sscanf(line, "MemAvailable: %ld kB", &free_ram);
        	}

            	fclose(f);
            	total_ram = total_ram /  1024;
            	free_ram = free_ram /  1024;
        }

        long used_ram = total_ram - free_ram;

    	void uptime_gentoo(long hours, long minutes) {
		if (hours == 0) {
			printf(DEFAULT_TEXT"   \\        )" KEY "   UPTIME: " DEFAULT_TEXT "%ldm\n", minutes);
	  	} else {
        		printf(DEFAULT_TEXT"   \\        )" KEY "   UPTIME: " DEFAULT_TEXT "%ldh %ldm\n", hours, minutes);
           	}
    	}

		void uptime_plan9(long hours, long minutes) {
			if (hours == 0) {
				printf(DEFAULT_TEXT"   |   ° ¡  " KEY "  UPTIME: " DEFAULT_TEXT "%ldm\n", minutes);
			} else {
				printf(DEFAULT_TEXT"   |   ° ¡  " KEY "  UPTIME: " DEFAULT_TEXT "%ldh %ldm\n", hours, minutes);
			}
		}

		if (argc == 2 && strcmp(argv[1], "--help") == 0) {
			printf("syntax: glfetch -l plan9/gentoo\n"
		      		"syntax help: glfetch --help\n");
			}

		if (argc == 3 && strcmp(argv[1], "-l") == 0 && strcmp(argv[2], "gentoo") == 0) {
			printf(DEFAULT_TEXT"   _-----_     " DEFAULT_TEXT " %s@%s\n",                                   user, hostname);
    		printf(DEFAULT_TEXT"  (       \\   " KEY "  OS: " DEFAULT_TEXT "%s\n",                                  distro);
    		printf(DEFAULT_TEXT"  \\    0   \\ " KEY "   KERNEL: " DEFAULT_TEXT "%s %s\n",  kernel.sysname, kernel.release);
    		uptime_gentoo(hours, minutes);            
    		printf(DEFAULT_TEXT"   /      _/   " KEY " SHELL: " DEFAULT_TEXT "%s\n",                                 shell);
    		printf(DEFAULT_TEXT"  (     _-     " KEY " TERM: " DEFAULT_TEXT "%s\n",                                   term);
    		printf(DEFAULT_TEXT"  \\____-      " KEY "  MEMORY: " DEFAULT_TEXT "%ldMiB/%ldMiB\n",      used_ram, total_ram);
    		printf("                                                                                                   \n");
		}
	
		if (argc == 3 && strcmp(argv[1], "-l") == 0 && strcmp(argv[2], "plan9") == 0) {
			printf(DEFAULT_TEXT"    (\\(\\      " DEFAULT_TEXT "%s@%s\n",                                   user, hostname);
			printf(DEFAULT_TEXT"   j'. ..   " KEY "  OS: " DEFAULT_TEXT "%s\n",                                  distro);
			printf(DEFAULT_TEXT"   (  . .)  " KEY "  KERNEL: " DEFAULT_TEXT "%s %s\n",  kernel.sysname, kernel.release);
			uptime_plan9(hours, minutes);
			printf(DEFAULT_TEXT"   ¿     ;  " KEY "  SHELL: " DEFAULT_TEXT "%s\n",                                 shell);
			printf(DEFAULT_TEXT"   c?'.UJ   " KEY "  TERM: " DEFAULT_TEXT "%s\n",                                   term);
			printf(DEFAULT_TEXT"            " KEY "  MEMORY: "  DEFAULT_TEXT "%ldMiB/%ldMiB\n",      used_ram, total_ram);
		}

		if (argc == 3 && strcmp(argv[1], "-l") == 1) {
			printf("syntax: glfetch -l plan9/gentoo\n");
		}

		if (argc < 2) {
			printf("syntax: glfetch -l plan9/gentoo\n");
		}
}
