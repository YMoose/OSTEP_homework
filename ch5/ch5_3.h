typedef enum
{
  IPC_METHOD_PIPE,
  IPC_METHOD_FIFO,
  IPC_METHOD_SYS_V_MQ,
  IPC_METHOD_POSIX_MQ,
  IPC_METHOD_SIGNAL,
  IPC_METHOD_SYS_V,
  IPC_METHOD_POSIX,
  IPC_METHOD_MMAP,
  IPC_METHOD_SOCKET,
  IPC_METHOD_MAX,
} IPC_METHOD_T;


typedef void *prepare_func ();
typedef void wait_func (void *wait_ctx);
typedef void child_func (void *wait_ctx);

typedef struct _wait_method_t
{
  prepare_func *prepare_for_wait_func;
  wait_func *wait_child_func; 
  child_func *child_end_func;
} wait_method_t;

extern const wait_method_t method_list[];

static inline void *
prepare_for_wait (IPC_METHOD_T ipc_method)
{
  if (method_list[ipc_method].prepare_for_wait_func)
    return method_list[ipc_method].prepare_for_wait_func ();
}

static inline void
wait_child_process (IPC_METHOD_T ipc_method, void *wait_ctx)
{
  if (method_list[ipc_method].wait_child_func)
    method_list[ipc_method].wait_child_func (wait_ctx);
}

static inline void
child_end (IPC_METHOD_T ipc_method, void *wait_ctx)
{
  if (method_list[ipc_method].child_end_func)
    method_list[ipc_method].child_end_func (wait_ctx);
}
