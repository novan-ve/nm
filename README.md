# nm
Reimplementation of the nm command in C.

```bash
$ cat << EOF > sample.c
#include <unistd.h>
int main() {
    write(1, "Hello world!\n", 13);
}
EOF
$
$ gcc -o sample sample.c
$ make && ./ft_nm sample
0000000000003df8 d _DYNAMIC
0000000000004000 d _GLOBAL_OFFSET_TABLE_
0000000000002000 R _IO_stdin_used
                 w _ITM_deregisterTMCloneTable
                 w _ITM_registerTMCloneTable
0000000000002154 r __FRAME_END__
0000000000002014 r __GNU_EH_FRAME_HDR
0000000000004030 D __TMC_END__
0000000000004030 B __bss_start
                 w __cxa_finalize@GLIBC_2.2.5
0000000000004020 D __data_start
00000000000010f0 t __do_global_dtors_aux
0000000000003df0 d __do_global_dtors_aux_fini_array_entry
0000000000004028 D __dso_handle
0000000000003de8 d __frame_dummy_init_array_entry
                 w __gmon_start__
0000000000003df0 d __init_array_end
0000000000003de8 d __init_array_start
00000000000011c0 T __libc_csu_fini
0000000000001160 T __libc_csu_init
                 U __libc_start_main@GLIBC_2.2.5
0000000000004030 D _edata
0000000000004038 B _end
00000000000011c4 T _fini
0000000000001000 t _init
0000000000001050 T _start
0000000000004030 b completed.0
0000000000004020 W data_start
0000000000001080 t deregister_tm_clones
0000000000001130 t frame_dummy
0000000000001135 T main
00000000000010b0 t register_tm_clones
                 U write@GLIBC_2.2.5
```
