����Ŀ�ģ����Ը��������memcpyʹ��CPU��ʹ���ʣ��Լ������ܵ�Ӱ������ԡ�

�豸1��Intel(R) Xeon(R) CPU E5-2648L 0 @ 1.80GHz
�豸2��CN6880

����һ�����˱Ƚ�memcpy��rte_memcpy���ٶ�
����Ч�������˵�CPU 100%��65536��С�ڴ���ڴ�飬���������ٶ���12GB/s��memcpy���ٶȱ�rte_memcpy����������ôһ��㡣
[wuy@PS168 mem_test]$ ./a.out
memcpy test. size: 16 cnt: 1000000:
    memcpy interval sec: 0, usec: 10063
rte_memcpy interval sec: 0, usec: 4296

memcpy test. size: 64 cnt: 1000000:
    memcpy interval sec: 0, usec: 8974
rte_memcpy interval sec: 0, usec: 3772

memcpy test. size: 256 cnt: 1000000:
    memcpy interval sec: 0, usec: 20875
rte_memcpy interval sec: 1, usec: -985810

memcpy test. size: 1024 cnt: 1000000:
    memcpy interval sec: 0, usec: 77263
rte_memcpy interval sec: 0, usec: 40460

memcpy test. size: 4096 cnt: 1000000:
    memcpy interval sec: 0, usec: 183119
rte_memcpy interval sec: 0, usec: 149092

memcpy test. size: 16384 cnt: 1000000:
    memcpy interval sec: 1, usec: -306859
rte_memcpy interval sec: 0, usec: 697520

memcpy test. size: 65536 cnt: 1000000:
    memcpy interval sec: 6, usec: -284327
rte_memcpy interval sec: 5, usec: -213702

memcpy test. size: 262144 cnt: 1000000:
    memcpy interval sec: 33, usec: 332318
rte_memcpy interval sec: 34, usec: -175920


���Զ������memcpy֮�������Ӱ��
����Ч�������к˵�CPU 100%��������ͬʱ�ܵ�ʱ���ٶȸ��������ơ���ͬʱ�ܵĺ˳���20����ʱ��ĳЩ���ܵø�����32����ͬʱ�ܵ�ʱ�����еĺ��ܵ��ٶ���ԭ����һ�롣
[wuy@PS168 mem_test]$ ./multi_mem_test.sh
memcpy test. size: 65536 cnt: 1000000:
memcpy test. size: 65536 cnt: 1000000:
memcpy test. size: 65536 cnt: 1000000:
memcpy test. size: 65536 cnt: 1000000:
memcpy test. size: 65536 cnt: 1000000:
memcpy test. size: 65536 cnt: 1000000:
memcpy test. size: 65536 cnt: 1000000:
memcpy test. size: 65536 cnt: 1000000:
memcpy test. size: 65536 cnt: 1000000:
memcpy test. size: 65536 cnt: 1000000:
memcpy test. size: 65536 cnt: 1000000:
memcpy test. size: 65536 cnt: 1000000:
memcpy test. size: 65536 cnt: 1000000:
memcpy test. size: 65536 cnt: 1000000:
memcpy test. size: 65536 cnt: 1000000:
memcpy test. size: 65536 cnt: 1000000:
memcpy test. size: 65536 cnt: 1000000:
memcpy test. size: 65536 cnt: 1000000:
memcpy test. size: 65536 cnt: 1000000:
memcpy test. size: 65536 cnt: 1000000:
memcpy test. size: 65536 cnt: 1000000:
memcpy test. size: 65536 cnt: 1000000:
[wuy@PS168 mem_test]$ memcpy test. size: 65536 cnt: 1000000:
memcpy test. size: 65536 cnt: 1000000:
memcpy test. size: 65536 cnt: 1000000:
memcpy test. size: 65536 cnt: 1000000:
memcpy test. size: 65536 cnt: 1000000:
memcpy test. size: 65536 cnt: 1000000:
memcpy test. size: 65536 cnt: 1000000:
memcpy test. size: 65536 cnt: 1000000:
memcpy test. size: 65536 cnt: 1000000:
memcpy test. size: 65536 cnt: 1000000:

[wuy@PS168 mem_test]$     memcpy interval sec: 11, usec: 688052
    memcpy interval sec: 11, usec: 695614
    memcpy interval sec: 11, usec: 714870
    memcpy interval sec: 11, usec: 722457
    memcpy interval sec: 11, usec: 734507
    memcpy interval sec: 11, usec: 751270
    memcpy interval sec: 11, usec: 733686
    memcpy interval sec: 11, usec: 774354
    memcpy interval sec: 11, usec: 815639
    memcpy interval sec: 11, usec: 821583
    memcpy interval sec: 11, usec: 828550
    memcpy interval sec: 11, usec: 831822
    memcpy interval sec: 11, usec: 831876
    memcpy interval sec: 11, usec: 890040
    memcpy interval sec: 11, usec: 894770
    memcpy interval sec: 11, usec: 903501
    memcpy interval sec: 11, usec: 912770
    memcpy interval sec: 11, usec: 930857
    memcpy interval sec: 11, usec: 937353
    memcpy interval sec: 12, usec: -34904
    memcpy interval sec: 12, usec: -13949
    memcpy interval sec: 12, usec: 20148
    memcpy interval sec: 12, usec: 18499
    memcpy interval sec: 12, usec: 37506
    memcpy interval sec: 12, usec: 49935
    memcpy interval sec: 12, usec: 61218
    memcpy interval sec: 12, usec: 86294
    memcpy interval sec: 12, usec: 91255
    memcpy interval sec: 12, usec: 96968
    memcpy interval sec: 12, usec: 148670
    memcpy interval sec: 12, usec: 157070
    memcpy interval sec: 12, usec: 197506

[wuy@PS168 mem_test]$ rte_memcpy interval sec: 10, usec: 33827

memcpy test. size: 262144 cnt: 1000000:
rte_memcpy interval sec: 10, usec: 42006

memcpy test. size: 262144 cnt: 1000000:
rte_memcpy interval sec: 10, usec: 176425

memcpy test. size: 262144 cnt: 1000000:
rte_memcpy interval sec: 10, usec: 136139

memcpy test. size: 262144 cnt: 1000000:
rte_memcpy interval sec: 10, usec: 150162

memcpy test. size: 262144 cnt: 1000000:
rte_memcpy interval sec: 10, usec: 219082

memcpy test. size: 262144 cnt: 1000000:
rte_memcpy interval sec: 11, usec: -733428

memcpy test. size: 262144 cnt: 1000000:
rte_memcpy interval sec: 11, usec: -648716

memcpy test. size: 262144 cnt: 1000000:
rte_memcpy interval sec: 11, usec: -707468

memcpy test. size: 262144 cnt: 1000000:
rte_memcpy interval sec: 11, usec: -487930

memcpy test. size: 262144 cnt: 1000000:
rte_memcpy interval sec: 11, usec: -629512

memcpy test. size: 262144 cnt: 1000000:


��������Caviumƽ̨�µ�memcpy������
�����ٶȱ�x86��������
~ # ./mem_test_cavium-1.0.0
CVMX_SHARED: 0x1200b0000-0x1200c0000
Active coremask = 0xf
memcpy test. size: 4096 cnt: 1000000:
     memcpy interval sec: 2, usec: -901540
cvmx memcpy interval sec: 1, usec: 58288

memcpy test. size: 16 cnt: 1000000:
     memcpy interval sec: 0, usec: 41708
cvmx memcpy interval sec: 0, usec: 24145

memcpy test. size: 64 cnt: 1000000:
     memcpy interval sec: 0, usec: 39205
cvmx memcpy interval sec: 0, usec: 55201

memcpy test. size: 256 cnt: 1000000:
     memcpy interval sec: 0, usec: 97273
cvmx memcpy interval sec: 0, usec: 175390

memcpy test. size: 1024 cnt: 1000000:
     memcpy interval sec: 0, usec: 289716
cvmx memcpy interval sec: 1, usec: -334538

memcpy test. size: 4096 cnt: 1000000:
     memcpy interval sec: 1, usec: 95449
cvmx memcpy interval sec: 3, usec: -401381

memcpy test. size: 16384 cnt: 1000000:
     memcpy interval sec: 4, usec: 331544
cvmx memcpy interval sec: 10, usec: 378776

memcpy test. size: 65536 cnt: 1000000:
     memcpy interval sec: 32, usec: -64851
cvmx memcpy interval sec: 55, usec: 45752

memcpy test. size: 262144 cnt: 1000000:
     memcpy interval sec: 128, usec: -623027


