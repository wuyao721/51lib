#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <sys/ioctl.h>
#include <linux/if_tun.h>
#include <net/if.h>
#include "pcap.h"
#include <netinet/in.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>

typedef struct 
{
    uint32_t	sec;	/* length this packet (off wire) */
    uint32_t	usec;	/* length this packet (off wire) */
	uint32_t	caplen;	/* length of portion present (saved) */
	uint32_t	len;	/* length this packet (off wire, all the packet length ) */
}pcap_hdr;
#define PCAP_VERSION_MAJOR 2
#define PCAP_VERSION_MINOR 4
typedef struct  
{
	uint32_t	magic;          // pcap file flag "d4 c3 b2 a1"
	uint16_t	version_major;  // major number
	uint16_t	version_minor;  // minor number     
	uint32_t	thiszone;       // time zone, default is 0
	uint32_t	sigfigs;        // default is 0
	uint32_t	snaplen;        // max packet lenght, if want full packet ,set it 0x0000ffff(65535)
                                    // tcpdump -s 0 is this argument, default is 68 bytes
	uint32_t	linktype;       // link type    default value is 1：ethernet
}pcap_filehdr;

pcap_t *g_pcapfd = NULL;
int _linux_open_pcap(const char* szDev)
{
	 
    int fd  = -1;
    struct ifreq ifr;
    memset(&ifr,0,sizeof(struct ifreq));
    
    if((fd=socket(AF_INET,SOCK_RAW,IPPROTO_RAW)) <0 )
    {
	  	printf("\n socket serror %s \n",strerror(errno));
	  	return -1;
    }	
    strncpy(ifr.ifr_name, szDev, strlen(szDev)+1);
    if((ioctl(fd,SIOCGIFFLAGS,&ifr)==-1))
    {
        close(fd);
        printf("\n socket serror %s \n",strerror(errno));
        return -1;
    }
    if( !(ifr.ifr_flags & IFF_UP ) ) 
    {
        close(fd);
        printf("!!!Erorr: device %s is down!,extend mode need UP this device.\n", szDev );
        return -1;
    }
    close(fd);
		   
    if((g_pcapfd = pcap_open_live(szDev, 8192, 1, 100, NULL)) == NULL)
    {
        printf("Erorr: pcap_open_live open failed;dev_name = %s!\n", szDev );
        return -1;
    }

    return 0;
}


int read_cap_file_multi(const char* capFile)
{
    static char *buf = NULL;
    static size_t size = 0;

    struct stat capfilestat;
    char *offset = NULL;
    char *packet = NULL;
    FILE *fp = NULL;
    pcap_hdr *pcaphdr = NULL;
    int idx = 1;

    if (NULL == buf) {
        if (stat(capFile, &capfilestat) != 0) {
            printf("stat %s false: err:%s\n", capFile, strerror(errno));
            return -1;
        }
        size = capfilestat.st_size;
        if (NULL == (buf = (char *)calloc(1, capfilestat.st_size))) {
            printf("calloc %s false: err:%s\n", capFile, strerror(errno));
            return -1;
        }
            
        if (NULL == (fp = fopen(capFile, "rb"))) {
            printf("fopen %s false: err:%s\n", capFile, strerror(errno));       
            return -1;
        }

        if (1 != fread(buf, capfilestat.st_size, 1, fp)) {
            printf("fread %s file false: %s.\n", capFile, strerror(errno));
            fclose(fp);
            return -1;
        }
        fclose(fp);
    }
  
    offset = buf + sizeof(pcap_filehdr);
    while (offset < buf + size)
    {
        pcaphdr = (pcap_hdr *)offset;
        offset += sizeof(pcap_hdr);
        packet = offset;
        offset += pcaphdr->caplen;
        //callback(packet, pcaphdr->caplen, userdata);
        if ((pcap_sendpacket(g_pcapfd, (const u_char*)packet,pcaphdr->caplen)) != 0) {
            printf("\nError sending the packet: %s\n", pcap_geterr(g_pcapfd));
            return ;
        }

        idx++;
    }
    return 0;
}

int process_packet_test(char *filepath)
{
    struct stat buf;

    if (-1 == stat(filepath, &buf)) {
        printf("\n stat(%s) false, error:%s \n", filepath, strerror(errno));
        return -1;
    }

    printf("reading file %s\n", filepath);
    read_cap_file_multi(filepath);
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc != 0) {
        printf("usage: if_send ethX:X file.pcap");
    }
    if (0 != _linux_open_pcap(argv[1])) {
        printf("_linux_open_pcap false.\n");
        return -1;
    }
    process_packet_test(argv[2]);
    return 0;
}
//gcc if_send.c -o if_send -Ilibethpcap/include libethpcap/lib/libpcap.a
