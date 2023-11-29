# 内存错误检测技术
## valgrind
`valgrind --leak-check=yes ./a.out`
- null   不可检测 释放空指针
- ch14_4 可检测 忘记释放(内存泄漏)
- ch14_5 可检测 越界使用
- ch14_6 可检测 用完前释放
- ch14_7 可检测 错误调用free()
## AddressSanitizer
`gcc -g ch14_X.c -fsanitize=address`
- null   不可检测 释放空指针
- ch14_4 不可检测 忘记释放(内存泄漏)
- ch14_5 可检测 越界使用
- ch14_6 可检测 用完前释放
- ch14_7 可检测 错误调用free()