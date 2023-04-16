#include <cstdlib>



#define ngx_align(d, a)     (((d) + (a - 1)) & ~(a - 1)) // 把数值d调整到临近a的倍数
#define ngx_align_ptr(p, a)                                                   \
    (u_char *) (((uintptr_t) (p) + ((uintptr_t) a - 1)) & ~((uintptr_t) a - 1))

const int ngx_pagesize = 4096;
const int  NGX_MAX_ALLOC_FROM_POOL  =  ngx_pagesize - 1;

const int  NGX_DEFAULT_POOL_SIZE = 16 * 1024;

const int  NGX_POOL_ALIGNMENT = 16;
const int NGX_MIN_POOL_SIZE = ngx_align((sizeof(ngx_pool_s) + 2 * sizeof(ngx_pool_large_s)),NGX_POOL_ALIGNMENT);




// 类型的重定义
using u_char = unsigned char;
using ngx_uint_t = unsigned int;

// 类型的前置声明
struct ngx_pool_s;

typedef void (*ngx_pool_cleanup_pt)(void *data);

struct ngx_pool_large_s
{
    ngx_pool_large_s *next;
    void *alloc;
};

struct ngx_pool_cleanup_s
{
    ngx_pool_cleanup_pt handler;
    void *data;
    ngx_pool_cleanup_s *next;
};

// 内存池管理小块内存 内存池的头
struct ngx_pool_data_t
{
    u_char *last;
    u_char *end;
    ngx_pool_s *next;
    ngx_uint_t failed;
};

// 内存池管理信息和数据信息的头集合
struct ngx_pool_s
{
    ngx_pool_data_t d;
    size_t max;
    ngx_pool_s *current;
    ngx_pool_large_s *large;
    ngx_pool_cleanup_s *cleanup;
};
class ngx_mem_pool
{ 
public:
    bool ngx_create_pool(size_t size); 

    void ngx_destroy_pool();

    void ngx_reset_pool();

    void *ngx_palloc(size_t size);
    ngx_pool_cleanup_s *ngx_pool_cleanup_add(size_t size);
    void ngx_pfree(void *p);
    void *ngx_pnalloc(size_t size);
    void *ngx_pcalloc(size_t size);
    void *ngx_pmemalign(size_t size, size_t alignment);

private:
     void* ngx_palloc_small(size_t size, ngx_uint_t align);
     void* ngx_palloc_large(size_t size);
     void* ngx_palloc_block(size_t size);
    ngx_pool_s *pool_;
};