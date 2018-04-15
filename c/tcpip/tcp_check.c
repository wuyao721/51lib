#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <stdio.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/in_systm.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <netinet/udp.h>
#if (HAVE_UNISTD_H)
#include <unistd.h>
#endif
#include <stdlib.h>
#define SET_IPV4_ADDR(a,v) do {                              \
        (a)->s6_addr32[0] = (uint32_t)v; \
        (a)->s6_addr32[1] = 0;                                  \
        (a)->s6_addr32[2] = 0;                                  \
        (a)->s6_addr32[3] = 0;                                  \
    } while (0)

typedef struct in6_addr in6_addr_t;
typedef struct {
    int        af;
    in6_addr_t src;
    in6_addr_t dst;
    uint16_t   sp;
    uint16_t   dp;
    uint8_t    proto;
    uint32_t   sgwip;
    uint32_t   enbip;
} session_key_t;

#pragma pack(1)  /* 下面的结构按照字节对齐 */    
typedef struct EthernetHdr_ {
    union
    {
        struct
        {
            uint8_t eth_dst[6];
            uint8_t eth_src[6];
        }mac;  
        struct
        {
            union
            {
                uint64_t cdmaimsi;
                struct
                {
                    uint32_t gsndst;
                    uint32_t teid;
                }gprs;
                struct 
                {
                    uint8_t mac[6];      // 用户的MAC地址；
                    uint16_t sessionid;  // PPPOE协议的会话ID，上下行的会话ID相同；
                }ppoe;
                struct 
                {
                    uint32_t ip_dst;
                    uint16_t tunnelid;
                    uint16_t sessionid;
                } l2tp;
            };
            uint8_t bDirect;          //数据方向
            uint8_t szReserve[3];     //保留位
        };  
    };
    uint16_t eth_type;
} EthernetHdr;
#pragma pack()  /* 恢复默认字节对齐 */

typedef struct IPV4Hdr_
{
    uint8_t ip_verhl;     /**< version & header length */
    uint8_t ip_tos;       /**< type of service */
    uint16_t ip_len;      /**< length */
    uint16_t ip_id;       /**< id */
    uint16_t ip_off;      /**< frag offset */
    uint8_t ip_ttl;       /**< time to live */
    uint8_t ip_proto;     /**< protocol (tcp, udp, etc) */
    uint16_t ip_csum;     /**< checksum */
    struct in_addr ip_src;/**< source address */
    struct in_addr ip_dst;/**< destination address */
} IPV4Hdr;
typedef struct TCPHdr_
{
    uint16_t th_sport;     /* source port */
    uint16_t th_dport;     /* destination port */
    uint32_t th_seq;       /* sequence number */
    uint32_t th_ack;       /* acknowledgement number */
    uint8_t th_off;        /* offset and reserved */
    uint8_t th_flags;      /* pkt flags */
#define TH_FIN	0x01
#define TH_SYN	0x02
#define TH_RST	0x04
#define TH_PUSH	0x08
#define TH_ACK	0x10
#define TH_URG	0x20
   uint16_t th_win;       /* pkt window */
    uint16_t th_sum;       /* checksum */
    uint16_t th_urp;       /* urgent pointer */
} TCPHdr;
#define IPV4_GET_RAW_VER(ip4h)            (((ip4h)->ip_verhl & 0xf0) >> 4)
#define IPV4_GET_RAW_HLEN(ip4h)           ((ip4h)->ip_verhl & 0x0f)
#define IPV4_GET_RAW_IPTOS(ip4h)          ((ip4h)->ip_tos)
#define IPV4_GET_RAW_IPLEN(ip4h)          ((ip4h)->ip_len)
#define IPV4_GET_RAW_IPID(ip4h)           ((ip4h)->ip_id)
#define IPV4_GET_RAW_IPOFFSET(ip4h)       ((ip4h)->ip_off)
#define IPV4_GET_RAW_IPTTL(ip4h)          ((ip4h)->ip_ttl)
#define IPV4_GET_RAW_IPPROTO(ip4h)        ((ip4h)->ip_proto)
#define IPV4_GET_RAW_IPSRC(ip4h)          ((ip4h)->ip_src)
#define IPV4_GET_RAW_IPDST(ip4h)          ((ip4h)->ip_dst)

/* XXX RAW* needs to be really 'raw', so no ntohs there */
#define UDP_GET_RAW_LEN(udph)                ntohs((udph)->uh_len)
#define UDP_GET_RAW_SRC_PORT(udph)           ntohs((udph)->uh_sport)
#define UDP_GET_RAW_DST_PORT(udph)           ntohs((udph)->uh_dport)

#define UDP_GET_LEN(p)                       UDP_GET_RAW_LEN(p->udph)
#define UDP_GET_SRC_PORT(p)                  UDP_GET_RAW_SRC_PORT(p->udph)
#define UDP_GET_DST_PORT(p)                  UDP_GET_RAW_DST_PORT(p->udph)

#define TCP_GET_RAW_OFFSET(tcph)             (((tcph)->th_off & 0xf0) >> 4)
#define TCP_GET_RAW_X2(tcph)                 ((tcph)->th_off & 0x0f)
#define TCP_GET_RAW_SRC_PORT(tcph)           ntohs((tcph)->th_sport)
#define TCP_GET_RAW_DST_PORT(tcph)           ntohs((tcph)->th_dport)
#define TCP_GET_RAW_SEQ(tcph)                ntohl((tcph)->th_seq)
#define TCP_GET_RAW_ACK(tcph)                ntohl((tcph)->th_ack)
#define TCP_GET_RAW_WINDOW(tcph)             ntohs((tcph)->th_win)
#define TCP_GET_OFFSET(p)                    TCP_GET_RAW_OFFSET(p->tcph)
#define TCP_GET_HLEN(p)                      TCP_GET_OFFSET(p) << 2
#define TCP_GET_SRC_PORT(p)                  TCP_GET_RAW_SRC_PORT(p->tcph)
#define TCP_GET_DST_PORT(p)                  TCP_GET_RAW_DST_PORT(p->tcph)
#define TCP_GET_SEQ(p)                       TCP_GET_RAW_SEQ(p->tcph)
#define TCP_GET_ACK(p)                       TCP_GET_RAW_ACK(p->tcph)
#define TCP_GET_WINDOW(p)                    TCP_GET_RAW_WINDOW(p->tcph)

typedef struct Packet_
{
    session_key_t addr;
 
    uint8_t    flags;
    uint32_t   hash_key;

    //int idx;
    //int datalink;
    /* header pointers */
    EthernetHdr *ethh;
    IPV4Hdr *ip4h;
    TCPHdr *tcph;


    /* ptr to the payload of the packet with it's length. */
    uint8_t *payload;
    uint16_t payload_len;

    /* storage: maximum ip packet size + link header */
    uint32_t pktlen;
    int skblen;
    uint32_t bSpec;
    uint8_t bCreatOK;
    uint8_t bDirect;
    uint8_t bCap;
    u_int fromclient;
    uint16_t mark;  
    uint16_t bfind;
    uint64_t Imsi;
    uint32_t data_type;
} Packet;

struct psuedo_hdr
{
  u_int saddr;      
  u_int daddr;      
  u_char zero;        
  u_char protocol;    
  u_short len;        
};

static uint64_t g_count = 0;

u_short ip_check_ext(register u_short *addr, register int len, int addon)
{
  register int nleft = len;
  register u_short *w = addr;
  register int sum = addon;
  u_short answer = 0;

  /*
   *  Our algorithm is simple, using a 32 bit accumulator (sum),
   *  we add sequential 16 bit words to it, and at the end, fold
   *  back all the carry bits from the top 16 bits into the lower
   *  16 bits.
   */
  while (nleft > 1)  {
    sum += *w++;
    nleft -= 2;
  }
  /* mop up an odd byte, if necessary */
  if (nleft == 1) {
    *(u_char *)(&answer) = *(u_char *)w;
    sum += answer;
  }  
  /* add back carry outs from top 16 bits to low 16 bits */
  sum = (sum >> 16) + (sum & 0xffff);     /* add hi 16 to low 16 */
  sum += (sum >> 16);                     /* add carry */
  answer = ~sum;                          /* truncate to 16 bits */
  return (answer);
}


u_short my_tcp_check(struct tcphdr *th, int len, u_int saddr, u_int daddr)
{
  unsigned int      i;
  int               sum = 0;
  struct psuedo_hdr hdr;
  
  g_count ++;
  
  //if (dontchksum(saddr))
  //	return 0;
  
  hdr.saddr = saddr;
  hdr.daddr = daddr;
  hdr.zero = 0;
  hdr.protocol = IPPROTO_TCP;
  hdr.len = htons(len);
  for (i = 0; i < sizeof(hdr); i += 2)
    sum += *(u_short *)((char *)(&hdr) + i);
  
  return (ip_check_ext((u_short *)th, len, sum));
}                     

inline int likely(int expr)
{
#ifdef __GNUC__
    return __builtin_expect(expr, 1);
#else
    return expr;
#endif
}

/** \brief hint for the branch prediction */
inline int unlikely(int expr)
{
#ifdef __GNUC__
    return __builtin_expect(expr, 0);
#else
    return expr;
#endif
}

u_short ip_check_ext2(register u_short *addr, register int len, int addon)
{
  register int nleft = len;
  register u_short *w = addr;
  register int sum = addon;
  u_short answer = 0;

  /*
   *  Our algorithm is simple, using a 32 bit accumulator (sum),
   *  we add sequential 16 bit words to it, and at the end, fold
   *  back all the carry bits from the top 16 bits into the lower
   *  16 bits.
   */

#if 1
  
  while (likely(nleft > 7))  {
    sum += *w++;
    sum += *w++;
    sum += *w++;
    sum += *w++;
//      sum += *w + *(w+1) + *(w+2) + *(w+3);
//      w += 4;
      nleft -= 8;
  }
#endif

  while (likely(nleft > 1)) {
      sum += *w++;
      nleft -= 2;
  }

  /* mop up an odd byte, if necessary */
  if (nleft == 1) {
    sum += *(u_char *)w;
  }  
  /* add back carry outs from top 16 bits to low 16 bits */
  sum = (sum >> 16) + (sum & 0xffff);     /* add hi 16 to low 16 */
  sum += (sum >> 16);                     /* add carry */
  answer = ~sum;                          /* truncate to 16 bits */
  return (answer);
}


u_short my_tcp_check2(struct tcphdr *th, int len, u_int saddr, u_int daddr)
{
  unsigned int      i;
  int               sum = 0;
  struct psuedo_hdr hdr;
  
  g_count ++;
  
  //if (dontchksum(saddr))
  //	return 0;
  
  hdr.saddr = saddr;
  hdr.daddr = daddr;
  hdr.zero = 0;
  hdr.protocol = IPPROTO_TCP;
  hdr.len = htons(len);
  for (i = 0; i < sizeof(hdr); i += 2)
    sum += *(u_short *)((char *)(&hdr) + i);
  
  return (ip_check_ext2((u_short *)th, len, sum));
}                     

#define TCP_HEADER_LEN            20
void DecodeTCP(Packet *p, uint8_t *pkt, uint16_t len)
{
    int hlen = 0;

    if (len < TCP_HEADER_LEN) {
        return ;
    }

    p->tcph = (TCPHdr *)pkt;
    hlen = TCP_GET_HLEN(p);
    if (len < hlen) {
        return;
    }
    
    if (0 != my_tcp_check2((struct tcphdr *)p->tcph, len, *(u_int*)&p->addr.src, *(u_int*)&p->addr.dst)) {
        printf("error.\n");
    }
}


#define IPV4_HEADER_LEN           20      /**< Header length */
#define TCP_HEADER_LEN            20

static void _ip_defragment(void *param, struct ip *iph) 
{
    Packet *p = (Packet*)param;
    uint16_t ip_len = ntohs(iph->ip_len);
    if (ip_len < (u_int)(iph->ip_hl << 2)) {
        return;
    }
    
    int skblen = ip_len + 16;
    skblen = (skblen + 15) & ~15;
    skblen += 4000;
      
    p->ip4h = (IPV4Hdr *)iph; 
    p->skblen = skblen;

    if (p->ip4h->ip_src.s_addr == 0 || p->ip4h->ip_dst.s_addr == 0 ) 
    {
        return;
    }
     
    switch (IPV4_GET_RAW_IPPROTO(p->ip4h)) {
        case IPPROTO_TCP:
            DecodeTCP( p, (uint8_t*)((char*)iph + IPV4_HEADER_LEN),ip_len - IPV4_HEADER_LEN);
            break;
        default:
            break;
    }
}

void DecodeIPV4(Packet *p, uint8_t *pkt, uint16_t len)
{
    struct ip *iph   = (struct ip *) pkt;
    uint16_t  ip_len = ntohs(iph->ip_len);

    //ip_fast_csum((unsigned char *) iph, iph->ip_hl) != 0 ||
    if (len < sizeof(struct ip) || 
        iph->ip_hl < 5 ||
        iph->ip_v != 4 ||
        len < ip_len ||
        ip_len < (iph->ip_hl << 2)) {
        return;
    }

    p->addr.af = AF_INET;
    if (p->addr.src.s6_addr32[0] == 0) {
        SET_IPV4_ADDR(&p->addr.src, iph->ip_src.s_addr);
    }
    if (p->addr.dst.s6_addr32[0] == 0) {
        SET_IPV4_ADDR(&p->addr.dst, iph->ip_dst.s_addr);
    }

    _ip_defragment(p, iph);

    return;
}
#define ETHERNET_HEADER_LEN       14

void DecodeEthPkt(Packet *p, uint8_t *pkt, uint16_t len, uint32_t gsnsrc)
{
    uint16_t eth_type = 0;

    if (len < ETHERNET_HEADER_LEN) {
        return;
    }

    p->ethh = (EthernetHdr *)pkt;
    //memcpy(&p->ethh, pkt, sizeof(EthernetHdr));
    p->pktlen = len;
    p->bDirect =  p->ethh->bDirect;
    eth_type = ntohs(p->ethh->eth_type);

    p->addr.sgwip = 0;
    p->addr.enbip = 0;

    switch (eth_type) {
        case 0x0800:
            DecodeIPV4(p, pkt + ETHERNET_HEADER_LEN, len - ETHERNET_HEADER_LEN);
            break;
        default:
            printf("unkonw eth frame, eth type: %04x, not support.\n", eth_type);
            break;  
    }
    return;
}

void SendCapPacket(const char* data, uint16_t len, void* userdata)
{
    static Packet pkt;	
    static int    idx = 1;
    char          *p  = (char*)data;
    char szValue[256]={0};
    uint32_t      gsnsrc = 0;
    
    //printf("parsing %dst packet. len: %d\n", idx++, len);
    memset(&pkt, 0, sizeof(Packet));  
    pkt.bfind = 0;
    pkt.bCap = 0;
    //pkt.idx = ++idx;
    pkt.mark = 0;

    DecodeEthPkt(&pkt, (uint8_t*)p, len, gsnsrc);
    return;
}

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
typedef void (*pcap_cb_t)(const char* data, uint16_t len, void* userdata);
int read_cap_file_multi(const char* capFile, pcap_cb_t callback, void* userdata)
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
        callback(packet, pcaphdr->caplen, userdata);
        idx++;
    }
    return 0;
}

int process_packet_test()
{
    int i = 0;
    int sec_cnt = 0;
    time_t pre_tm;
    time_t last_tm;
    struct stat buf;
    struct timeval tv1;
    struct timeval tv2;
    

    if (-1 == stat("a.pcap", &buf)) {
        printf("\n stat(%s) false, error:%s \n", "a.pcap", strerror(errno));
        return -1;
    }

    pre_tm = time(0);
    gettimeofday(&tv1, NULL);
    for (i = 0; i < 1000; i++) {
        read_cap_file_multi("a.pcap", SendCapPacket, NULL);
    }
    gettimeofday(&tv2, NULL);
    printf("time: %d.%d, count: %d\n", tv2.tv_sec - tv1.tv_sec, tv2.tv_usec - tv1.tv_usec, g_count);
    return 0;
}

int main()
{
    process_packet_test();
}
