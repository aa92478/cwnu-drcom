#ifndef _COMMON_H
#define _COMMON_H
/*
 * 通用的代码和定义
 */
typedef unsigned char uchar;	/* 一个字节 */
typedef unsigned short uint16;	/* 两个字节 */
typedef unsigned int uint32;	/* 四个字节 */

/* 用户名和密码长度 */
#define UNAME_LEN	(32)
#define PWD_LEN		(32)

#ifdef LINUX
# include <unistd.h>
# include <netinet/if_ether.h>
# include <net/if.h>
# define EXE_PATH_MAX   (PATH_MAX+1)
#elif defined(WINDOWS)
# include <windows.h>
# define ETH_ALEN	    (6)
# define IFNAMSIZ	    (64)
# define MTU_MAX	    (65536)
# define EXE_PATH_MAX   (MAX_PATH+1)
# define IFDESCSIZ      (126)
#endif

typedef struct {
    char name[IFNAMSIZ]; /* linux下是eth0, windows采用的是注册表类似的(\Device\NPF_{xxxx-xxx-xx-xx-xxx}) */
#ifdef WINDOWS
    char desc[IFDESCSIZ]; /* windows下描述(AMD PCNET Family PCI Ethernet Adapter) */
#endif
}iflist_t;


#undef ARRAY_SIZE
#define ARRAY_SIZE(arr)	(sizeof(arr)/sizeof(arr[0]))

#define MAX(x, y)	((x)>(y)?(x):(y))
#define MIN(x, y)	((x)>(y)?(y):(x))

#undef PRINT
#ifdef GUI
# include <glib.h>
# define PRINT(...) g_print(__VA_ARGS__)
#else
# include <stdio.h>
# define PRINT(...) fprintf(stderr, __VA_ARGS__)
#endif

#ifdef DEBUG
# define _D(...) \
    do { \
        PRINT("%s:%d:", __FILE__, __LINE__); \
        PRINT(__VA_ARGS__); \
    } while(0)
#else
# define _D(...)    ((void)0)
#endif

#define _M(...)    PRINT(__VA_ARGS__);

/*
 * 获取程序所在的实际绝对路径的目录
 * exedir: 返回目录，加上\0一起长度是EXE_PATH_MAX，
 *         如果本上长度达到了EXE_PATH_MAX(不包括\0)，那么也会返回失败
 * @return: 0: 成功
 *         !0: 失败
 */
extern int getexedir(char *exedir);
/*
 * 比较两个mac是否相同
 * @return: 0: 不同
 *         !0: 相同
 */
extern int mac_equal(uchar const *mac1, uchar const *mac2);
/*
 * 获取所有网络接口
 * ifnames 实际获取的接口
 * cnt     两个作用，1：传入表示ifnames最多可以存储的接口个数
 *                   2：返回表示实际获取了的接口个数
 * 返回接口个数在cnt里
 * @return: >=0  成功，实际获取的接口个数
 *          -1 获取失败
 *          -2 cnt过小
 */
extern int getall_ifs(iflist_t *ifs, int *cnt);

#endif
