һ������ͻ�ʼ�顢��ʱ���ƵĹ�ϣ��

������ԣ�
 - �����������ͻ����
 - ��ϣ�����ͱȽϺ���ͨ���ӿڷ�ʽ�ṩ
 - ֧�ֹ�ϣ���ѯ�����롢ɾ���Ȳ���
 - ��ϣ�������������7������ͻ�ʽϵͣ�4%���£�
 - ��ʱ���ƣ�ɾ��ʧЧԪ��
 - ͳ�Ƴ�ͻ�ʣ��������
 - ��̬�����ڴ棬�ͷŵ��ڴ汻��ӿ����б�����malloc�������ô���

�÷���
���ȴ�����ϣ��
htable_t* htable_create(uint32_t payload_size, uint32_t cnt_used_max,
                        uint32_t cnt_idle_init, uint32_t cnt_idle_max,
                        uint32_t cnt_timeout, uint32_t (*hash)(const void*),
                        int (*equal)(const void*, const void*));

payload_sizeΪÿ�����ݵĴ�С��cnt_used_max���������������cnt_idle_init��Ԥ����Ŀ���������cnt_idle_max�ǿ������������ֵ
cnt_timeout�ǳ�ʱʱ�䣬���Ϊ0���򲻽��г�ʱ��飬hashΪ��ϣ������equalΪ�ȽϺ�����

Ȼ��Ϳ��Խ��в��롢��ѯ��ɾ���Ȳ�����
htable_item_t* htable_find(htable_t *table, void *key, void *payload);
htable_item_t* htable_insert(htable_t *table, void *key, void *payload);
int htable_remove(htable_t *table, htable_item_t *item);

���⻹���Խ��ж���ɾ����ʱʧЧ����������ڸ��µ�ǰʱ�䣬
void htable_remove_timeout(htable_t *table);
void htable_update_now(htable_t *table, time_t now);

���ڴ�ӡͳ����Ϣ
void htable_print_stat(htable_t *table);